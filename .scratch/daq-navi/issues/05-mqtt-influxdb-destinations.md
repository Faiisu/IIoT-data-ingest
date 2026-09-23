# 05: MQTT + InfluxDB output destinations

**What to build:** Alternative output paths so the pipeline can publish telemetry to MQTT and InfluxDB in addition to PostgreSQL. The refactored `MQTTClient` includes `device_id` in every JSON payload so subscribers can filter by device. The refactored `InfluxDBClient` tags each point with `device_id`. Destination selection via `DESTINATION` field in config (`postgresql`, `mqtt`, `influxdb`). All three clients share the same `send_samples(rows, page_size)` interface so the writer thread doesn't need destination-specific logic.

**Blocked by:** 02: Mockup → PostgreSQL end-to-end tracer bullet

**Status:** resolved

- [x] `MQTTClient.send_samples()` includes `device_id` in each JSON object: `{"time": "...", "device_id": "pci1716-0", "channel": 0, "value": 2.45}`
- [x] `InfluxDBClient` tags each line protocol point with `device_id`: `daq_telemetry,device_id=pci1716-0,ch=0 voltage=2.45,scaled=50.0 <ts>`
- [x] `DESTINATION` config field selects the active output client
- [x] MQTT connection parameters read from config (broker, port, topic, QoS, TLS settings)
- [x] InfluxDB parameters read from config (URL, org, bucket, token)
- [x] Verified: mockup with `DESTINATION=mqtt` produces JSON with `device_id` on broker; `DESTINATION=influxdb` writes tagged points

## Answer

### What was built
1. **MQTT Output Destination (`MQTTClient`)**:
   - Refactored `send_samples(rows, page_size=1000)` to format each sample into JSON payload with `{"time": "...", "device_id": "pci1716-0", "channel": 0, "value": 2.45}`.
   - Chunks batches into `page_size` increments via shared helper `_chunk_rows()`.
   - Supports QoS, username/password, and full TLS/mTLS parameters (`MQTT_TLS_ENABLED`, `MQTT_CA_CERTS`, `MQTT_CLIENT_CERT`, `MQTT_CLIENT_KEY`).
   - Unified connection and disconnect handling for paho-mqtt v1/v2 callbacks.

2. **InfluxDB Output Destination (`InfluxDBClient`)**:
   - Implemented `format_line(row)` generating InfluxDB 2.x Line Protocol points tagged with `device_id` and channel: `daq_telemetry,device_id=pci1716-0,ch=0 voltage=2.45,scaled=50.0 <ts>`.
   - Implemented `send_samples(rows, page_size=1000)` executing chunked HTTP POST requests against `/api/v2/write?org={org}&bucket={bucket}&precision=s` with Token authentication.
   - Health check validation via `/health` with boolean `is_connected` status tracking.

3. **Unified Client Interface & Destination Factory**:
   - Extracted `create_destination_client(config, stop_event)` factory in `stream_to_db.py`, shared by both `stream_to_db.py` and `mockup_stream_to_db.py`.
   - Destination selection driven by `DESTINATION` config setting (`postgresql`, `mqtt`, `influxdb`).
   - All three clients (`TimescaleDBClient`, `MQTTClient`, `InfluxDBClient`) share identical signatures:
     - `send_samples(rows, page_size=1000)`
     - `rollback()`
     - `disconnect()`
     - `is_connected` (property/attribute)
   - Writer thread error recovery and reconnect logic eliminated all destination-specific branching.

### Verification
- **Unit & Mockup Tests (`test_destinations.py`)**:
  - `test_destination_selection_factory`: Config parameter mapping and instantiation across all 3 destination types.
  - `test_shared_client_interface`: Verified shared duck typing interface.
  - `test_mqtt_client_send_samples_includes_device_id`: Verified JSON formatting with `device_id`.
  - `test_influxdb_client_line_protocol_tags_device_id`: Line protocol formatting with `device_id` tag.
  - `test_influxdb_client_send_samples_http_write`: Verified HTTP headers, authentication token, and POST body.
  - `test_mockup_writer_thread_mqtt_execution` & `test_mockup_writer_thread_influxdb_execution`: Verified mockup writer thread dispatching to MQTT and InfluxDB clients.
  - `test_live_mqtt_socket_transport`: Live TCP socket test verifying paho-mqtt CONNECT and JSON PUBLISH with `device_id`.
  - `test_live_influxdb_http_transport`: Live HTTP server test verifying `/health` check and HTTP POST line protocol payload.
- Full daq_navi test suite: 26 passed in 7.14s.
