# 01: Test standalone production acquisition

**What to build:** An executable test harness that exercises the standalone acquisition script from DAQ input through persisted telemetry, using controlled DAQ data and isolated database data. It establishes a repeatable baseline before script changes and remains the regression check for later tickets.

**Blocked by:** None (can start immediately).

**Status:** resolved

- [x] Tests can run without changing production telemetry or requiring the web application.
- [x] The harness can drive channel data, database failures, process restarts, and a full local buffer, and reports which expectation failed.
- [x] A documented command runs the script tests and reports a clear pass or fail result; existing defects may fail the baseline at this stage.

## Answer

`services/daq_navi/tests/README.md` gives repeatable commands and the isolated
database guard. `test_production_acquisition.py`, `test_production_timescale.py`,
and the physical qualification runners cover the fault and restart cases.
