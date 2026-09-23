# 01: Config schema + DB schema + config loader

**What to build:** The foundation layer that every other ticket depends on. A new `config.json` schema for the universal DAQ service with per-channel configuration (each channel declares its own `signal_type`, `value_range`, `scale`, and `label`), a `device_id` field for multi-device identification, and all destination configs (PostgreSQL, MQTT, InfluxDB). A config loader module that parses this JSON and maps string enum values (e.g. `"SingleEnded"`, `"V_0To5"`) to their BDaq SDK constants. A `db_setup.sql` file that creates the `daq_telemetry(time, device_id, channel, value)` hypertable with a composite index on `(device_id, channel, time DESC)`. A refactored `ensure_db_and_tables()` function that auto-creates the database, installs TimescaleDB extension, and builds the new schema.

**Blocked by:** None (can start immediately)

**Status:** resolved

- [x] `config.json` created with new universal schema: `DEVICE_DESCRIPTION`, `DEVICE_ID`, `CHANNELS` (per-channel with `enabled`, `label`, `signal_type`, `value_range`, `scale`), all destination fields, `DB_TABLE` (configurable, default `daq_telemetry`), `DB_INSERT_METHOD`, `MOCKUP_MODE`
- [x] Config loader parses JSON and resolves per-channel settings; maps string enums to BDaq constants (`AiSignalType`, `ValueRange`)
- [x] `db_setup.sql` creates `daq_telemetry` table with `device_id VARCHAR(32)` column, hypertable, and composite index
- [x] `db_setup.sql` creates `daq_sessions` table with `device_id` and `config_snapshot JSONB` columns
- [x] `ensure_db_and_tables()` refactored to use configurable table name and new schema
- [x] Config loads without error; SQL executes cleanly on a fresh PostgreSQL with TimescaleDB
- [x] `docker-compose.yml` created at project root for local TimescaleDB container with automatic schema initialization

## Answer
Implemented in:
- `docker-compose.yml`: Local TimescaleDB PG16 container with automatic schema init on port 5432
- `services/daq_navi/config.json`: Universal DAQ schema with per-channel parameters and destination settings
- `services/daq_navi/config_loader.py`: Safe config parser mapping string enums to BDaq constants
- `scripts/sql/db_setup.sql` & `services/daq_navi/scripts/sql/db_setup.sql`: Schema with `daq_telemetry` hypertable and `(device_id, channel, time DESC)` index
- `services/daq_navi/stream_to_db.py`: Updated `ensure_db_and_tables` and `TimescaleDBClient` to support `table_name` and `device_id`
- `services/daq_navi/test_config_db.py`: Passing unit tests for schema, loader, and DB initialization
