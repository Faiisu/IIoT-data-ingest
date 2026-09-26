# MUSASHI IV Dispenser API & Stream Service (Standalone Application)

Telemetry ingestion client and Web Control Center for MUSASHI IV advanced shot dispensing systems. Connects to dispenser REST APIs, streams operational parameters to TimescaleDB / InfluxDB, includes a mock dispenser simulator, and provides a real-time Web dashboard on port 8083.

---

## 🚀 Standalone Deployment (1 Command)

This directory is completely self-contained. You can copy this folder to any Linux host with Docker installed and deploy it immediately:

```bash
docker compose up -d --build
```

### Configuration & Environment Variables

You can configure deployment options via an optional `.env` file in this directory:

```env
# Web dashboard and API port (Default: 8083)
MUSASHI_IV_PORT=8083
```

### API Endpoint & Database Configuration

Communication parameters and destination databases are configured in `config.json`:

- **`api_endpoint`**: MUSASHI IV hardware controller API URL (or local mock server).
- **`polling_interval`**: Query frequency in seconds.
- **`destinations`**: TimescaleDB and InfluxDB credentials and table definitions.

---

## 📁 Directory Structure

```text
musashi_iv/
├── Dockerfile          # Self-contained container build
├── compose.yml         # Standalone Docker Compose definition
├── requirements.txt    # Python runtime dependencies
├── config.json         # API endpoint & database credentials
├── app.py              # Web application & Socket.IO server (port 8083)
├── api_client.py       # REST API communication client
├── stream_to_db.py     # Background streaming & database writer
├── mock_api_server.py  # Local mock server for development
├── templates/          # HTML templates for Web UI
└── static/             # Static UI assets (CSS, JS)
```

---

## 🔍 Verification

Once started, access the Web Interface in your browser:
```text
http://<host-ip>:8083/
```

Or check status endpoint:
```bash
curl http://localhost:8083/api/status
```
