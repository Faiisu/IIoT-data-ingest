-- MDDP Ingestion Control Suite - Database Initialization Script
-- Supports PostgreSQL with TimescaleDB Extension

-- 1. Create Database Extensions
CREATE EXTENSION IF NOT EXISTS timescaledb CASCADE;

-- 2. Telemetry Samples Table & Hypertable (Legacy USB-4716)
CREATE TABLE IF NOT EXISTS daq_samples (
    time TIMESTAMPTZ NOT NULL,
    channel INT NOT NULL,
    value DOUBLE PRECISION NOT NULL
);

SELECT create_hypertable('daq_samples', 'time', if_not_exists => TRUE);

CREATE INDEX IF NOT EXISTS idx_daq_samples_channel_time ON daq_samples (channel, time DESC);

-- 3. Universal DAQ Telemetry Table & Hypertable (Universal DAQNavi - PCI-1716, USB-4716, etc.)
CREATE TABLE IF NOT EXISTS daq_telemetry (
    time TIMESTAMPTZ NOT NULL,
    device_id VARCHAR(32) NOT NULL,
    channel INT NOT NULL,
    value DOUBLE PRECISION NOT NULL
);

SELECT create_hypertable('daq_telemetry', 'time', chunk_time_interval => INTERVAL '1 hour', if_not_exists => TRUE);

CREATE INDEX IF NOT EXISTS idx_daq_telemetry_device_channel_time 
    ON daq_telemetry (device_id, channel, time DESC);

-- 4. Telemetry Session Metadata Table
CREATE TABLE IF NOT EXISTS daq_sessions (
    session_id VARCHAR(64) PRIMARY KEY,
    device_id VARCHAR(32),
    start_time TIMESTAMPTZ NOT NULL,
    end_time TIMESTAMPTZ,
    clock_rate INT,
    channel_count INT,
    config_snapshot JSONB,
    mode VARCHAR(32)
);

-- 5. Musashi II Dispenser Telemetry Table
CREATE TABLE IF NOT EXISTS musashi_ii_data (
    id SERIAL PRIMARY KEY,
    time TIMESTAMPTZ NOT NULL,
    dispense_time DOUBLE PRECISION,
    pressure DOUBLE PRECISION,
    vacuum DOUBLE PRECISION,
    status VARCHAR(32)
);

-- 6. Musashi IV Dispenser Telemetry Table
CREATE TABLE IF NOT EXISTS musashi_iv_data (
    id SERIAL PRIMARY KEY,
    time TIMESTAMPTZ NOT NULL,
    channel INT,
    pressure DOUBLE PRECISION,
    vacuum DOUBLE PRECISION,
    status VARCHAR(32)
);
