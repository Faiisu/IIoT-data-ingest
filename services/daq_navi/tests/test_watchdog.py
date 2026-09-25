#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test_watchdog.py
────────────────
Unit tests for DAQ pipeline watchdog checks and timeouts.
"""

import os
import sys
import time
import unittest
from unittest.mock import MagicMock, patch
SERVICE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORE_DIR = os.path.join(SERVICE_DIR, "core")
for p in (CORE_DIR, SERVICE_DIR):
    if p not in sys.path:
        sys.path.insert(0, p)

from buffered_daq_to_timescaledb import check_pipeline_watchdog, TimescaleDBClient


class TestPipelineWatchdog(unittest.TestCase):
    """Test in-process stream watchdog logic."""

    def test_pipeline_healthy(self):
        now = 1000.0
        stats_snapshot = {
            "last_polled_time": now - 2.0,
            "last_written_time": now - 1.0,
            "polled": 2000,
            "written": 2000,
            "dropped": 0,
            "db_errors": 0,
        }
        healthy, msg = check_pipeline_watchdog(stats_snapshot, qsize=0, timeout_sec=10.0, current_time=now)
        self.assertTrue(healthy)
        self.assertIsNone(msg)

    def test_daq_stalled_detection(self):
        now = 1000.0
        stats_snapshot = {
            "last_polled_time": now - 15.0,  # 15s ago, threshold 10s
            "last_written_time": now - 1.0,
            "polled": 1000,
            "written": 1000,
            "dropped": 0,
            "db_errors": 0,
        }
        healthy, msg = check_pipeline_watchdog(stats_snapshot, qsize=0, timeout_sec=10.0, current_time=now)
        self.assertFalse(healthy)
        self.assertIn("DAQ acquisition stalled", msg)
        self.assertIn("15.0s", msg)

    def test_writer_stalled_with_pending_queue(self):
        now = 1000.0
        stats_snapshot = {
            "last_polled_time": now - 1.0,
            "last_written_time": now - 25.0,  # 25s ago
            "polled": 5000,
            "written": 2000,
            "dropped": 0,
            "db_errors": 0,
        }
        # qsize > 0 with expired write time indicates a writer hang
        healthy, msg = check_pipeline_watchdog(stats_snapshot, qsize=5, timeout_sec=10.0, current_time=now)
        self.assertFalse(healthy)
        self.assertIn("Writer stalled", msg)
        self.assertIn("5 batches queued", msg)

    def test_writer_idle_empty_queue_is_healthy(self):
        now = 1000.0
        stats_snapshot = {
            "last_polled_time": now - 1.0,
            "last_written_time": now - 100.0,  # very old write time
            "polled": 1000,
            "written": 1000,
            "dropped": 0,
            "db_errors": 0,
        }
        # If queue is empty, writer having no recent writes is expected when DAQ produces slowly
        healthy, msg = check_pipeline_watchdog(stats_snapshot, qsize=0, timeout_sec=10.0, current_time=now)
        self.assertTrue(healthy)
        self.assertIsNone(msg)

    def test_both_daq_and_writer_stalled(self):
        now = 1000.0
        stats_snapshot = {
            "last_polled_time": now - 30.0,
            "last_written_time": now - 30.0,
            "polled": 1000,
            "written": 500,
            "dropped": 0,
            "db_errors": 0,
        }
        healthy, msg = check_pipeline_watchdog(stats_snapshot, qsize=2, timeout_sec=10.0, current_time=now)
        self.assertFalse(healthy)
        self.assertIn("DAQ acquisition stalled", msg)
        self.assertIn("Writer stalled", msg)


class TestTimescaleClientTimeouts(unittest.TestCase):
    """Verify database connection includes connect_timeout and statement_timeout options."""

    @patch("buffered_daq_to_timescaledb.ensure_db_and_tables", return_value=True)
    @patch("buffered_daq_to_timescaledb.psycopg2.connect")
    def test_connect_uses_timeouts(self, mock_pg_connect, mock_ensure):
        mock_conn = MagicMock()
        mock_pg_connect.return_value = mock_conn

        client = TimescaleDBClient(dsn="postgresql://admin:admin@localhost:5432/daq_test")
        success = client.connect()

        self.assertTrue(success)
        mock_pg_connect.assert_called_once()
        kwargs = mock_pg_connect.call_args[1]
        self.assertEqual(kwargs.get("connect_timeout"), 10)
        self.assertIn("statement_timeout=15000", kwargs.get("options", ""))


if __name__ == "__main__":
    unittest.main()
