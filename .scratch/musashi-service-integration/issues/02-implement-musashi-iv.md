# 02: Audit and implement MUSASHI IV as a supported service

Status: ready-for-agent

## Outcome

MUSASHI IV can be configured, started, stopped, monitored, and deployed on the Linux Docker host as an independent ingestion service. Real mode polls the dispenser HTTP API and persists records to the selected destination; mock API data stays explicit and separate.

## Work

1. Audit `services/musashi_iv/` end to end: API polling and payload parsing, configuration and web controls, child process lifecycle, startup recovery, PostgreSQL/InfluxDB/SQLite writes, schema creation, mock API behavior, error handling, and existing tests. Record the current behavior, defects, and deployment assumptions before changing them.
2. Define and implement the production API URL, channel, polling interval, startup mode, and storage settings for Docker networking. Replace machine-specific checked-in hosts, localhost assumptions, and example credentials with safe defaults or deployment settings. Ensure saved web configuration and container settings have a clear precedence, and keep mock and real destinations distinguishable.
3. Verify that API failures, invalid payloads, database outages, child process crashes, manual Stop, and container restarts produce accurate status and logs. In particular, audit `stream_to_db.py` paths that increment `written` without an active database connection or recognized destination, and the statistics path that may access `rec` before a successful poll. Make successful delivery observable rather than inferred from polling alone.
4. Package the web control, ingestion process, and optional mock API for Linux, including required Python packages, persistent writable configuration/state where needed, a healthcheck, and a `musashi-iv` Compose service on port 8083. Keep it isolated from DAQ state and tables. Update the Portal status/link behavior and deployment documentation for the resulting service.
5. Add focused automated checks for valid and invalid API responses, destination failures, startup/stop behavior, and the mock API path. Run a repeatable Compose check with the bundled mock API; document and record the real-device check when the endpoint is available.

## Acceptance

- The audit records the existing data flow, configuration sources, known defects, storage schema, and decisions made to address them.
- `docker compose up -d --build` starts MUSASHI IV and its web/API endpoint on the configured host port; the health and Portal status reflect the actual service state.
- In real mode, valid HTTP responses reach the selected destination. API, parsing, and destination failures are visible and are not counted as delivered records; mock data is never substituted silently.
- Explicit mock mode runs with the bundled mock API and is clearly identified in the UI, status, and stored data or isolated destination.
- Stop, restart, and container recreation follow the saved startup policy without orphaned acquisition or mock API processes or accidental duplicate polling.
- The documented configuration and deployment steps work on a clean Linux host without relying on the previous machine's addresses or credentials; the existing DAQ service continues to operate.
