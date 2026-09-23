#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test_timescaledb_policies.py
────────────────────────────
Integration tests for Ticket 04:
- Compression policy (device_id, channel segmentby)
- Retention policy (configurable DB_RETENTION_DAYS)
- Continuous aggregates daq_telemetry_1s and daq_telemetry_1m
- Refresh policies and idempotency
- End-to-end verification with mockup data
"""

import os
import sys
import unittest
from datetime import datetime, timezone, timedelta
import time

import psycopg2
import psycopg2.extras

sys.path.insert(0, os.path.dirname(__file__))
from config_loader import load_daq_config
from stream_to_db import ensure_db_and_tables, TimescaleDBClient

class TestTimescaleDBPolicies(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.config_path = os.path.join(os.path.dirname(__file__), "config.json")
        cls.cfg = load_daq_config(cls.config_path)
        cls.dsn = cls.cfg.DB_DSN
        try:
            conn = psycopg2.connect(cls.dsn, connect_timeout=3)
            conn.close()
            cls.db_available = True
        except Exception:
            cls.db_available = False

    def setUp(self):
        if not self.db_available:
            self.skipTest("TimescaleDB database is not reachable at " + self.dsn)

    def test_policies_and_aggregates_idempotent_init(self):
        # Running ensure_db_and_tables multiple times must succeed without error
        res1 = ensure_db_and_tables(self.dsn, self.cfg.DB_TABLE, retention_days=self.cfg.DB_RETENTION_DAYS)
        self.assertTrue(res1)
        res2 = ensure_db_and_tables(self.dsn, self.cfg.DB_TABLE, retention_days=self.cfg.DB_RETENTION_DAYS)
        self.assertTrue(res2)

    def test_continuous_aggregates_exist_and_populate(self):
        conn = psycopg2.connect(self.dsn)
        conn.autocommit = True
        cur = conn.cursor()

        # Check continuous aggregates exist
        cur.execute("SELECT view_name FROM timescaledb_information.continuous_aggregates;")
        views = [row[0] for row in cur.fetchall()]
        self.assertIn("daq_telemetry_1s", views)
        self.assertIn("daq_telemetry_1m", views)

        # Insert a deterministic set of data into daq_telemetry
        test_device = "test-policy-dev"
        # 10 samples in second 0, values 1.0 to 10.0 (avg=5.5, min=1.0, max=10.0, count=10)
        base_time = datetime(2026, 1, 1, 12, 0, 0, tzinfo=timezone.utc)
        test_rows = [
            (base_time + timedelta(milliseconds=i * 50), test_device, 0, float(i + 1))
            for i in range(10)
        ]
        psycopg2.extras.execute_values(
            cur,
            "INSERT INTO daq_telemetry (time, device_id, channel, value) VALUES %s",
            test_rows
        )

        # Refresh the continuous aggregate over this window
        cur.execute(
            "CALL refresh_continuous_aggregate('daq_telemetry_1s', '2026-01-01 12:00:00+00', '2026-01-01 12:00:05+00');"
        )

        # Query the aggregate for our test device
        cur.execute(
            "SELECT bucket, device_id, channel, avg, min, max, count FROM daq_telemetry_1s WHERE device_id = %s ORDER BY bucket;",
            (test_device,)
        )
        agg_rows = cur.fetchall()
        self.assertGreaterEqual(len(agg_rows), 1)

        b, dev, ch, avg_v, min_v, max_v, count_v = agg_rows[0]
        self.assertEqual(b, base_time)
        self.assertEqual(dev, test_device)
        self.assertEqual(ch, 0)
        self.assertAlmostEqual(avg_v, 5.5, places=2)
        self.assertAlmostEqual(min_v, 1.0, places=2)
        self.assertAlmostEqual(max_v, 10.0, places=2)
        self.assertEqual(count_v, 10)

        # Clean up test rows
        cur.execute("DELETE FROM daq_telemetry WHERE device_id = %s;", (test_device,))
        conn.close()

    def test_compression_policy_and_chunk_compression(self):
        conn = psycopg2.connect(self.dsn)
        conn.autocommit = True
        cur = conn.cursor()

        # Check compression settings
        cur.execute("""
            SELECT attname, segmentby_column_index, orderby_column_index 
            FROM timescaledb_information.compression_settings 
            WHERE hypertable_name = 'daq_telemetry';
        """)
        settings = {row[0]: (row[1], row[2]) for row in cur.fetchall()}
        self.assertIn("device_id", settings)
        self.assertIn("channel", settings)
        self.assertIn("time", settings)

        # Check compression job exists
        cur.execute("""
            SELECT job_id, application_name, schedule_interval, config 
            FROM timescaledb_information.jobs 
            WHERE application_name LIKE '%Columnstore Policy%' OR application_name LIKE '%Compression%';
        """)
        jobs = cur.fetchall()
        self.assertGreaterEqual(len(jobs), 1)

        # Roundtrip test decompress -> compress on a chunk
        cur.execute("""
            SELECT chunk_schema, chunk_name, is_compressed 
            FROM timescaledb_information.chunks 
            WHERE hypertable_name = 'daq_telemetry'
            ORDER BY range_start LIMIT 1;
        """)
        chunk = cur.fetchone()
        self.assertIsNotNone(chunk, "At least one chunk should exist in daq_telemetry")
        schema, name, is_comp = chunk

        if is_comp:
            cur.execute(f"SELECT decompress_chunk('{schema}.{name}');")
            cur.execute(f"SELECT is_compressed FROM timescaledb_information.chunks WHERE chunk_name = '{name}';")
            self.assertFalse(cur.fetchone()[0])
            cur.execute(f"SELECT compress_chunk('{schema}.{name}');")
            cur.execute(f"SELECT is_compressed FROM timescaledb_information.chunks WHERE chunk_name = '{name}';")
            self.assertTrue(cur.fetchone()[0])
        else:
            cur.execute(f"SELECT compress_chunk('{schema}.{name}');")
            cur.execute(f"SELECT is_compressed FROM timescaledb_information.chunks WHERE chunk_name = '{name}';")
            self.assertTrue(cur.fetchone()[0])

        # Verify storage reduction using hypertable_compression_stats
        cur.execute("""
            SELECT before_compression_total_bytes, after_compression_total_bytes 
            FROM hypertable_compression_stats('daq_telemetry');
        """)
        stats_row = cur.fetchone()
        self.assertIsNotNone(stats_row)
        before_bytes, after_bytes = stats_row[0], stats_row[1]
        self.assertGreater(before_bytes, 0)
        self.assertGreater(after_bytes, 0)
        self.assertLess(after_bytes, before_bytes)
        reduction_ratio = 1.0 - (after_bytes / before_bytes)
        # Verify storage reduction is ~90% (> 80%)
        self.assertGreater(reduction_ratio, 0.80)
        conn.close()

    def test_retention_policy_and_drop_chunks(self):
        conn = psycopg2.connect(self.dsn)
        conn.autocommit = True
        cur = conn.cursor()

        # Check retention job exists
        cur.execute("""
            SELECT job_id, application_name, schedule_interval, config 
            FROM timescaledb_information.jobs 
            WHERE application_name LIKE '%Retention Policy%';
        """)
        jobs = cur.fetchall()
        self.assertGreaterEqual(len(jobs), 1)

        # Test inserting chunk older than 90 days (100 days ago)
        old_time = datetime.now(timezone.utc) - timedelta(days=100)
        cur.execute("INSERT INTO daq_telemetry (time, device_id, channel, value) VALUES (%s, %s, %s, %s);", (old_time, 'retention-test', 0, 99.9))

        # Drop chunks older than 90 days
        cur.execute("SELECT drop_chunks('daq_telemetry', older_than => INTERVAL '90 days');")
        dropped = cur.fetchall()
        self.assertIsInstance(dropped, list)
        self.assertGreaterEqual(len(dropped), 1)

        # Verify old chunk was dropped
        cur.execute("SELECT chunk_name FROM timescaledb_information.chunks WHERE hypertable_name = 'daq_telemetry' AND range_end < NOW() - INTERVAL '90 days';")
        self.assertEqual(len(cur.fetchall()), 0)

        conn.close()

    def test_continuous_aggregate_1m(self):
        conn = psycopg2.connect(self.dsn)
        conn.autocommit = True
        cur = conn.cursor()

        test_device = "test-policy-dev-1m"
        base_time = datetime(2026, 2, 1, 10, 0, 0, tzinfo=timezone.utc)
        test_rows = [
            (base_time + timedelta(seconds=i * 5), test_device, 1, float(i * 10))
            for i in range(12)  # spans 1 minute (0 to 55s)
        ]
        psycopg2.extras.execute_values(
            cur,
            "INSERT INTO daq_telemetry (time, device_id, channel, value) VALUES %s",
            test_rows
        )

        cur.execute(
            "CALL refresh_continuous_aggregate('daq_telemetry_1m', '2026-02-01 10:00:00+00', '2026-02-01 10:02:00+00');"
        )

        cur.execute(
            "SELECT bucket, device_id, channel, avg, min, max, count FROM daq_telemetry_1m WHERE device_id = %s ORDER BY bucket;",
            (test_device,)
        )
        agg_rows = cur.fetchall()
        self.assertGreaterEqual(len(agg_rows), 1)

        b, dev, ch, avg_v, min_v, max_v, count_v = agg_rows[0]
        self.assertEqual(b, base_time)
        self.assertEqual(dev, test_device)
        self.assertEqual(ch, 1)
        self.assertAlmostEqual(min_v, 0.0, places=2)
        self.assertAlmostEqual(max_v, 110.0, places=2)
        self.assertEqual(count_v, 12)

        cur.execute("DELETE FROM daq_telemetry WHERE device_id = %s;", (test_device,))
        conn.close()

    def test_mockup_stream_pipeline_e2e_verification(self):
        from stream_to_db import Calibrator, DaqSampleParser
        
        calibrator = Calibrator(
            start_channel=self.cfg.START_CHANNEL,
            channel_count=self.cfg.CHANNEL_COUNT,
            channel_configs=self.cfg.channels
        )
        test_dev = f"mockup-e2e-{int(time.time())}"
        parser = DaqSampleParser(
            start_channel=self.cfg.START_CHANNEL,
            channel_count=self.cfg.CHANNEL_COUNT,
            clock_rate=self.cfg.CLOCK_RATE,
            calibrator=calibrator,
            device_id=test_dev
        )

        # Generate exactly 1 second of mockup data aligned to second boundary
        base_dt = datetime.now(timezone.utc).replace(microsecond=0) - timedelta(seconds=10)
        base_ts_ns = int(base_dt.timestamp() * 1e9)
        raw_interleaved = []
        for i in range(2000):
            # ch0: 3.0V (0.0 kPa)
            # ch1: 5.0V (100.0 kPa)
            raw_interleaved.extend([3.0, 5.0])
        
        parsed_rows = parser.parse_batch(base_ts_ns, raw_interleaved, len(raw_interleaved))
        self.assertEqual(len(parsed_rows), 4000)

        conn = psycopg2.connect(self.dsn)
        conn.autocommit = True
        cur = conn.cursor()

        # Clean up any leftover test data
        cur.execute("DELETE FROM daq_telemetry WHERE device_id LIKE 'mockup-e2e-%';")

        # Insert via psycopg2.extras.execute_values (shared with TimescaleDBClient)
        psycopg2.extras.execute_values(
            cur,
            "INSERT INTO daq_telemetry (time, device_id, channel, value) VALUES %s",
            parsed_rows
        )

        # Refresh continuous aggregates over a 2-minute bounded window
        window_start = base_dt - timedelta(minutes=1)
        window_end = base_dt + timedelta(minutes=1)
        for cagg in ('daq_telemetry_1s', 'daq_telemetry_1m'):
            for attempt in range(5):
                try:
                    cur.execute(
                        f"CALL refresh_continuous_aggregate('{cagg}', %s, %s);",
                        (window_start, window_end)
                    )
                    break
                except psycopg2.errors.LockNotAvailable:
                    conn.rollback()
                    time.sleep(0.5)

        # Verify daq_telemetry_1s contains aggregated rows for mockup device
        cur.execute(
            "SELECT bucket, device_id, channel, avg, min, max, count FROM daq_telemetry_1s WHERE device_id = %s ORDER BY channel;",
            (test_dev,)
        )
        cagg_rows = cur.fetchall()
        self.assertEqual(len(cagg_rows), 2)
        
        # ch 0: avg=0.0 kPa, count=2000
        self.assertEqual(cagg_rows[0][1], test_dev)
        self.assertEqual(cagg_rows[0][2], 0)
        self.assertAlmostEqual(cagg_rows[0][3], 0.0, places=2)
        self.assertEqual(cagg_rows[0][6], 2000)

        # ch 1: avg=100.0 kPa, count=2000
        self.assertEqual(cagg_rows[1][1], test_dev)
        self.assertEqual(cagg_rows[1][2], 1)
        self.assertAlmostEqual(cagg_rows[1][3], 100.0, places=2)
        self.assertEqual(cagg_rows[1][6], 2000)

        # Clean up
        cur.execute("DELETE FROM daq_telemetry WHERE device_id = %s;", (test_dev,))
        conn.close()

if __name__ == "__main__":
    unittest.main()
