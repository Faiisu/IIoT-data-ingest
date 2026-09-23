#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
config_loader.py
────────────────
Loads and validates DAQNavi universal configuration with per-channel settings
and maps string enums to Advantech BDaq constants.
"""

import os
import json
import logging
from types import SimpleNamespace

log = logging.getLogger(__name__)

# Fallback / mock enums if BDaq SDK is not available in the current environment
try:
    from Automation.BDaq import AiSignalType, ValueRange
except ImportError:
    class MockEnum:
        def __init__(self, **kwargs):
            self.__dict__.update(kwargs)
        def __getattr__(self, name):
            return name

    AiSignalType = MockEnum(
        SingleEnded="SingleEnded",
        Differential="Differential",
        PseudoDifferential="PseudoDifferential"
    )
    ValueRange = MockEnum(
        V_0To5="V_0To5",
        V_0To10="V_0To10",
        V_Neg5To5="V_Neg5To5",
        V_Neg10To10="V_Neg10To10",
        V_Neg12To12="V_Neg12To12"
    )

def resolve_signal_type(name: str):
    """Maps string representation to AiSignalType enum."""
    if hasattr(AiSignalType, name):
        return getattr(AiSignalType, name)
    log.warning(f"Unknown signal_type '{name}', falling back to SingleEnded")
    return getattr(AiSignalType, "SingleEnded", "SingleEnded")

def resolve_value_range(name: str):
    """Maps string representation to ValueRange enum."""
    if hasattr(ValueRange, name):
        return getattr(ValueRange, name)
    log.warning(f"Unknown value_range '{name}', falling back to V_0To5")
    return getattr(ValueRange, "V_0To5", "V_0To5")

def _get_bool_env(key: str, default: bool = False) -> bool:
    val = os.getenv(key)
    if val is not None:
        return val.lower() in ("true", "1", "yes")
    return bool(default)

class ChannelConfig:
    def __init__(self, channel_id: int, raw_dict: dict):
        self.channel_id = int(channel_id)
        self.enabled = bool(raw_dict.get("enabled", True))
        self.label = str(raw_dict.get("label", f"channel-{channel_id}"))
        self.signal_type_str = raw_dict.get("signal_type", "SingleEnded")
        self.value_range_str = raw_dict.get("value_range", "V_0To5")
        self.signal_type = resolve_signal_type(self.signal_type_str)
        self.value_range = resolve_value_range(self.value_range_str)
        
        scale_dict = raw_dict.get("scale", {})
        self.scale_enabled = bool(scale_dict.get("enabled", False))
        self.low_voltage = float(scale_dict.get("low_voltage", 0.0))
        self.high_voltage = float(scale_dict.get("high_voltage", 5.0))
        self.low_value = float(scale_dict.get("low_value", 0.0))
        self.high_value = float(scale_dict.get("high_value", 100.0))

class DaqNaviConfig:
    def __init__(self, config_dict: dict):
        self.raw = config_dict
        self.DEVICE_DESCRIPTION = config_dict.get("DEVICE_DESCRIPTION", "PCI-1716,BID#0")
        self.DEVICE_ID = config_dict.get("DEVICE_ID", "pci1716-0")
        self.PROFILE_PATH = config_dict.get("PROFILE_PATH", "")
        self.START_CHANNEL = int(config_dict.get("START_CHANNEL", 0))
        self.CHANNEL_COUNT = int(config_dict.get("CHANNEL_COUNT", 4))
        self.CLOCK_RATE = int(config_dict.get("CLOCK_RATE", 2000))
        self.SECTION_LENGTH = int(config_dict.get("SECTION_LENGTH", 500))
        self.SECTION_COUNT = int(config_dict.get("SECTION_COUNT", 0))
        self.QUEUE_MAXSIZE = int(config_dict.get("QUEUE_MAXSIZE", 200))
        self.MOCKUP_MODE = _get_bool_env("MOCKUP_MODE", config_dict.get("MOCKUP_MODE", False))
        
        self.USER_BUFFER_SIZE = self.SECTION_LENGTH * self.CHANNEL_COUNT
        self.QUEUE_BATCH_SIZE = self.USER_BUFFER_SIZE
        
        # Parse per-channel settings
        self.channels = {}
        raw_channels = config_dict.get("CHANNELS", {})
        for ch_key, ch_val in raw_channels.items():
            ch_idx = int(ch_key)
            self.channels[ch_idx] = ChannelConfig(ch_idx, ch_val)
            
        # Ensure all active channels within range have an entry
        for ch in range(self.START_CHANNEL, self.START_CHANNEL + self.CHANNEL_COUNT):
            if ch not in self.channels:
                self.channels[ch] = ChannelConfig(ch, {})
                
        # Output destination
        self.DESTINATION = os.getenv("DESTINATION", config_dict.get("DESTINATION", "postgresql")).lower()
        
        # Database
        self.DB_HOST = os.getenv("DB_HOST", config_dict.get("DB_HOST", "localhost"))
        self.DB_PORT = str(os.getenv("DB_PORT", config_dict.get("DB_PORT", "5432")))
        self.DB_NAME = os.getenv("DB_NAME", config_dict.get("DB_NAME", "daq_db"))
        self.DB_TABLE = os.getenv("DB_TABLE", config_dict.get("DB_TABLE", "daq_telemetry"))
        self.DB_USER = os.getenv("DB_USER", config_dict.get("DB_USER", "admin"))
        self.DB_PASSWORD = os.getenv("DB_PASSWORD", config_dict.get("DB_PASSWORD", "admin"))
        self.DB_DSN = os.getenv("DB_DSN", config_dict.get("DB_DSN", f"postgresql://{self.DB_USER}:{self.DB_PASSWORD}@{self.DB_HOST}:{self.DB_PORT}/{self.DB_NAME}"))
        self.DB_PAGE_SIZE = int(os.getenv("DB_PAGE_SIZE", config_dict.get("DB_PAGE_SIZE", 8000)))
        self.DB_INSERT_METHOD = os.getenv("DB_INSERT_METHOD", config_dict.get("DB_INSERT_METHOD", "execute_values"))
        self.DB_RETENTION_DAYS = int(os.getenv("DB_RETENTION_DAYS", config_dict.get("DB_RETENTION_DAYS", 90)))
        self.DB_COMPRESSION_INTERVAL = str(os.getenv("DB_COMPRESSION_INTERVAL", config_dict.get("DB_COMPRESSION_INTERVAL", "1 hour")))
        
        # InfluxDB
        self.INFLUX_URL = os.getenv("INFLUX_URL", config_dict.get("INFLUX_URL", "http://localhost:8086"))
        self.INFLUX_ORG = os.getenv("INFLUX_ORG", config_dict.get("INFLUX_ORG", "mddp"))
        self.INFLUX_BUCKET = os.getenv("INFLUX_BUCKET", config_dict.get("INFLUX_BUCKET", "daq_telemetry"))
        self.INFLUX_MEASUREMENT = os.getenv("INFLUX_MEASUREMENT", config_dict.get("INFLUX_MEASUREMENT", "daq_telemetry"))
        self.INFLUX_TOKEN = os.getenv("INFLUX_TOKEN", config_dict.get("INFLUX_TOKEN", ""))
        
        # MQTT
        self.MQTT_BROKER = os.getenv("MQTT_BROKER", config_dict.get("MQTT_BROKER", "localhost"))
        self.MQTT_PORT = int(os.getenv("MQTT_PORT", config_dict.get("MQTT_PORT", 1883)))
        self.MQTT_TOPIC = os.getenv("MQTT_TOPIC", config_dict.get("MQTT_TOPIC", "daq/telemetry"))
        self.MQTT_QOS = int(os.getenv("MQTT_QOS", config_dict.get("MQTT_QOS", 0)))
        self.MQTT_USERNAME = os.getenv("MQTT_USERNAME", config_dict.get("MQTT_USERNAME", ""))
        self.MQTT_PASSWORD = os.getenv("MQTT_PASSWORD", config_dict.get("MQTT_PASSWORD", ""))
        self.MQTT_TLS_ENABLED = _get_bool_env("MQTT_TLS_ENABLED", config_dict.get("MQTT_TLS_ENABLED", False))
        self.MQTT_CA_CERTS = os.getenv("MQTT_CA_CERTS", config_dict.get("MQTT_CA_CERTS", ""))
        self.MQTT_CLIENT_CERT = os.getenv("MQTT_CLIENT_CERT", config_dict.get("MQTT_CLIENT_CERT", ""))
        self.MQTT_CLIENT_KEY = os.getenv("MQTT_CLIENT_KEY", config_dict.get("MQTT_CLIENT_KEY", ""))
        
        # Operational
        self.STATS_INTERVAL_SEC = int(config_dict.get("STATS_INTERVAL_SEC", 10))
        self.ANCHOR_RECALIBRATE_INTERVAL_HR = float(config_dict.get("ANCHOR_RECALIBRATE_INTERVAL_HR", 24.0))
        self.WATCHDOG_TIMEOUT_SEC = int(os.getenv("WATCHDOG_TIMEOUT_SEC", config_dict.get("WATCHDOG_TIMEOUT_SEC", 30)))
        self.HEARTBEAT_FILE = os.getenv("HEARTBEAT_FILE", config_dict.get("HEARTBEAT_FILE", "/tmp/daq_navi_heartbeat"))

def load_daq_config(config_path: str = None) -> DaqNaviConfig:
    if config_path is None:
        p1 = os.path.join(os.path.dirname(os.path.dirname(__file__)), "config.json")
        p2 = os.path.join(os.path.dirname(__file__), "config.json")
        if os.path.exists(p1):
            config_path = p1
        elif os.path.exists(p2):
            config_path = p2
        else:
            config_path = p1
    if not os.path.exists(config_path):
        raise FileNotFoundError(f"Config file not found: {config_path}")
    with open(config_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    return DaqNaviConfig(data)
