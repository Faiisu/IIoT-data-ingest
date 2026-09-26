# 05: Keep TimescaleDB retention and saved config consistent

Status: resolved
Blocked by: 03, 04

## Outcome

After a successful save, the effective TimescaleDB raw retention matches the saved config. A failed save restores the prior policy and config when possible, and reports any unresolved mismatch precisely.

## Evidence

`services/daq_navi/web/app.py:save_config()` calls `TimescaleProductionDestination(...).ensure_schema()` for a changed `DB_RETENTION_DAYS` before `write_config(updated)`. A subsequent write failure leaves the database policy changed while the old value remains saved.

## Work

1. Add retention preflight to the save plan and handle the external policy update within the serialized transition from ticket 04. State the commit and compensation order for config file, spool metadata, retention policy, and process restart.
2. On failure after applying the new policy, restore the prior effective policy and prior file value. If compensation fails, return an explicit partial-failure result with both values and an operator recovery instruction; never say the save simply failed with no side effect.
3. Read back the effective TimescaleDB policy after an update before reporting success. Treat InfluxDB retention as bucket-managed and do not attempt a TimescaleDB policy operation when InfluxDB is selected.
4. Keep retention policy changes scoped to the selected production table; avoid unrelated schema or data deletion as part of this fix.

## Acceptance

- A successful retention save reports the same days in the saved file and effective TimescaleDB policy.
- Inject file-write failure, policy-apply failure, readback mismatch, and compensation failure. Assert precise file/policy/process outcomes and response/UI messages.
- Saving unrelated settings or an InfluxDB config does not alter the TimescaleDB retention policy.

## Comments

- 2026-09-26: Added policy readback before reporting success and compensation after policy apply, spool-owner, or config-write failure. A simultaneous switch to a different PostgreSQL target and retention change is rejected before side effects; target policy must match saved retention before a destination switch. Fault-injection and rejection tests pass in the 122-test focused suite. See `../qualification.md`.
