import unittest
from unittest.mock import MagicMock, patch, call
import sys
import os
import sqlite3
import datetime
import threading
import urllib.error

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from database_handler import (
    DatabaseHandler,
    validate_identifier,
    quote_identifier,
    escape_tag,
    escape_measurement,
    escape_string_field,
)


class TestDatabaseHandlerSecurityAndReliability(unittest.TestCase):
    def setUp(self):
        self.test_db_path = "test_security_handler.db"
        if os.path.exists(self.test_db_path):
            os.remove(self.test_db_path)

    def tearDown(self):
        if os.path.exists(self.test_db_path):
            try:
                os.remove(self.test_db_path)
            except Exception:
                pass

    # -------------------------------------------------------------
    # 1. SQL Injection Prevention & Identifier Sanitization
    # -------------------------------------------------------------
    def test_identifier_validation(self):
        """Test validation of alphanumeric and underscore identifiers."""
        self.assertEqual(validate_identifier("valid_table_123"), "valid_table_123")
        self.assertEqual(validate_identifier("TelemetryData"), "TelemetryData")

        invalid_identifiers = [
            "table; DROP TABLE users;--",
            "table name with space",
            "table-with-dash",
            "table' OR '1'='1",
            "table\"--",
            "table`--",
            "table/name",
            "",
        ]
        for invalid in invalid_identifiers:
            with self.assertRaises(ValueError):
                validate_identifier(invalid)

    def test_database_handler_rejects_malicious_table_name(self):
        """Test DatabaseHandler raises ValueError for SQL injection in table_name."""
        malicious_config = {
            "db_type": "sqlite",
            "db_name": self.test_db_path,
            "table_name": "telemetry; DROP TABLE users;--",
        }
        with self.assertRaises(ValueError):
            DatabaseHandler(malicious_config)

    def test_database_handler_rejects_malicious_db_name(self):
        """Test DatabaseHandler raises ValueError for SQL injection in db_name."""
        malicious_postgres = {
            "db_type": "postgresql",
            "db_name": "db; DROP DATABASE test;--",
            "table_name": "telemetry",
        }
        with self.assertRaises(ValueError):
            DatabaseHandler(malicious_postgres)

        malicious_mysql = {
            "db_type": "mysql",
            "db_name": "db` DROP DATABASE test;--",
            "table_name": "telemetry",
        }
        with self.assertRaises(ValueError):
            DatabaseHandler(malicious_mysql)

    def test_quote_identifier_dialects(self):
        """Test dialect-specific identifier quoting."""
        self.assertEqual(quote_identifier("my_table", "sqlite"), '"my_table"')
        self.assertEqual(quote_identifier("my_table", "postgresql"), '"my_table"')
        self.assertEqual(quote_identifier("my_table", "postgres"), '"my_table"')
        self.assertEqual(quote_identifier("my_table", "mysql"), "`my_table`")

    @patch("psycopg2.connect")
    def test_postgres_create_database_uses_psycopg2_sql(self, mock_pg_connect):
        """Test PostgreSQL CREATE DATABASE uses psycopg2.sql.Identifier and sql.SQL."""
        from psycopg2 import OperationalError, sql

        # Primary connection fails initially, maint connection succeeds
        mock_maint_conn = MagicMock()
        mock_maint_cur = MagicMock()
        mock_maint_conn.cursor.return_value = mock_maint_cur
        mock_maint_cur.fetchone.return_value = None  # DB does not exist

        mock_main_conn = MagicMock()
        mock_pg_connect.side_effect = [
            OperationalError("database 'secure_db' does not exist"),
            mock_maint_conn,
            mock_main_conn,
        ]

        handler = DatabaseHandler({
            "db_type": "postgresql",
            "db_name": "secure_db",
            "table_name": "secure_telemetry",
        })

        # Verify CREATE DATABASE was composed with sql.SQL and sql.Identifier
        execute_calls = mock_maint_cur.execute.call_args_list
        create_db_call = execute_calls[1][0][0]
        self.assertIsInstance(create_db_call, sql.Composed)
        # Check that maint_conn was closed in finally
        mock_maint_conn.close.assert_called_once()
        handler.close()

    def test_mysql_create_database_escaping_and_finally(self):
        """Test MySQL CREATE DATABASE escapes backticks and closes maint_conn in finally."""
        mock_mysql_module = MagicMock()
        mock_main_conn = MagicMock()
        mock_maint_conn = MagicMock()
        mock_maint_cur = MagicMock()
        mock_maint_conn.cursor.return_value = mock_maint_cur

        # First connection fails, maint connection auto-creates DB, second connection succeeds
        mock_mysql_module.connector.connect.side_effect = [
            Exception("Database unknown"),
            mock_maint_conn,
            mock_main_conn,
        ]

        with patch.dict(sys.modules, {"mysql": mock_mysql_module, "mysql.connector": mock_mysql_module.connector}):
            handler = DatabaseHandler({
                "db_type": "mysql",
                "db_name": "mddp_mysql_db",
                "table_name": "mddp_table",
            })
            mock_maint_cur.execute.assert_called_with("CREATE DATABASE IF NOT EXISTS `mddp_mysql_db`")
            mock_maint_conn.close.assert_called_once()
            handler.close()

    # -------------------------------------------------------------
    # 2. Connection & Socket Leak Prevention on Reconnect
    # -------------------------------------------------------------
    def test_reconnect_closes_existing_connection(self):
        """Test that connect() calls close() before opening a new connection."""
        handler = DatabaseHandler({
            "db_type": "sqlite",
            "db_name": self.test_db_path,
            "table_name": "telemetry",
        })
        old_conn = handler.conn
        self.assertIsNotNone(old_conn)

        # Calling connect again should close the old connection
        with patch.object(handler, "close", wraps=handler.close) as mock_close:
            handler.connect()
            mock_close.assert_called_once()
            self.assertIsNotNone(handler.conn)
            self.assertNotEqual(id(old_conn), id(handler.conn))
        handler.close()

    # -------------------------------------------------------------
    # 3. Transaction Rollback & InFailedSqlTransaction Fix
    # -------------------------------------------------------------
    def test_safe_rollback_called_on_insert_error(self):
        """Test _safe_rollback() is invoked on execute errors."""
        handler = DatabaseHandler({
            "db_type": "sqlite",
            "db_name": self.test_db_path,
            "table_name": "telemetry",
        })

        mock_conn = MagicMock()
        mock_cur = MagicMock()
        mock_cur.execute.side_effect = sqlite3.OperationalError("Simulated write failure")
        mock_conn.cursor.return_value = mock_cur
        handler.conn = mock_conn

        with patch.object(handler, "_safe_rollback", wraps=handler._safe_rollback) as mock_rollback:
            with self.assertRaises(sqlite3.OperationalError):
                handler._execute_insert("INSERT INTO query", ())
            self.assertTrue(mock_rollback.called)

        # Also test that retry failure in insert_telemetry triggers _safe_rollback
        with patch.object(handler, "connect", side_effect=sqlite3.OperationalError("Reconnect failed")):
            with patch.object(handler, "_safe_rollback", wraps=handler._safe_rollback) as mock_rollback_retry:
                with self.assertRaises(sqlite3.OperationalError):
                    handler.insert_telemetry({"pressure_kpa": 10.0})
                self.assertTrue(mock_rollback_retry.called)

    def test_safe_rollback_handles_conn_rollback_exceptions(self):
        """Test _safe_rollback does not raise if conn.rollback() raises."""
        handler = DatabaseHandler({
            "db_type": "sqlite",
            "db_name": self.test_db_path,
            "table_name": "telemetry",
        })
        mock_conn = MagicMock()
        mock_conn.rollback.side_effect = Exception("Broken connection")
        handler.conn = mock_conn
        # Should not raise exception
        handler._safe_rollback()

    # -------------------------------------------------------------
    # 4. Cursor Lifecycle Management
    # -------------------------------------------------------------
    def test_cursor_closed_in_finally_on_success_and_error(self):
        """Test that cursor.close() is always called across executions."""
        handler = DatabaseHandler({
            "db_type": "sqlite",
            "db_name": self.test_db_path,
            "table_name": "telemetry",
        })

        # Test on successful insert with mock connection & cursor
        mock_conn = MagicMock()
        mock_cur = MagicMock()
        mock_cur.lastrowid = 1
        mock_conn.cursor.return_value = mock_cur
        handler.conn = mock_conn

        handler._execute_insert("INSERT INTO query", ())
        mock_cur.close.assert_called_once()

        # Test on failed insert
        mock_failing_conn = MagicMock()
        mock_failing_cur = MagicMock()
        mock_failing_cur.execute.side_effect = sqlite3.DatabaseError("DB locked")
        mock_failing_conn.cursor.return_value = mock_failing_cur
        handler.conn = mock_failing_conn

        with self.assertRaises(sqlite3.DatabaseError):
            handler._execute_insert("INSERT INTO query", ())
        mock_failing_cur.close.assert_called_once()

    # -------------------------------------------------------------
    # 5. InfluxDB Line Protocol RFC Compliance
    # -------------------------------------------------------------
    def test_influxdb_escaping_helpers(self):
        """Test escaping of tags, measurements, and string fields."""
        # Tag escaping: commas, equal signs, spaces, and backslashes
        self.assertEqual(escape_tag(r"tag,with=spaces and\slash"), r"tag\,with\=spaces\ and\\slash")

        # Measurement escaping: commas, spaces, and backslashes
        self.assertEqual(escape_measurement(r"meas,name with\slash"), r"meas\,name\ with\\slash")

        # String field escaping: double quotes with quotes and backslashes escaped
        self.assertEqual(
            escape_string_field(r'Raw "Payload" with \backslash'),
            r'"Raw \"Payload\" with \\backslash"'
        )

    @patch("urllib.request.urlopen")
    def test_insert_influx_formatting_and_precision(self, mock_urlopen):
        """Test InfluxDB insert includes millisecond precision, escaped tags, and fields."""
        mock_resp = MagicMock()
        mock_resp.status = 204
        mock_urlopen.return_value.__enter__.return_value = mock_resp

        handler = DatabaseHandler({
            "db_type": "influxdb",
            "influx_url": "http://influx.internal:8086",
            "influx_token": "secret_token",
            "influx_bucket": "telemetry_bucket",
            "influx_measurement": "dispenser,reading 1",
            "table_name": "dispenser_table",
        })

        sample_data = {
            "channel": 1,
            "pressure_kpa": 15.5,
            "pressure_raw": 155,
            "time_ms": 120,
            "time_sec": 0.12,
            "vacuum_kpa": 0.3,
            "mode_code": 1,
            "mode_name": "Sigma, Mode=1",
            "product_name": "PROD 001, Batch=A",
            "raw_payload": '21DA01P0155"test"\\raw',
        }

        success = handler.insert_telemetry(sample_data)
        self.assertTrue(success)

        # Check the URL contains precision=ms
        req = mock_urlopen.call_args[0][0]
        self.assertIn("precision=ms", req.full_url)
        self.assertEqual(req.headers["Authorization"], "Token secret_token")

        body = req.data.decode("utf-8")
        # Check measurement escaped
        self.assertTrue(body.startswith(r"dispenser\,reading\ 1,"))
        # Check tags escaped
        self.assertIn(r"mode_name=Sigma\,\ Mode\=1", body)
        self.assertIn(r"product_name=PROD\ 001\,\ Batch\=A", body)
        # Check raw_payload escaped as string field
        self.assertIn(r'raw_payload="21DA01P0155\"test\"\\raw"', body)
        # Check timestamp is 13 digits (millisecond epoch)
        parts = body.strip().split()
        ts = parts[-1]
        self.assertEqual(len(ts), 13)

    @patch("urllib.request.urlopen")
    def test_insert_influx_handles_http_errors_gracefully(self, mock_urlopen):
        """Test InfluxDB HTTP error response is caught and logged, returning False."""
        mock_http_err = urllib.error.HTTPError(
            url="http://influx:8086",
            code=400,
            msg="Bad Request",
            hdrs={},
            fp=MagicMock(read=lambda: b'{"error":"invalid line protocol"}')
        )
        mock_urlopen.side_effect = mock_http_err

        handler = DatabaseHandler({
            "db_type": "influxdb",
            "table_name": "telemetry",
        })

        result = handler.insert_telemetry({"pressure_kpa": 1.0})
        self.assertFalse(result)

    # -------------------------------------------------------------
    # 6. Driver Dialect Compatibility
    # -------------------------------------------------------------
    @patch("psycopg2.connect")
    def test_postgres_insert_returns_id_via_returning(self, mock_pg_connect):
        """Test PostgreSQL uses RETURNING id and cursor.fetchone()[0]."""
        mock_conn = MagicMock()
        mock_cur = MagicMock()
        mock_conn.cursor.return_value = mock_cur
        mock_cur.fetchone.return_value = (42,)
        mock_pg_connect.return_value = mock_conn

        handler = DatabaseHandler({
            "db_type": "postgresql",
            "db_name": "test_db",
            "table_name": "telemetry",
        })

        row_id = handler.insert_telemetry({"pressure_kpa": 20.0})
        self.assertEqual(row_id, 42)

        # Verify query contains RETURNING id
        insert_call = mock_cur.execute.call_args[0][0]
        self.assertIn("RETURNING id", insert_call)
        handler.close()

    def test_mysql_datetime_is_naive_utc(self):
        """Test MySQL inserts naive UTC datetime without tzinfo."""
        mock_mysql_module = MagicMock()
        mock_conn = MagicMock()
        mock_cur = MagicMock()
        mock_conn.cursor.return_value = mock_cur
        mock_cur.lastrowid = 101
        mock_mysql_module.connector.connect.return_value = mock_conn

        with patch.dict(sys.modules, {"mysql": mock_mysql_module, "mysql.connector": mock_mysql_module.connector}):
            handler = DatabaseHandler({
                "db_type": "mysql",
                "db_name": "test_db",
                "table_name": "telemetry",
            })

            row_id = handler.insert_telemetry({"pressure_kpa": 30.0})
            self.assertEqual(row_id, 101)

            # Check executed params for datetime
            params = mock_cur.execute.call_args[0][1]
            db_dt = params[0]
            self.assertIsInstance(db_dt, datetime.datetime)
            self.assertIsNone(db_dt.tzinfo, "MySQL datetime parameter must be naive UTC")
            handler.close()

    def test_fallback_configuration_db_name_and_sqlite_path(self):
        """Test fallback between config.get('db_name') and config.get('sqlite_path')."""
        # Case A: sqlite_path specified, db_name omitted
        handler_a = DatabaseHandler({
            "db_type": "sqlite",
            "sqlite_path": self.test_db_path,
            "table_name": "telemetry",
        })
        self.assertEqual(handler_a.sqlite_path, self.test_db_path)
        self.assertEqual(handler_a.db_name, "test_security_handler")
        handler_a.close()

        # Case B: db_name specified as .db filename, sqlite_path omitted
        handler_b = DatabaseHandler({
            "db_type": "sqlite",
            "db_name": self.test_db_path,
            "table_name": "telemetry",
        })
        self.assertEqual(handler_b.sqlite_path, self.test_db_path)
        self.assertEqual(handler_b.db_name, self.test_db_path)
        handler_b.close()

    # -------------------------------------------------------------
    # 7. Concurrency & Thread Safety
    # -------------------------------------------------------------
    def test_concurrent_inserts_thread_safety(self):
        """Test multiple threads safely inserting into SQLite using RLock."""
        handler = DatabaseHandler({
            "db_type": "sqlite",
            "db_name": self.test_db_path,
            "table_name": "telemetry",
        })

        self.assertIsInstance(handler._lock, type(threading.RLock()))

        errors = []

        def worker(channel_idx):
            try:
                for i in range(10):
                    row_id = handler.insert_telemetry({
                        "channel": channel_idx,
                        "pressure_kpa": float(channel_idx * 10 + i),
                        "pressure_raw": 100,
                        "time_ms": 50,
                        "time_sec": 0.05,
                        "vacuum_kpa": 0.1,
                        "mode_code": 0,
                        "mode_name": "Timed",
                        "product_name": f"P_{channel_idx}",
                        "raw_payload": "DATA",
                    })
                    if row_id is None:
                        errors.append(f"Channel {channel_idx} got None row_id")
            except Exception as e:
                errors.append(f"Worker {channel_idx} failed: {e}")

        threads = [threading.Thread(target=worker, args=(ch,)) for ch in range(1, 6)]
        for t in threads:
            t.start()
        for t in threads:
            t.join()

        handler.close()

        self.assertEqual(len(errors), 0, f"Thread errors encountered: {errors}")

        # Verify all 50 records were written to SQLite
        conn = sqlite3.connect(self.test_db_path)
        cur = conn.cursor()
        cur.execute("SELECT COUNT(*) FROM telemetry")
        count = cur.fetchone()[0]
        conn.close()
        self.assertEqual(count, 50)


if __name__ == "__main__":
    unittest.main()
