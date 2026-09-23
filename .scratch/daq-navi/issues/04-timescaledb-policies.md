# 04: TimescaleDB policies + continuous aggregates

**What to build:** Production-grade TimescaleDB configuration for high-throughput DAQ data (8,000 rows/sec at 4ch × 2kHz). Compression policy that auto-compresses chunks older than 1 hour, segmented by `device_id` and `channel`, reducing storage ~90%. Configurable retention policy (default 90 days) that auto-drops expired chunks. Two continuous aggregates for downsampling: `daq_telemetry_1s` (1-second buckets with avg/min/max/count) and `daq_telemetry_1m` (1-minute buckets). These aggregates serve both the plotter UI (future) and external sync software.

**Blocked by:** 02: Mockup → PostgreSQL end-to-end tracer bullet

**Status:** ready-for-agent

- [ ] Compression policy added: `compress_segmentby = 'device_id, channel'`, `compress_orderby = 'time DESC'`, auto-compress after configurable interval (default 1 hour)
- [ ] Retention policy added: auto-drop chunks older than configurable days (default 90), reading from `DB_RETENTION_DAYS` in config
- [ ] `daq_telemetry_1s` continuous aggregate created: `time_bucket('1 second')` with `AVG`, `MIN`, `MAX`, `COUNT` grouped by `device_id, channel`
- [ ] `daq_telemetry_1m` continuous aggregate created: `time_bucket('1 minute')` with same aggregations
- [ ] Continuous aggregate refresh policies added with appropriate offsets
- [ ] Policies are idempotent: re-running `db_setup.sql` doesn't error on existing policies
- [ ] Verified with mockup data: chunks compress, aggregates populate, retention drops old chunks
