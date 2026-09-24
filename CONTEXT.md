# Industrial data acquisition

This context covers sensor acquisition through an Advantech DAQ card and the telemetry recorded from it.

## Language

**Production acquisition**: A run that measures physical sensor values through the DAQ card for operational records. Avoid “real mode.”

**Mockup acquisition**: A run that generates synthetic sensor values for demonstration or testing. Avoid “fallback data.”

**DAQ sample**: One measurement from one physical input channel at a particular sampling instant.

**Raw voltage**: The electrical value read from a DAQ input channel before sensor calibration.

**Calibrated measurement**: A DAQ sample converted from raw voltage into the physical unit defined by that channel's calibration.

**Acquisition gap**: An interval during which production acquisition could not record physical samples. Represent it as missing data, not synthetic values.

## System boundaries

Production capture uses Advantech DAQNavi/BioDAQ hardware access available to the Linux host, stores batches in a persistent local SQLite spool, and delivers them to the configured PostgreSQL/TimescaleDB destination. The production sample and gap records are separate from legacy/mockup telemetry tables. Do not describe `daq_telemetry` as a view of production data unless the deployed database explicitly defines such a view.
