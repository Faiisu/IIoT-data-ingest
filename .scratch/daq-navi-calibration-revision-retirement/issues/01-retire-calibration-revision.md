# 01: Retire calibration revision from DAQ production records

**What to build:** Production DAQ records and operator views no longer include calibration revision metadata. Existing schema is migrated according to the approved retirement plan, with any removal of stored revision values explicit and performed once.

**Blocked by:** None (can start immediately).

**Status:** resolved

- [x] Remove calibration revision from newly captured production records and both supported destination representations.
- [x] Remove calibration revision from sample APIs, Config Center displays, and operator documentation.
- [x] Apply a versioned, repeatable schema migration that retires the old column; any deletion of existing revision values is explicit in the migration and documented for operators.
- [x] Update the DAQ production domain spec to reflect that revision metadata is no longer part of the production record.
- [x] Verify PostgreSQL/TimescaleDB and InfluxDB writes and sample views work without calibration revision metadata, and repeated service startup does not perform destructive migration work again.

## Comments

- 2026-09-26: Calibration revision retired across DAQ production records, APIs, destination sinks, and schema migrations.
  - Implemented versioned migration `0001_retire_calibration_revision` tracked via `daq_schema_migrations` table in `TimescaleProductionDestination._apply_migrations`.
  - Removed blind unversioned destructive `DROP COLUMN` from `ensure_schema()` so repeated service startup performs zero destructive operations.
  - Added standalone SQL migration script `scripts/sql/migrations/0001_retire_calibration_revision.sql` and operator guide `docs/operations/calibration-revision-retirement.md`.
  - Updated domain documentation and architecture specifications: `.scratch/daq-navi-production/spec.md`, `docs/architecture/erd.md`, `docs/adr/0008-preserve-raw-and-calibrated-measurements.md`, `docs/adr/0011-retire-calibration-revision.md`, and `services/daq_navi/web/README.md`.
  - Added automated unit and integration tests in `test_production_acquisition.py` and `test_production_timescale.py`.
  - Verified full test suite (`test_production_timescale.py`, `test_production_acquisition.py`, `test_production_web.py`, `test_access_control.py`): all 128 tests passed cleanly.
