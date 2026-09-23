# 09: Mitigate hardware crystal clock drift and NTP step jumps

**What to solve:** The DAQ hardware crystal oscillator (accuracy ~±50 ppm) and the host CPU/OS system clock run independently and drift apart over time (~4.32 seconds of drift over 24 hours at 50 ppm). The current periodic recalibration resets the anchor timestamp every 24 hours (`self.anchor_time_ns = batch_wall_ts_ns` and `self.samples_since_anchor = 0`), which introduces an instantaneous step discontinuity (a backward time jump or a forward gap). Furthermore, using `time.time_ns()` (wall clock) makes the pipeline vulnerable to host NTP step synchronizations and leap seconds, risking out-of-order chunk insertion into TimescaleDB.

**Blocked by:** 03: Universal DAQ hardware reader

**Status:** needs-triage

**Severity:** Medium (Temporal Continuity & Out-of-Order Ingestion)

### Root Cause Analysis
In `services/daq_navi/stream_to_db.py`:
1. `DaqSampleParser` re-anchors to `batch_wall_ts_ns` every 24 hours:
   ```python
   current_time_ns = time.time_ns()
   if self.anchor_time_ns is None or (current_time_ns - self.anchor_time_ns) >= self.recalibrate_interval_ns:
       self.anchor_time_ns = batch_wall_ts_ns
       self.samples_since_anchor = 0
   ```
2. If the physical DAQ crystal runs slightly faster than the OS clock, the new `batch_wall_ts_ns` will be *earlier* than the previous sample's calculated timestamp (`last_emitted_ts`), producing a negative time jump. TimescaleDB hypertables handle out-of-order data, but with a performance penalty during chunk decompression.
3. If an NTP daemon adjusts the OS clock backwards (step sync), `current_time_ns - self.anchor_time_ns` can become negative or trigger premature re-anchoring.

### Acceptance Criteria / Action Items
- [ ] Replace `time.time_ns()` in the duration check with `time.monotonic_ns()` to immunize interval calculation against NTP step changes.
- [ ] Add monotonicity guard: ensure `anchor_time_ns` never resets to a value that would produce a timestamp prior to the latest emitted timestamp (`max(batch_wall_ts_ns, last_emitted_ts_ns + dt_ns)`).
- [ ] Evaluate implementing a smooth clock slew (gradually distributing drift across N batches using a Software Phase-Locked Loop: PLL or clock smearing) instead of an abrupt 24-hour step reset.
- [ ] Add unit tests verifying that sudden OS clock step-backs or crystal drift do not generate out-of-order timestamps.

### Trade-offs & Decision Points for Maintainer
- **Pros:** Eliminates timestamp discontinuities and protects against TimescaleDB compression chunk invalidation caused by backward time jumps.
- **Cons:** Slew-rate clock adjustment (PLL) adds algorithmic complexity compared to a simple periodic re-anchor.
