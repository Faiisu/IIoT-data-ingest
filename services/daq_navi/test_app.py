# test_app.py
# Verification tests for DAQ USB-4716 Web API (CORS, Status Schema, Interface Binding)

import os
import sys
import unittest

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

from services.daq_navi.app import app


class TestDaqUsb4716App(unittest.TestCase):

    def setUp(self):
        self.client = app.test_client()

    def test_cors_headers_on_get(self):
        """Verify CORS headers are present on GET responses."""
        res = self.client.get('/api/status')
        self.assertEqual(res.status_code, 200)
        self.assertEqual(res.headers.get('Access-Control-Allow-Origin'), '*')
        self.assertEqual(res.headers.get('Access-Control-Allow-Methods'), 'GET, POST, OPTIONS')
        self.assertEqual(res.headers.get('Access-Control-Allow-Headers'), 'Content-Type, Authorization')

    def test_options_preflight(self):
        """Verify OPTIONS preflight request returns 204 with CORS headers."""
        res = self.client.options('/api/status')
        self.assertEqual(res.status_code, 204)
        self.assertEqual(res.headers.get('Access-Control-Allow-Origin'), '*')
        self.assertEqual(res.headers.get('Access-Control-Allow-Methods'), 'GET, POST, OPTIONS')
        self.assertEqual(res.headers.get('Access-Control-Allow-Headers'), 'Content-Type, Authorization')

    def test_standardized_status_schema(self):
        """Verify /api/status returns standardized fields matching portal contract."""
        res = self.client.get('/api/status')
        self.assertEqual(res.status_code, 200)
        data = res.get_json()

        # Required standardized top-level keys
        self.assertEqual(data.get('service_name'), 'DAQ USB-4716')
        self.assertEqual(data.get('port'), 8081)
        self.assertIsInstance(data.get('is_running'), bool)
        self.assertIn('status', data)
        self.assertEqual(data.get('status'), 'running' if data['is_running'] else 'stopped')
        self.assertIn('mode', data)
        self.assertIn('run_mode', data)

        # Service specific retained fields
        self.assertIn('destination', data)
        self.assertIn('pid', data)

    def test_host_binding_verification(self):
        """Verify entrypoint specifies host='0.0.0.0' for LAN edge deployment."""
        app_py_path = os.path.join(os.path.dirname(__file__), 'app.py')
        with open(app_py_path, 'r', encoding='utf-8') as f:
            content = f.read()
        self.assertIn("host='0.0.0.0'", content)
        self.assertIn("port=8081", content)


if __name__ == '__main__':
    unittest.main()
