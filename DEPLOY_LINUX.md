# Linux Deployment Guide

Linux is the only supported deployment host for these Compose projects. The DAQ service mounts Linux host device files and Advantech libraries into its container. Physical acquisition also requires the supported Advantech BioDAQ SDK, driver, hardware, and configuration on that host. Windows deployment is not supported.

## Prepare

- Install Docker Engine and the Docker Compose plugin.
- For physical acquisition, install and configure the Advantech DAQNavi/BioDAQ driver on the host and confirm the device is visible there.
- Clone the repository, then prepare environment settings:

```bash
cp .env.example .env
cp deploy/daq-navi/.env.example deploy/daq-navi/.env
cp deploy/portal/.env.example deploy/portal/.env
mkdir -p deploy/daq-navi/config
cp services/daq_navi/config.json deploy/daq-navi/config/config.json
```

Edit the root `.env` for TimescaleDB, Mosquitto, and InfluxDB; replace all demo credentials and tokens. The two files under `deploy/` set DAQ and Portal host ports independently. Portal links and polling ports live in `services/portal/config.json`; update its `daq` entry when changing `DAQ_PORT`. Review the private `deploy/daq-navi/config/config.json` for the device, channel span, signal types, input ranges, calibration, and destination. Its saved `DB_DSN` must match the database credentials in the root `.env` and use host `timescaledb` for this Docker network. For InfluxDB, use host `influxdb` on this Docker network, with the organization, bucket, and token from the infrastructure installation. The checked-in values may not match the installed hardware. The private DAQ config directory is ignored by Git and mounted at `/app/config`; atomic saves replace `config.json` inside that directory.

## Start and operate

The root Compose project starts only TimescaleDB, Mosquitto, and InfluxDB. DAQ Navi and Portal have independent Compose projects. Create the DAQ spool volume once on a new host; an existing volume with this name is reused.

```bash
docker compose -f docker-compose.yml up -d
docker volume create iiot-data-ingest_daq_spool
docker compose --env-file deploy/daq-navi/.env -f deploy/daq-navi/compose.yml up -d --build
docker compose --env-file deploy/portal/.env -f deploy/portal/compose.yml up -d
docker compose ps
docker compose --env-file deploy/daq-navi/.env -f deploy/daq-navi/compose.yml ps
docker compose --env-file deploy/portal/.env -f deploy/portal/compose.yml ps
curl http://localhost:8081/api/health
```

Use the Portal at `http://localhost:8080` and DAQ Config Center at `http://localhost:8081`; DAQ APIs use the same port. To use development source mounts and Flask debugging, add the DAQ override:

```bash
docker compose --env-file deploy/daq-navi/.env -f deploy/daq-navi/compose.yml -f deploy/daq-navi/compose.dev.yml up -d --build
```

Manage each project with its own Compose file:

```bash
docker compose --env-file deploy/daq-navi/.env -f deploy/daq-navi/compose.yml logs -f daq-navi
docker compose --env-file deploy/daq-navi/.env -f deploy/daq-navi/compose.yml restart daq-navi
docker compose --env-file deploy/portal/.env -f deploy/portal/compose.yml restart portal
docker compose -f docker-compose.yml ps
```

Stopping DAQ or Portal this way does not stop the infrastructure project. The DAQ spool is an external volume in its Compose file, so DAQ project removal does not delete it. Avoid `down -v` on the infrastructure project when preserving database volumes.

### Migrate an existing private DAQ config mount

The DAQ project now bind mounts `deploy/daq-navi/config/` as a directory. On an existing installation, stop acquisition through Config Center and check pending batches. Preserve the current file and the external spool volume. Copy the old file into the new directory, keep it private, and compare the copy before recreating the container:

```bash
mkdir -p deploy/daq-navi/config
cp -a deploy/daq-navi/config.local.json deploy/daq-navi/config/config.json
chmod 600 deploy/daq-navi/config/config.json
cmp deploy/daq-navi/config.local.json deploy/daq-navi/config/config.json
docker volume inspect iiot-data-ingest_daq_spool
```

If the new container fails its health check, stop that container, change the Compose mount and `DAQ_CONFIG_PATH` back to the previous file mount, then recreate the previous image. Retain both config copies until acquisition, destination, operator authentication, and API readback have been checked. Rollback never deletes or recreates the spool volume.

### Cutover from the former combined stack

The old stack used the same project name, container names, infrastructure network, and `iiot-data-ingest_daq_spool` volume. Before starting the independent projects on an existing host, stop acquisition from the DAQ Config Center and check pending batches. Then remove the old DAQ and Portal containers while leaving infrastructure and volumes intact:

```bash
docker compose -f docker-compose.yml up -d --remove-orphans
docker volume inspect iiot-data-ingest_daq_spool
docker compose --env-file deploy/daq-navi/.env -f deploy/daq-navi/compose.yml up -d --build
docker compose --env-file deploy/portal/.env -f deploy/portal/compose.yml up -d
```

`--remove-orphans` removes the old DAQ and Portal containers from the infrastructure project; it does not remove the spool volume. Review the two new Compose configurations and saved DAQ settings before cutover. Do not run this cutover while acquisition is active.

## Physical DAQ access

The `daq-navi` service is privileged and mounts `/dev`, `/usr/lib`, `/opt/advantech`, `/etc/biobdaq`, and `/var/lib/daq` from the host. Install the vendor SDK and libraries in those host locations as required by the driver package. Confirm the host OS and installed SDK are supported by Advantech. Docker cannot supply a missing host driver.

Start production acquisition only after checking the saved configuration, signal wiring, channel mode, destination connection, and device scan. The saved `MOCKUP_MODE` and selected mode in the DAQ service control acquisition. Read status after starting and verify samples reach the intended production table.

## Services and ports

| Service | Default host port |
|:---|---:|
| Portal | 8080 |
| DAQ Config Center / DAQ Navi API | 8081 |
| TimescaleDB/PostgreSQL | 5432 |
| Mosquitto | 1883 |
| InfluxDB | 8086 |

Infrastructure port mappings are in the root `.env`; DAQ and Portal host ports are in their files under `deploy/`. Database and broker ports are published by default; restrict them with host firewall/network rules when they are not needed by other machines. The web interfaces do not provide authentication, so do not expose them to an untrusted network without adding access control.

## Optional host setup helpers

`deploy/linux/install_deps.sh` and `scripts/setup_wizard.sh` are host setup helpers. Inspect the selected script before running it and use only the helper matching your installation. They are not required for a manual `docker compose up` deployment.
