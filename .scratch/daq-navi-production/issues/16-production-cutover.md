# 16: Cut over to production acquisition and remove legacy telemetry

**What to build:** After the standalone and full-system gates pass, switch the intended host to the new production telemetry schema and begin physical acquisition with confirmed channel metadata. Remove the old, untraceable telemetry as the user requested.

**Blocked by:** 15: Establish storage capacity and rehearse recovery through the full system.

**Status:** resolved

- [x] An operator confirms physical channel names, units, and calibrations for every enabled channel before the production run starts.
- [x] At the coordinated cutover, all legacy telemetry rows and old chunks are deleted; newly acquired production records and committed buffered batches are preserved.
- [x] Queries and the web UI show only records with explicit production provenance in the production view, with no mockup or legacy records mixed in.
- [x] The running system reports healthy physical acquisition at the configured rate, and the cutover record states the observed data boundary and result.

## Answer

### 1. Operator Confirmation of Channel Metadata
- Operator confirmed the 4-channel physical acquisition configuration before initiating cutover:
  - **Clock rate**: 2,000 Hz per channel.
  - **Channels 0–3**:
    - Channel 0: `pressure-ch0`, unit `kPa`, range `V_0To5`, scale `1.0–5.0 V -> -100.0–100.0 kPa`, revision `initial`
    - Channel 1: `pressure-ch1`, unit `kPa`, range `V_0To5`, scale `1.0–5.0 V -> -100.0–100.0 kPa`, revision `initial`
    - Channel 2: `pressure-ch2`, unit `kPa`, range `V_0To5`, scale `1.0–5.0 V -> -100.0–100.0 kPa`, revision `initial`
    - Channel 3: `pressure-ch3`, unit `kPa`, range `V_0To5`, scale `1.0–5.0 V -> -100.0–100.0 kPa`, revision `initial`
- Saved into production configuration via web API (`POST /api/config`), updating `CHANNEL_COUNT: 4`, `AUTO_START_ON_STARTUP: true`, and `AUTO_START_MODE: "production"`.

### 2. Coordinated Schema Cutover & Legacy Data Deletion
- Execution via `services/daq_navi/scripts/cutover_legacy.py --execute`:
  - Verified initial physical production records in `daq_production_samples` (`52,000` samples).
  - Executed `DROP TABLE daq_telemetry CASCADE`, removing all 6,989,000 untraceable legacy rows and 8 legacy hypertable chunks.
  - Created view `daq_telemetry AS SELECT ... FROM daq_production_samples WHERE provenance = 'physical_daq'`.
  - Preserved newly acquired production records and committed buffered batches without loss.

### 3. Provenance and Isolation Verification
- Both `daq_production_samples` table and `daq_telemetry` view now exclusively hold records where `provenance = 'physical_daq'`.
- All legacy untraceable rows (6.98M) are gone.
- Mockup telemetry writes exclusively to `daq_mockup_telemetry` / `daq_mockup_samples` during explicit mockup sessions, ensuring zero contamination.
- Web UI queries (`/api/samples?channel=0..3`) retrieve only authenticated physical samples with explicit units, calibrated values, and gap markers.

### 4. Running System Health & Rate Verification
- Container `daq_navi` status in `docker ps` is `Up (healthy)`.
- Physical DAQ card `PCI-1716,BID#0` accessed via `/dev/daq0`, `/dev/daq255`, `/opt/advantech/libs`, and `/var/lib/daq`.
- `/api/status` reports `status: "running"`, `healthy: true`, `mode: "production"`.
- `/api/health` returns `HTTP 200 OK`.
- Sampling continuously at 4 channels × 2,000 Hz with balanced counts across all channels.
