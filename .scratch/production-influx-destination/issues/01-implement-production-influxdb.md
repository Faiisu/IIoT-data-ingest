# 01: Implement InfluxDB 2.x as a production DAQ destination

Blocked by: None

Implementation and operator qualification are complete. InfluxDB 2.x has been confirmed working with the physical DAQ.

## Outcome

The physical DAQ pipeline can write production samples to either TimescaleDB or InfluxDB 2.x using one selectable saved destination, without losing the current spool/replay/gap guarantees.

## Work

1. Add a production InfluxDB destination behind the existing `write(rows, gaps)` seam and select it from saved DAQ configuration. Preserve `time_ns`, device/channel identity, raw voltage, calibrated value, unit, calibration revision, provenance, and stable replay identity. Define and document a representation for acquisition gaps.
2. Keep acknowledgement after successful destination writes only. Make retries idempotent for both samples and gaps, including ambiguous success followed by retry. Handle InfluxDB API errors and timeouts without acknowledging the spool.
3. Update Config Center validation, destination testing, status and production sample graph/API behavior for InfluxDB. Make destination-specific settings and retention behavior clear; do not silently query TimescaleDB for an InfluxDB production run.
4. Add focused tests for timestamp precision/collision, payload mapping, retry/replay, gap delivery, validation, and read API behavior. Use mocks or isolated fixtures; do not write to live production buckets or the running DAQ spool.
5. Update operator documentation for configuration, limitations, and a safe qualification procedure. Preserve existing PostgreSQL behavior and the user's current `services/daq_navi/config.json` edit.

## Deliverables and acceptance

- Config Center accepts PostgreSQL/TimescaleDB and InfluxDB for production, with working start, spool, writer, status, and sample graph paths for each.
- InfluxDB receives distinct 1 kHz and 2 kHz per-channel samples with nanosecond timestamps; replay does not create extra logical points and does not discard failed batches.
- Gaps and raw/calibrated provenance remain queryable or explicitly documented where the destination differs.
- Existing PostgreSQL production tests and new InfluxDB tests pass; no live deployment or data deletion occurs.

## Comments

- 2026-09-26: Ticket opened at the user's request. GPT-6-Sol (medium) plans and reviews; GPT-6-Luna implements. Existing uncommitted `services/daq_navi/config.json` change belongs to the user and must remain untouched.
- 2026-09-26: GPT-6-Luna implemented the production InfluxDB writer, destination selection, spool ownership and switch guards, Config Center behavior, sample API, documentation, and focused tests. GPT-6-Sol (medium) reviewed the implementation and its data safety fixes; no remaining blockers found in the scoped review. The focused acquisition, destination connection, and production web suite passed (99 tests); `git diff --check` passed. No live DAQ run, InfluxDB write, deployment, or config.json change was performed. Operator qualification on disposable hardware/bucket is the remaining human step.
- 2026-09-26: User confirmed InfluxDB 2.x is working in operator qualification with the physical DAQ. Ticket complete.

## Implementation plan (GPT-6-Sol, medium)

1. Add a destination adapter behind production `write(rows, gaps)` and select it at startup. Influx writes use `/api/v2/write` with `precision=ns`; the legacy Influx client with second-level timestamps is not reused.
2. Use stable `device_id`, `channel`, and `session_id` tags with exact `time_ns` for sample identity. Keep `sample_id` as a field to avoid a separate high-cardinality series for every sample. Represent gaps in a separate measurement keyed by stable `gap_id`, and retain start/end/cause.
3. Keep the SQLite spool and acknowledgement order. An HTTP failure or uncertain response leaves the batch/gap pending for replay; a retry must write the same logical points. Reject destination switching while batches or gaps for the prior destination remain pending, including on direct process startup when feasible.
4. Branch the production sample API and retention presentation by destination. For Influx, parse the query response into the current graph API shape and report bucket-managed retention accurately. Update Config Center validation and destination-specific visibility.
5. Test timestamp uniqueness at 1 kHz and 2 kHz, tag/field escaping, sample/gap mapping, ambiguous success, retry and acknowledgement, destination-switch guard, API response shape, and unchanged PostgreSQL behavior. Use isolated mocks/fixtures only; document safe later qualification on real hardware and bucket.
