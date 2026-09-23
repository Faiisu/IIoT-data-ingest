# 10: Address integer division truncation and sub-microsecond timestamp limits

**What to solve:** Two mathematical and data-type precision edge cases exist in the current timestamp pipeline:
1. `dt_ns` is computed via integer division: `int(1_000_000_000 / clock_rate)`. When `clock_rate` does not evenly divide $10^9$ (e.g. 3,000 Hz, where $\Delta t = 333,333.333...$ ns), the truncation discards $0.333$ ns per sample. Over 24 hours ($259,200,000$ samples @ 3 kHz), this accumulates to an ~86.4 ms drift before recalibration.
2. Python's `datetime.datetime` object natively supports up to microsecond ($10^{-6}$ s) resolution. If hardware sampling rate exceeds 1 MHz (such as high-speed ultrasound or transient vibration capture cards), adjacent samples within the same channel will collide with identical microsecond timestamps.

**Blocked by:** 03: Universal DAQ hardware reader

**Status:** needs-triage

**Severity:** Low (Minor Drift on Non-Standard Rates / Future High-Frequency Scaling)

### Root Cause Analysis
In `services/daq_navi/stream_to_db.py`:
1. `self.dt_ns = int(1_000_000_000 / clock_rate)` drops fractional nanoseconds.
2. In `sample_ts = datetime.fromtimestamp(sample_ts_ns / 1_000_000_000, tz=timezone.utc)`:
   The floating point seconds representation is truncated/rounded to 6 decimal places by Python's `datetime`, effectively throwing away the lower 3 digits of nanosecond precision.

### Acceptance Criteria / Action Items
- [ ] For integer division: compute timestamps using floating-point scaling or maintain a remainder accumulator:
  `sample_ts_ns = self.anchor_time_ns + int((self.samples_since_anchor + s) * (1_000_000_000.0 / self.clock_rate))`.
  This guarantees zero cumulative rounding error across any arbitrary clock rate.
- [ ] Document the valid clock rate operating envelope (up to 500 kHz) for the microsecond `datetime` column.
- [ ] If sub-microsecond sampling (>1 MHz) is needed in future iterations, evaluate storing timestamps as `BIGINT` nanoseconds (supported natively by InfluxDB and TimescaleDB integer hypertables).
- [ ] Add unit tests verifying timestamp accuracy for clock rates like 3,000 Hz and 7,000 Hz over 1,000,000 simulated samples.

### Trade-offs & Decision Points for Maintainer
- **Pros:** Eliminates mathematical drift for odd sampling frequencies; future-proofs the pipeline for higher sampling rates.
- **Cons:** For the current production PCI-1716 card running at 2,000 Hz (which divides $10^9$ cleanly into 500,000 ns), this issue does not manifest in current deployments.
