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

-- Compression Policy: compress chunks older than 1 hour, segmented by device_id and channel
ALTER TABLE daq_telemetry SET (
    timescaledb.compress,
    timescaledb.compress_segmentby = 'device_id, channel',
    timescaledb.compress_orderby = 'time DESC'
);

SELECT add_compression_policy('daq_telemetry', INTERVAL '1 hour', if_not_exists => TRUE);

-- Retention Policy: drop chunks older than 90 days
SELECT add_retention_policy('daq_telemetry', INTERVAL '90 days', if_not_exists => TRUE);

-- Continuous Aggregate: 1-second downsampling (avg, min, max, count)
CREATE MATERIALIZED VIEW IF NOT EXISTS daq_telemetry_1s
WITH (timescaledb.continuous) AS
SELECT
    time_bucket('1 second', time) AS bucket,
    device_id,
    channel,
    AVG(value) AS avg,
    MIN(value) AS min,
    MAX(value) AS max,
    COUNT(value) AS count
FROM daq_telemetry
GROUP BY bucket, device_id, channel
WITH NO DATA;

SELECT add_continuous_aggregate_policy('daq_telemetry_1s',
    start_offset => INTERVAL '1 hour',
    end_offset => INTERVAL '1 second',
    schedule_interval => INTERVAL '10 seconds',
    if_not_exists => TRUE);

-- Continuous Aggregate: 1-minute downsampling (avg, min, max, count)
CREATE MATERIALIZED VIEW IF NOT EXISTS daq_telemetry_1m
WITH (timescaledb.continuous) AS
SELECT
    time_bucket('1 minute', time) AS bucket,
    device_id,
    channel,
    AVG(value) AS avg,
    MIN(value) AS min,
    MAX(value) AS max,
    COUNT(value) AS count
FROM daq_telemetry
GROUP BY bucket, device_id, channel
WITH NO DATA;

SELECT add_continuous_aggregate_policy('daq_telemetry_1m',
    start_offset => INTERVAL '1 day',
    end_offset => INTERVAL '1 minute',
    schedule_interval => INTERVAL '1 minute',
    if_not_exists => TRUE);

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
