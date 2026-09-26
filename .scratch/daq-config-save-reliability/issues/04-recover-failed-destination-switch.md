# 04: Recover acquisition after a failed destination switch

Status: resolved
Blocked by: 02, 03

## Outcome

A failed destination change cannot silently leave a previously running DAQ stopped or reassign pending data to the new target. The response and UI state identify the saved config, effective destination, pending spool owner, and acquisition state.

## Evidence

`services/daq_navi/web/app.py:save_config()` stops a running acquisition before `drain_spool_for_destination_switch()`. A drain exception returns 503 without restarting the old run. Save requests have no transaction lock across stop, spool, config, and restart steps.

## Work

1. Serialize saves and related process/destination transitions with a service-wide lock; decide how start, stop, and buffer-clear requests interact with an in-progress save. Reject stale submissions or require a config revision so two browser tabs cannot silently overwrite each other.
2. Separate preflight from commit: validate the full new config and new destination connectivity before stopping; capture the old config, mode, process state, destination identity, and spool ownership. Keep the old destination authoritative until pending batches and gaps have been acknowledged there.
3. On failure after a running acquisition stops but before the new config commits, attempt to restart the old mode with the old config. Preserve remaining old-target records for replay. Report both the original failure and whether recovery succeeded. If the acquisition was already stopped, keep it stopped.
4. Define the post-commit failure policy: if the new run cannot start, either compensate back to the old config and mode or retain the new config while explicitly reporting the stopped state. Choose one documented rule and apply it consistently; never return an ordinary success for a stopped or mismatched run.
5. Make the browser refresh saved config and runtime status after a partial failure, showing the operator what is persisted and whether acquisition resumed. Do not merely clear the dirty flag based on a `config` response field.

## Acceptance

- With old-target drain failure, a previously running acquisition resumes on the old config when restart is possible; pending records and spool identity remain old-target. The error includes recovery outcome.
- Inject failures at stop, drain, spool metadata update, config commit, and new-run start. Each case has asserted file content, pending data, spool owner, process state, and API/UI result.
- Concurrent or stale saves cannot interleave stop/start transitions or overwrite a newer config without detection.

## Comments

- 2026-09-26: Serialized save/start/stop/buffer transitions with `CONFIG_TRANSITION_LOCK` and rejected stale config revisions with HTTP 409. Destination preflight runs before stop; drain, spool-owner update, and file-commit failures attempt to restore prior ownership and running mode. Post-commit restart failure reports `persisted=true` and `runtime=stopped`. The browser refreshes saved state after partial persistence and retains unsaved edits after pre-commit failure. Fault-injection cases are in `test_config_reliability.py`; the 122 focused tests pass. Deployment and pending-spool caveats are recorded in `../qualification.md`.
