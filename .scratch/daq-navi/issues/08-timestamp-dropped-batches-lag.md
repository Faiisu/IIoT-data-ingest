# 08: Fix timestamp lag caused by dropped batches in bounded queue

**What to solve:** When `data_queue` becomes full (e.g. during a transient database reconnection or write latency spike), `daq_reader_thread` drops batches to avoid unbounded memory growth. However, `DaqSampleParser.samples_since_anchor` only increments by the samples that actually reach the parser in `db_writer_thread`. Dropped batches are not accounted for in the forward timestamp calculation (`sample_ts = anchor_time_ns + (samples_since_anchor + s) * dt_ns`), causing all subsequent sample timestamps to permanently lag behind real-time by the duration of the dropped batches until the next periodic recalibration (up to 24 hours later).

**Blocked by:** 03: Universal DAQ hardware reader

**Status:** needs-triage

**Severity:** High (Data Integrity / Real-Time Accuracy)

### Root Cause Analysis
In `services/daq_navi/stream_to_db.py`:
1. `daq_reader_thread` attempts `data_queue.put_nowait(...)`. If full, it increments `stats["dropped"]` and discards the batch.
2. In `DaqSampleParser.parse_batch(...)`:
   ```python
   sample_ts_ns = self.anchor_time_ns + (self.samples_since_anchor + s) * self.dt_ns
   ...
   self.samples_since_anchor += samples_per_channel
   ```
3. Because the parser is unaware of how many samples were dropped upstream, `self.samples_since_anchor` falls behind the actual elapsed hardware samples. For example, if 10 batches of 500 samples are dropped (5,000 samples @ 2 kHz = 2.5 seconds), the recorded telemetry timestamps will be delayed by 2.5 seconds relative to real-world events.

### Acceptance Criteria / Action Items
- [ ] Reader thread tracks a cumulative hardware sample counter (`cumulative_samples_polled`) or sequence number and includes it in each enqueued tuple: `(batch_wall_ts_ns, raw_data, returned_count, hw_sample_index)`.
- [ ] `DaqSampleParser` detects sequence gaps or jumps in `hw_sample_index`.
- [ ] If a gap is detected, `DaqSampleParser` automatically advances `samples_since_anchor` by the missing sample count to maintain real-time alignment with the hardware timeline.
- [ ] Unit tests in `services/daq_navi/test_pipeline_e2e.py` simulating dropped queue items confirm timestamps remain synchronized with wall clock.

### Trade-offs & Decision Points for Maintainer
- **Pros:** Prevents cumulative time lag; preserves accurate real-world timestamps for time-correlated analysis with external systems (e.g. Musashi dispensers).
- **Cons:** Creates a time gap in the hypertable for the dropped period, which continuous aggregates and downsampling queries must handle (TimescaleDB time buckets handle gaps naturally).
