#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test_pipeline_e2e.py
────────────────────
Tests for Ticket 02: Mockup -> PostgreSQL pipeline, 4-column tuples (time, device_id, channel, value),
and DP-101A sensor calibration.
"""

import os
import sys
import unittest
from datetime import datetime, timezone
from unittest.mock import MagicMock, patch

SERVICE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORE_DIR = os.path.join(SERVICE_DIR, "core")
PROJECT_ROOT = os.path.abspath(os.path.join(SERVICE_DIR, "..", ".."))
for p in (CORE_DIR, SERVICE_DIR, PROJECT_ROOT):
    if p not in sys.path:
        sys.path.insert(0, p)

from config_loader import load_daq_config, DaqNaviConfig
from buffered_daq_to_timescaledb import Calibrator, DaqSampleParser, TimescaleDBClient

class TestPipelineE2E(unittest.TestCase):
    def setUp(self):
        self.config_path = os.path.join(SERVICE_DIR, "config.json")
        base = load_daq_config(self.config_path).raw
        channels = {}
        for channel in (0, 1):
            entry = dict(base['CHANNELS'][str(channel)])
            entry['scale'] = {
                'enabled': True, 'low_voltage': 1.0, 'high_voltage': 5.0,
                'low_value': -100.0, 'high_value': 100.0,
            }
            channels[str(channel)] = entry
        self.cfg = DaqNaviConfig({
            **base, 'CHANNEL_COUNT': 2, 'CLOCK_RATE': 2000, 'CHANNELS': channels,
        }, allow_env_overrides=False)

    def test_dp101a_calibration(self):
        calibrator = Calibrator(
            start_channel=self.cfg.START_CHANNEL,
            channel_count=self.cfg.CHANNEL_COUNT,
            channel_configs=self.cfg.channels
        )
        # Ch 0 has scale: 1.0V -> -100, 5.0V -> +100
        # Check 1.0V => -100.0
        val_min = calibrator.calibrate(0, 1.0)
        self.assertAlmostEqual(val_min, -100.0, places=2)
        
        # Check 3.0V (midpoint) => 0.0
        val_mid = calibrator.calibrate(0, 3.0)
        self.assertAlmostEqual(val_mid, 0.0, places=2)
        
        # Check 5.0V => +100.0
        val_max = calibrator.calibrate(0, 5.0)
        self.assertAlmostEqual(val_max, 100.0, places=2)

    def test_daq_sample_parser_emits_device_id(self):
        calibrator = Calibrator(
            start_channel=self.cfg.START_CHANNEL,
            channel_count=self.cfg.CHANNEL_COUNT,
            channel_configs=self.cfg.channels
        )
        parser = DaqSampleParser(
            start_channel=self.cfg.START_CHANNEL,
            channel_count=self.cfg.CHANNEL_COUNT,
            clock_rate=self.cfg.CLOCK_RATE,
            calibrator=calibrator,
            device_id=self.cfg.DEVICE_ID
        )

        batch_wall_ts_ns = 1_700_000_000_000_000_000  # sample timestamp
        # 2 channels, 2 samples per channel = 4 interleaved values: [ch0_s0, ch1_s0, ch0_s1, ch1_s1]
        raw_data = [3.0, 3.0, 5.0, 1.0]
        returned_count = 4

        rows = parser.parse_batch(batch_wall_ts_ns, raw_data, returned_count)
        self.assertEqual(len(rows), 4)

        # Each row must have 4 elements: (sample_ts, device_id, channel, value)
        for row in rows:
            self.assertEqual(len(row), 4)
            ts, dev_id, ch, val = row
            self.assertIsInstance(ts, datetime)
            self.assertEqual(dev_id, "pci1716-0")
            self.assertIn(ch, [0, 1])

        # Verify parsed values
        # sample 0, ch 0 (3.0V -> 0.0)
        self.assertEqual(rows[0][1], "pci1716-0")
        self.assertEqual(rows[0][2], 0)
        self.assertAlmostEqual(rows[0][3], 0.0, places=2)

        # sample 0, ch 1 (3.0V -> 0.0)
        self.assertEqual(rows[1][1], "pci1716-0")
        self.assertEqual(rows[1][2], 1)
        self.assertAlmostEqual(rows[1][3], 0.0, places=2)

        # sample 1, ch 0 (5.0V -> 100.0)
        self.assertEqual(rows[2][1], "pci1716-0")
        self.assertEqual(rows[2][2], 0)
        self.assertAlmostEqual(rows[2][3], 100.0, places=2)

        # sample 1, ch 1 (1.0V -> -100.0)
        self.assertEqual(rows[3][1], "pci1716-0")
        self.assertEqual(rows[3][2], 1)
        self.assertAlmostEqual(rows[3][3], -100.0, places=2)

    @patch("psycopg2.extras.execute_values")
    def test_timescaledb_client_insert(self, mock_execute_values):
        stop_event = MagicMock()
        client = TimescaleDBClient(
            dsn="postgresql://admin:admin@localhost:5432/daq_db",
            stop_event=stop_event,
            table_name="daq_telemetry"
        )
        client.conn = MagicMock()
        client.cur = MagicMock()

        sample_rows = [
            (datetime.now(timezone.utc), "pci1716-0", 0, 12.345),
            (datetime.now(timezone.utc), "pci1716-0", 1, -45.678)
        ]

        client.insert_samples(sample_rows, page_size=1000)

        # Verify execute_values called with INSERT query targeting daq_telemetry and 4 columns
        call_args = mock_execute_values.call_args[0]
        cur, sql, rows = call_args[0], call_args[1], call_args[2]
        self.assertIn("INSERT INTO daq_telemetry (time, device_id, channel, value)", sql)
        self.assertEqual(rows, sample_rows)
        client.conn.commit.assert_called_once()

if __name__ == "__main__":
    unittest.main()
