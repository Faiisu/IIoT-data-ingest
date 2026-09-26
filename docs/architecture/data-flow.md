# Production Data Flow

1. The operator configures the device, channel span, signal types, voltage ranges, calibration, and destination (PostgreSQL/TimescaleDB or InfluxDB 2.x) through DAQ Navi.
2. The control service starts the production acquisition process. It opens the configured Advantech device and requests waveform input using the saved sampling and section parameters.
3. The process converts hardware reads into timestamped per-channel records, retaining raw voltage and the configured calibrated value.
4. Each batch is compressed and committed to the persistent SQLite spool before it is eligible for destination delivery.
5. A background writer delivers pending batches to the configured destination (PostgreSQL/TimescaleDB production table or InfluxDB 2.x line-protocol measurement). Acknowledgement/removal from the spool follows a successful write; failed writes remain pending for retry.
6. The service records acquisition interruptions in the production gaps table (or `daq_acquisition_gaps` measurement in InfluxDB). The spool size is bounded by configuration; elapsed outage coverage depends on actual sample volume and available capacity.
7. DAQ Navi status and sample endpoints expose runtime state and recent production records.

Mockup and legacy telemetry follow separate paths and schemas. Do not infer production delivery from mockup rows or from the existence of the legacy `daq_telemetry` table.
