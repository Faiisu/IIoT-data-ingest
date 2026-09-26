-- Migration: 0001_retire_calibration_revision
-- Description: Retire calibration_revision from DAQ production records.
-- Explicitly drops the calibration_revision column from daq_production_samples if present,
-- deleting stored revision metadata, and records completion in daq_schema_migrations
-- to ensure destructive changes are performed only once.

CREATE TABLE IF NOT EXISTS daq_schema_migrations (
    version TEXT NOT NULL,
    table_name TEXT NOT NULL,
    applied_at TIMESTAMPTZ NOT NULL,
    description TEXT NOT NULL,
    PRIMARY KEY (version, table_name)
);

DO $$
BEGIN
    IF NOT EXISTS (
        SELECT 1 FROM daq_schema_migrations 
        WHERE version = '0001_retire_calibration_revision' AND table_name = 'daq_production_samples'
    ) THEN
        IF EXISTS (
            SELECT 1 FROM information_schema.columns 
            WHERE table_name = 'daq_production_samples' AND column_name = 'calibration_revision'
        ) THEN
            ALTER TABLE daq_production_samples DROP COLUMN calibration_revision;
        END IF;

        INSERT INTO daq_schema_migrations (version, table_name, applied_at, description)
        VALUES ('0001_retire_calibration_revision', 'daq_production_samples', NOW(), 'Retire calibration_revision column from production samples');
    END IF;
END $$;
