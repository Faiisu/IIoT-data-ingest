# MDDP Ingestion Control Suite

The Multi-Device Data Ingestion Control Suite (MDDP) is a modular, high-performance software system designed to orchestrate and visualize time-series telemetry from hardware data acquisition systems (Advantech DAQNavi) dispensers.

This repository features:
- **Portal Gateway (Port 8080)**: Centralized industrial dashboard for navigation and auditing active device control panels.
- **DAQ Control Console & Web API (Port 8081)**: Dedicated Flask-SocketIO dashboard to configure, start, stop, calibrate channels, and audit telemetry streams with continuous gap rendering.
- **Database Plotter (Port 8084)**: Dynamic multi-chart grid workspace powered by Plotly.js, displaying time-series telemetry from TimescaleDB hypertables.

---

## 1. System Architecture & Operation Principles

### A. User Operation Flow
Shows how operators configure channels, execute production runs, inspect health, and view data.

```mermaid
graph LR
    Start([User Starts System]) --> ComposeUp[Docker Compose Up Stack]
    ComposeUp --> AccessPortal[Open Portal Gateway :8080]
    AccessPortal --> SelectDAQ[Select DAQ Control Panel :8081]
    
    SelectDAQ --> AdjustConfig[Configure Channels 0-3, Units & Calibration]
    AdjustConfig --> StartStream{Start Acquisition}
    
    StartStream -->|Production Mode| StartProd[Acquire from Physical DAQ Card]
    StartStream -->|Mockup Mode| StartMock[Acquire Synthetic Waveform]
    
    StartProd --> SpoolCommit[Commit to Local SQLite Buffer daq_spool]
    SpoolCommit --> TimescaleFlush[Async Flush to TimescaleDB daq_production_samples]
    StartMock --> MockFlush[Direct Flush to daq_mockup_telemetry]
    
    TimescaleFlush --> OpenPlotter[View Real-Time Data & Plotter :8084]
    MockFlush --> OpenPlotter
    
    style Start fill:#e1f5e1,stroke:#4caf50,color:#000
    style AccessPortal fill:#e3f2fd,stroke:#2196f3,color:#000
    style StartStream fill:#fff3e0,stroke:#ff9800,color:#000
    style SpoolCommit fill:#ede7f6,stroke:#673ab7,color:#000
    style TimescaleFlush fill:#e8f5e9,stroke:#2e7d32,color:#000
```

### B. Technical Architecture Diagram
Depicts the layered structure of the tech stack and data pathways across services.

```mermaid
graph LR
    subgraph "Presentation Layer"
        Portal[Portal Gateway<br/>Vanilla HTML / CSS / JS :8080]
        DAQView[DAQ Web Console<br/>Bootstrap + Socket.IO :8081]
        PlotView[Plotter UI<br/>Plotly.js :8084]
    end

    subgraph "Application & Service Layer"
        DAQGUISvc["DAQ Control Server & REST API<br/>services/daq_navi/web/app.py (Port 8081)"]
        ProductionPipeline["Production Pipeline Daemon<br/>services/daq_navi/core/production_acquisition.py"]
        PlotSvc["Analytics & Plotter Service<br/>Flask Stateless Web API (Port 8084)"]
    end

    subgraph "Local Storage & Persistence"
        SpoolVol[("💾 Persistent Spool Volume<br/>daq_spool / SQLite zlib")]
    end

    subgraph "Data & Messaging Layer"
        TimescaleDB[("🗄️ TimescaleDB / PostgreSQL (Port 5432)<br/>daq_production_samples<br/>daq_production_gaps<br/>daq_telemetry (View)")]
        MQTTBroker[MQTT Broker<br/>Port 1883]
    end

    Portal -.->|links| DAQView
    Portal -.->|links| PlotView

    DAQView -->|WebSockets & REST| DAQGUISvc
    DAQGUISvc -->|Subprocess Control| ProductionPipeline
    PlotView -->|REST queries| PlotSvc

    ProductionPipeline -->|1. Immediate commit| SpoolVol
    SpoolVol -->|2. Asynchronous replay/drain| ProductionPipeline
    ProductionPipeline -->|3. Bulk INSERT ON CONFLICT| TimescaleDB
    ProductionPipeline -.->|Optional publish| MQTTBroker
    PlotSvc -->|SELECT queries on daq_telemetry| TimescaleDB

    style Portal fill:#61dafb,stroke:#00d8ff,color:#000
    style DAQGUISvc fill:#ff6b6b,stroke:#ff0000,color:#000
    style SpoolVol fill:#9c27b0,stroke:#4a148c,color:#fff
    style TimescaleDB fill:#4caf50,stroke:#2e7d32,color:#000
    style MQTTBroker fill:#ff9800,stroke:#e65100,color:#000
```

---

## 2. Production Acquisition Features

