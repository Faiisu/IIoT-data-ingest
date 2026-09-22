import sqlite3
import datetime
import os
import re
import time
import logging
import threading
import urllib.request
import urllib.parse
import urllib.error
from typing import Any, Optional, Dict

logger = logging.getLogger(__name__)

IDENTIFIER_REGEX = re.compile(r"^[a-zA-Z0-9_]+$")


def validate_identifier(name: str, identifier_type: str = "identifier") -> str:
    """
    Validates that the identifier contains only alphanumeric characters and underscores.
    Raises ValueError if invalid to prevent SQL injection.
    """
    if not isinstance(name, str) or not IDENTIFIER_REGEX.match(name):
        raise ValueError(
            f"Invalid {identifier_type}: '{name}'. Must match regex ^[a-zA-Z0-9_]+$"
        )
    return name


def quote_identifier(identifier: str, dialect: str = "sqlite") -> str:
    """
    Quotes an SQL identifier safely according to database dialect:
    Double quotes for SQLite / PostgreSQL, backticks for MySQL.
    """
    dialect_lower = dialect.lower()
    if dialect_lower == "mysql":
        escaped = identifier.replace("`", "``")
        return f"`{escaped}`"
    else:  # sqlite, postgres, postgresql, timescaledb
        escaped = identifier.replace('"', '""')
        return f'"{escaped}"'


def escape_tag(val: Any) -> str:
    """
    Escapes InfluxDB line protocol tag keys and values:
    Commas, equal signs, spaces, and backslashes must be escaped.
    """
    s = str(val)
    return s.replace("\\", "\\\\").replace(",", "\\,").replace("=", "\\=").replace(" ", "\\ ")


def escape_measurement(val: Any) -> str:
    """
    Escapes InfluxDB line protocol measurement names:
    Commas, spaces, and backslashes must be escaped.
    """
    s = str(val)
    return s.replace("\\", "\\\\").replace(",", "\\,").replace(" ", "\\ ")


def escape_string_field(val: Any) -> str:
    """
    Escapes InfluxDB line protocol string field values:
    Enclosed in double quotes with quotes and backslashes escaped.
    """
    s = str(val)
    escaped = s.replace("\\", "\\\\").replace('"', '\\"')
    return f'"{escaped}"'


