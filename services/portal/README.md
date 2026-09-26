# IIoT Portal Service (Standalone Application)

Central Industrial IoT web dashboard providing real-time subsystem monitoring, telemetry status, and unified navigation for DAQ-Navi, MUSASHI II, and MUSASHI IV.

---

## 🚀 Standalone Deployment (1 Command)

This directory is completely self-contained. You can copy this folder to any Linux host with Docker installed and deploy it immediately:

```bash
docker compose up -d --build
```

### Configuration & Environment Variables

You can configure deployment options via an optional `.env` file in this directory:

```env
# Host port to expose the central portal (Default: 8080)
PORTAL_PORT=8080
```

### Subsystem Endpoint Configuration

Subsystem endpoints and health polling are configured in `config.json`:

```json
{
  "daq": "http://localhost:8081",
  "musashi_ii": "http://localhost:8082",
  "musashi_iv": "http://localhost:8083"
}
```

If the services are hosted on different IPs or domain names, adjust `config.json` accordingly. Changes to `config.json` are mounted directly into the container and reflected immediately on browser refresh.

---

## 📁 Directory Structure

```text
portal/
├── Dockerfile          # Nginx Alpine container definition
├── compose.yml         # Standalone Docker Compose definition
├── config.json         # Subsystem URL endpoints
├── index.html          # Dashboard UI markup
├── app.js              # Real-time health polling & dynamic link binding
└── style.css           # Dashboard styling & responsiveness
```

---

## 🔍 Verification

Once started, access the Portal in your browser:
```text
http://<host-ip>:8080/
```
