#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test_config_db.py
─────────────────
Tests for Ticket 01: Config schema, loader, and DB schema setup.
"""

import os
import sys
import unittest
from unittest.mock import MagicMock, patch

sys.path.insert(0, os.path.dirname(__file__))
from config_loader import load_daq_config, DaqNaviConfig, ChannelConfig

class TestConfigAndSchema(unittest.TestCase):
    def test_load_default_config(self):
        config_path = os.path.join(os.path.dirname(__file__), "config.json")
        cfg = load_daq_config(config_path)
        
        self.assertEqual(cfg.DEVICE_ID, "pci1716-0")
        self.assertEqual(cfg.DEVICE_DESCRIPTION, "PCI-1716,BID#0")
        self.assertEqual(cfg.CHANNEL_COUNT, 2)
        self.assertEqual(cfg.CLOCK_RATE, 2000)
        self.assertEqual(cfg.DB_TABLE, "daq_telemetry")
        self.assertEqual(cfg.DESTINATION, "postgresql")
        self.assertEqual(cfg.DB_RETENTION_DAYS, 90)
        self.assertEqual(cfg.DB_COMPRESSION_INTERVAL, "1 hour")
        
        # Verify 4 channels are parsed
        self.assertIn(0, cfg.channels)
        self.assertIn(1, cfg.channels)
        self.assertIn(2, cfg.channels)
        self.assertIn(3, cfg.channels)
        
        ch0 = cfg.channels[0]
        self.assertEqual(ch0.label, "pressure-ch0")
        self.assertTrue(ch0.enabled)
        self.assertTrue(ch0.scale_enabled)
        self.assertEqual(ch0.low_voltage, 1.0)
        self.assertEqual(ch0.high_voltage, 5.0)
        self.assertEqual(ch0.low_value, -100.0)
        self.assertEqual(ch0.high_value, 100.0)

    def test_sql_schema_file_exists_and_contains_table(self):
        sql_path = os.path.join(os.path.dirname(__file__), "scripts", "sql", "db_setup.sql")
        self.assertTrue(os.path.exists(sql_path), "db_setup.sql must exist")
        with open(sql_path, "r", encoding="utf-8") as f:
            content = f.read()
        
        self.assertIn("daq_telemetry", content)
        self.assertIn("device_id", content)
        self.assertIn("create_hypertable", content)
        self.assertIn("idx_daq_telemetry_device_channel_time", content)
        self.assertIn("timescaledb.compress", content)
        self.assertIn("compress_segmentby", content)
        self.assertIn("add_compression_policy", content)
        self.assertIn("add_retention_policy", content)
        self.assertIn("daq_telemetry_1s", content)
        self.assertIn("daq_telemetry_1m", content)
        self.assertIn("add_continuous_aggregate_policy", content)

    @patch("psycopg2.connect")
    def test_ensure_db_and_tables_execution(self, mock_connect):
        from stream_to_db import ensure_db_and_tables
        
        mock_conn = MagicMock()
        mock_cur = MagicMock()
        mock_conn.cursor.return_value.__enter__.return_value = mock_cur
        mock_cur.fetchone.return_value = (1,)  # DB exists
        mock_connect.return_value = mock_conn
        
        success = ensure_db_and_tables("postgresql://user:pass@localhost:5432/test_db", "test_telemetry", retention_days=60)
        self.assertTrue(success)
        
        # Verify execute calls contained create table and index
        executed_sqls = [call[0][0] for call in mock_cur.execute.call_args_list]
        self.assertTrue(any("CREATE TABLE IF NOT EXISTS test_telemetry" in sql for sql in executed_sqls))
        self.assertTrue(any("idx_test_telemetry_device_channel_time" in sql for sql in executed_sqls))
        self.assertTrue(any("timescaledb.compress" in sql for sql in executed_sqls))
        self.assertTrue(any("add_compression_policy" in sql for sql in executed_sqls))
        self.assertTrue(any("add_retention_policy" in sql for sql in executed_sqls))
        self.assertTrue(any("60 days" in sql for sql in executed_sqls))
        self.assertTrue(any("test_telemetry_1s" in sql for sql in executed_sqls))
        self.assertTrue(any("test_telemetry_1m" in sql for sql in executed_sqls))
        self.assertTrue(any("add_continuous_aggregate_policy" in sql for sql in executed_sqls))

if __name__ == "__main__":
    unittest.main()
