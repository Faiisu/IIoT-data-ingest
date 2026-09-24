# Entity Relationship Diagram (ERD)

```mermaid
erDiagram
    daq_production_samples {
        TIMESTAMPTZ time PK "Hypertable Time Partition Key"
        TEXT sample_id PK "Unique stable sample identifier"
        UUID session_id "Acquisition run UUID"
        TEXT device_id "Hardware device ID (e.g. pci1716-0)"
        SMALLINT channel "Physical input channel (0-3)"
        TEXT sensor_name "Operator sensor label"
        DOUBLE_PRECISION raw_voltage "Uncalibrated electrical voltage (V)"
        DOUBLE_PRECISION calibrated_value "Converted engineering value"
        TEXT unit "Engineering unit (e.g. kPa)"
        TEXT calibration_revision "Revision identifier (e.g. initial)"
        TEXT provenance "Source provenance (physical_daq)"
    }

    daq_production_gaps {
        UUID gap_id PK "Unique gap identifier"
        TIMESTAMPTZ start_time "Start time of acquisition interruption"
        TIMESTAMPTZ end_time "End time when acquisition resumed"
        TEXT cause "Interruption reason (e.g. requested_stop, buffer_full)"
    }

    daq_telemetry {
        VIEW daq_telemetry "Compatibility view pointing to daq_production_samples WHERE provenance='physical_daq'"
    }

    daq_production_samples ||--o{ daq_telemetry : "projects"
```

**What this shows**:
- **`daq_production_samples`**: TimescaleDB hypertable partitioned by `time` with 1-hour chunks, holding validated physical sensor measurements with full calibration metadata, dual voltage/calibrated storage, and idempotent `(time, sample_id)` primary key.
- **`daq_production_gaps`**: Tracks missing-data intervals and fault causes (`buffer_full`, `requested_stop`, process crash) so dashboards display real acquisition gaps rather than interpolated data.
- **`daq_telemetry`**: A compatibility view exposing `daq_production_samples WHERE provenance = 'physical_daq'` to support legacy dashboard queries while ensuring 100% untraceable legacy and mockup rows are excluded.
