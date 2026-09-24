# 05: Preserve DAQ sample time and record acquisition gaps

**What to build:** A standalone production run assigns time according to each sample's actual position in the DAQ stream and records an acquisition gap when physical samples could not be collected.

**Blocked by:** 04: Persist complete production DAQ samples.

**Status:** resolved

- [x] Per-channel sample order and timestamps remain stable when batches are delayed, retried, or missing; a missing batch does not shift later samples in time.
- [x] Hardware clock drift and host wall-clock adjustments do not create backward timestamps; physical DAQ samples stay within one second of this PC's clock during qualification.
- [x] Detectable gaps have a start, end, and cause when known, and are never filled with zero or mockup measurements.
- [x] Script tests cover interleaved four-channel data, delayed reads, missing batches, clock drift, wall-clock adjustments, and timestamp reconstruction; physical timing is checked against this PC at the script qualification gate.

## Comments

Synthetic tests cover drift and a backward wall-clock step without backward
sample timestamps. This PC is the local database server and time authority;
the earlier cross-machine comparison requirement was removed by the user.
Replay now uses SQLite commit order, so a backward host clock adjustment cannot
move later committed batches ahead of earlier ones. Batch rows, latest sample
position, and closing gap boundary commit in one SQLite transaction.

## Answer

`test_production_acquisition.py` covers four-channel time reconstruction,
delayed reads, drift, a backward host-clock adjustment, and gap closure.
The isolated PCI-1716 reports `ea31673402.json` (2 kHz, 30 seconds) and
`c2febdf5bd.json` (1 kHz, 10 seconds) show all four channels at the expected
counts with no unexpected gaps. First and last samples differ from this PC's
run boundaries by at most 0.089 seconds.
