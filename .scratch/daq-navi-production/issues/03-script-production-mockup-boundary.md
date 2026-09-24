# 03: Keep production and mockup acquisition separate in the script

**What to build:** A standalone run explicitly selects physical production acquisition or mockup acquisition. Synthetic samples never appear as physical production records, and a hardware fault ends the production run with an error.

**Blocked by:** 01: Test standalone production acquisition.

**Status:** resolved

- [x] Production acquisition requires the physical DAQ and never switches to mockup after a DAQ or driver failure.
- [x] Production acquisition writes to PostgreSQL/TimescaleDB; existing alternative destinations cannot silently replace the production destination.
- [x] Mockup acquisition starts only when explicitly selected and stores its samples separately from production telemetry.
- [x] Script tests distinguish each mode and verify the fault result and data destination.

## Answer

`test_production_runtime.py` checks the failed-hardware exit and the distinct
mockup table. The standalone production validator rejects mockup mode and
non-PostgreSQL destinations. An isolated three-second mockup run exited cleanly
and wrote 9,000 rows only to `daq_mockup_telemetry` in
`daq_navi_test_4a287a5e26`.
