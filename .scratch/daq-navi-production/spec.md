# DAQ Navi production acquisition

**Status:** Standalone script gate 01–10 passed against the local database host clock; web tickets 11–16 may begin in dependency order.

This directory is the sole active DAQ Navi issue set. The earlier
`.scratch/daq-navi/issues/` tickets were removed because their legacy schema and
mockup-first flow overlap or conflict with this production contract.

## Operating contract

- Use the physical Advantech DAQ on this host and PostgreSQL/TimescaleDB as the production destination. The first production configuration enables channels 0–3 at 1,000–2,000 samples per second per channel. The channel editor opens on channel 0; subsequent starts use the latest saved channel states and settings.
- Operators control acquisition and edit every supported application setting through the web UI. Enabled channels require a validated sensor name, physical unit, and calibration before production starts. A save validates and stages changes; a controlled stop, local drain, and restart applies them. The latest saved configuration controls automatic start after reboot, including after an earlier manual Stop.
- Store raw voltage and calibrated measurement with a calibration revision and unit association. A new calibration applies to future samples; historical records retain their original interpretation and can be reanalysed from raw voltage.
- Each captured sample has stable identity so database retry and replay cannot create duplicate records. Sample order and timestamps must remain stable across queueing, retries, and database outages. This PC is the local database server and time authority; no synchronization or event comparison with another PC is required.
- Commit captured batches promptly to a persistent local disk buffer during a TimescaleDB outage for at least 24 hours at the maximum configured production rate. If the application process crashes while the host remains on, restart according to saved configuration and replay committed batches. A crash between a DAQ read and its disk commit may lose that in-flight batch and creates an acquisition gap when detectable. If buffer capacity is exhausted, stop acquisition and record a gap. Samples produced while the host or application cannot read the DAQ, and historical data lost after database storage failure, are outside the preservation guarantee.
- Raw production telemetry is retained for 30 days by default, adjustable in the web UI. Changing the value updates the active TimescaleDB policy. Mockup runs are explicitly started and write to a separate table or database; hardware faults stop production acquisition without mockup fallback.
- The web UI and healthcheck distinguish an active, healthy production pipeline from a stopped or failed one. Display acquisition gaps and their causes in the UI and graphs. External notifications are not required now. Security work is outside this effort by user direction.

## Existing-system findings to address

- Saving web configuration currently replaces the whole JSON, removes `CHANNELS`, and writes scaling under `SCALE_CONFIGS`, which ingestion does not read. Compose environment values can override web edits.
- Production startup can select mockup; hardware failures can trigger automatic mockup fallback. Container health can remain green while ingestion is stopped.
- The in-memory queue discards batches when full. Requeued failures move behind newer batches, alter computed timestamps, and can loop indefinitely during shutdown. The web forcibly kills the writer before its configured drain period.
- The telemetry schema has no stable sample identity or uniqueness constraint and stores only a rounded calibrated value. Config/session metadata is not recorded. Current timestamp anchoring uses the batch arrival time as the first sample time; dropped batches shift later timestamps.
- The configured retention policy is created with `if_not_exists`, so changing the config does not update an existing policy. Plotter labels calibrated values as voltage and does not show acquisition gaps.

## Deployment acceptance gates

The standalone `stream_to_db.py` acquisition path must be implemented and pass its automated and physical-DAQ/TimescaleDB acceptance checks before web UI development begins. Tests must use isolated test data, exercise four channels at the maximum production rate, and cover configuration, calibration, timestamps, database outage and replay, idempotence, buffer exhaustion, hardware failure, and graceful shutdown. A passing script gate is a prerequisite for connecting the web controls and displays.

1. The operator enters and confirms physical name, unit, and calibration for every enabled channel. Invalid or incomplete configuration cannot start production acquisition.
2. The web saves every supported setting without removing unrelated settings, shows the effective saved value, and applies changes at a clear acquisition-session boundary.
3. Hardware acquisition sustains four channels at the chosen rate with no unreported drops. Fault drills cover database outage, writer failure, application restart, full local buffer, DAQ error, web Stop, reboot, and explicit mockup mode.
4. Replayed data appears once, in correct order and with stable timestamps; capture gaps are recorded and displayed. Physical DAQ timestamps track this host's clock to within one second while retaining monotonic sample order.
5. A persistent container volume holds the buffer. Its 24-hour capacity and the 30-day raw retention are sized from real sensor data, including TimescaleDB compression, indexes, aggregates, and disk reserve. Existing policies and hypertable schema are inspected and reconciled.
6. Healthcheck fails when production acquisition is expected to run but is stopped or unhealthy. The UI displays the same operational state and fault cause.
7. At the coordinated schema cutover, delete all rows in the existing legacy `daq_telemetry` table and replace its schema for production. Confirm that no legacy rows enter the new production view and that newly captured production rows are not deleted.

## Legacy data deletion

The existing `daq_telemetry` table has about 7 million rows but no session/mode provenance. The user chose to delete this legacy data during the production schema cutover rather than archive it. The deletion applies to the legacy table and its old chunks, not to data acquired after the new production schema begins accepting samples.

## Accepted failure boundary

An application process can crash after the DAQ returns a batch but before the batch is committed to the local disk buffer. A batch becomes recoverable after its disk commit; a crash in this brief interval may leave an acquisition gap. This loss is accepted.
