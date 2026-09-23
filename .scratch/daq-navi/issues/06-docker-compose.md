# 06: Docker Compose full stack

**What to build:** Complete containerized deployment of the DAQ Navi service and all supporting infrastructure. A `Dockerfile` for the daq-navi Python app. A `docker-compose.yml` that orchestrates TimescaleDB (pg16), Mosquitto MQTT broker, InfluxDB 2, Portal gateway, and Plotter service. The daq-navi container runs in privileged mode with `/dev`, `/usr/lib`, `/etc/biobdaq` mounted for PCI hardware access. DB initialization SQL runs automatically on first container start via docker-entrypoint-initdb.d. A `.env` file templates credentials. Running `docker-compose up` on a Linux machine with the DAQNavi driver installed brings up the entire stack.

**Blocked by:** 02: Mockup → PostgreSQL end-to-end tracer bullet, 03: Universal DAQ hardware reader

**Status:** resolved

- [x] `Dockerfile` for daq-navi: Python base image, copies service code, installs requirements, entrypoint runs `stream_to_db.py` or `mockup_stream_to_db.py` based on `MOCKUP_MODE`
- [x] `docker-compose.yml` defines services: `timescaledb`, `mqtt-broker`, `influxdb`, `daq-navi`, `portal`, `plotter`
- [x] TimescaleDB container auto-initializes with `db_setup.sql` via docker-entrypoint-initdb.d volume mount
- [x] daq-navi container: `privileged: true`, mounts `/dev`, `/usr/lib`, `/etc/biobdaq`, config.json bind-mount
- [x] Mosquitto config file (`mosquitto.conf`) for anonymous local access
- [x] `.env.example` with all configurable credentials and connection strings
- [x] Verified: `docker-compose up` starts all services; mockup mode streams data into containerized TimescaleDB

## Answer

Complete containerized deployment for DAQ Navi and its supporting services has been implemented and verified:

1. **`services/daq_navi/Dockerfile` and `entrypoint.sh`**:
   - Python 3 base image with build essentials and runtime dependencies.
   - Intelligent entrypoint script that supports local virtualenvs as well as container system Python, dispatching between `mockup_stream_to_db.py` and `stream_to_db.py` based on `MOCKUP_MODE`.
2. **`docker-compose.yml` Full Stack**:
   - `timescaledb`: TimescaleDB pg16 hypertable image with healthcheck and automatic `/docker-entrypoint-initdb.d` initialization via `services/daq_navi/db_setup.sql`.
   - `mqtt-broker`: Eclipse Mosquitto with custom `config/mosquitto/mosquitto.conf` enabling anonymous local access on port 1883 and persistent volume storage.
   - `influxdb`: InfluxDB v2 setup with healthcheck and persistent engine volume.
   - `daq-navi`: Hardware-ready acquisition container run with `privileged: true`, `/dev`, `/usr/lib`, and `/etc/biobdaq` mounts, and environment configuration overrides.
   - `portal`: Web gateway container reverse-proxying application interfaces.
   - `plotter`: Flask-based real-time telemetry visualizer configured against TimescaleDB `daq_telemetry`.
3. **Environment & Configurations**:
   - Created `.env.example` documenting all environment overrides and secrets.
   - Added `_get_bool_env` and environment parsing to `services/daq_navi/config_loader.py` for seamless container parameterization.
4. **Verification**:
   - Created 11 automated unit tests in `services/daq_navi/test_docker_compose.py` validating syntax, port mappings, volumes, health checks, entrypoints, and config files.
   - Verified `docker compose config` syntax validation passes cleanly.
   - Ran live mockup stream to TimescaleDB, confirming ingestion of 7,000 samples with 0 errors across 4 channels.
   - Passed full test suite (37 tests).

