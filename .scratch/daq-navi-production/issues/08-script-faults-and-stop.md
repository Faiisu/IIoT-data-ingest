# 08: Stop the standalone script safely on faults and buffer exhaustion

**What to build:** The standalone script reports a DAQ or storage fault, stops acquiring when it cannot preserve more samples, and completes a requested stop without hanging or discarding committed batches.

**Blocked by:** 07: Buffer committed DAQ batches and replay them after an outage.

**Status:** resolved

- [x] Full local storage or an unwritable buffer stops production acquisition and records a detectable acquisition gap and cause.
- [x] A DAQ read error produces a failure result rather than a successful exit or a switch to mockup acquisition.
- [x] A requested stop drains what it can, leaves untransmitted committed batches available for replay, and terminates within a defined bound.
- [x] Script tests exercise full buffer, DAQ failure, writer failure, and requested stop.

## Answer

`test_production_acquisition.py` covers full and unwritable spool, DAQ read
failure, database writer failure, and stop with pending committed data. The
writer has a ten-second drain deadline; the main thread waits up to fifteen
seconds and leaves any remaining committed batches in the spool for replay.
