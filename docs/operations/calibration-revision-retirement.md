# Migration Guide: Retiring Calibration Revision Metadata

## Overview

Calibration revision metadata has been retired from DAQ production sample records.
Newly captured samples, TimescaleDB hypertable records, InfluxDB line-protocol points, and `/api/samples` query responses no longer include `calibration_revision`.

## Schema Migration (`0001_retire_calibration_revision`)

The PostgreSQL/TimescaleDB schema is updated via a versioned, repeatable migration tracked in the `daq_schema_migrations` table:
- **Migration ID**: `0001_retire_calibration_revision`
- **Migration Ledger Table**: `daq_schema_migrations`
- **Migration SQL Script**: `scripts/sql/migrations/0001_retire_calibration_revision.sql`

### Manual Execution (Optional)

Operators who wish to run schema updates explicitly prior to deploying new application containers can execute the migration script directly against the database:

```bash
psql -h <DB_HOST> -p <DB_PORT> -U <DB_USER> -d <DB_NAME> -f scripts/sql/migrations/0001_retire_calibration_revision.sql
```

### Automatic Execution & Idempotency Guarantee

If the migration has not been applied beforehand, the DAQ service executes it automatically on first startup:
1. It queries `daq_schema_migrations` to check if `0001_retire_calibration_revision` has already been recorded.
2. If unapplied, any existing `calibration_revision` column in the configured production samples table is dropped via `ALTER TABLE ... DROP COLUMN calibration_revision`, permanently removing legacy revision metadata.
3. The migration is recorded in `daq_schema_migrations` with the current UTC timestamp and description.
4. On subsequent service startups, the service observes that `0001_retire_calibration_revision` is already applied and skips destructive DDL entirely. Repeated startup will never run destructive operations again.

## Verification

To verify that the migration completed:
```sql
-- Check recorded migration
SELECT * FROM daq_schema_migrations WHERE version = '0001_retire_calibration_revision';

-- Check that column is gone
SELECT column_name, data_type 
FROM information_schema.columns 
WHERE table_name = 'daq_production_samples' AND column_name = 'calibration_revision';
```
