# 09: Apply production telemetry retention from script configuration

**What to build:** The standalone production path creates and reconciles the active TimescaleDB raw telemetry retention policy from its saved configuration, defaulting to 30 days.

**Blocked by:** 04: Persist complete production DAQ samples.

**Status:** resolved

- [x] A fresh production database receives a 30-day raw telemetry retention policy by default.
- [x] Changing the configured period updates the existing policy rather than leaving an older period active.
- [x] Isolated database tests verify the effective policy and do not delete legacy or production test data outside their own scope.

## Answer

`test_production_timescale.py` created a unique table in
`daq_navi_test_4a287a5e26`, read back a 30-day policy, changed it to 45 days,
and read back the updated policy. The test drops only its unique table.
