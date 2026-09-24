# System Context Diagram

```mermaid
graph TB
  subgraph HW [Hardware Layer]
    DAQ["🔌 Advantech DAQ Card<br/>(PCI-1716,BID#0 / USB-4716)"]
  end

  subgraph STORAGE [Local Storage & Buffering]
    SpoolVol[("💾 Persistent Buffer Volume<br/>(daq_spool / SQLite zlib)")]
  end

  subgraph APP [DAQ Navi Service (Port 8081)]
    WebUI["🌐 Web GUI & REST API<br/>(services/daq_navi/web/app.py)"]
    Pipeline["⚡ Production Pipeline Daemon<br/>(services/daq_navi/core/production_acquisition.py)"]
  end

  subgraph DB [Database Layer (Port 5432)]
    TimescaleDB[("🗄️ TimescaleDB<br/>daq_production_samples<br/>daq_production_gaps<br/>daq_telemetry (view)")]
  end

  subgraph UI [Visualization & Client Services]
    Portal["🚪 Portal Gateway :8080"]
    Plotter["📈 Plotly Visualizer :8084"]
  end

  DAQ -->|Analog Voltage Signals| Pipeline
  Pipeline -->|1. Commit batches promptly| SpoolVol
  Pipeline -->|2. Drain & Replay batches| TimescaleDB
  Pipeline -->|3. Gap intervals & Health state| WebUI
  WebUI -->|Start / Stop / Config| Pipeline
  Portal -.->|Control Links| WebUI
  TimescaleDB -->|SQL Query daq_telemetry| Plotter
  TimescaleDB -->|SQL Query samples & gaps| WebUI
```

**What this shows**:
- The Advantech DAQ hardware (e.g. `PCI-1716,BID#0`) feeds physical sensor signals into the Python production pipeline daemon.
- Samples are first committed into a dedicated, persistent local SQLite disk buffer (`daq_spool` volume) with zlib compression, providing >24h local buffering during database outages.
- In-flight or buffered batches drain automatically to TimescaleDB (`daq_production_samples`) when the connection is healthy.
- Acquisition interruptions open gap records (`daq_production_gaps`) so graphs show missing segments.
- Downstream visualizers (Plotter) query the compatibility view `daq_telemetry` containing exclusively validated physical samples.
