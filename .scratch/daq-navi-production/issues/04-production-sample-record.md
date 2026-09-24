# 04: Persist complete production DAQ samples

**What to build:** A standalone production run writes DAQ samples with the information needed to interpret and identify each measurement. New production records remain separate from the legacy telemetry until the final cutover.

**Blocked by:** 02: Apply validated channel configuration in the standalone script; 03: Keep production and mockup acquisition separate in the script.

**Status:** resolved

- [x] Each production sample retains raw voltage, calibrated measurement, physical unit, calibration revision, channel, device, acquisition session, provenance, and stable sample identity.
- [x] Changing a channel calibration affects future samples only; earlier records retain their original calibrated value and revision.
- [x] Standalone script and isolated database tests can read back the complete record without modifying legacy telemetry.
- [x] The new sample representation does not silently break explicitly selected non-production MQTT or InfluxDB outputs.

## Answer

`test_production_timescale.py` reads back every required field from a unique
TimescaleDB test table. `test_production_acquisition.py` checks that a new
calibration revision changes only later samples. The existing MQTT and
InfluxDB destination tests pass in the full script suite.
