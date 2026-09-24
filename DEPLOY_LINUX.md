# Linux Deployment Guide

This repository runs its services with Docker Compose. Physical DAQ acquisition requires a Linux host where the Advantech BioDAQ SDK, libraries, device files, and configuration are installed and visible at the paths mounted by Compose.

## Prepare

- Install Docker Engine and the Docker Compose plugin.
- For physical acquisition, install and configure the Advantech DAQNavi/BioDAQ driver on the host and confirm the device is visible there.
- Clone the repository, then prepare environment settings:

```bash
cp .env.example .env
```

Edit `.env` and replace all demo credentials/tokens before exposing the services. Review `services/daq_navi/config.json` for the device, channel span, signal types, input ranges, calibration, and destination. The checked-in values may not match the installed hardware.

## Start and operate

The default `docker-compose.override.yml` adds development mounts and settings:

```bash
docker compose up -d
docker compose ps
curl http://localhost:8081/api/health
```

Use the portal at `http://localhost:8080`, DAQ Navi at `http://localhost:8081`, and Plotter at `http://localhost:8084`. Development mounts make source visible inside containers; restart the affected service if a code change does not take effect. For the base Compose file without the override:

```bash
docker compose -f docker-compose.yml up -d --build
```

Useful operations:

```bash
docker compose logs -f daq-navi
docker compose restart daq-navi
docker compose down
```

`docker compose down` preserves named database and spool volumes. `docker compose down -v` deletes those volumes and their data.

## Physical DAQ access

The `daq-navi` service is privileged and mounts `/dev`, `/usr/lib`, `/opt/advantech`, `/etc/biobdaq`, and `/var/lib/daq` from the host. Install the vendor SDK and libraries in those host locations as required by the driver package. Confirm the host OS and installed SDK are supported by Advantech. Docker cannot supply a missing host driver.

Start production acquisition only after checking the saved configuration, signal wiring, channel mode, destination connection, and device scan. `MOCKUP_MODE` controls the Compose environment default; the saved configuration and selected mode in the DAQ service also matter. Read status after starting and verify samples reach the intended production table.

## Services and ports

| Service | Default host port |
|:---|---:|
| Portal | 8080 |
| DAQ Navi | 8081 |
| TimescaleDB/PostgreSQL | 5432 |
| Mosquitto | 1883 |
| InfluxDB | 8086 |
| Plotter | 8084 |

Port mappings can be changed with the corresponding variables in `.env`. Database and broker ports are published by default; restrict them with host firewall/network rules when they are not needed by other machines. The web interfaces do not provide authentication in this stack, so do not expose them to an untrusted network without adding access control.

## Optional host setup helpers

`deploy/linux/install_deps.sh`, `scripts/setup_wizard.sh`, `deploy/linux/setup_systemd.sh`, and `deploy/linux/setup_systemd_docker.sh` are host setup helpers. Inspect the selected script before running it and use only the helper matching your installation. The systemd helpers require administrator privileges. They are not required for a manual `docker compose up` deployment.
