# 01: Make all config responses secret-safe

Status: resolved
Blocked by: None

## Outcome

No Config Center API response reveals a saved database password, credential-bearing DSN, Influx token, or MQTT password. Operators can keep or replace each secret without reading it back.

## Evidence

- `services/daq_navi/web/auth.py`: `redact_config_secrets()` handles `POSTGRES_PASSWORD` but omits the active `DB_PASSWORD` key.
- `services/daq_navi/web/app.py`: `GET /api/config` calls the redactor, but successful and some failure paths in `POST /api/config` return `config: updated` directly.
- `.scratch/daq-navi-access-control/spec.md` explicitly requires secret-free configuration responses.

## Work

1. Define one authoritative secret-field inventory for this service, including `DB_PASSWORD`, legacy `POSTGRES_PASSWORD`, `INFLUX_TOKEN`, `MQTT_PASSWORD`, and credentials embedded in `DB_DSN`. Apply it to GET readback and every POST response that includes config. Review error messages from validation, connection, drain, and restart for credential echo.
2. Preserve an unchanged saved secret when the browser sends a documented placeholder or omits the field. Accept an explicit replacement. Define how an operator deliberately clears an optional secret, so blank does not ambiguously mean both clear and keep.
3. Update Config Center secret controls to show `saved/unchanged` or `replace` state without filling a password input with a real secret. Do not reconstruct a DSN containing a placeholder password in the browser. Coordinate the PostgreSQL mode behavior with ticket 02; release both tickets together.
4. Remove raw `config: updated` from success and partial-failure responses or replace it with the same safe readback representation. Keep enough non-secret state for the UI to distinguish persisted config from a failed restart.

## Acceptance

- With known sentinel secrets in an isolated config, neither GET nor any POST response contains a sentinel, including `Saved; restart failed` and `Saved; prior session is still stopping` responses.
- Unchanged-secret and replacement saves persist the intended value for every listed secret. The browser never receives a usable old secret after reload or save.
- Tests cover both normal and failure responses. Existing access-control tests are updated to include `DB_PASSWORD` and POST readback, without logging secret values.

## Comments

- 2026-09-26: Resolved alongside Ticket 02.
  - Defined authoritative `SECRET_FIELDS` inventory in `auth.py`.
  - Added keyword and URL password redaction in `redact_dsn_password()` and `redact_error_message()`.
  - `save_config()` redacts `safe_config` across all success and failure return paths.
  - Added `CLEAR_SECRET` sentinel handling in `merge_preserved_secrets()`.
  - Frontend `app.js` renders secret placeholder indicating unchanged saved secrets without prefilling inputs with secrets or placeholders.
  - Automated tests added in `services/daq_navi/tests/test_config_reliability.py`. All 134 production and access control tests pass.
