# 02: Apply validated channel configuration in the standalone script

**What to build:** A standalone production run uses the latest supported configuration to acquire only enabled physical channels at the configured per-channel rate. Operators can configure channels 0–3 for the initial production run, including sensor name, unit, and calibration.

**Blocked by:** 01: Test standalone production acquisition.

**Status:** resolved

- [x] Incomplete or invalid metadata for an enabled channel prevents a production run and identifies the affected setting.
- [x] Enabled and disabled states, channel order, rate, and calibration values used by acquisition match the saved configuration; valid zero values are preserved.
- [x] Standalone tests cover four enabled channels at 1,000–2,000 samples per second per channel and reject invalid configurations.

## Answer

`validate_production_config()` rejects incomplete enabled channels and unknown
DAQ enum values. Unit checks cover disabled channels and zero calibration
values. Isolated physical reports `c2febdf5bd.json` (1 kHz) and
`ea31673402.json` (2 kHz) contain four channels at the requested rates.
