# MDDP Ingestion Control Suite — Windows Deployment Guide

> **Primary deployment is Docker-based (Linux).** This document covers Windows-only concerns:
> Advantech DAQNavi SDK setup, Windows Firewall rules, and the Musashi II/IV bare-metal services
> that are not yet containerized.

---

## Table of Contents

1. [Prerequisites](#1-prerequisites)
2. [Database & Broker Setup](#2-database--broker-setup)
3. [Docker Deployment (Recommended)](#3-docker-deployment-recommended)
4. [Musashi II / IV Bare-metal Services](#4-musashi-ii--iv-bare-metal-services)
5. [24-Hour Background Operation (Task Scheduler)](#5-24-hour-background-operation-task-scheduler)
6. [Watchdog & Crash Recovery](#6-watchdog--crash-recovery)
7. [Windows Firewall Configuration](#7-windows-firewall-configuration)
8. [Configuration Reference](#8-configuration-reference)
9. [Troubleshooting](#9-troubleshooting)
10. [Uninstalling](#10-uninstalling)

---

## 1. Prerequisites

### Required Software

| Software | Version | Purpose | Download |
|:---|:---|:---|:---|
| **Docker Desktop** | Latest | Run containerized stack | [docker.com/products/docker-desktop](https://www.docker.com/products/docker-desktop/) |
| **Python** | 3.9 or higher | Musashi II/IV bare-metal services | [python.org/downloads](https://www.python.org/downloads/) |
| **Advantech DAQNavi SDK** | Latest | USB-4716/PCI-1716 hardware driver | [Advantech Support](https://www.advantech.com/en/support/details/driver?id=1-RNKLZI) |
| **Git** *(optional)* | Latest | Clone project repository | [git-scm.com](https://git-scm.com/) |

### Advantech DAQNavi SDK Installation

1. Download and install the **DAQNavi SDK** from the Advantech Support website.
2. After installation, verify the device appears in **Advantech Navigator**.
3. Note the device description string (e.g., `PCI-1716,BID#0`) — it must match `DEVICE_DESCRIPTION` in `services\daq_navi\config.json`.

---

## 2. Database & Broker Setup

All database services (TimescaleDB, InfluxDB, Mosquitto) run inside Docker containers.
No separate installation is required on Windows.

```powershell
# Copy environment template
copy .env.example .env

# Start infrastructure containers
docker compose up -d timescaledb mqtt-broker influxdb
```

---

## 3. Docker Deployment (Recommended)

The DAQ Navi panel, Portal, and Plotter run as Docker containers.

```powershell
# Start full stack (dev mode — hot-reload via volume mount)
docker compose up -d

# Check health
docker compose ps
```

For **production mode** (baked image, no live mount):
```powershell
docker compose -f docker-compose.yml up -d
```

After editing `services\daq_navi\` Python files, the Werkzeug reloader restarts automatically in dev mode. After changing `Dockerfile` or `requirements.txt`, rebuild first:

```powershell
docker compose build daq-navi
docker compose up -d --force-recreate daq-navi
```

---

## 4. Musashi II / IV Bare-metal Services

Musashi II (port 8082) and Musashi IV (port 8083) are not yet containerized and must run directly with Python.

### Install Dependencies

```cmd
deploy\windows\install_deps.bat
```

### Start Manually

```cmd
# Musashi II
start /B python services\musashi_ii\app.py

# Musashi IV
start /B python services\musashi_iv\app.py
```

### Autostart via Task Scheduler

See [Section 5](#5-24-hour-background-operation-task-scheduler) for scheduled autostart of these services.

---

## 5. 24-Hour Background Operation (Task Scheduler)

Use Windows Task Scheduler to autostart Musashi II/IV on boot and run the watchdog.

### Setup (One-Time — Requires Administrator)

1. Open **PowerShell as Administrator**
2. Navigate to the project directory:
   ```powershell
   cd C:\MDDP
   ```
3. Allow script execution:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```
4. Run the setup script:
   ```powershell
   powershell -ExecutionPolicy Bypass -File .\deploy\windows\setup_task_scheduler.ps1
   ```

### Verify Scheduled Tasks

Open **Task Scheduler** → look for `MDDP_StartServices` and `MDDP_Watchdog`.

---

## 6. Watchdog & Crash Recovery

The watchdog script (`watchdog.ps1`) runs every 5 minutes and:

1. **Checks** if each service port (8080, 8081, 8083, 8084) has an active TCP listener
2. **Restarts** any service that is down
3. **Logs** all actions to `logs\watchdog.log`

### Manual Watchdog Check

```powershell
powershell -ExecutionPolicy Bypass -File .\deploy\windows\watchdog.ps1
```

### View Watchdog Log

```cmd
type logs\watchdog.log
```

---

## 7. Windows Firewall Configuration

To allow access from other machines on the network:

```powershell
# Run as Administrator
New-NetFirewallRule -DisplayName "MDDP Portal (8080)"    -Direction Inbound -Protocol TCP -LocalPort 8080 -Action Allow
New-NetFirewallRule -DisplayName "MDDP DAQ Panel (8081)" -Direction Inbound -Protocol TCP -LocalPort 8081 -Action Allow
New-NetFirewallRule -DisplayName "MDDP Musashi IV (8083)" -Direction Inbound -Protocol TCP -LocalPort 8083 -Action Allow
New-NetFirewallRule -DisplayName "MDDP Plotter (8084)"   -Direction Inbound -Protocol TCP -LocalPort 8084 -Action Allow
```

---

## 8. Configuration Reference

### services\daq_navi\config.json — Key Parameters

| Parameter | Default | Description |
|:---|:---|:---|
| `DEVICE_DESCRIPTION` | `PCI-1716,BID#0` | DAQ hardware identifier |
| `DESTINATION` | `postgresql` | Output mode: `postgresql`, `mqtt`, `influxdb` |
| `DB_DSN` | see `.env` | Production database DSN |
| `CLOCK_RATE` | `2000` | Samples per second per channel |
| `CHANNEL_COUNT` | `4` | Number of analog channels to scan |

### Service Ports

| Service | Port | Runtime |
|:---|:---|:---|
| Portal Gateway | 8080 | Docker (nginx) |
| DAQ Control Panel | 8081 | Docker (Flask) |
| Musashi II Panel | 8082 | Bare-metal Python |
| Musashi IV Panel | 8083 | Bare-metal Python |
| Plotter Visualizer | 8084 | Docker (Flask) |

---

## 9. Troubleshooting

### ⚠️ Port Conflict

**Symptom**: `address already in use`

**Solution**:
```cmd
for /f "tokens=5" %a in ('netstat -aon ^| findstr ":8081.*LISTENING"') do taskkill /f /pid %a
```

### ⚠️ TimescaleDB Connection Timeout

**Symptom**: `psycopg2.OperationalError: connection to server failed`

**Solution**:
```cmd
docker compose ps timescaledb
docker compose logs timescaledb
```

### ⚠️ Advantech DAQ Device Not Found

**Symptom**: `DAQ prepare() failed — check device connection`

**Solution**:
1. Open **Advantech Navigator** and verify device appears
2. Check `DEVICE_DESCRIPTION` in `config.json` matches exactly
3. Try resetting the USB/PCI connection

---

## 10. Uninstalling

### Remove Task Scheduler Tasks

```powershell
cd C:\MDDP
powershell -ExecutionPolicy Bypass -File .\deploy\windows\remove_task_scheduler.ps1
```

### Stop Docker Services

```powershell
docker compose down
```

### Remove Firewall Rules (If Created)

```powershell
Remove-NetFirewallRule -DisplayName "MDDP Portal (8080)"
Remove-NetFirewallRule -DisplayName "MDDP DAQ Panel (8081)"
Remove-NetFirewallRule -DisplayName "MDDP Musashi IV (8083)"
Remove-NetFirewallRule -DisplayName "MDDP Plotter (8084)"
```

### Delete Project Files

```cmd
rmdir /s /q C:\MDDP
```
