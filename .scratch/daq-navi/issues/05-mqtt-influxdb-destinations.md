# 05: MQTT + InfluxDB output destinations

**What to build:** Alternative output paths so the pipeline can publish telemetry to MQTT and InfluxDB in addition to PostgreSQL. The refactored `MQTTClient` includes `device_id` in every JSON payload so subscribers can filter by device. The refactored `InfluxDBClient` tags each point with `device_id`. Destination selection via `DESTINATION` field in config (`postgresql`, `mqtt`, `influxdb`). All three clients share the same `send_samples(rows, page_size)` interface so the writer thread doesn't need destination-specific logic.

**Blocked by:** 02: Mockup → PostgreSQL end-to-end tracer bullet

**Status:** ready-for-agent

- [ ] `MQTTClient.send_samples()` includes `device_id` in each JSON object: `{"time": "...", "device_id": "pci1716-0", "channel": 0, "value": 2.45}`
- [ ] `InfluxDBClient` tags each line protocol point with `device_id`: `daq_telemetry,device_id=pci1716-0,ch=0 voltage=2.45,scaled=50.0 <ts>`
- [ ] `DESTINATION` config field selects the active output client
- [ ] MQTT connection parameters read from config (broker, port, topic, QoS, TLS settings)
- [ ] InfluxDB parameters read from config (URL, org, bucket, token)
- [ ] Verified: mockup with `DESTINATION=mqtt` produces JSON with `device_id` on broker; `DESTINATION=influxdb` writes tagged points
