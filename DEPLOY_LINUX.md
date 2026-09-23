# MDDP Ingestion Control Suite — Linux Deployment Guide

All services run as Docker containers. The `docker-compose.override.yml` file enables **dev mode** (hot-reload via volume mount) automatically when you run `docker compose up`. For production (baked image, no mount), pass `-f docker-compose.yml` explicitly.

---

## Quick Start

```bash
# Clone repository
git clone <repository-url>
cd IIoT-data-ingest

# Copy and edit environment file
cp .env.example .env

# Start full stack (dev mode — auto-reload enabled)
docker compose up -d

# Verify health
docker compose ps
curl http://localhost:8081/api/status
```

---

## Table of Contents

1. [Prerequisites](#1-prerequisites)
2. [Configuration](#2-configuration)
3. [Dev Mode vs Production Mode](#3-dev-mode-vs-production-mode)
4. [Service Startup & Management](#4-service-startup--management)
5. [24/7 Autostart (Systemd)](#5-247-autostart-systemd)
6. [Hardware (Advantech PCI/USB DAQ)](#6-hardware-advantech-pciusb-daq)
7. [Service Access & Ports](#7-service-access--ports)
8. [Viewing Logs & Diagnostics](#8-viewing-logs--diagnostics)
9. [Stopping Services](#9-stopping-services)

---

## 1. Prerequisites

- **Docker Engine** ≥ 24 and **Docker Compose** plugin
- **Git**
- (Real hardware) Advantech DAQNavi SDK driver installed on the host

Install Docker:
```bash
./deploy/linux/install_deps.sh
```

---

## 2. Configuration

Copy the environment template and edit credentials:
```bash
cp .env.example .env
```

Edit `services/daq_navi/config.json` to match your hardware/DB settings:
```json
{
  "DEVICE_DESCRIPTION": "PCI-1716,BID#0",
  "DESTINATION": "postgresql",
  "CLOCK_RATE": 2000,
  "CHANNEL_COUNT": 4
}
```

---

## 3. Dev Mode vs Production Mode

| | **Dev mode** (default) | **Production mode** |
|---|---|---|
| Command | `docker compose up -d` | `docker compose -f docker-compose.yml up -d` |
| Source code | Volume-mounted from host — edit & reload in place | Baked into image at build time |
| Flask debug | ✅ Auto-reload on file save | ❌ Off |
| Rebuild needed? | ❌ No | ✅ Yes (`docker compose build`) |
| When to use | Active development | Stable release / production server |

**Dev mode** is activated automatically by `docker-compose.override.yml`. This file mounts `./services/daq_navi` into the container and sets `FLASK_DEBUG=1`, so Werkzeug restarts the server whenever you save a Python file.

---

## 4. Service Startup & Management

```bash
# Start all services (dev mode)
docker compose up -d

# Rebuild image after Dockerfile or requirements.txt changes, then start
docker compose build daq-navi && docker compose up -d --force-recreate daq-navi

# Restart a single service
docker compose restart daq-navi

# View live status
docker compose ps
```

---

## 5. 24/7 Autostart (Systemd)

To launch the Docker stack automatically on boot, use the provided systemd unit:

```bash
# One-time setup (requires sudo)
sudo ./deploy/linux/setup_systemd_docker.sh

# Manage via systemctl
sudo systemctl status mddp
sudo systemctl start mddp
sudo systemctl stop mddp
sudo systemctl restart mddp
```

Docker's own `restart: unless-stopped` policy also handles individual container crash recovery automatically.

---

## 6. Hardware (Advantech PCI/USB DAQ)

Set `MOCKUP_MODE=false` in `.env` for real hardware. The container already has the necessary device mounts:

```yaml
# docker-compose.yml (already configured)
privileged: true
volumes:
  - /dev:/dev
  - /usr/lib:/usr/lib:ro
  - /opt/advantech:/opt/advantech:ro
  - /etc/biobdaq:/etc/biobdaq:ro
```

Ensure the host user can access DAQ devices:
```bash
sudo usermod -aG dialout,plugdev $USER
```

For guided production setup on a fresh server (kernel check, driver install, Docker install):
```bash
./deploy/linux/setup_wizard.sh
```

---

## 7. Service Access & Ports

| Service | Port | URL |
|:---|:---|:---|
| **Portal Gateway** | `8080` | http://localhost:8080 |
| **DAQ Control Panel** | `8081` | http://localhost:8081 |
| **Musashi II Panel** | `8082` | http://localhost:8082 *(bare-metal)* |
| **Musashi IV Panel** | `8083` | http://localhost:8083 *(bare-metal)* |
| **Database Plotter** | `8084` | http://localhost:8084 |
| **TimescaleDB** | `5432` | postgresql://... |
| **MQTT Broker** | `1883` | mqtt://... |
| **InfluxDB** | `8086` | http://localhost:8086 |

> **Note**: Musashi II/IV are bare-metal services (not Dockerized).

---

## 8. Viewing Logs & Diagnostics

```bash
# Follow DAQ panel logs
docker compose logs -f daq-navi

# Follow all services
docker compose logs -f

# One-shot watchdog health check
./deploy/linux/watchdog.sh --oneshot
```

---

## 9. Stopping Services

```bash
# Stop all containers (data volumes preserved)
docker compose down

# Stop + remove volumes (full reset — deletes DB data)
docker compose down -v
```
