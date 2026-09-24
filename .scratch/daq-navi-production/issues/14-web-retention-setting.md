# 14: Change raw telemetry retention through the web UI

**What to build:** Operators can change the production raw telemetry retention period from its 30-day default in the web UI and see the effective TimescaleDB policy.

**Blocked by:** 11: Edit supported acquisition settings through the web UI.

**Status:** resolved

- [x] The retention control displays the saved period and validates edits without losing other settings.
- [x] A saved change updates the active TimescaleDB policy and the UI confirms the effective period or reports an application error.
- [x] Web/API and isolated database tests cover a fresh policy and changing an existing policy.

## Answer

### 1. Retention Control Display & Validation
- **Web UI & Form Binding**: In `services/daq_navi/web/templates/index.html` and `services/daq_navi/web/static/app.js`, the `DB_RETENTION_DAYS` numeric input control (`min="1"`, `required`) displays the current saved retention period loaded from `/api/config`.
- **Validation & Non-Destructive Merging**: In `services/daq_navi/web/app.py`, `merge_config()` validates that `DB_RETENTION_DAYS` is an integer >= 1 (rejecting non-integers, floats, booleans, and values < 1 with HTTP 400) while keeping all other settings (`CHANNELS`, `CLOCK_RATE`, `DESTINATION`, etc.) intact.

### 2. Active TimescaleDB Policy Updates & UI Confirmation
- **Policy Synchronization**: When `DB_RETENTION_DAYS` is modified, `POST /api/config` in `services/daq_navi/web/app.py` triggers `TimescaleProductionDestination.ensure_schema()`, updating `add_retention_policy` on the production hypertable via `timescaledb_information.jobs`.
- **Error Handling**: If the database is unreachable or fails to apply the retention policy, `save_config()` returns HTTP 503 and aborts persisting the invalid config change.
- **Effective Policy Inspection**: `GET /api/retention` queries `timescaledb_information.jobs` for the hypertable's active drop interval. The frontend `refreshRetentionPolicy()` displays the effective period or reports error details inside `#production-retention-policy`.

### 3. Test Verification
- **Web API Tests (`services/daq_navi/tests/test_production_web.py`)**:
  - `test_retention_save_fresh_policy_applies_and_preserves_other_settings`: Validates applying a fresh retention policy when missing from original configuration and confirms non-destructive merge.
  - `test_retention_save_changing_existing_policy_updates_timescaledb`: Validates applying an updated retention policy.
  - `test_retention_save_unchanged_does_not_reapply_policy`: Validates that saving unrelated parameters does not redundantly execute `ensure_schema`.
  - `test_retention_validation_rejects_non_positive_integers`: Validates rejection of non-integers, floats, <= 0, and non-numeric types.
  - `test_retention_database_error_reports_503_and_prevents_save`: Validates 503 response and rollback upon database outage.
  - `test_get_retention_effective_policy`, `test_get_retention_missing_policy_reports_503`, and `test_get_retention_database_error_reports_503`: Validates `/api/retention` contract for active policies, missing policies, and connection errors.
- **Isolated Database Tests (`services/daq_navi/tests/test_production_timescale.py`)**:
  - `test_duplicate_batch_is_idempotent_and_retention_changes`: Verifies initial creation of a 30-day retention policy on the production hypertable and dynamic modification to 45 days against live TimescaleDB.


