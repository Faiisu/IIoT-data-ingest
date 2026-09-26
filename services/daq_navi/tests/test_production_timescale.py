"""Production schema contract against an explicitly isolated TimescaleDB database."""

import os
import tempfile
import unittest
import uuid
from pathlib import Path

import psycopg2
from psycopg2 import sql

from services.daq_navi.core.production_acquisition import (
    ProductionPipeline,
    TimescaleProductionDestination,
)
from services.daq_navi.tests.test_production_acquisition import configuration


class ProductionTimescaleTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        dsn = os.environ.get("DAQ_TEST_DB_DSN", "")
        dbname = psycopg2.extensions.parse_dsn(dsn).get("dbname", "")
        if not dbname.startswith("daq_navi_test_"):
            raise unittest.SkipTest("set DAQ_TEST_DB_DSN to a daq_navi_test_* database")
        cls.dsn = dsn
        cls.table = "test_samples_" + uuid.uuid4().hex[:10]
        cls.cfg = configuration(DB_DSN=dsn, DB_PRODUCTION_TABLE=cls.table)

    @classmethod
    def tearDownClass(cls):
        if not hasattr(cls, "dsn"):
            return
        with psycopg2.connect(cls.dsn) as conn:
            with conn.cursor() as cur:
                cur.execute(sql.SQL("DROP TABLE IF EXISTS {} CASCADE").format(sql.Identifier(cls.table)))

    def test_duplicate_batch_is_idempotent_and_retention_changes(self):
        sink = TimescaleProductionDestination(self.cfg)
        with tempfile.TemporaryDirectory() as directory:
            pipeline = ProductionPipeline(self.cfg, Path(directory), sink)
            pipeline.capture([1, 2, 3, 4], end_time_ns=1_700_000_000_000_000_000)
            _, original_rows = pipeline.spool.oldest()
            pipeline.flush_once()
            sink.write(original_rows, [])
            with psycopg2.connect(self.dsn) as conn:
                with conn.cursor() as cur:
                    cur.execute(sql.SQL("SELECT COUNT(*), MIN(raw_voltage), MAX(calibrated_value) FROM {}").format(sql.Identifier(self.table)))
                    self.assertEqual(cur.fetchone(), (4, 1.0, 80.0))
                    cur.execute(sql.SQL("""SELECT sample_id, session_id, device_id, channel,
                        sensor_name, raw_voltage, calibrated_value, unit,
                        provenance FROM {} WHERE channel=0""").format(
                        sql.Identifier(self.table)))
                    sample = cur.fetchone()
                    self.assertEqual(sample[0], f"{pipeline.session_id}:0:0")
                    self.assertEqual(str(sample[1]), pipeline.session_id)
                    self.assertEqual(sample[2:], ("test-device", 0, "sensor-0", 1.0,
                                                  20.0, "kPa", "physical_daq"))
                    cur.execute("SELECT config->>'drop_after' FROM timescaledb_information.jobs WHERE hypertable_name=%s AND proc_name='policy_retention'", (self.table,))
                    self.assertEqual(cur.fetchone()[0], "30 days")
            self.cfg.DB_RETENTION_DAYS = 45
            sink.ensure_schema()
            with psycopg2.connect(self.dsn) as conn:
                with conn.cursor() as cur:
                    cur.execute("SELECT config->>'drop_after' FROM timescaledb_information.jobs WHERE hypertable_name=%s AND proc_name='policy_retention'", (self.table,))
                    self.assertEqual(cur.fetchone()[0], "45 days")
            pipeline.close()

    def test_lost_commit_response_replays_oldest_batch_once(self):
        sink = TimescaleProductionDestination(self.cfg)

        class LostReply:
            lose_reply = True

            def write(self, rows, gaps):
                sink.write(rows, gaps)
                if self.lose_reply:
                    self.lose_reply = False
                    raise ConnectionError("commit response lost")

        with tempfile.TemporaryDirectory() as directory:
            pipeline = ProductionPipeline(self.cfg, Path(directory), LostReply())
            pipeline.capture([1, 2, 3, 4], end_time_ns=1_700_000_001_000_000_000)
            with self.assertRaisesRegex(ConnectionError, "response lost"):
                pipeline.flush_once()
            self.assertEqual(pipeline.pending_batches, 1)
            pipeline.capture([1, 2, 3, 4], end_time_ns=1_700_000_001_000_500_000)
            pipeline.flush_once()
            pipeline.flush_once()
            self.assertEqual(pipeline.pending_batches, 0)
            with psycopg2.connect(self.dsn) as conn:
                with conn.cursor() as cur:
                    cur.execute(sql.SQL("""SELECT COUNT(*), COUNT(DISTINCT sample_id),
                        MIN(time), MAX(time) FROM {} WHERE session_id=%s""").format(
                        sql.Identifier(self.table)), (pipeline.session_id,))
                    count, unique, first, last = cur.fetchone()
                    self.assertEqual((count, unique), (8, 8))
                    self.assertLess(first, last)
            pipeline.close()

if __name__ == "__main__":
    unittest.main()
