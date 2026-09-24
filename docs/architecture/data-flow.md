# Data Flow Diagram

```mermaid
graph LR
  subgraph HW [Advantech DAQ Hardware]
    AI["Analog Input Channels (ch0-ch3)<br/>2,000 Hz / channel"]
  end

  subgraph Pipeline [Production Acquisition Pipeline]
    direction TB
    DAQReader["🧵 Acquisition Thread<br/>Advantech WaveformAiCtrl"]
    Spool[("💾 Local SQLite Spool Buffer<br/>zlib payload compression<br/>SPOOL_MAX_BYTES quota")]
    WriterThread["🧵 Spool Drain / Writer Thread<br/>Auto-replay & retry"]
    GapsTracker["⚠️ Gap Tracker<br/>Records missing intervals"]

    DAQReader -->|1. Read interleaved samples| AI
    DAQReader -->|2. Scale voltage & linear calibrate| DAQReader
    DAQReader -->|3. Commit batch immediately| Spool
    DAQReader -.->|On fault or full buffer| GapsTracker
    GapsTracker -->|Record start_ns / cause| Spool

    Spool -->|4. Oldest unacknowledged batch| WriterThread
    WriterThread -->|5. Bulk INSERT ON CONFLICT DO NOTHING| TimescaleDB
    WriterThread -->|6. Acknowledge & delete batch| Spool
  end

  subgraph Database [TimescaleDB]
    TimescaleDB[("🗄️ daq_production_samples<br/>(1-hr chunk hypertable)")]
    GapsTable[("⚠️ daq_production_gaps")]
    TelemetryView[("👁️ daq_telemetry (View)")]
  end

  subgraph Consumers [Dashboards & APIs]
    WebUI["🌐 DAQ Navi Web UI (:8081)<br/>/api/samples & /api/status"]
    Plotter["📈 Plotter Service (:8084)"]
  end

  WriterThread --> TimescaleDB
  WriterThread --> GapsTable
  TimescaleDB --- TelemetryView
  TimescaleDB --> WebUI
  GapsTable --> WebUI
  TelemetryView --> Plotter
```

**What this shows**:
1. **Acquisition**: Physical analog signals from channels 0–3 are captured at 2,000 Hz per channel. Raw voltage and calibrated values are calculated per sample.
2. **Buffering & Persistence**: Batches are committed immediately into a persistent SQLite spool file (`production-spool.sqlite3`) compressed with zlib. If TimescaleDB is down, capture continues uninterrupted for at least 24 hours.
3. **Replay & Idempotence**: The background writer thread reads unacknowledged batches from the spool and flushes them into `daq_production_samples` using `ON CONFLICT (time, sample_id) DO NOTHING`. Upon successful database commit, the batch is pruned from the spool.
4. **Gap Tracking**: Deliberate stops, driver errors, or buffer overflows create entries in `daq_production_gaps` to ensure gaps are rendered as blank intervals on charts.
5. **Consumption**: Web API (`/api/samples`) and Plotter query the hypertable and compatibility view `daq_telemetry`.
