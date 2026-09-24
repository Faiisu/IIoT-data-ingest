# 13: Show production health and acquisition gaps on the web

**What to build:** Operators can tell whether physical acquisition, buffering, and database delivery are healthy, and can see acquisition gaps alongside correctly labeled raw and calibrated measurements.

**Blocked by:** 12: Control acquisition and apply saved settings from the web UI.

**Status:** resolved

- [x] The web UI shows running, stopped, faulted, buffer usage, pending replay, and the cause of a known fault or gap.
- [x] Graphs distinguish raw voltage from calibrated measurements, show the associated unit and calibration revision, and display gaps as missing data.
- [x] Healthcheck fails when production acquisition is expected but stopped or unhealthy; it agrees with the UI state.
- [x] Web/API tests cover healthy acquisition, database outage with buffering, stopped acquisition, and a recorded gap.

## Answer

### Implementation Summary
1. **Production Health & Runtime Telemetry Reporting (`/api/status` & Web UI):**
   - The `/api/status` endpoint computes comprehensive health and telemetry status, including running state, mode, buffer usage (`spool_bytes`), pending replay (`pending_batches`), recorded acquisition gaps, and explicit fault/writer error causes (`last_fault` and `last_writer_error`).
   - In `app.js` (`showProductionStatus` and `updateUIState`), the UI renders current state (`RUNNING`, `STOPPED`, `FAULTED`, `BUFFERING`), buffer usage in MiB, pending batches, and detailed breakdowns of gaps (timestamp range and cause) or active fault/writer errors.
   - Header indicators dynamically reflect live status including online (green), mock (purple), buffering (amber), or faulted/offline (red).

2. **Graph Visualization & Gap Representation (`/api/samples` & Web UI Canvas):**
   - `/api/samples` queries 1-second aggregated points from TimescaleDB and returns both `raw_voltage` and `calibrated_value`, tagged with the sensor's physical `unit` and `calibration_revision`, alongside recent gaps read from the persistent spool (`production-spool.sqlite3`).
   - In `app.js` (`refreshProductionGraphs` and `drawProductionGraph`), separate canvas charts render raw voltage and calibrated measurements with their respective engineering units and calibration revisions labeled.
   - Gap segments are visually highlighted with red background shaded zones, and line traces are broken across gap intervals (`ctx.moveTo`) so gaps are distinctly displayed as missing data.

3. **Production Healthcheck Consistency (`/api/health`):**
   - `/api/health` returns HTTP 200 when acquisition is healthy (or clean stopped when not configured for auto-start).
   - It returns HTTP 503 (`healthy: false`) when acquisition is expected to run but stopped, when an active fault occurs (`last_fault`), when database outage causes buffering (`last_writer_error`), or when telemetry heartbeats become stale (> 10s).
   - The healthcheck status payload and decision rules strictly agree with the status displayed in the web UI.

4. **Automated Testing Suite (`tests.test_production_web`):**
   - Enhanced `services/daq_navi/tests/test_production_web.py` with tests covering:
     - `test_healthy_acquisition_state_in_status_and_health`: Validates healthy acquisition status and 200 healthcheck.
     - `test_database_outage_with_buffering_reports_unhealthy_and_buffer_stats`: Validates buffering status, spool tracking, writer error reporting, and 503 health response.
     - `test_stopped_acquisition_healthy_when_not_expected`: Validates 200 response when stopped intentionally.
     - `test_stopped_acquisition_unhealthy_when_expected`: Validates 503 response when expected to be running but stopped.
     - `test_recorded_acquisition_gap_exposure_in_status_and_samples`: Validates SQLite gap record exposure in both `/api/status` and `/api/samples`.
     - `test_samples_query_associates_unit_and_calibration_revision`: Validates query parsing and association of units and calibration revisions.
     - `test_samples_channel_validation_and_db_failure`: Validates parameter bounds checking and graceful 503 on database unavailability.
   - All 33 tests in `tests.test_production_web` pass cleanly inside Docker (`Ran 33 tests ... OK`).
