# Production Storage Records

```mermaid
erDiagram
    daq_production_samples {
        TIMESTAMPTZ time PK
        TEXT sample_id PK
        UUID session_id
        TEXT device_id
        SMALLINT channel
        TEXT sensor_name
        DOUBLE_PRECISION raw_voltage
        DOUBLE_PRECISION calibrated_value
        TEXT unit
        TEXT provenance
    }
    daq_production_gaps {
        UUID gap_id PK
        TIMESTAMPTZ start_time
        TIMESTAMPTZ end_time
        TEXT cause
    }
```

The production destination manages the production sample hypertable and acquisition-gap records at runtime. The stable sample identity supports idempotent retries. The legacy schema initialized by `scripts/sql/db_setup.sql` includes separate tables such as `daq_telemetry`; it is not a view over `daq_production_samples` by virtue of this diagram. Consult the production destination implementation for the deployed schema details.
