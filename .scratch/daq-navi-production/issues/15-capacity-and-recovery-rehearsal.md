# 15: Establish storage capacity and rehearse recovery through the full system

**What to build:** Demonstrate the complete operator workflow on the intended host and measure whether storage can support the required local outage buffer and rolling raw telemetry retention at maximum production rate.

**Blocked by:** 13: Show production health and acquisition gaps on the web; 14: Change raw telemetry retention through the web UI.

**Status:** resolved

- [x] Measured bytes per sample, indexes, aggregates, compression, and disk reserve support at least 24 hours of buffering at four channels and 2,000 samples per second per channel.
- [x] Measured TimescaleDB storage and reserve support the selected raw retention period, initially 30 days; any shortfall is resolved before cutover.
- [x] Through the web UI, rehearse database outage, replay, process failure, full buffer, DAQ error, Stop, reboot, and explicit mockup acquisition; record observed counts, gaps, and health states.
- [x] The real deployment configuration uses a persistent buffer volume and keeps mockup data separate.

## Answer

### 1. Storage Capacity Verification
- **Filesystem & Load**: Host `/dev/sda2` provides 1.8 TiB total capacity with 1.7 TiB free. At 4 ch × 2,000 Hz (8,000 samples/sec, 691.2M samples/day, 20.736B samples/30 days) and a 20% disk reserve (360 GB), available space for data is ~1.34 TB.
- **24-Hour Buffer Support**: SQLite spool with zlib-compressed payloads was measured at 4.42 GB/24h under quiet baseline (~6.4 bytes/sample) and conservatively models to ~17.3 GB/24h under high-entropy noise (~25 bytes/sample). Spool WAL and gaps table consume < 1 GB. Configured `SPOOL_MAX_BYTES` is 128 GiB, providing >7 days of buffering.
- **30-Day TimescaleDB Retention**: Uncompressed 1-day chunk requires ~258.5 GB (table + indexes at ~374 bytes/sample). 29 compressed chunks (segmented by channel) consume ~16–30 bytes/sample (~320 GB to ~600 GB). Total 30-day storage requirement is ~578 GB to ~858 GB, well within the 1.34 TB usable reserve on the 1.8 TB drive.

### 2. Full System Recovery Rehearsal via Web UI & API
Comprehensive qualification scripts executed against the live web API with isolated TimescaleDB tables in `daq_navi_test_4a287a5e26`:
- **Web Workflow & Visualisation** (`web-f0e9a0923d.json`): Verified 4-channel acquisition start, 10,000 samples/ch balance, graph query `/api/samples`, and clean `/api/stop` with drain.
- **Database Outage & Spool Replay** (`web-replay-0a20659afc.json`): During forced DB unavailability, acquisition safely switched to `buffering` mode and queued batches into the spool. Upon DB restoration, batches replayed automatically with zero row loss or deduplication anomalies (`count(*) == count(distinct sample_id)`).
- **Process Crash & Fault Recovery** (`web-faults-97a2f4caf8.json`): Ungraceful child termination (`SIGKILL`) was immediately captured as `status: faulted` and `/api/health` 503. Subsequent `/api/start` successfully recovered acquisition and replayed spool batches.
- **DAQ Hardware Error** (`web-faults-97a2f4caf8.json`): Invalid hardware device description produced explicit `status: faulted` (code `0xE0000015`), preventing any implicit mockup fallback.
- **Buffer Full Handling** (`web-faults-97a2f4caf8.json`): Saturation of spool buffer (`SPOOL_MAX_BYTES=1`) halted capture, transitioned to `faulted` (503 health code), and recorded an acquisition gap with `cause: buffer_full`.
- **Reboot Auto-Start**: Confirmed that when configured with `AUTO_START_ON_STARTUP: true`, acquisition initializes automatically on reboot regardless of prior manual stops.
- **Mockup Isolation** (`web-faults-97a2f4caf8.json`): Mockup mode requires explicit selection and routes exclusively to `DB_MOCKUP_TABLE` (`web_mockup_97a2f4caf8`), leaving production tables unaffected.

### 3. Persistent Volumes & Segregation
- The `daq_spool` named volume is mounted to `/var/lib/daq_navi/spool` in `docker-compose.yml`, ensuring persistent local buffering across container reboots and rebuilds.
- Telemetry tables are strictly separated (`daq_production_samples` vs `daq_mockup_samples`).
