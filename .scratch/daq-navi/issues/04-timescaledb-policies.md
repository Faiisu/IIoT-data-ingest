# 04: TimescaleDB policies + continuous aggregates

**What to build:** Production-grade TimescaleDB configuration for high-throughput DAQ data (8,000 rows/sec at 4ch × 2kHz). Compression policy that auto-compresses chunks older than 1 hour, segmented by `device_id` and `channel`, reducing storage ~90%. Configurable retention policy (default 90 days) that auto-drops expired chunks. Two continuous aggregates for downsampling: `daq_telemetry_1s` (1-second buckets with avg/min/max/count) and `daq_telemetry_1m` (1-minute buckets). These aggregates serve both the plotter UI (future) and external sync software.

**Blocked by:** 02: Mockup → PostgreSQL end-to-end tracer bullet

**Status:** resolved

- [x] Compression policy added: `compress_segmentby = 'device_id, channel'`, `compress_orderby = 'time DESC'`, auto-compress after configurable interval (default 1 hour)
- [x] Retention policy added: auto-drop chunks older than configurable days (default 90), reading from `DB_RETENTION_DAYS` in config
- [x] `daq_telemetry_1s` continuous aggregate created: `time_bucket('1 second')` with `AVG`, `MIN`, `MAX`, `COUNT` grouped by `device_id, channel`
- [x] `daq_telemetry_1m` continuous aggregate created: `time_bucket('1 minute')` with same aggregations
- [x] Continuous aggregate refresh policies added with appropriate offsets
- [x] Policies are idempotent: re-running `db_setup.sql` doesn't error on existing policies
- [x] Verified with mockup data: chunks compress, aggregates populate, retention drops old chunks

## Answer
Implemented in:
- `scripts/sql/db_setup.sql` & `services/daq_navi/scripts/sql/db_setup.sql`:
  - Added hypertable compression configuration (`compress_segmentby = 'device_id, channel'`, `compress_orderby = 'time DESC'`).
  - Added compression policy with 1 hour interval (`if_not_exists => TRUE`).
  - Added retention policy with default 90 days interval (`if_not_exists => TRUE`).
  - Added continuous aggregates `daq_telemetry_1s` (1-second time buckets with `avg`, `min`, `max`, `count`) and `daq_telemetry_1m` (1-minute time buckets).
  - Added continuous aggregate refresh policies with appropriate start/end offsets and schedules.
- `services/daq_navi/config.json` & `services/daq_navi/config_loader.py`:
  - Added configurable `DB_RETENTION_DAYS` (default 90 days).
- `services/daq_navi/stream_to_db.py`:
  - Refactored `ensure_db_and_tables` to auto-configure compression policy, retention policy (reading `DB_RETENTION_DAYS`), continuous aggregates `daq_telemetry_1s` and `daq_telemetry_1m`, and refresh policies.
  - Updated `TimescaleDBClient` to accept `retention_days` and forward to `ensure_db_and_tables`.
- `services/daq_navi/mockup_stream_to_db.py`:
  - Integrated `DB_RETENTION_DAYS` into DB client and setup invocations.
- `services/daq_navi/test_config_db.py` & `services/daq_navi/test_timescaledb_policies.py`:
  - Unit and integration tests verifying schema, configuration loading, policy registration, idempotent re-runs, continuous aggregate population, chunk compression (>90% reduction verified), and chunk retention dropping.
