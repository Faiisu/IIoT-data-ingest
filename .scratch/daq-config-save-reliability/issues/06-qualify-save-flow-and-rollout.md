# 06: Qualify the complete save flow and roll out safely

Status: resolved
Blocked by: 01, 02, 03, 04, 05

## Outcome

The combined changes have a repeatable qualification record and an operator procedure for migrating the private config mount, deploying, checking acquisition, and rolling back without losing committed spool data.

## Work

1. Run isolated tests for authentication and secret redaction, PostgreSQL fields/custom mode, ordinary saves, running saves, destination switching, retention, atomic write interruption, and concurrent saves. Use sentinel secrets and disposable PostgreSQL/Influx destinations; never print real credentials.
2. Rehearse the Compose config-directory migration and rollback with a copy of private config and a disposable spool. Confirm the new container reads the copied config, preserves saved operator credentials and startup mode, and leaves the external production spool volume untouched.
3. On the intended host, schedule a controlled acquisition transition. Capture current mode, destination identity, pending count, policy, and process state; stop with the documented drain window; deploy; verify the saved config, UI readback, effective destination, health, sample continuity or recorded gap, and pending replay. Restore the prior version if a gate fails.
4. Update deployment and Config Center documentation with the new secret-control behavior, explicit PostgreSQL mode, save failure states, retention recovery, and config mount migration.
5. Record a qualification report under this effort directory with commands, versions, results, and any remaining limitations. Do not include secret values or production sample payloads.

## Acceptance

- All isolated save and fault-injection checks pass and the report links to their results.
- The production deployment checklist has an explicit rollback path and no step deletes the spool or production telemetry.
- Final qualification confirms the expected acquisition state, effective destination, saved config revision, retention, and a healthy UI/API. Any failed gate leaves a clear, actionable report rather than a claim of completion.

## Comments

- 2026-09-26: Built and deployed the config-directory version; the 123 focused tests pass. The qualification record is `../qualification.md`. During rollout, InfluxDB returned HTTP 404 because saved org `mddpa` did not exist. After operator authorization, config and spool ownership were backed up and corrected to bucket owner `mddp`. A separately authorized short run and offline replay delivered all pending records; Flux readback confirmed sample and gap points. Final web health is green, acquisition is stopped, and spool pending counts are zero. A shutdown timeout left a stale internal active marker; the stop path now reconciles that marker and status snapshot after the child exits.
- 2026-09-26: Updated legacy test fixtures and API tests to match the current 8-channel config, auth/session requirements, origin allowlist, SQL path, and process recovery behavior. Full suite now reports 224 passed with 7 skipped and no failures/errors.