- **High-Rate 4-Channel Acquisition**: Continuous sampling at up to 2,000 Hz per channel across channels 0–3 using Advantech BioDAQ SDK (`PCI-1716,BID#0`).
- **Resilient Local Spool Buffering**: All captured batches are committed first to a local SQLite buffer with zlib compression on the persistent `daq_spool` Docker volume (`128 GiB` quota). Supports over 24 hours (up to 7 days) of physical buffering during database outages without memory leaks or data loss.
- **Automatic Replay with Idempotence**: Background writer thread continuously flushes batches to TimescaleDB. Unique `(time, sample_id)` keys prevent duplicated samples upon network or database restoration.
- **Traceable Calibration & Raw Dual-Storage**: Stores both `raw_voltage` and `calibrated_value` alongside physical `unit` and `calibration_revision`. Historical records preserve original interpretation and allow reanalysis.
- **Explicit Acquisition Gap Tracking**: Distinguishes intentional stops, process crashes, and driver failures via `daq_production_gaps`. UI charts visually render discontinuities rather than false interpolated curves.
- **Strict Mockup Isolation**: Mockup runs require explicit operator selection and store telemetry in a segregated table (`daq_mockup_telemetry`), ensuring zero synthetic data in production views.
- **Compatibility View `daq_telemetry`**: Provides downstream visualizers (e.g. Plotter) seamless access to production data (`WHERE provenance = 'physical_daq'`) while eliminating untraceable legacy telemetry.
- **Configurable Retention**: Default 30-day raw retention enforced by TimescaleDB policies, adjustable dynamically via the Web UI (`/api/retention`).

---

## 3. Quick Start & Deployment

### Production Container Stack (Docker Compose)

Launch all microservices (TimescaleDB, Mosquitto, InfluxDB, Portal, Plotter, and DAQ Navi):

```bash
docker compose up -d
```

Verify service health:
```bash
docker compose ps
curl http://localhost:8081/api/health
```

Access web applications in your browser:
- **Portal Gateway**: `http://localhost:8080`
- **DAQ Control Console**: `http://localhost:8081`
- **Database Plotter**: `http://localhost:8084`

---

## 4. Configuration Reference

The acquisition pipeline is configured via [`services/daq_navi/config.json`](services/daq_navi/config.json) and managed via the Web UI.

### Hardware & Sampling Settings
| Parameter | Default | Description |
|:---|:---|:---|
| `DEVICE_DESCRIPTION` | `PCI-1716,BID#0` | Hardware device identifier for Advantech BioDAQ driver. |
| `START_CHANNEL` | `0` | Starting physical analog input channel index. |
| `CHANNEL_COUNT` | `4` | Number of enabled analog input channels (0 to 3). |
| `CLOCK_RATE` | `2000` | Sampling frequency in Hz per channel. |
| `SECTION_LENGTH` | `500` | Hardware acquisition section length (samples per channel per read). |

### Storage & Retention Parameters
| Parameter | Default | Description |
|:---|:---|:---|
| `DESTINATION` | `postgresql` | Primary storage backend (`postgresql` / `timescaledb`). |
| `DB_DSN` | `postgresql://admin:admin@timescaledb:5432/daq_db` | Connection DSN string for TimescaleDB. |
| `DB_PRODUCTION_TABLE` | `daq_production_samples` | Hypertable storing physical production telemetry. |
| `DB_MOCKUP_TABLE` | `daq_mockup_telemetry` | Segregated table for synthetic mockup data. |
| `DB_RETENTION_DAYS` | `30` | Rolling raw telemetry retention window in days. |
| `SPOOL_DIR` | `/var/lib/daq_navi/spool` | Path to persistent SQLite disk buffer. |
| `SPOOL_MAX_BYTES` | `137438953472` | Spool disk buffer capacity quota (128 GiB). |

### Channel Calibration Schema (`CHANNELS`)
Every enabled channel specifies sensor labeling, voltage input range, and linear scaling:
```json
"CHANNELS": {
  "0": {
    "enabled": true,
    "label": "pressure-ch0",
    "unit": "kPa",
    "signal_type": "SingleEnded",
    "value_range": "V_0To5",
    "scale": {
      "enabled": true,
      "low_voltage": 1.0,
      "high_voltage": 5.0,
      "low_value": -100.0,
      "high_value": 100.0,
      "revision": "initial"
    }
  }
}
```

---

## 5. Web Control & REST API

| Endpoint | Method | Description |
|:---|:---|:---|
| `/api/status` | `GET` | Returns runtime health, running state, buffer bytes, pending replay count, and recent gaps. |
| `/api/health` | `GET` | Healthcheck probe; returns `200 OK` when healthy, `503 Service Unavailable` on faults or stopped expected runs. |
| `/api/config` | `GET` | Retrieves effective saved acquisition configuration. |
| `/api/config` | `POST` | Updates and validates configuration settings (preserves existing settings and applies changes safely). |
| `/api/start` | `POST` | Starts physical production (`mode: "production"`) or synthetic mockup (`mode: "mockup"`). |
| `/api/stop` | `POST` | Drains pending buffers and gracefully halts acquisition. |
| `/api/samples?channel=N` | `GET` | Queries recent production samples with voltage, calibrated values, units, and gap boundaries. |
| `/api/retention` | `GET` | Returns active TimescaleDB hypertable retention policy. |

---

## 6. Testing & Quality Verification

Run unit test suites:
```bash
# Web UI and REST API tests (41 tests)
docker exec daq_navi python3 -m unittest tests.test_production_web -v

# Core acquisition, timing, and buffer tests (22 tests)
PYTHONPATH=. .venv/bin/python -m unittest services/daq_navi/tests/test_production_acquisition.py

# End-to-end fault and outage qualification scripts
PYTHONPATH=. DAQ_TEST_DB_DSN="postgresql://admin:admin@localhost:5432/daq_navi_test_*" .venv/bin/python services/daq_navi/tests/qualify_web_faults.py
```
