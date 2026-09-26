# DAQ Config Center

The DAQ Navi Flask service serves the Config Center at port `8081`. Its REST API is available under `/api/` on the same port. The page template is `templates/index.html`; the JavaScript and CSS are in `static/config_center/`.

## Configuration workflow

1. Set the start channel and number of AI channels to read. The sensor table follows that span. The current production service accepts AI0–AI15. Enabled inputs outside a changed span remain visible so they can be disabled.
2. Edit Enabled, sensor label, engineering unit, signal type, and input range directly in the sensor table. On PCI-1716, differential pairs start on an even channel and reserve the following odd channel.
3. Turn calibration on or off in each sensor row. Select **Edit** on a row to set its linear conversion. Production acquisition requires calibration on every enabled sensor.
4. Configure and test the destination, then save. PostgreSQL can use host and credentials or a custom connection string. Saving while acquisition runs stops and restarts that run after confirmation.

Configuration errors appear in the header of the section that contains them, with details directly below that header. The page scrolls to the first affected section after an unsuccessful save.

The **Pending data** card shows the current pending batch count and observed increase, decrease, and net rates in batches per minute. The page samples `/api/status` every five seconds and calculates these rates over the most recent 60 seconds (or the time observed so far). The separate increase and decrease rates expose fluctuations that a net rate alone would hide. Rates restart after a status request fails or the page reloads; changes between polls cannot be measured.

The **Clear pending data** button becomes available after acquisition stops and when the production spool contains undelivered batches. It permanently discards those batches, records their sample intervals as `operator_cleared_buffer` gaps, and reclaims local spool space. It does not delete samples already delivered to TimescaleDB. The matching API is `POST /api/buffer/clear` with JSON `{"confirm":"CLEAR BUFFER"}`; it rejects a running acquisition or locked spool. Clearing runs in a separate process so the web API stays responsive. Poll `GET /api/buffer/clear` for completion or failure.

In development mode, Compose mounts `services/daq_navi` into the DAQ container. Static asset edits become visible immediately. Restart `daq-navi` after changing the page template if its Flask process has cached the template.
# Production destinations

Production acquisition supports PostgreSQL/TimescaleDB and InfluxDB 2.x. Select the destination in Config Center, fill its connection settings, and use **Test destination** before saving. InfluxDB requires an HTTP(S) URL, organization, bucket, and token with write access. Production writes use the configured measurement at `precision=ns`; `sample_id` is a field, while `device_id`, `channel`, `session_id`, `unit`, and `provenance` are tags. Do not add `sample_id` as a tag: that creates a high-cardinality series per sample.

Influx acquisition gaps are written to the `daq_acquisition_gaps` measurement. `gap_id` is the stable tag; `start_ns`, optional `end_ns`, `open`, and `cause` are fields. Open intervals are updated in place when their boundary becomes known. Influx retention is configured on the bucket in InfluxDB and is displayed as bucket-managed in Config Center. The production samples API reads the selected Influx bucket; it does not query TimescaleDB for an Influx run.

The SQLite spool acknowledges a batch only after the destination returns success. An HTTP error or timeout leaves samples and gaps pending for replay. Before changing a destination target, stop the process through Config Center: it closes open gap intervals at the stopped boundary and drains pending records through the old backend before saving the new settings. Target changes include database/bucket, URL, measurement, or table changes. Influx token rotation does not change the target. If the old write fails, the old settings remain active and the pending spool is retained. Direct configuration edits that change a known target while records remain are rejected on startup. Config Center does not allow changing `SPOOL_DIR`; moving a spool requires an explicit migration.

## Safe Influx qualification

Use a disposable Influx organization and bucket with a short bucket retention period and a token scoped to that bucket. Start with one enabled channel at 1 kHz, then 2 kHz, and confirm distinct per-channel timestamps at the expected 1 ms and 500 μs intervals. Stop acquisition and compare sample IDs and point counts after an induced HTTP outage/replay; ambiguous retries should overwrite the same points. Exercise a recorded gap and verify its stable `gap_id`, start/end, cause, and open state. Confirm Config Center status, retention text, and the samples graph/API, then return to the production bucket only after qualification. Do not use a production bucket for fault injection.
