# 10: Qualify the standalone acquisition script before web development

**What to build:** Run the complete script test suite and a controlled physical-DAQ/TimescaleDB exercise, then record evidence that the standalone production path meets the operating contract before any web development ticket starts.

**Blocked by:** 08: Stop the standalone script safely on faults and buffer exhaustion; 09: Apply production telemetry retention from script configuration.

**Status:** resolved

## Comments

Isolated physical DAQ runs at both 1 kHz and 2 kHz passed with four channels.
Database outage, orderly restart, forced process crash, replay, and no duplicate
sample identities passed in isolated TimescaleDB tables. This PC is the local
database server and time authority, so the user removed the cross-machine
comparison requirement. Physical timing is qualified against this PC's clock.
The isolated PCI-1716 report `ea31673402.json` records the kernel,
PostgreSQL and TimescaleDB versions, four 60,000-sample channels at 2 kHz,
and 120 reliable DAQ timing reads. The current script suite passes 86 tests with
seven database-dependent legacy tests skipped by their isolation guard.
Crash/replay report `e69420fcf5-replay.json` compares every committed outage
sample against its TimescaleDB row: zero missing identities, zero value
mismatches, and at most 720 ns timestamp rounding at PostgreSQL precision.

- [x] The physical DAQ acquires four channels at 2,000 samples per second per channel without unreported loss; stored counts, values, and order match the captured stream.
- [x] Physical DAQ timestamps stay within one second of this PC's clock during qualification; drift and wall-clock adjustment scenarios are covered without changing the host clock during the check.
- [x] Controlled checks cover database outage and replay, process restart, uncertain write response, full buffer, DAQ error, and graceful stop; no replayed sample is duplicated.
- [x] Results use isolated test data, record hardware and database conditions, and clearly state pass or fail. Web development begins only after all criteria pass.

## Answer

The standalone script gate passed against the local database host clock.
`ea31673402.json` and `c2febdf5bd.json` show exact four-channel counts at
2 kHz and 1 kHz, respectively, with host boundary offsets below 0.09 seconds.
`6e0e737f82-replay.json` and `e69420fcf5-replay.json` cover orderly and
forced-crash replay; the latter compares every committed sample with its
TimescaleDB row. The isolated database integration tests pass. Tickets 11–16
may now start in dependency order.
