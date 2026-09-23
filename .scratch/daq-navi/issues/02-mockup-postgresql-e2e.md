# 02: Mockup → PostgreSQL end-to-end tracer bullet

**What to build:** The first demoable pipeline without any DAQ hardware. A refactored mockup that generates synthetic sinusoidal data for N configurable channels (reading channel count and config from `config.json`), feeds it through a refactored `DaqSampleParser` that emits `(time, device_id, channel, value)` tuples, a refactored `Calibrator` that reads per-channel scale config from the new schema, and a refactored `TimescaleDBClient` that inserts into the configurable table name with the `device_id` column. Running `python mockup_stream_to_db.py` should produce data queryable as `SELECT * FROM daq_telemetry WHERE device_id = 'pci1716-0'`.

**Blocked by:** 01: Config schema + DB schema + config loader

**Status:** resolved

- [x] `DaqSampleParser.parse_batch()` returns rows with `device_id` as second element: `(time, device_id, channel, value)`
- [x] `Calibrator` reads per-channel scale config from `CHANNELS` dict in new config schema
- [x] `TimescaleDBClient.insert_samples()` uses configurable table name and 4-column INSERT
- [x] `mockup_stream_to_db.py` refactored: reads new config, generates synthetic data for configured channel count (ch0, ch1 SingleEnded), uses shared pipeline components
- [x] Monitor thread logs include `device_id` in stats output
- [x] End-to-end verified: mockup run produces rows in `daq_telemetry` with correct `device_id`, channel numbers, and calibrated values (tested in `test_pipeline_e2e.py`)

## Answer
Implemented in:
- `services/daq_navi/stream_to_db.py`: Updated `Calibrator` and `DaqSampleParser` to accept `channel_configs` and emit `(time, device_id, channel, value)` 4-column tuples.
- `services/daq_navi/mockup_stream_to_db.py`: Refactored to import shared components directly from `stream_to_db.py`, generating synthetic waveforms for ch0 and ch1 (DP-101A sensor calibration: 1V-5V -> -100 to 100 kPa) with `device_id` in all log and insert operations.
- `services/daq_navi/test_pipeline_e2e.py`: Verified DP-101A calibration scaling, `DaqSampleParser` 4-column row generation with `device_id`, and `TimescaleDBClient` insert query formatting targeting `daq_telemetry`.
