#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test_docker_compose.py
───────────────────────
Tests for Ticket 06: Docker Compose full stack deployment.
- Verifies docker-compose.yml defines: timescaledb, mqtt-broker, influxdb, daq-navi, portal
- Verifies TimescaleDB auto-initialization with db_setup.sql
- Verifies daq-navi container: privileged, /dev, /usr/lib, /etc/biobdaq, config.json bind-mount
- Verifies mosquitto.conf for anonymous local access
- Verifies .env.example with all configurable credentials
- Verifies daq-navi Dockerfile and entrypoint script
- Verifies config_loader environment variable overrides
"""

import os
import sys
import unittest
import yaml

SERVICE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORE_DIR = os.path.join(SERVICE_DIR, "core")
PROJECT_ROOT = os.path.abspath(os.path.join(SERVICE_DIR, "..", ".."))
for p in (CORE_DIR, SERVICE_DIR, PROJECT_ROOT):
    if p not in sys.path:
        sys.path.insert(0, p)

from config_loader import load_daq_config, DaqNaviConfig


class TestDockerComposeStack(unittest.TestCase):
    def setUp(self):
        self.project_root = PROJECT_ROOT
        self.compose_path = os.path.join(self.project_root, "docker-compose.yml")
        self.env_example_path = os.path.join(self.project_root, ".env.example")
        self.mosquitto_conf_path = os.path.join(self.project_root, "config", "mosquitto", "mosquitto.conf")
        self.dockerfile_path = os.path.join(self.project_root, "services", "daq_navi", "Dockerfile")
        self.entrypoint_path = os.path.join(self.project_root, "services", "daq_navi", "entrypoint.sh")

    def test_docker_compose_file_exists_and_parses(self):
        self.assertTrue(os.path.exists(self.compose_path), "docker-compose.yml does not exist")
        with open(self.compose_path, "r", encoding="utf-8") as f:
            compose_data = yaml.safe_load(f)
        self.assertIsInstance(compose_data, dict)
        self.assertIn("services", compose_data)

    def test_required_services_defined(self):
        with open(self.compose_path, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        services = data.get("services", {})
        required = ["timescaledb", "mqtt-broker", "influxdb", "daq-navi", "portal"]
        for req in required:
            self.assertIn(req, services, f"Required service '{req}' missing from docker-compose.yml")

    def test_timescaledb_service_configuration(self):
        with open(self.compose_path, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        tsdb = data["services"]["timescaledb"]
        self.assertIn("timescale/timescaledb", tsdb.get("image", ""))
        self.assertIn("pg16", tsdb.get("image", ""))
        
        # Verify db_setup.sql mount in docker-entrypoint-initdb.d
        volumes = tsdb.get("volumes", [])
        has_init_sql = any("docker-entrypoint-initdb.d" in str(v) and "db_setup.sql" in str(v) for v in volumes)
        self.assertTrue(has_init_sql, "timescaledb must mount db_setup.sql into docker-entrypoint-initdb.d")

        # Verify healthcheck
        self.assertIn("healthcheck", tsdb, "timescaledb must configure healthcheck")

    def test_mqtt_broker_service_configuration(self):
        with open(self.compose_path, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        mqtt = data["services"]["mqtt-broker"]
        self.assertIn("mosquitto", mqtt.get("image", ""))
        
        # Verify mosquitto.conf volume mount
        volumes = mqtt.get("volumes", [])
        has_conf = any("mosquitto.conf" in str(v) for v in volumes)
        self.assertTrue(has_conf, "mqtt-broker must mount mosquitto.conf")

    def test_influxdb_service_configuration(self):
        with open(self.compose_path, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        influx = data["services"]["influxdb"]
        self.assertIn("influxdb", influx.get("image", ""))
        
        # Verify port 8086
        ports = [str(p) for p in influx.get("ports", [])]
        has_port = any("8086" in p for p in ports)
        self.assertTrue(has_port, "influxdb must expose port 8086")

    def test_daq_navi_service_configuration(self):
        with open(self.compose_path, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        daq = data["services"]["daq-navi"]
        
        # Verify privileged: true
        self.assertTrue(daq.get("privileged", False), "daq-navi must have privileged: true")
        
        # Verify volume mounts: /dev, /usr/lib, /etc/biobdaq, config.json
        volumes = [str(v) for v in daq.get("volumes", [])]
        self.assertTrue(any("/dev" in v for v in volumes), "daq-navi must mount /dev")
        self.assertTrue(any("/usr/lib" in v for v in volumes), "daq-navi must mount /usr/lib")
        self.assertTrue(any("/etc/biobdaq" in v for v in volumes), "daq-navi must mount /etc/biobdaq")
        self.assertTrue(any("config.json" in v for v in volumes), "daq-navi must bind-mount config.json")

    def test_portal_port(self):
        with open(self.compose_path, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        portal = data["services"]["portal"]
        
        portal_ports = [str(p) for p in portal.get("ports", [])]
        self.assertTrue(any("8080" in p for p in portal_ports), "portal must expose port 8080")
        

    def test_mosquitto_conf_file(self):
        self.assertTrue(os.path.exists(self.mosquitto_conf_path), f"Missing {self.mosquitto_conf_path}")
        with open(self.mosquitto_conf_path, "r", encoding="utf-8") as f:
            content = f.read()
        self.assertIn("1883", content)
        self.assertIn("allow_anonymous true", content)

    def test_env_example_file(self):
        self.assertTrue(os.path.exists(self.env_example_path), f"Missing {self.env_example_path}")
        with open(self.env_example_path, "r", encoding="utf-8") as f:
            content = f.read()
        required_keys = [
            "POSTGRES_USER", "POSTGRES_PASSWORD", "POSTGRES_DB", "DB_PORT",
            "MQTT_PORT", "INFLUX_PORT", "INFLUX_TOKEN", "MOCKUP_MODE",
            "DESTINATION", "PORTAL_PORT"
        ]
        for k in required_keys:
            self.assertIn(k, content, f"Missing key '{k}' in .env.example")

    def test_daq_navi_dockerfile_and_entrypoint(self):
        self.assertTrue(os.path.exists(self.dockerfile_path), f"Missing {self.dockerfile_path}")
        with open(self.dockerfile_path, "r", encoding="utf-8") as f:
            df_content = f.read()
        self.assertIn("FROM python:", df_content)
        self.assertIn("requirements.txt", df_content)
        self.assertIn("entrypoint.sh", df_content)

        self.assertTrue(os.path.exists(self.entrypoint_path), f"Missing {self.entrypoint_path}")
        with open(self.entrypoint_path, "r", encoding="utf-8") as f:
            ep_content = f.read()
        self.assertIn("MOCKUP_MODE", ep_content)
        self.assertIn("mockup_stream_to_db.py", ep_content)
        self.assertIn("buffered_daq_to_timescaledb.py", ep_content)

    def test_config_loader_env_overrides(self):
        config_path = os.path.join(SERVICE_DIR, "config.json")
        base_cfg = load_daq_config(config_path)

        os.environ["MOCKUP_MODE"] = "true"
        os.environ["DESTINATION"] = "mqtt"
        os.environ["DB_DSN"] = "postgresql://test:test@timescaledb:5432/testdb"
        os.environ["MQTT_BROKER"] = "broker.test.local"
        os.environ["INFLUX_URL"] = "http://influxdb:8086"
        os.environ["INFLUX_TOKEN"] = "token123"

        try:
            cfg = load_daq_config()
            self.assertTrue(cfg.MOCKUP_MODE)
            self.assertEqual(cfg.DESTINATION, "mqtt")
            self.assertEqual(cfg.DB_DSN, "postgresql://test:test@timescaledb:5432/testdb")
            self.assertEqual(cfg.MQTT_BROKER, "broker.test.local")
            self.assertEqual(cfg.INFLUX_URL, "http://influxdb:8086")
            self.assertEqual(cfg.INFLUX_TOKEN, "token123")
            explicit = load_daq_config(config_path)
            self.assertEqual(explicit.DESTINATION, base_cfg.DESTINATION)
            self.assertEqual(explicit.DB_DSN, base_cfg.DB_DSN)
        finally:
            for k in ["MOCKUP_MODE", "DESTINATION", "DB_DSN", "MQTT_BROKER", "INFLUX_URL", "INFLUX_TOKEN"]:
                os.environ.pop(k, None)


if __name__ == "__main__":
    unittest.main()