class DatabaseHandler:
    validate_identifier = staticmethod(validate_identifier)
    quote_identifier = staticmethod(quote_identifier)
    escape_tag = staticmethod(escape_tag)
    escape_measurement = staticmethod(escape_measurement)
    escape_string_field = staticmethod(escape_string_field)

    def __init__(self, db_config: Dict[str, Any]):
        """
        Initializes Database Connection based on configuration.
        Supports SQLite out of the box, with extensible support for PostgreSQL/MySQL/InfluxDB.
        """
        self.config = db_config
        self.db_type = db_config.get("db_type", "sqlite").lower()
        self._lock = threading.RLock()

        # Fallback configuration: check both config.get("db_name") and config.get("sqlite_path")
        raw_db_name = db_config.get("db_name")
        raw_sqlite_path = db_config.get("sqlite_path")

        # Validate table_name against alphanumeric + underscore regex
        raw_table_name = db_config.get("table_name", "musashi_telemetry")
        self.table_name = validate_identifier(raw_table_name, "table_name")

        if self.db_type == "sqlite":
            self.sqlite_path = raw_sqlite_path or raw_db_name or "musashi_data.db"
            if raw_db_name:
                if raw_db_name.endswith(".db"):
                    stem = raw_db_name[:-3]
                    validate_identifier(stem, "db_name")
                    self.db_name = raw_db_name
                elif raw_db_name == ":memory:":
                    self.db_name = raw_db_name
                else:
                    self.db_name = validate_identifier(raw_db_name, "db_name")
            else:
                self.db_name = os.path.splitext(os.path.basename(self.sqlite_path))[0] or "musashi_data"
                validate_identifier(self.db_name, "db_name")
        elif self.db_type == "influxdb":
            self.db_name = raw_db_name or "musashi_telemetry"
            self.sqlite_path = raw_sqlite_path or "musashi_data.db"
        else:
            effective_db_name = raw_db_name or raw_sqlite_path or "musashi_data"
            self.db_name = validate_identifier(effective_db_name, "db_name")
            self.sqlite_path = raw_sqlite_path or f"{self.db_name}.db"

        self.description = db_config.get("description", "MUSASHI Dispenser Telemetry DB")
        
        self.conn = None
        self.connect()
        self.init_db()

    def _quote_identifier(self, identifier: str) -> str:
        """Helper to quote an identifier based on self.db_type."""
        return quote_identifier(identifier, self.db_type)

    def _safe_rollback(self):
        """Safely rolls back the active transaction inside try/except without raising."""
        with self._lock:
            if self.conn:
                try:
                    self.conn.rollback()
                except Exception as e:
                    logger.warning(f"Database rollback failed: {e}")

    def connect(self):
        """Establishes connection to the configured database. Auto-creates DB if missing."""
        with self._lock:
            # Cleanly close pre-existing connection first to avoid socket leaks on reconnect
            self.close()

            if self.db_type == "sqlite":
                target_path = self.sqlite_path or self.db_name
                self.conn = sqlite3.connect(target_path, check_same_thread=False)
                logger.info(f"Connected to SQLite database: {target_path}")
            elif self.db_type in ("postgres", "postgresql", "timescaledb"):
                try:
                    import psycopg2
                    from psycopg2 import sql
                    try:
                        self.conn = psycopg2.connect(
                            dbname=self.db_name,
                            user=self.config.get("user", "postgres"),
                            password=self.config.get("password", ""),
                            host=self.config.get("host", "localhost"),
                            port=self.config.get("port", 5432)
                        )
                    except psycopg2.OperationalError as oe:
                        logger.warning(f"Connecting to database '{self.db_name}' failed ({oe}). Attempting database creation...")
                        maint_conn = None
                        maint_cur = None
                        try:
                            maint_conn = psycopg2.connect(
                                dbname="postgres",
                                user=self.config.get("user", "postgres"),
                                password=self.config.get("password", ""),
                                host=self.config.get("host", "localhost"),
                                port=self.config.get("port", 5432)
                            )
                            maint_conn.autocommit = True
                            maint_cur = maint_conn.cursor()
                            maint_cur.execute("SELECT 1 FROM pg_database WHERE datname = %s", (self.db_name,))
                            if not maint_cur.fetchone():
                                maint_cur.execute(
                                    sql.SQL("CREATE DATABASE {}").format(sql.Identifier(self.db_name))
                                )
                                logger.info(f"Database '{self.db_name}' auto-created successfully.")
                        finally:
                            if maint_cur:
                                try:
                                    maint_cur.close()
                                except Exception:
                                    pass
                            if maint_conn:
                                try:
                                    maint_conn.close()
                                except Exception:
                                    pass

                        self.conn = psycopg2.connect(
                            dbname=self.db_name,
                            user=self.config.get("user", "postgres"),
                            password=self.config.get("password", ""),
                            host=self.config.get("host", "localhost"),
                            port=self.config.get("port", 5432)
                        )
                    logger.info(f"Connected to PostgreSQL database: {self.db_name} at {self.config.get('host')}")
                except ImportError:
                    raise ImportError("psycopg2 package is required for PostgreSQL connections.")
            elif self.db_type == "mysql":
                try:
                    import mysql.connector
                    try:
                        self.conn = mysql.connector.connect(
                            database=self.db_name,
                            user=self.config.get("user", "root"),
                            password=self.config.get("password", ""),
                            host=self.config.get("host", "localhost"),
                            port=self.config.get("port", 3306)
                        )
                    except Exception as me:
                        logger.warning(f"Connecting to MySQL database '{self.db_name}' failed ({me}). Attempting database creation...")
                        maint_conn = None
                        maint_cur = None
                        try:
                            maint_conn = mysql.connector.connect(
                                user=self.config.get("user", "root"),
                                password=self.config.get("password", ""),
                                host=self.config.get("host", "localhost"),
                                port=self.config.get("port", 3306)
                            )
                            maint_cur = maint_conn.cursor()
                            escaped_db = self.db_name.replace("`", "``")
                            maint_cur.execute(f"CREATE DATABASE IF NOT EXISTS `{escaped_db}`")
                            logger.info(f"MySQL database '{self.db_name}' auto-created successfully.")
                        finally:
                            if maint_cur:
                                try:
                                    maint_cur.close()
                                except Exception:
                                    pass
                            if maint_conn:
                                try:
                                    maint_conn.close()
                                except Exception:
                                    pass

                        self.conn = mysql.connector.connect(
                            database=self.db_name,
                            user=self.config.get("user", "root"),
                            password=self.config.get("password", ""),
                            host=self.config.get("host", "localhost"),
                            port=self.config.get("port", 3306)
                        )
                    logger.info(f"Connected to MySQL database: {self.db_name} at {self.config.get('host')}")
                except ImportError:
                    raise ImportError("mysql-connector-python package is required for MySQL connections.")
            elif self.db_type == "influxdb":
                logger.info("Configured InfluxDB destination.")
                self.conn = None
            else:
                raise ValueError(f"Unsupported database type: {self.db_type}")

    def init_db(self):
        """Creates the target table if it does not already exist."""
        if self.db_type == "influxdb":
            return

        with self._lock:
            table_quoted = self._quote_identifier(self.table_name)
            if self.db_type == "sqlite":
                query = f"""
                CREATE TABLE IF NOT EXISTS {table_quoted} (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    timestamp TEXT NOT NULL,
                    channel INTEGER NOT NULL,
                    pressure_kpa REAL NOT NULL,
                    pressure_raw INTEGER NOT NULL,
                    time_ms INTEGER NOT NULL,
                    time_sec REAL NOT NULL,
                    vacuum_kpa REAL NOT NULL,
                    mode_code INTEGER NOT NULL,
                    mode_name TEXT NOT NULL,
                    product_name TEXT NOT NULL,
                    raw_payload TEXT NOT NULL
                );
                """
            elif self.db_type in ("postgres", "postgresql", "timescaledb"):
                query = f"""
                CREATE TABLE IF NOT EXISTS {table_quoted} (
                    id SERIAL PRIMARY KEY,
                    timestamp TIMESTAMP WITH TIME ZONE NOT NULL,
                    channel INT NOT NULL,
                    pressure_kpa DOUBLE PRECISION NOT NULL,
                    pressure_raw INT NOT NULL,
                    time_ms INT NOT NULL,
                    time_sec DOUBLE PRECISION NOT NULL,
                    vacuum_kpa DOUBLE PRECISION NOT NULL,
                    mode_code INT NOT NULL,
                    mode_name VARCHAR(50) NOT NULL,
                    product_name VARCHAR(100) NOT NULL,
                    raw_payload TEXT NOT NULL
                );
                """
            elif self.db_type == "mysql":
                query = f"""
                CREATE TABLE IF NOT EXISTS {table_quoted} (
                    id INT AUTO_INCREMENT PRIMARY KEY,
                    timestamp DATETIME NOT NULL,
                    channel INT NOT NULL,
                    pressure_kpa DOUBLE NOT NULL,
                    pressure_raw INT NOT NULL,
                    time_ms INT NOT NULL,
                    time_sec DOUBLE NOT NULL,
                    vacuum_kpa DOUBLE NOT NULL,
                    mode_code INT NOT NULL,
                    mode_name VARCHAR(50) NOT NULL,
                    product_name VARCHAR(100) NOT NULL,
                    raw_payload TEXT NOT NULL
                );
                """
            else:
                raise ValueError(f"Unsupported database type: {self.db_type}")

            cursor = None
            try:
                cursor = self.conn.cursor()
                cursor.execute(query)
                self.conn.commit()
                logger.info(f"Database table '{self.table_name}' verified/initialized.")
            except Exception as e:
                self._safe_rollback()
                logger.error(f"Failed to initialize database table '{self.table_name}': {e}")
                raise
            finally:
                if cursor:
                    try:
                        cursor.close()
                    except Exception:
                        pass

    def _execute_insert(self, query: str, params: tuple):
        """Executes INSERT query safely and returns inserted row ID."""
        cursor = None
        try:
            cursor = self.conn.cursor()
            cursor.execute(query, params)
            if self.db_type in ("postgres", "postgresql", "timescaledb"):
                row = cursor.fetchone()
                last_row_id = row[0] if row else None
            else:
                last_row_id = getattr(cursor, "lastrowid", None)
            self.conn.commit()
            return last_row_id
        except Exception:
            self._safe_rollback()
            raise
        finally:
            if cursor:
                try:
                    cursor.close()
                except Exception:
                    pass

    def insert_telemetry(self, data: Dict[str, Any]):
        """
        Inserts a single telemetry record into the database.
        
        :param data: Dictionary containing telemetry parameters from MusashiDispenser
        :return: Inserted record ID or boolean success
        """
        if self.db_type == "influxdb":
            return self._insert_influx(data)

        with self._lock:
            now_dt = datetime.datetime.now(datetime.timezone.utc)
            if self.db_type == "sqlite":
                db_timestamp = now_dt.isoformat(" ")
            elif self.db_type == "mysql":
                # Convert timezone-aware datetime to naive UTC datetime for MySQL DATETIME columns
                db_timestamp = now_dt.astimezone(datetime.timezone.utc).replace(tzinfo=None)
            else:
                db_timestamp = now_dt

            table_quoted = self._quote_identifier(self.table_name)
            params = (
                db_timestamp,
                data.get("channel", 1),
                data.get("pressure_kpa", 0.0),
                data.get("pressure_raw", 0),
                data.get("time_ms", 0),
                data.get("time_sec", 0.0),
                data.get("vacuum_kpa", 0.0),
                data.get("mode_code", 0),
                data.get("mode_name", ""),
                data.get("product_name", ""),
                data.get("raw_payload", "")
            )

            if self.db_type == "sqlite":
                query = f"""
                INSERT INTO {table_quoted} (
                    timestamp, channel, pressure_kpa, pressure_raw,
                    time_ms, time_sec, vacuum_kpa, mode_code,
                    mode_name, product_name, raw_payload
                ) VALUES ({', '.join(['?'] * 11)});
                """
            elif self.db_type in ("postgres", "postgresql", "timescaledb"):
                query = f"""
                INSERT INTO {table_quoted} (
                    timestamp, channel, pressure_kpa, pressure_raw,
                    time_ms, time_sec, vacuum_kpa, mode_code,
                    mode_name, product_name, raw_payload
                ) VALUES ({', '.join(['%s'] * 11)}) RETURNING id;
                """
            elif self.db_type == "mysql":
                query = f"""
                INSERT INTO {table_quoted} (
                    timestamp, channel, pressure_kpa, pressure_raw,
                    time_ms, time_sec, vacuum_kpa, mode_code,
                    mode_name, product_name, raw_payload
                ) VALUES ({', '.join(['%s'] * 11)});
                """
            else:
                raise ValueError(f"Unsupported database type: {self.db_type}")

            try:
                last_row_id = self._execute_insert(query, params)
                logger.info(f"Inserted record into '{self.table_name}' at {now_dt}")
                return last_row_id
            except Exception as e:
                logger.warning(f"Telemetry insert failed ({e}). Auto-creating database/table and retrying...")
                try:
                    self.connect()
                    self.init_db()
                    last_row_id = self._execute_insert(query, params)
                    logger.info(f"Inserted record into '{self.table_name}' after auto-creation at {now_dt}")
                    return last_row_id
                except Exception as retry_err:
                    self._safe_rollback()
                    logger.error(f"Retry insert failed: {retry_err}")
                    raise

    def _insert_influx(self, data: Dict[str, Any]) -> bool:
        """Inserts telemetry data into InfluxDB using RFC-compliant line protocol."""
        with self._lock:
            url = self.config.get("influx_url", "http://localhost:8086").rstrip('/')
            token = self.config.get("influx_token", "")
            org = self.config.get("influx_org", "mddp")
            bucket = self.config.get("influx_bucket", "musashi_telemetry")
            measurement = self.config.get("influx_measurement", self.table_name)

            # Change precision to milliseconds to prevent points within the same second from overwriting
            write_url = (
                f"{url}/api/v2/write?org={urllib.parse.quote(org)}"
                f"&bucket={urllib.parse.quote(bucket)}&precision=ms"
            )

            tags = [f"channel={escape_tag(data.get('channel', 1))}"]
            mode_name = str(data.get("mode_name", "")).strip()
            if mode_name:
                tags.append(f"mode_name={escape_tag(mode_name)}")
            product_name = str(data.get("product_name", "")).strip()
            if product_name:
                tags.append(f"product_name={escape_tag(product_name)}")

            fields = [
                f"pressure_kpa={float(data.get('pressure_kpa', 0.0))}",
                f"pressure_raw={int(data.get('pressure_raw', 0))}i",
                f"time_ms={int(data.get('time_ms', 0))}i",
                f"time_sec={float(data.get('time_sec', 0.0))}",
                f"vacuum_kpa={float(data.get('vacuum_kpa', 0.0))}",
                f"mode_code={int(data.get('mode_code', 0))}i",
                f"raw_payload={escape_string_field(data.get('raw_payload', ''))}"
            ]

            ts_ms = int(time.time() * 1000)
            measurement_escaped = escape_measurement(measurement)
            line_protocol = f"{measurement_escaped},{','.join(tags)} {','.join(fields)} {ts_ms}"

            headers = {
                "Content-Type": "text/plain; charset=utf-8",
                "Accept": "application/json"
            }
            if token:
                headers["Authorization"] = f"Token {token}"

            req = urllib.request.Request(
                write_url, data=line_protocol.encode('utf-8'), headers=headers, method="POST"
            )
            try:
                with urllib.request.urlopen(req, timeout=3.0) as resp:
                    if resp.status not in (200, 204):
                        logger.error(f"InfluxDB HTTP status {resp.status}")
                        return False
                return True
            except urllib.error.HTTPError as he:
                error_body = ""
                try:
                    error_body = he.read().decode('utf-8', errors='replace')
                except Exception:
                    pass
                logger.error(f"InfluxDB HTTPError {he.code}: {he.reason}. Response body: {error_body}")
                return False
            except urllib.error.URLError as ue:
                logger.error(f"InfluxDB URLError: {ue.reason}")
                return False
            except Exception as e:
                logger.error(f"Failed to insert into InfluxDB: {e}")
                return False

    def close(self):
        """Closes the database connection cleanly."""
        with self._lock:
            if self.conn:
                try:
                    self.conn.close()
                except Exception as e:
                    logger.warning(f"Error closing database connection: {e}")
                finally:
                    self.conn = None
                    logger.info("Database connection closed.")
