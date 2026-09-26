# MUSASHI II Dispenser Ingestion & Control Service (Standalone Application)

Serial acquisition pipeline and Web Control Center for MUSASHI II adhesive dispensing systems. Provides automated polling, pressure and vacuum telemetry recording, local SQLite spooling, multi-database export (TimescaleDB / InfluxDB / MySQL), and real-time WebSocket dashboard.

---

## 🚀 Standalone Deployment (1 Command)

This directory is completely self-contained. You can copy this folder to any Linux host with Docker installed and deploy it immediately:

```bash
docker compose up -d --build
```

### Configuration & Environment Variables

You can configure deployment options via an optional `.env` file in this directory:

```env
# Web dashboard and API port (Default: 8082)
MUSASHI_II_PORT=8082
```

### Serial Hardware & Database Configuration

Acquisition and serial parameters are configured in `config.json`:

- **`serial`**: Serial port path (e.g. `/dev/ttyUSB0`), baud rate, parity, timeout.
- **`acquisition`**: Polling interval and mock simulation mode (`simulation: true` for development without physical hardware).
- **`database`**: Local SQLite buffering and destination database configuration (PostgreSQL/TimescaleDB, MySQL, InfluxDB).

To bind-mount serial devices into the container when running with physical hardware, add the device mapping in `compose.yml`:
```yaml
devices:
  - /dev/ttyUSB0:/dev/ttyUSB0
```

---

## 📁 Directory Structure

```text
musashi_ii/
├── Dockerfile          # Self-contained container build
├── compose.yml         # Standalone Docker Compose definition
├── requirements.txt    # Python runtime dependencies
├── config.json         # Serial communication & database settings
├── app.py              # Web application & Socket.IO server (port 8082)
├── read_musashi.py     # Background acquisition engine
├── database_handler.py # Storage abstraction (SQLite/TimescaleDB/InfluxDB/MySQL)
├── templates/          # HTML templates for Web UI
└── static/             # Static UI assets (CSS, JS)
```

---

## 🔍 Verification

Once started, access the Web Interface in your browser:
```text
http://<host-ip>:8082/
```

Or verify API health/status:
```bash
curl http://localhost:8082/api/status
```
