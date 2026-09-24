"""Rehearse child crash, full spool, DAQ open error, and explicit mockup via web API."""

import importlib
import json
import os
import signal
import tempfile
import time
import uuid
from pathlib import Path

import psycopg2
from psycopg2 import sql


ROOT = Path(__file__).resolve().parents[3]


def main():
    dsn = os.environ.get('DAQ_TEST_DB_DSN', '')
    dbname = psycopg2.extensions.parse_dsn(dsn).get('dbname', '')
    if not dbname.startswith('daq_navi_test_'):
        raise SystemExit('DAQ_TEST_DB_DSN must name a daq_navi_test_* database')
    web = importlib.import_module('services.daq_navi.web.app')
    run_id = uuid.uuid4().hex[:10]
    table = f'web_faults_{run_id}'
    mockup = f'web_mockup_{run_id}'
    report = {'database': dbname, 'production_table': table, 'mockup_table': mockup}
    source = json.loads((ROOT / 'services/daq_navi/config.json').read_text(encoding='utf-8'))
    with tempfile.TemporaryDirectory(prefix='daq_web_faults_') as directory:
        root = Path(directory)
        source.update(DB_DSN=dsn, DB_PRODUCTION_TABLE=table, DB_MOCKUP_TABLE=mockup,
                      SPOOL_DIR=str(root / 'spool'), AUTO_START_ON_STARTUP=False,
                      AUTO_START_MODE='production', MOCKUP_MODE=False)
        config = root / 'config.json'
        config.write_text(json.dumps(source), encoding='utf-8')
        web.CONFIG_PATH = str(config)
        web.PID_PATH = str(root / 'acquisition.pid')
        web.MODE_PATH = str(root / 'acquisition.mode')
        web.LOG_PATH = str(root / 'acquisition.log')
        client = web.app.test_client()
        try:
            # A killed child leaves a fault and an open gap; a new Start replays the spool.
            first = client.post('/api/start', json={'mode': 'production'}).get_json()
            if not first['started']:
                raise RuntimeError(first)
            time.sleep(2)
            os.kill(first['pid'], signal.SIGKILL)
            time.sleep(0.7)
            report['crash_status'] = client.get('/api/status').get_json()
            report['crash_health_code'] = client.get('/api/health').status_code
            restarted = client.post('/api/start', json={'mode': 'production'}).get_json()
            report['restart'] = restarted
            if not restarted['started']:
                raise RuntimeError(restarted)
            time.sleep(3)
            report['crash_recovery_stop'] = client.post('/api/stop').get_json()

            # An invalid device must fault, never switch to mockup.
            saved = client.post('/api/config', json={'DEVICE_DESCRIPTION': 'NO_SUCH_DAQ'})
            if saved.status_code != 200:
                raise RuntimeError(saved.get_json())
            report['daq_error_start'] = client.post('/api/start', json={'mode': 'production'}).get_json()
            time.sleep(1)
            report['daq_error_status'] = client.get('/api/status').get_json()
            report['daq_error_health_code'] = client.get('/api/health').status_code
            client.post('/api/stop')

            # The application must stop physical acquisition when the spool is full.
            saved = client.post('/api/config', json={
                'DEVICE_DESCRIPTION': source['DEVICE_DESCRIPTION'],
                'SPOOL_DIR': str(root / 'small-spool'),
                'SPOOL_MAX_BYTES': 1,
            })
            if saved.status_code != 200:
                raise RuntimeError(saved.get_json())
            report['full_buffer_start'] = client.post('/api/start', json={'mode': 'production'}).get_json()
            time.sleep(2)
            report['full_buffer_status'] = client.get('/api/status').get_json()
            report['full_buffer_health_code'] = client.get('/api/health').status_code
            client.post('/api/stop')

            # Mockup is a separate explicit selection and separate table.
            saved = client.post('/api/config', json={'SPOOL_MAX_BYTES': source['SPOOL_MAX_BYTES']})
            if saved.status_code != 200:
                raise RuntimeError(saved.get_json())
            report['mockup_start'] = client.post('/api/start', json={'mode': 'mockup'}).get_json()
            time.sleep(3)
            report['mockup_status'] = client.get('/api/status').get_json()
            report['mockup_stop'] = client.post('/api/stop').get_json()
        finally:
            client.post('/api/stop')
            report['log_tail'] = (root / 'acquisition.log').read_text(encoding='utf-8')[-2200:] if (root / 'acquisition.log').exists() else ''
        with psycopg2.connect(dsn) as conn:
            with conn.cursor() as cursor:
                cursor.execute(sql.SQL('SELECT count(*),count(distinct sample_id) FROM {}').format(sql.Identifier(table)))
                report['production_rows'] = list(cursor.fetchone())
                cursor.execute('SELECT to_regclass(%s)', (mockup,))
                if cursor.fetchone()[0]:
                    cursor.execute(sql.SQL('SELECT count(*) FROM {}').format(sql.Identifier(mockup)))
                    report['mockup_rows'] = cursor.fetchone()[0]
                else:
                    report['mockup_rows'] = 0
        target = ROOT / '.scratch/daq-navi-production/qualification' / f'web-faults-{run_id}.json'
        target.write_text(json.dumps(report, indent=2, default=str), encoding='utf-8')
        for name in (table, mockup):
            for attempt in range(5):
                try:
                    with psycopg2.connect(dsn) as conn:
                        with conn.cursor() as cursor:
                            cursor.execute(sql.SQL('DROP TABLE IF EXISTS {} CASCADE').format(sql.Identifier(name)))
                    break
                except psycopg2.Error:
                    time.sleep(0.5)
        print(target)
        print('crash:', report['crash_status']['status'], report['crash_health_code'])
        print('DAQ error:', report['daq_error_status']['status'], report['daq_error_health_code'])
        print('full buffer:', report['full_buffer_status']['status'], report['full_buffer_health_code'])
        print('production rows:', report['production_rows'], 'mockup rows:', report['mockup_rows'])
        if (report['crash_status']['status'] != 'faulted' or report['crash_health_code'] != 503 or
                report['daq_error_status']['status'] != 'faulted' or report['daq_error_health_code'] != 503 or
                report['full_buffer_status']['status'] != 'faulted' or report['full_buffer_health_code'] != 503 or
                report['production_rows'][0] < 1 or report['production_rows'][0] != report['production_rows'][1] or
                report['mockup_rows'] < 1 or report['mockup_status']['mode'] != 'mockup'):
            raise SystemExit(1)


if __name__ == '__main__':
    main()
