# DAQ Navi Service (Standalone Application)

This service provides hardware data acquisition for Advantech DAQ cards (PCI-1716, USB-4716), a durable SQLite spooling buffer with automatic offline replay, nanosecond-precision sample recording, TimescaleDB / InfluxDB 2.x delivery, and a Web-based Config Center with operator access control.

---

## 🚀 Standalone Deployment (1 Command)

This directory is completely self-contained. You can copy this folder to any Linux host with Docker installed and deploy it immediately:

```bash
docker compose up -d --build
```

### Configuration & Environment Variables

You can configure deployment options via an optional `.env` file in this directory:

```env
# Port for DAQ Web Config Center (Default: 8081)
DAQ_PORT=8081

# Origin of the central Portal (Default: http://localhost:8080)
PORTAL_ORIGIN=http://localhost:8080

# Operator credentials (PBKDF2 Salted Hash) & Session Signing Key
DAQ_OPERATOR_USER=operator
DAQ_OPERATOR_HASH=pbkdf2_sha256:100000:<salt_hex>:<hash_hex>
DAQ_SESSION_KEY=<random_32_bytes_key>
```

To generate operator hash and session key:
```bash
python3 -c "from web import auth; print(auth.hash_password('MySecretPassword'))"
python3 -c "import secrets; print(secrets.token_hex(32))"
```

---

## 📁 Directory Structure

```text
daq_navi/
├── Dockerfile          # Self-contained container build
├── compose.yml         # Standalone Docker Compose definition
├── entrypoint.sh       # Container entrypoint & hardware/mockup runner
├── requirements.txt    # Python dependencies
├── config.json         # Acquisition & channel settings
├── app.py              # Root application entrypoint
├── core/               # Production acquisition pipeline & durable spooler
├── web/                # Web Config Center (Flask + Socket.IO + Auth)
├── scripts/            # Database schema & maintenance scripts
├── tools/              # Utility & plotting scripts
└── tests/              # Unit & integration test suites
```

---

## 🔍 Health & Verification

Once started, verify service availability:
```bash
curl http://localhost:8081/api/health
```
Web Config Center is accessible at:
```text
http://<host-ip>:8081/
```
