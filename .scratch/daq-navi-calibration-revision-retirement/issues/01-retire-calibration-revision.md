# 01: Retire calibration revision from DAQ production records

**What to build:** Production DAQ records and operator views no longer include calibration revision metadata. Existing schema is migrated according to the approved retirement plan, with any removal of stored revision values explicit and performed once.

**Blocked by:** None (can start immediately).

**Status:** ready-for-agent

- [ ] Remove calibration revision from newly captured production records and both supported destination representations.
- [ ] Remove calibration revision from sample APIs, Config Center displays, and operator documentation.
- [ ] Apply a versioned, repeatable schema migration that retires the old column; any deletion of existing revision values is explicit in the migration and documented for operators.
- [ ] Update the DAQ production domain spec to reflect that revision metadata is no longer part of the production record.
- [ ] Verify PostgreSQL/TimescaleDB and InfluxDB writes and sample views work without calibration revision metadata, and repeated service startup does not perform destructive migration work again.
