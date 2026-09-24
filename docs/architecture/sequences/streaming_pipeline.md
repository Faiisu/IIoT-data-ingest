# Production Acquisition Sequence

```mermaid
sequenceDiagram
    actor Operator
    participant Web as DAQ Navi UI/API
    participant Process as Acquisition process
    participant DAQ as Advantech device
    participant Spool as SQLite spool
    participant Writer as Database writer
    participant DB as PostgreSQL/TimescaleDB

    Operator->>Web: Start production acquisition
    Web->>Process: Launch with saved configuration
    Process->>DAQ: Prepare and start waveform input
    loop Each acquired section
        Process->>DAQ: Read configured channel span
        DAQ-->>Process: Raw voltage values
        Process->>Process: Timestamp and calibrate samples
        Process->>Spool: Append compressed batch and commit
    end
    loop Pending batches
        Writer->>Spool: Read oldest pending batch
        Spool-->>Writer: Batch records
        Writer->>DB: Insert production samples
        alt Database write succeeds
            DB-->>Writer: Commit success
            Writer->>Spool: Acknowledge batch
        else Database unavailable/write fails
            DB-->>Writer: Error
            Note over Writer,Spool: Keep pending batch for retry, within spool capacity
        end
    end
    Process-->>Web: Runtime status
    Web->>DB: Query recent samples or retention policy
    DB-->>Web: Query result
```

The exact start and stop behavior depends on the saved configuration and process state. Acquisition gaps are persisted separately; status and sample APIs expose runtime/database information but are not a substitute for checking that expected rows are arriving at the destination.
