# 03: Commit the private DAQ configuration atomically

Status: resolved
Blocked by: None

## Outcome

A save either commits one complete JSON config or leaves the previous complete config intact, including on the production Docker deployment.

## Evidence

`services/daq_navi/web/app.py:write_config()` creates a temporary file and calls `os.replace()`, then falls back to truncating and rewriting `CONFIG_PATH` on `OSError`. `deploy/daq-navi/compose.yml` bind-mounts one host file at `/app/config.json`, where replacement can fail with `EBUSY`.

## Work

1. Use a dedicated private host directory mounted as a directory so a same-directory temporary file can replace the config path. Update `CONFIG_PATH`, standalone script config path, entrypoint assumptions, Compose, setup docs, and any development override consistently. Do not mount the entire deployment directory or expose `.env` inside the container.
2. Write a same-directory temporary JSON file, flush and `fsync` it, atomically replace the target, then `fsync` the parent directory. Preserve owner and restrictive permissions. Remove the truncation fallback; return a failure if atomic commit is impossible.
3. Provide a migration path from the existing `deploy/daq-navi/config.local.json` that copies rather than discards private settings. The deployment steps must preserve the external spool volume and operator secret material. Specify rollback to the previous Compose mount if startup fails.
4. Make an unreadable, missing, or malformed saved config a visible error for GET and POST. A save must never merge edits into `{}` after a read failure.

## Acceptance

- Fault injection before replacement leaves the old JSON intact; a completed replacement yields the new complete JSON; no partial JSON is observable.
- Failure to write, replace, or sync returns a clear error and does not report a successful save or restart with unsaved values.
- The production Compose path uses the atomic path. Migration rehearsal confirms existing private settings, file permissions, and spool content survive container recreation.

## Comments

- 2026-09-26: Resolved.
  - Updated `write_config()` to write temporary files with `fsync`, set restrictive file permissions matching the target, perform atomic `os.replace()`, and `fsync` the parent directory. Truncation fallback removed.
  - Made `read_config()` raise immediately on missing or malformed JSON, returning clear 500 responses on `GET` and `POST` without merging into `{}`.
  - Config directory mount `./config:/app/config` configured in `deploy/daq-navi/compose.yml` with `DAQ_CONFIG_PATH: /app/config/config.json`.
  - Migrated `deploy/daq-navi/config.local.json` to `deploy/daq-navi/config/config.json` with permissions 0600, preserving existing settings, operator credentials, and spool volume. Added to `.gitignore` and `.dockerignore`.
  - Added fault injection tests in `services/daq_navi/tests/test_config_reliability.py`. All 137 tests pass.
