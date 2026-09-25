# 01: Audit and implement MUSASHI II as a supported service

Status: ready-for-agent

## Outcome

MUSASHI II can be configured, started, stopped, monitored, and deployed on the Linux Docker host as an independent ingestion service. Real mode polls the dispenser through RS-232C and persists records to the selected destination; mock mode remains explicitly distinguishable.

## Work

1. Audit `services/musashi_ii/` end to end: serial frame handling and polling, configuration and validation, web controls, child process lifecycle, startup recovery, database writers, error handling, existing tests, and `service_linux.sh`. Record the current behavior, defects, and deployment assumptions before changing them. Determine which host setup or process manager remains relevant once Compose owns the container.
2. Define and implement the Linux configuration path for the actual serial device, baud rate, polling interval, startup mode, and storage destination. Replace machine-specific checked-in defaults such as `/dev/cu.usbserial-A600bsZD` and the current database host with safe examples or deployment settings. Ensure saved web configuration and container settings have a clear precedence, and avoid embedding live credentials in tracked files.
3. Check that serial disconnects, malformed frames, timeouts, database outages, child process crashes, manual Stop, and container restarts produce accurate status and logs. Make reported success mean that a record reached the configured destination; do not silently switch real acquisition to synthetic data. Decide and document the recovery behavior after an outage based on the audit.
4. Package the web control and ingestion process for Linux, including required Python packages, serial-device access, persistent writable configuration/state where needed, a healthcheck, and a `musashi-ii` Compose service on port 8082. Keep it isolated from DAQ state and tables. Update the Portal status/link behavior and deployment documentation for the resulting service.
5. Add focused automated checks for the serial protocol and process/storage failure paths, plus a repeatable deployment check using a simulated serial peer. Document the real-hardware check and record its result when the dispenser and host port are available.

## Acceptance

- The audit records the existing data flow, configuration sources, known defects, storage schema, and decisions made to address them.
- `docker compose up -d --build` starts MUSASHI II and its web/API endpoint on the configured host port; the health and Portal status reflect the actual service state.
- With a configured serial device, real mode accepts valid dispenser responses and stores traceable records in the selected destination. Bad frames, disconnects, and destination failures are visible and are not counted as delivered records.
- Explicit mock mode can be exercised without a physical dispenser and is clearly identified in the UI, status, and stored data or isolated destination.
- Stop, restart, and container recreation follow the saved startup policy without orphaned acquisition processes or accidental duplicate polling.
- The documented configuration and deployment steps work on a clean Linux host without relying on the previous machine's paths or credentials; the existing DAQ service continues to operate.
