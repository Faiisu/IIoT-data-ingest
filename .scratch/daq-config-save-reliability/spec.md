# DAQ Config Center save reliability and secret-safe readback

## Problem and evidence

The DAQ Config Center save path spans browser state, `POST /api/config`, the private JSON file, the production spool, destination policy, and acquisition process control. A code audit found five related defects or failure hazards:

1. `auth.redact_config_secrets()` omits the active `DB_PASSWORD` field, while successful and some failed `POST /api/config` responses return the unredacted merged config. This conflicts with the DAQ access-control contract that configuration responses never return credentials.
2. The browser infers `DB_CONNECTION_MODE` by comparing a masked `DB_DSN` with a DSN assembled from form fields. A masked DSN cannot equal an unmasked one. In PostgreSQL fields mode, subsequent host or credential edits can leave the effective DSN pointing to the previous target.
3. `write_config()` falls back to truncating and rewriting `/app/config.json` because the production Compose project bind-mounts one file. An interruption can leave invalid JSON.
4. A destination switch stops a running acquisition before draining the old spool. If drain or a later step fails, the old run may remain stopped without an automatic recovery attempt.
5. A TimescaleDB retention change is applied before the config file is saved. A later file-write failure leaves the effective policy and saved configuration inconsistent.

Relevant code: `services/daq_navi/web/auth.py`, `services/daq_navi/web/app.py`, `services/daq_navi/web/static/config_center/app.js`, `deploy/daq-navi/compose.yml`. Existing expectations: `.scratch/daq-navi-access-control/spec.md`, `.scratch/daq-navi-production/spec.md`, and `docs/adr/0003-web-managed-acquisition-configuration.md`.

## Required behavior

- Configuration GET and every POST response, including partial-success and restart-failure responses, contain no usable database password, DSN password, Influx token, or MQTT password. An unchanged secret can be preserved without browser readback; an explicitly supplied replacement takes effect. Error text must not echo secrets.
- PostgreSQL connection mode is explicit and survives reload. Fields mode derives the effective DSN from the saved host, port, database, user, and secret. Custom DSN mode uses the saved custom DSN. The UI shows which one is effective and never silently ignores a field edit.
- A completed save has a complete, durable JSON file. A crash before the commit leaves the previous complete file. An invalid or missing file fails visibly; it must not be treated as an empty config and overwritten by a later save.
- Destination changes never redirect pending batches or gaps to another target. If a running acquisition is stopped and a pre-commit step fails, the service attempts to resume the original mode with the original configuration and reports both the save failure and recovery outcome. If the new config is committed but its run cannot start, the response states the persisted and runtime states precisely.
- TimescaleDB retention and the saved config agree after success. On failure, compensate any policy change and restore the prior config when possible; otherwise report the exact inconsistent state and required operator action. Influx bucket retention remains externally managed.
- Concurrent save requests are serialized across the config file, spool ownership, policy change, and process transition. A stale browser edit cannot silently overwrite a newer save.

## Delivery order

1. Ticket 01 establishes a secret-safe API and form contract. Ticket 02 replaces DSN inference with an explicit connection mode. Ship these together so masking `DB_PASSWORD` cannot break PostgreSQL editing.
2. Ticket 03 changes the production mount and write path so config replacement is atomic and durable. Keep existing private settings and spool volume through the migration.
3. Ticket 04 makes destination switching and process recovery one serialized operation. Ticket 05 adds retention policy to the same recovery model.
4. Ticket 06 exercises the full save matrix in isolation, documents the rollout, and qualifies the intended host before release. Do not use production telemetry or a production destination for fault injection.

## End-to-end acceptance

- Repeated GET and POST responses never contain known test secrets; readback and saving with unchanged placeholders preserve credentials. PostgreSQL fields and custom-DSN modes both survive reload and use the expected target.
- Invalid edits do not write, stop acquisition, drain spool, or alter retention. A successful running save stops and restarts once with the saved mode and values. A stopped save stays stopped.
- Inject failure at old-target drain, config commit, retention apply, and new-run start. Assert saved config, effective policy, spool owner and pending records, process state, response body, and UI message for each case. Pending data remains replayable and never moves to a new destination on a failed switch.
- An interrupted config write preserves either the old or new complete JSON. The deployment migration retains the private configuration, operator secret material, and external spool volume.

## Non-goals

This effort does not change the DAQ sample schema, create a global login, or manage InfluxDB bucket retention from Config Center.
