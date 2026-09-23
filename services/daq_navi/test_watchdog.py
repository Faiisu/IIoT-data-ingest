#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test_watchdog.py
────────────────
Unit tests for DAQ pipeline watchdog checks, timeouts, and watchdog script.
"""

import os
import sys
import time
import subprocess
import unittest
from unittest.mock import MagicMock, patch

sys.path.append(os.path.dirname(__file__))

from stream_to_db import check_pipeline_watchdog, TimescaleDBClient


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

    @patch("stream_to_db.ensure_db_and_tables", return_value=True)
    @patch("stream_to_db.psycopg2.connect")
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


class TestWatchdogShellScript(unittest.TestCase):
    """Test deploy/linux/watchdog.sh script execution and options."""

    @classmethod
    def setUpClass(cls):
        cls.script_path = os.path.abspath(
            os.path.join(os.path.dirname(__file__), "../../deploy/linux/watchdog.sh")
        )

    def test_script_syntax_valid(self):
        """bash -n ensures no syntax errors in watchdog.sh."""
        res = subprocess.run(["bash", "-n", self.script_path], capture_output=True, text=True)
        self.assertEqual(res.returncode, 0, f"watchdog.sh syntax error: {res.stderr}")

    def test_help_flag(self):
        """watchdog.sh --help should exit 0 and display usage."""
        res = subprocess.run(["bash", self.script_path, "--help"], capture_output=True, text=True)
        self.assertEqual(res.returncode, 0)
        self.assertIn("Usage:", res.stdout)
        self.assertIn("--daemon", res.stdout)
        self.assertIn("--timeout", res.stdout)
        self.assertIn("--check", res.stdout)

    def test_check_flag_execution(self):
        """watchdog.sh --check executes one-shot without hanging."""
        res = subprocess.run(
            ["bash", self.script_path, "--check", "--timeout", "5"],
            capture_output=True,
            text=True,
            timeout=15
        )
        self.assertIn(res.returncode, (0, 1))


if __name__ == "__main__":
    unittest.main()
