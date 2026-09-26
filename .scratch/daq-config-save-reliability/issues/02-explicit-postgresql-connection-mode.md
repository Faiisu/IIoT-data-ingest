# 02: Persist and apply PostgreSQL connection mode explicitly

Status: resolved
Blocked by: 01

## Outcome

The PostgreSQL connection controls identify the effective target after every reload and save. Editing fields mode changes the actual destination; custom DSN mode retains the custom target until explicitly changed.

## Evidence

`services/daq_navi/web/static/config_center/app.js` sets `manualDsn` by comparing a redacted `DB_DSN` from GET with `postgresDsn()` built from form fields. Redaction guarantees a mismatch when the DSN has a password. `services/daq_navi/core/config_loader.py` uses `DB_DSN` as the effective production connection.

## Work

1. Add an explicit `fields`/`dsn` mode to the saved configuration and API contract. For existing files without the mode, infer it once on the server using the unredacted saved values and record a deterministic migration rule; preserve truly custom PostgreSQL URL and keyword DSNs.
2. In fields mode, build the effective DSN from the merged saved fields and preserved or replaced password on the server. In custom mode, use the saved custom DSN. Treat a mode or effective target change as a destination-identity change so ticket 04 can drain the old spool before switching.
3. Make the UI render the explicit mode from readback. Switching modes must show the effective target and must not submit a masked DSN as a real credential. A field edit in custom mode should explain that the custom DSN remains effective, or switch mode explicitly with operator intent.
4. Keep PostgreSQL credential encoding, URL DSNs, and keyword DSNs valid. Ensure production validation and destination tests use the same effective connection chosen by Save.

## Acceptance

- Existing fields-mode and custom-DSN configs reload into the correct control state without exposing passwords.
- Changing host, port, database, user, or password in fields mode updates the effective DSN and destination identity; unchanged secrets remain valid.
- Changing only the display fields in custom mode cannot silently change or appear to change the effective target. Explicit mode switches behave predictably and survive reload.
- Isolated tests cover legacy config migration, masked readback, both mode transitions, DSN encoding, and destination identity comparison.

## Comments

- 2026-09-26: Resolved alongside Ticket 01.
  - Added `infer_db_connection_mode()` to `core/config_loader.py` and `web/auth.py` providing deterministic migration for existing files.
  - Added `DB_CONNECTION_MODE` to `DaqNaviConfig` and `merge_config()`.
  - In `fields` mode, effective DSN is automatically derived from the merged saved fields and credentials on the server.
  - `destination_identity` incorporates `DB_CONNECTION_MODE` ensuring mode transitions trigger destination boundary drain.
  - `_test_destination` and UI `app.js` respect explicit connection mode.
  - Verified with 7 dedicated tests in `test_config_reliability.py` and full suite passes.
