# 02: Acquire data concurrently from multiple DAQ devices

Status: ready-for-agent
Blocked by: 01

## Outcome

One Linux host can run production acquisition concurrently from at least two configured Advantech DAQ devices. Supported examples are two PCI cards with distinct board identities, and one PCI card plus a USB-4716 if the installed driver and SDK support that combination. Each device's data and operational state remain independently identifiable.

## Work

1. Use the findings and measured constraints from ticket 01 to define a per-device configuration model. Give each device a stable, unique logical ID tied to its DAQNavi identity; store its model, enabled channels, signal types, ranges, calibrations, sampling settings, and startup policy. Keep existing single-device configuration usable or provide a documented, reversible migration. Reject duplicate device identities and overlapping ownership of one physical device.
2. Implement independent acquisition lifecycles that can run simultaneously without one device's read, stop, fault, or configuration change blocking the other unnecessarily. Apply each model's real channel count, wiring, voltage range, and timing limits; do not use PCI-1716-specific validation or a fixed 16-channel limit for all devices. Decide and document whether starts and configuration changes are per device or coordinated across devices.
3. Make spool state, batch/sample identity, session state, acquisition gaps, writer progress, and recovery unambiguous per device. Preserve idempotent replay and raw/calibrated provenance. A device failure or full buffer must not silently discard another device's committed data or substitute mockup samples. Confirm how shared destination outages and shared disk capacity affect all devices.
4. Extend schema and queries only as needed to filter samples and gaps by device without confusing channels that have the same number on different devices. Extend the Config Center, API, status/health reporting, and graphs so an operator can discover devices, configure each one, start/stop acquisition, and identify which device has a fault or backlog. Preserve a useful overall health summary.
5. Update the Docker deployment and operator documentation for access to multiple PCI/USB devices, stable device names after reboot, host SDK requirements, configuration, capacity sizing, and recovery. Add focused automated checks with two independent DAQ fakes, then qualify two real devices when available. Record the models, driver versions, wiring, settings, actual per-channel rates, timestamps, database rows, and fault results.

## Acceptance

- Existing single-device configuration and production reads continue to work after the change or complete the documented reversible migration.
- Two configured devices acquire at the same time. Records from identical channel numbers on different devices have distinct device IDs, session/sample identities, calibration metadata, and query results.
- Stopping, disconnecting, or faulting one device leaves the other device's acquisition and delivery running; status and gaps identify the affected device. A shared database outage retains committed batches within the measured spool capacity and replays them once after recovery.
- Configuration and UI validation reflect the actual selected hardware model and verified DAQNavi capabilities. The PCI+USB scenario is marked supported only after a real USB-4716 qualification; the two-PCI scenario is marked supported only after a real two-card qualification.
- A recorded concurrent-load check measures per-device sample cadence, timestamp ordering, queue growth, and storage use at the chosen production settings. The operator can see both per-device and overall state through the API and Config Center.
