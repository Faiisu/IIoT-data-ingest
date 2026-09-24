# 06: Write each production DAQ sample at most once

**What to build:** The standalone database writer can safely retry a production batch after a timeout or uncertain response while preserving the identity, time, and order of its samples.

**Blocked by:** 04: Persist complete production DAQ samples.

**Status:** resolved

- [x] Repeating a write for the same production samples leaves exactly one record per sample in TimescaleDB.
- [x] A retry does not regenerate identities or timestamps and does not move failed samples behind newer samples in the logical stream.
- [x] Isolated database tests cover a successful write, a failed write, and a commit whose response is lost.

## Answer

The spool retains the original batch on any uncertain response and always
retries its oldest batch first. `test_production_timescale.py` writes and then
simulates a lost commit reply; the isolated database still contains one row
per original sample after replay.
The spool orders replay by SQLite row insertion order, which stays stable when
wall time moves backward.
