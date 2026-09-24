"""A stale PID file must not hide an active acquisition child process."""

import importlib
import tempfile
import time
import unittest
from pathlib import Path
from unittest.mock import patch

web = importlib.import_module('services.daq_navi.web.app')


class ProcessRecoveryTests(unittest.TestCase):
    def test_status_and_start_recover_live_child_when_pid_file_is_stale(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'acquisition.pid').write_text('921')
            (root / 'acquisition.mode').write_text('production')
            children = root / 'proc/self/task/1/children'
            children.parent.mkdir(parents=True)
            children.write_text('710 921 ')
            child = root / 'proc/710/cmdline'
            child.parent.mkdir(parents=True)
            child.write_bytes(
                b'/usr/local/bin/python3\0' +
                str(Path(web.CORE_DIR) / 'stream_to_db.py').encode() + b'\0'
                b'--config\0' + str(root / 'config.json').encode() + b'\0')

            with patch.object(web, 'PID_PATH', str(root / 'acquisition.pid')), \
                 patch.object(web, 'MODE_PATH', str(root / 'acquisition.mode')), \
                 patch.object(web, 'CONFIG_PATH', str(root / 'config.json')), \
                 patch.object(web, 'PROC_ROOT', root / 'proc', create=True), \
                 patch.object(web, 'is_pid_running', side_effect=lambda pid: pid == 710), \
                 patch.object(web, 'read_config', return_value={
                     'AUTO_START_ON_STARTUP': False, 'AUTO_START_MODE': 'production',
                     'DESTINATION': 'postgresql'}), \
                 patch.object(web, 'read_runtime_status', return_value={
                     'checked_at_ns': time.time_ns(), 'state': 'running'}), \
                 patch.object(web, 'read_recent_gaps', return_value=[]):
                status = web.app.test_client().get('/api/status').get_json()
                start = web.start_acquisition('production')

            self.assertTrue(status['is_running'])
            self.assertEqual(status['pid'], 710)
            self.assertEqual(status['status'], 'running')
            self.assertFalse(start['started'])
            self.assertIn('already running', start['message'])
            self.assertEqual((root / 'acquisition.pid').read_text(), '710')


if __name__ == '__main__':
    unittest.main()
