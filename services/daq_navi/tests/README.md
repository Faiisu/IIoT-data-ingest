# Standalone DAQ script checks

Run the local script checks without touching production telemetry:

```bash
.venv/bin/python -m unittest discover -s services/daq_navi/tests -p 'test_production*.py' -v
.venv/bin/python -m unittest discover -s services/daq_navi/tests -p 'test_qualification_runner.py' -v
```

The TimescaleDB check skips unless `DAQ_TEST_DB_DSN` names an existing, isolated
database whose name starts with `daq_navi_test_`. With that variable set, rerun
the first command to check idempotent writes and retention policy reconciliation.
The legacy TimescaleDB policy tests have the same database guard.

On the host with the PCI-1716, use that isolated DSN for physical checks:

```bash
.venv/bin/python services/daq_navi/tests/qualify_standalone.py --rate 1000 --duration 30
.venv/bin/python services/daq_navi/tests/qualify_standalone.py --rate 2000 --duration 30
.venv/bin/python services/daq_navi/tests/qualify_outage_replay.py
.venv/bin/python services/daq_navi/tests/qualify_outage_replay.py --crash-first
```

These commands require `DAQ_TEST_DB_DSN` in the environment. They create unique
test tables and write reports under `.scratch/daq-navi-production/qualification/`.
They never stop the shared database or alter `daq_db.daq_telemetry`. The physical
run checks DAQ timing against this PC's clock, which is the local database host
and production time authority.

The local SQLite spool is the recovery boundary: a batch is replayable after
its disk commit. A process crash after a DAQ read but before that commit can
lose the in-flight batch. The outage runner verifies replay of committed
batches after process restart.
