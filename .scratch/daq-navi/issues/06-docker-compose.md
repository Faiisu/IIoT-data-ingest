# 06: Docker Compose full stack

**What to build:** Complete containerized deployment of the DAQ Navi service and all supporting infrastructure. A `Dockerfile` for the daq-navi Python app. A `docker-compose.yml` that orchestrates TimescaleDB (pg16), Mosquitto MQTT broker, InfluxDB 2, Portal gateway, and Plotter service. The daq-navi container runs in privileged mode with `/dev`, `/usr/lib`, `/etc/biobdaq` mounted for PCI hardware access. DB initialization SQL runs automatically on first container start via docker-entrypoint-initdb.d. A `.env` file templates credentials. Running `docker-compose up` on a Linux machine with the DAQNavi driver installed brings up the entire stack.

**Blocked by:** 02: Mockup → PostgreSQL end-to-end tracer bullet, 03: Universal DAQ hardware reader

**Status:** ready-for-agent

- [ ] `Dockerfile` for daq-navi: Python base image, copies service code, installs requirements, entrypoint runs `stream_to_db.py` or `mockup_stream_to_db.py` based on `MOCKUP_MODE`
- [ ] `docker-compose.yml` defines services: `timescaledb`, `mqtt-broker`, `influxdb`, `daq-navi`, `portal`, `plotter`
- [ ] TimescaleDB container auto-initializes with `db_setup.sql` via docker-entrypoint-initdb.d volume mount
- [ ] daq-navi container: `privileged: true`, mounts `/dev`, `/usr/lib`, `/etc/biobdaq`, config.json bind-mount
- [ ] Mosquitto config file (`mosquitto.conf`) for anonymous local access
- [ ] `.env.example` with all configurable credentials and connection strings
- [ ] Verified: `docker-compose up` starts all services; mockup mode streams data into containerized TimescaleDB
