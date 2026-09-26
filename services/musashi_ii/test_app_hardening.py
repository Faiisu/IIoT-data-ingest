# test_app_hardening.py
# Verification tests for Musashi II Web Control Panel hardening

import os
import sys
import subprocess
import time
import json
import unittest

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

try:
    from services.musashi_ii.app import (
        app, is_pid_running, terminate_pid, validate_config, write_config,
        sanitize_error, get_running_process, PID_PATH, MODE_PATH
    )
except ModuleNotFoundError:
    from app import (
        app, is_pid_running, terminate_pid, validate_config, write_config,
        sanitize_error, get_running_process, PID_PATH, MODE_PATH
    )


class TestMusashiIIAppHardening(unittest.TestCase):

    def test_pid_liveness_and_recycling_guard(self):
        """Verify is_pid_running detects process existence and prevents PID recycling hazards."""
        # Non-existent PID
        self.assertFalse(is_pid_running(9999999))

        # Current process does not contain 'read_musashi.py'
        self.assertFalse(is_pid_running(os.getpid()))

        # Child process with 'read_musashi.py'
        dummy = subprocess.Popen(
            [sys.executable, '-c', 'import time; time.sleep(10)', 'read_musashi.py'],
            start_new_session=True
        )
        try:
            self.assertTrue(is_pid_running(dummy.pid))
        finally:
            terminate_pid(dummy.pid)
            try:
                dummy.wait(timeout=1.0)
            except Exception:
                pass
            time.sleep(0.3)
            self.assertFalse(is_pid_running(dummy.pid))

    def test_config_schema_validation(self):
        """Verify validate_config strictly enforces schemas and positive intervals."""
        # Valid config
        valid, _ = validate_config({'acquisition': {'interval_time': 1.0}})
        self.assertTrue(valid)

        # Invalid intervals
        self.assertFalse(validate_config({'acquisition': {'interval_time': -1}})[0])
        self.assertFalse(validate_config({'acquisition': {'interval_time': 0}})[0])
        self.assertFalse(validate_config({'acquisition': {'interval_time': 'invalid'}})[0])

        # Invalid serial settings
        self.assertFalse(validate_config({'serial': {'baudrate': -9600}})[0])
        self.assertFalse(validate_config({'serial': {'timeout': -1.0}})[0])

        # Invalid top-level type
        self.assertFalse(validate_config("not_a_dict")[0])

    def test_credential_sanitization(self):
        """Verify sanitize_error masks credentials and sensitive values in exceptions."""
        secret = "super_secret_password_123"
        msg = f"Failed connecting to postgresql://admin:{secret}@10.0.0.1:5432/db with {secret}"
        sanitized = sanitize_error(msg, [secret])
        self.assertNotIn(secret, sanitized)
        self.assertIn("******", sanitized)

    def test_api_status_standardized_fields(self):
        """Verify /api/status returns standardized fields matching portal contract."""
        client = app.test_client()
        res = client.get('/api/status')
        self.assertEqual(res.status_code, 200)
        data = res.get_json()
        self.assertEqual(data['service_name'], 'MUSASHI II')
        self.assertEqual(data['port'], 8082)
        self.assertIn('mode', data)
        self.assertIn('run_mode', data)
        self.assertIn('is_running', data)
        self.assertIn('status', data)
        self.assertEqual(data['status'], 'running' if data['is_running'] else 'stopped')
        self.assertIn('serial_port', data)
        self.assertIn('db_type', data)

    def test_cors_headers_and_preflight(self):
        """Verify CORS headers on responses and preflight OPTIONS handler."""
        client = app.test_client()
        # Test GET CORS headers
        res = client.get('/api/status')
        self.assertEqual(res.headers.get('Access-Control-Allow-Origin'), '*')
        self.assertEqual(res.headers.get('Access-Control-Allow-Methods'), 'GET, POST, OPTIONS')
        self.assertEqual(res.headers.get('Access-Control-Allow-Headers'), 'Content-Type, Authorization')

        # Test OPTIONS preflight
        res_opt = client.options('/api/status')
        self.assertEqual(res_opt.status_code, 204)
        self.assertEqual(res_opt.headers.get('Access-Control-Allow-Origin'), '*')
        self.assertEqual(res_opt.headers.get('Access-Control-Allow-Methods'), 'GET, POST, OPTIONS')
        self.assertEqual(res_opt.headers.get('Access-Control-Allow-Headers'), 'Content-Type, Authorization')

    def test_api_test_serial_port_collision_guard(self):
        """Verify /api/test_serial refuses to open port when active ingestion worker is running."""
        client = app.test_client()
        dummy = subprocess.Popen(
            [sys.executable, '-c', 'import time; time.sleep(10)', 'read_musashi.py'],
            start_new_session=True
        )
        try:
            with open(PID_PATH, 'w') as f:
                f.write(str(dummy.pid))
            with open(MODE_PATH, 'w') as f:
                f.write('real')

            res = client.post('/api/test_serial', json={'serial': {'port': 'COM1'}})
            self.assertEqual(res.status_code, 200)
            data = res.get_json()
            self.assertFalse(data['success'])
            self.assertIn('currently in use by active worker', data['message'])
        finally:
            terminate_pid(dummy.pid)
            try:
                dummy.wait(timeout=1.0)
            except Exception:
                pass
            if os.path.exists(PID_PATH):
                try: os.remove(PID_PATH)
                except OSError: pass
            if os.path.exists(MODE_PATH):
                try: os.remove(MODE_PATH)
                except OSError: pass

    def test_api_test_db_credential_protection(self):
        """Verify /api/test_db does not leak plaintext passwords in connection errors."""
        client = app.test_client()
        secret_pw = "my_classified_db_pass_5544"
        res = client.post('/api/test_db', json={
            'database': {
                'db_type': 'postgresql',
                'host': '127.0.0.1',
                'port': 54321,
                'user': 'admin',
                'password': secret_pw,
                'db_name': 'test_db'
            }
        })
        self.assertEqual(res.status_code, 200)
        data = res.get_json()
        self.assertFalse(data['success'])
        self.assertNotIn(secret_pw, data['message'])


if __name__ == '__main__':
    unittest.main()
