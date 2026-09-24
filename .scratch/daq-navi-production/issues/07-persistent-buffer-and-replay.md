# 07: Buffer committed DAQ batches and replay them after an outage

**What to build:** While the host is running, the standalone acquisition script commits captured batches promptly to persistent local storage and continues acquiring during a database outage. It replays committed batches after the database or process returns.

**Blocked by:** 05: Preserve DAQ sample time and record acquisition gaps; 06: Write each production DAQ sample at most once.

**Status:** resolved

- [x] A database outage does not silently discard captured batches while local buffer capacity is available.
- [x] Committed batches survive process restart and replay in order with original identities and timestamps, producing no duplicate database records.
- [x] The buffer is mounted on persistent container storage and exposes usage and pending-batch status for later capacity and web work.
- [x] Tests document the accepted boundary: a crash after a DAQ read but before local commit may lose that in-flight batch.

## Answer

The SQLite spool uses WAL and full synchronous commits. Compose mounts
`daq_spool` persistently, and `status.json` exposes pending count and bytes.
Physical reports `6e0e737f82-replay.json` and `e69420fcf5-replay.json` show
complete replay after an outage and a killed application process, respectively.
The measured outage payload extrapolates to at most 6.8 GB per 24 hours at
four channels × 2 kHz; configured spool allowance is 128 GiB. Long-duration
storage and reserve sizing remain ticket 15.
