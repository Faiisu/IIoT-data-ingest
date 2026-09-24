# System Context

```mermaid
graph LR
    Operator[Operator browser] --> Portal[Portal :8080]
    Operator --> DAQUI[DAQ Navi UI/API :8081]
    Portal -->|links| DAQUI
    DAQUI --> Control[DAQ Navi control process]
    Control --> Driver[Advantech BioDAQ SDK and physical card]
    Control --> Spool[(Persistent SQLite spool)]
    Spool --> Writer[Production database writer]
    Writer --> Production[(TimescaleDB production samples and gaps)]
    DAQUI --> Production
    Legacy[(Legacy/mockup tables)] -. separate schema/path .- DB[(PostgreSQL/TimescaleDB)]
```

Production acquisition requires the supported Linux host's DAQNavi driver and device. The persistent spool buffers batches for database delivery. Legacy/mockup tables are not a projection of the production hypertable unless the database is separately configured to provide one. MQTT and InfluxDB are included services, but their presence alone does not imply that the production acquisition path publishes data to them.
