"""Public command-line checks for the isolated physical DAQ qualification runner."""

import json
from datetime import datetime, timedelta, timezone
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


SERVICE = Path(__file__).resolve().parents[1]
RUNNER = SERVICE / "tests" / "qualify_standalone.py"
OUTAGE_RUNNER = SERVICE / "tests" / "qualify_outage_replay.py"
if str(SERVICE / "tests") not in sys.path:
    sys.path.insert(0, str(SERVICE / "tests"))


class QualificationRunnerTests(unittest.TestCase):
    def test_replay_comparison_checks_every_timestamp_and_value(self):
        from qualify_outage_replay import compare_replayed_rows

        at = datetime(2026, 9, 24, tzinfo=timezone.utc)
        expected = [{
            "sample_id": "session:0:0",
            "time_ns": int(at.timestamp()) * 1_000_000_000 + 123,
            "raw_voltage": 1.0,
            "calibrated_value": 20.0,
            "unit": "kPa",
            "channel": 0,
        }]
        stored = [("session:0:0", at, 1.0, 20.0, "kPa", 0)]
        result = compare_replayed_rows(expected, stored)
        self.assertEqual(result["missing_sample_ids"], 0)
        self.assertEqual(result["value_mismatches"], 0)
        self.assertEqual(result["maximum_timestamp_rounding_ns"], 123)
        altered = [("session:0:0", at, 2.0, 20.0, "kPa", 0)]
        self.assertEqual(compare_replayed_rows(expected, altered)["value_mismatches"], 1)

    def test_physical_assessment_rejects_missing_sample_window(self):
        from qualify_standalone import assess

        start = datetime(2026, 9, 24, tzinfo=timezone.utc)
        rows = [{
            "channel": channel,
            "count": 18000,
            "unique_sample_ids": 18000,
            "first_utc": start.isoformat(),
            "last_utc": (start + timedelta(seconds=10)).isoformat(),
            "rate_from_timestamps_hz": 2000,
            "max_calibration_error_v": 0,
            "sessions": 1,
            "wrong_provenance_rows": 0,
        } for channel in range(4)]
        errors = assess(rows, [], 10, 2000, start.timestamp(),
                        (start + timedelta(seconds=10)).timestamp(), 0, False, False)
        self.assertTrue(any("missing over half a second" in error for error in errors))

    def test_refuses_a_non_test_database_before_touching_hardware(self):
        result = subprocess.run(
            [sys.executable, str(RUNNER), "--test-dsn", "postgresql:///daq_db", "--duration", "2"],
            cwd=SERVICE,
            capture_output=True,
            text=True,
            timeout=10,
            check=False,
        )
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("daq_navi_test_", result.stderr)

    def test_outage_runner_refuses_a_non_test_database(self):
        result = subprocess.run(
            [sys.executable, str(OUTAGE_RUNNER), "--test-dsn", "postgresql:///daq_db"],
            cwd=SERVICE,
            capture_output=True,
            text=True,
            timeout=10,
            check=False,
        )
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("daq_navi_test_", result.stderr)

    def test_prepares_four_channel_identity_calibration_in_isolated_config(self):
        with tempfile.TemporaryDirectory() as directory:
            config_path = Path(directory) / "qualification.json"
            result = subprocess.run(
                [
                    sys.executable,
                    str(RUNNER),
                    "--test-dsn", "postgresql:///daq_navi_test_example",
                    "--prepare-only",
                    "--output-config", str(config_path),
                    "--spool-dir", str(Path(directory) / "spool"),
                    "--table", "daq_qualification_example",
                ],
                cwd=SERVICE,
                capture_output=True,
                text=True,
                timeout=10,
                check=False,
            )
            self.assertEqual(result.returncode, 0, result.stderr)
            prepared = json.loads(config_path.read_text())
            self.assertEqual(prepared["DB_DSN"], "postgresql:///daq_navi_test_example")
            self.assertFalse(prepared["MOCKUP_MODE"])
            self.assertEqual(prepared["DESTINATION"], "postgresql")
            self.assertEqual(prepared["START_CHANNEL"], 0)
            self.assertEqual(prepared["CHANNEL_COUNT"], 4)
            self.assertEqual(prepared["CLOCK_RATE"], 2000)
            self.assertEqual(prepared["DB_PRODUCTION_TABLE"], "daq_qualification_example")
            for channel in range(4):
                settings = prepared["CHANNELS"][str(channel)]
                self.assertTrue(settings["enabled"])
                self.assertEqual(settings["unit"], "V")
                self.assertEqual(settings["scale"]["revision"], "qualification-identity-v1")
                self.assertEqual(settings["scale"]["low_voltage"], settings["scale"]["low_value"])
                self.assertEqual(settings["scale"]["high_voltage"], settings["scale"]["high_value"])


if __name__ == "__main__":
    unittest.main()
