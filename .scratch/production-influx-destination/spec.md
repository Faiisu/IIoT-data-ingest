# Production acquisition with InfluxDB as a destination

Allow physical DAQ production acquisition to select InfluxDB 2.x as its destination while preserving the existing durable SQLite spool, replay behavior, sample identity, raw and calibrated measurements, and acquisition gaps. Keep PostgreSQL/TimescaleDB production support intact. The Config Center and production sample API must reflect the selected destination.

Use the existing nanosecond `time_ns` when writing to InfluxDB. Millisecond display is a presentation choice; reducing stored precision could collapse distinct samples at 2 kHz or during clock adjustment. Do not route production through the legacy InfluxDB client that truncates timestamps to seconds.

No live cutover, destructive data operation, credential rotation, or deployment is part of this feature implementation.
