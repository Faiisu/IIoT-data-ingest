"""Behavior checks for the standalone production container boundary."""

import os
import subprocess
import tempfile
import unittest
from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parents[3]
SERVICE = ROOT / "services" / "daq_navi"


class ProductionRuntimeTests(unittest.TestCase):
    def test_explicit_mockup_uses_separate_table(self):
        from services.daq_navi.core import mockup_stream_to_db

        cfg = mockup_stream_to_db.config
        self.assertEqual(cfg.DB_TABLE, cfg.DB_MOCKUP_TABLE)
        self.assertNotEqual(cfg.DB_TABLE, cfg.DB_PRODUCTION_TABLE)

    def test_failed_hardware_run_does_not_launch_mockup(self):
        with tempfile.TemporaryDirectory() as directory:
            log = Path(directory) / "invocations"
            python_stub = Path(directory) / "python-stub"
            python_stub.write_text(
                "#!/bin/sh\n"
                'printf "%s\\n" "$*" >> "$INVOCATION_LOG"\n'
                "exit 17\n"
            )
            python_stub.chmod(0o755)

            env = os.environ.copy()
            env.update(
                {
                    "PYTHON_BIN": str(python_stub),
                    "INVOCATION_LOG": str(log),
                    "MOCKUP_MODE": "false",
                    "ENABLE_WEB_UI": "false",
                    "HEADLESS": "true",
                    "AUTO_FALLBACK": "true",
                }
            )
            result = subprocess.run(
                ["bash", str(SERVICE / "entrypoint.sh")],
                cwd=SERVICE,
                env=env,
                capture_output=True,
                text=True,
                timeout=10,
                check=False,
            )

            invocations = log.read_text().splitlines() if log.exists() else []
            self.assertNotEqual(result.returncode, 0)
            self.assertFalse(any("mockup_stream_to_db" in call for call in invocations))

    def test_compose_persists_standalone_buffer(self):
        config = yaml.safe_load((ROOT / "docker-compose.yml").read_text())
        mounts = config["services"]["daq-navi"]["volumes"]
        self.assertIn("daq_spool:/var/lib/daq_navi/spool", mounts)
        self.assertIn("daq_spool", config["volumes"])


if __name__ == "__main__":
    unittest.main()
