# 01: Audit the DAQ data ingestion system

Status: ready-for-agent
Blocked by: None

## Outcome

Produce an evidence-backed map of the current production DAQ path, its operating limits, and any gaps between documented guarantees and observed behavior. The audit must give the multiple-device ticket a concrete baseline without changing or deleting production telemetry.

## Work

1. Trace configuration from `services/daq_navi/config.json` and the Config Center through validation, process startup, DAQNavi device selection, channel setup, and acquisition. Compare saved settings with effective runtime values and the Compose environment. Identify every assumption that only one device or one channel span exists.
2. Trace each sample from hardware read through timestamping, raw/calibrated values, session and device identity, SQLite spool commit, replay, TimescaleDB write, retention, API query, and graph. Trace acquisition gaps and health/status through the same boundaries. Check that mockup data cannot be mistaken for production data.
3. Review the failure paths: device or driver errors, short/empty reads, process and container restart, database outage, slow writer, full spool, manual Stop, configuration changes, and recovery. For each path, state what is preserved, lost, duplicated, delayed, or reported; distinguish code inspection from observed results.
4. Verify the actual meaning of `CLOCK_RATE` and per-channel sample cadence against the installed DAQNavi SDK and PCI-1716 hardware behavior. Compare UI wording, validation, buffer sizing, timestamp calculations, and the measured rate. Record device discovery and stable identity behavior for multiple PCI cards and for a supported USB device such as USB-4716.
5. Review the existing automated and physical qualification evidence, resource and disk capacity assumptions, schema/indexes, operational logs, and deployment instructions. Run only isolated or read-only checks needed to substantiate findings; do not interrupt acquisition or modify live data without an explicit operational plan.

## Deliverables and acceptance

- An audit report at `.scratch/daq-ingestion-evolution/audit.md` records a data-flow diagram or ordered trace, config precedence, schema and identity model, current deployment topology, findings with file/line or observed evidence, and the checks performed.
- Findings are ranked by effect on data correctness, continuity, observability, or multiple-device support. Unverified hardware behavior and unavailable checks are clearly marked.
- The report states whether the existing single-device guarantees in `.scratch/daq-navi-production/spec.md` still hold and identifies any conflicting documentation or ADRs.
- The report gives ticket 02 concrete design inputs: device discovery/identity, per-device settings and limits, concurrency model, spool and failure isolation, sample/gap attribution, status/API/UI changes, capacity targets, and hardware qualification matrix.
