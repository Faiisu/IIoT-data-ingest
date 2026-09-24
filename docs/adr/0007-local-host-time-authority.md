# Use the local database host as the DAQ time authority

The DAQ card and PostgreSQL/TimescaleDB run on the same PC, which is the time authority for production records. Timestamp qualification compares DAQ sample position with this host's clock and verifies monotonic order and explicit acquisition gaps. Synchronization or shared-event comparison with another PC is outside the acceptance criteria because this PC is the main local database server.
