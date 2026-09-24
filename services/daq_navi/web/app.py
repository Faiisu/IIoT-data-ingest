# web_gui.py
# See: docs/architecture/context.md
# English comments only

try:
    import eventlet
    eventlet.monkey_patch()
except Exception as _e:
    print(f"[WARNING] Eventlet initialization warning: {_e}")

import os
import sys
import json
import subprocess
import threading
import re
import time
import signal
import tempfile
import math
import uuid
from pathlib import Path
from flask import Flask, render_template, jsonify, request
from flask_socketio import SocketIO, emit


PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

from daq_navi.core.config_loader import DaqNaviConfig
from daq_navi.core.production_acquisition import (
    TimescaleProductionDestination, validate_production_config,
)

app = Flask(__name__, template_folder='templates', static_folder='static')
socketio = SocketIO(app, cors_allowed_origins="*")

@app.before_request
def handle_preflight():
    if request.method == "OPTIONS":
        return ('', 204)

@app.after_request
def add_cors_headers(response):
    response.headers['Access-Control-Allow-Origin'] = '*'
    response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS'
    response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
    return response

@app.route('/', defaults={'path': ''}, methods=['OPTIONS'])
@app.route('/<path:path>', methods=['OPTIONS'])
def options_preflight(path=''):
    return ('', 204)

# Service directory paths
WEB_DIR = os.path.dirname(os.path.abspath(__file__))
SERVICE_DIR = os.path.dirname(WEB_DIR)
CORE_DIR = os.path.join(SERVICE_DIR, 'core')

CONFIG_PATH = os.path.join(SERVICE_DIR, 'config.json')
PID_PATH = os.path.join(SERVICE_DIR, '.daq_process.pid')
MODE_PATH = os.path.join(SERVICE_DIR, '.daq_process.mode')
LOG_PATH = os.path.join(SERVICE_DIR, 'daq_pipeline.log')
PROC_ROOT = Path('/proc')

# Global monitoring variables
tail_thread = None
stop_tail_event = threading.Event()
last_stats = {}

def read_config():
    """Reads configuration parameters from config.json."""
    try:
        with open(CONFIG_PATH, 'r') as f:
            return json.load(f)
    except Exception as e:
        print(f"Error reading config.json: {e}")
        return {}

def write_config(config_data):
    """Atomically replace the saved configuration."""
    temporary = None
    try:
        config_data = {**config_data, '_WEB_MANAGED': True}
        with tempfile.NamedTemporaryFile('w', dir=os.path.dirname(CONFIG_PATH),
                                         encoding='utf-8', delete=False) as f:
            temporary = f.name
            json.dump(config_data, f, indent=2)
            f.flush()
            os.fsync(f.fileno())
        try:
            os.replace(temporary, CONFIG_PATH)
        except OSError:
            # When CONFIG_PATH is bind-mounted directly in Docker, os.replace can fail with EBUSY.
            with open(CONFIG_PATH, 'w', encoding='utf-8') as f:
                json.dump(config_data, f, indent=2)
                f.flush()
                os.fsync(f.fileno())
        return True
    except Exception as e:
        print(f"Error writing config.json: {e}")
        return False
    finally:
        if temporary and os.path.exists(temporary):
            os.unlink(temporary)


def merge_config(current, changes):
    if not isinstance(changes, dict):
        raise ValueError('Configuration must be an object')
    merged = dict(current)
    for key, value in changes.items():
        if key == 'CHANNELS':
            if not isinstance(value, dict):
                raise ValueError('CHANNELS must be an object')
            channels = {name: dict(channel) for name, channel in current.get('CHANNELS', {}).items()}
            for name, update in value.items():
                if not name.isdecimal() or not isinstance(update, dict):
                    raise ValueError('Each channel must be an object with a numeric key')
                channel = dict(channels.get(name, {}))
                for field, field_value in update.items():
                    if field == 'scale':
                        if not isinstance(field_value, dict):
                            raise ValueError(f'channel {name} scale must be an object')
                        channel[field] = {**channel.get(field, {}), **field_value}
                    else:
                        channel[field] = field_value
                channels[name] = channel
            merged[key] = channels
        elif key in current or key in ('AUTO_START_ON_STARTUP', 'AUTO_START_MODE', 'DB_RETENTION_DAYS'):
            merged[key] = value
        else:
            raise ValueError(f'Unsupported setting: {key}')
    for key in ('START_CHANNEL', 'CHANNEL_COUNT', 'CLOCK_RATE', 'SECTION_LENGTH',
                'SECTION_COUNT', 'SPOOL_MAX_BYTES', 'DB_RETENTION_DAYS'):
        if key in merged and type(merged[key]) is not int:
            raise ValueError(f'{key} must be an integer')
    if type(merged.get('AUTO_START_ON_STARTUP', False)) is not bool:
        raise ValueError('AUTO_START_ON_STARTUP must be a boolean')
    if merged.get('AUTO_START_MODE', 'production') not in ('production', 'mockup'):
        raise ValueError('AUTO_START_MODE must be production or mockup')
    if merged.get('DB_RETENTION_DAYS', 30) < 1:
        raise ValueError('DB_RETENTION_DAYS must be at least one day')
    if merged.get('CHANNEL_COUNT', 0) < 1 or merged.get('SECTION_LENGTH', 0) < 1:
        raise ValueError('CHANNEL_COUNT and SECTION_LENGTH must be positive')
    if not 1000 <= merged.get('CLOCK_RATE', 0) <= 2000:
        raise ValueError('CLOCK_RATE must be 1000–2000 Hz per channel')
    for name, channel in merged.get('CHANNELS', {}).items():
        if type(channel.get('enabled')) is not bool:
            raise ValueError(f'channel {name} enabled must be a boolean')
        scale = channel.get('scale', {})
        for field in ('low_voltage', 'high_voltage', 'low_value', 'high_value'):
            if field in scale and (type(scale[field]) not in (int, float) or
                                   not math.isfinite(scale[field])):
                raise ValueError(f'channel {name} {field} must be a finite number')
    cfg = DaqNaviConfig(merged, allow_env_overrides=False)
    if merged.get('AUTO_START_MODE', 'production') == 'production':
        validate_production_config(cfg)
    return merged

# Cross-platform utility to check if a process is still active on the host OS
def is_pid_running(pid):
    if sys.platform == "win32":
        try:
            # Query tasklist on Windows
            output = subprocess.check_output(f'tasklist /fi "PID eq {pid}"', shell=True)
            return str(pid) in str(output)
        except Exception:
            return False
    else:
        try:
            stat_path = f'/proc/{pid}/stat'
            if os.path.exists(stat_path) and Path(stat_path).read_text().split(') ', 1)[1][0] == 'Z':
                return False
            # Query signal 0 (null signal) on POSIX
            os.kill(pid, 0)
            return True
        except (OSError, ProcessLookupError):
            return False

def acquisition_mode_for_pid(pid):
    """Identify a process launched by this service from its exact command arguments."""
    if not is_pid_running(pid):
        return None
    if sys.platform == 'win32':
        return None
    try:
        arguments = (PROC_ROOT / str(pid) / 'cmdline').read_bytes().split(b'\0')
    except OSError:
        return None
    if len(arguments) < 2:
        return None
    script = arguments[1].decode(errors='replace')
    if script == os.path.join(CORE_DIR, 'mockup_stream_to_db.py'):
        return 'mockup'
    if script == os.path.join(CORE_DIR, 'stream_to_db.py'):
        for index, argument in enumerate(arguments[:-1]):
            if argument == b'--config' and arguments[index + 1] == os.fsencode(CONFIG_PATH):
                return 'production'
    return None


def find_acquisition_child():
    """Recover a live acquisition child when its PID file was overwritten."""
    if sys.platform == 'win32':
        return None, None
    try:
        tasks = (PROC_ROOT / 'self' / 'task').iterdir()
        children = set()
        for task in tasks:
            children.update(int(pid) for pid in (task / 'children').read_text().split())
    except (OSError, ValueError):
        return None, None
    for pid in sorted(children):
        mode = acquisition_mode_for_pid(pid)
        if mode:
            return pid, mode
    return None, None


# Retrieve the running process info if active
def get_running_process():
    if os.path.exists(PID_PATH) and os.path.exists(MODE_PATH):
        try:
            with open(PID_PATH, 'r') as f:
                pid = int(f.read().strip())
            with open(MODE_PATH, 'r') as f:
                mode = f.read().strip()
            
            if (sys.platform == 'win32' and is_pid_running(pid)) or acquisition_mode_for_pid(pid) == mode:
                return pid, mode
        except Exception as e:
            print(f"Error checking active PID file: {e}")
    pid, mode = find_acquisition_child()
    if pid is not None:
        Path(PID_PATH).write_text(str(pid), encoding='utf-8')
        Path(MODE_PATH).write_text(mode, encoding='utf-8')
        return pid, mode
    return None, None

# Terminate process by PID cross-platform
def terminate_pid(pid):
    if sys.platform == "win32":
        try:
            subprocess.run(f"taskkill /pid {pid} /t /f", shell=True)
        except Exception as e:
            print(f"Error terminating Windows PID {pid}: {e}")
    else:
        try:
            os.kill(pid, 15) # SIGTERM (graceful exit)
            # The production writer has a 10-second drain window and a 15-second join.
            for _ in range(250):
                if not is_pid_running(pid):
                    return True
                time.sleep(0.1)
            return False
        except ProcessLookupError:
            return True
        except OSError as e:
            print(f"Error terminating Unix PID {pid}: {e}")
            return False

# Regex to extract statistics from the log file
# E.g.: [STATS] polled=1,024 | written=1,024 | dropped_batches=0 (0.0%) | db_errors=0 | queue=0/200
STATS_REGEX = re.compile(
    r"\[STATS\] polled=(?P<polled>[0-9,]+) \| written=(?P<written>[0-9,]+) \| dropped_batches=(?P<dropped>[0-9]+) \((?P<loss_pct>[0-9\.]+)%\) \| db_errors=(?P<errors>[0-9]+) \| queue=(?P<qsize>[0-9]+)/(?P<qmax>[0-9]+)"
)

def parse_and_emit_stats(line):
    """Parses stats from a line and updates global caches."""
    global last_stats
    match = STATS_REGEX.search(line)
    if match:
        last_stats = {
            'polled': match.group('polled'),
            'written': match.group('written'),
            'dropped': match.group('dropped'),
            'loss_pct': match.group('loss_pct'),
            'errors': match.group('errors'),
            'queue_util': f"{match.group('qsize')}/{match.group('qmax')}"
        }
        socketio.emit('stats_update', last_stats)

def tail_log_file():
    """Background loop tailing the physical log file to feed sockets."""
    global last_stats
    print("[SYSTEM] Log tailing thread started.")
    
    # Wait until log file is created
    while not os.path.exists(LOG_PATH) and not stop_tail_event.is_set():
        time.sleep(0.2)
        
    try:
        with open(LOG_PATH, 'r', errors='replace') as f:
            # Start tailing from the end of the file
            f.seek(0, os.SEEK_END)
            
            while not stop_tail_event.is_set():
                pid, _ = get_running_process()
                if pid is None:
                    # DAQ process stopped; close tailing thread and notify client
                    cfg = read_config()
                    try:
                        rec_mode = Path(MODE_PATH).read_text(encoding='utf-8').strip()
                    except OSError:
                        rec_mode = None
                    stopped_mode = rec_mode or cfg.get('AUTO_START_MODE', 'production')
                    socketio.emit('status_change', {'is_running': False, 'mode': stopped_mode})
                    break
                    
                line = f.readline()
                if not line:
                    time.sleep(0.1)
                    continue
                
                decoded_line = line.strip()
                # Broadcast log line to connected sockets
                socketio.emit('log_update', {'log': decoded_line})
                parse_and_emit_stats(decoded_line)
                
    except Exception as e:
        print(f"Error tailing log file: {e}")
    finally:
        print("[SYSTEM] Log tailing thread finished.")

def start_tailing():
    """Starts a new background tailing thread if not active."""
    global tail_thread, stop_tail_event
    stop_tail_event.clear()
    if tail_thread is None or not tail_thread.is_alive():
        tail_thread = threading.Thread(target=tail_log_file, daemon=True)
        tail_thread.start()

def get_last_logs(count=50):
    """Retrieves last few log lines for newly connected clients."""
    if not os.path.exists(LOG_PATH):
        return []
    try:
        with open(LOG_PATH, 'r', errors='replace') as f:
            lines = f.readlines()
            return [line.strip() for line in lines[-count:]]
    except Exception as e:
        print(f"Error reading historical logs: {e}")
        return []

def scan_host_usb_devices():
    """Scan installed Advantech DAQ cards and serial ports on this host."""
    detected = []
    warnings = []

    # Use the installed DAQNavi enumerator so the device ID matches acquisition.
    try:
        result = subprocess.run(
            ['/opt/advantech/tools/dev_enum'],
            capture_output=True, text=True, timeout=5, check=True,
        )
        for line in result.stdout.splitlines():
            row = re.match(r'^\|\s*\d+\s*\|\s*\d+\s*\|\s*([^|]+?)\s*\|', line)
            if not row:
                continue
            description = row.group(1).strip()
            board_id = re.search(r'BID#\d+', description)
            detected.append({
                'id': description,
                'name': f"Advantech {description}",
                'type': 'Advantech DAQ Card',
                'port': board_id.group(0) if board_id else '',
                'vendor': 'Advantech',
                'is_daq': True
            })
    except (OSError, subprocess.SubprocessError) as exc:
        print(f"[SCAN] Advantech device enumeration failed: {exc}")
        warnings.append('Advantech DAQ scan failed; check that DAQNavi is installed and the device is accessible.')

    # Serial ports may contain devices outside the Advantech DAQNavi driver.
    try:
        import serial.tools.list_ports
        ports = serial.tools.list_ports.comports()
        for p in ports:
            desc = p.description if p.description else p.device
            mfg = p.manufacturer if hasattr(p, 'manufacturer') and p.manufacturer else 'USB Serial'
            detected.append({
                'id': p.device,
                'name': f"{p.device} ({desc})",
                'type': 'USB Serial Port',
                'port': p.device,
                'vendor': mfg,
                'hwid': p.hwid if hasattr(p, 'hwid') else '',
                'is_daq': False
            })
    except Exception as exc:
        print(f"[SCAN] Serial port scan failed: {exc}")
        warnings.append('Serial port scan failed.')

    # Deduplicate by 'id' while retaining order
    seen = set()
    unique_detected = []
    for d in detected:
        if d['id'] not in seen:
            seen.add(d['id'])
            unique_detected.append(d)

    return unique_detected, warnings

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/api/config', methods=['GET'])
def get_config():
    return jsonify(read_config())

@app.route('/api/config', methods=['POST'])
def save_config():
    try:
        current = read_config()
        payload = request.get_json(silent=True)
        updated = merge_config(current, payload)
    except (ValueError, TypeError, KeyError) as exc:
        return jsonify({'status': 'error', 'message': str(exc)}), 400
    previous_retention = current.get('DB_RETENTION_DAYS')
    if 'DB_RETENTION_DAYS' in updated and updated['DB_RETENTION_DAYS'] != previous_retention:
        try:
            TimescaleProductionDestination(DaqNaviConfig(updated, allow_env_overrides=False)).ensure_schema()
        except Exception as exc:
            return jsonify({'status': 'error', 'message': f'Could not apply retention policy: {exc}'}), 503
    if not write_config(updated):
        return jsonify({'status': 'error', 'message': 'Failed to save configuration.'}), 500
    pid, mode = get_running_process()
    if pid is not None:
        stop_result = stop_acquisition(manual=False)
        if not stop_result['stopped']:
            return jsonify({'status': 'error', 'message': 'Saved; prior session is still stopping',
                            'config': updated, **stop_result}), 503
        target_mode = updated.get('AUTO_START_MODE') if ('AUTO_START_MODE' in (payload or {})) else (mode or updated.get('AUTO_START_MODE', 'production'))
        start_result = start_acquisition(target_mode)
        if not start_result['started']:
            return jsonify({'status': 'error', 'message': 'Saved; restart failed',
                            'config': updated, **start_result}), 503
        drained = stop_result.get('drained', not stop_result.get('pending_replay', False))
        pending_replay = stop_result.get('pending_replay', False)
        pending_batches = stop_result.get('pending_batches', 0)
        return jsonify({
            'status': 'success',
            'config': updated,
            'retention_days': updated['DB_RETENTION_DAYS'],
            'previous_session': {
                'stopped': True,
                'drained': drained,
                'pending_replay': pending_replay,
                'pending_batches': pending_batches,
            },
            'drained': drained,
            'pending_replay': pending_replay,
            'pending_batches': pending_batches,
        })
    runtime = read_runtime_status(updated)
    pending = runtime.get('pending_batches', 0)
    return jsonify({
        'status': 'success',
        'config': updated,
        'retention_days': updated['DB_RETENTION_DAYS'],
        'drained': pending == 0,
        'pending_replay': pending > 0,
        'pending_batches': pending,
    })


@app.route('/api/retention', methods=['GET'])
def get_retention():
    config = read_config()
    try:
        import psycopg2
        with psycopg2.connect(config['DB_DSN'], connect_timeout=3) as conn:
            with conn.cursor() as cursor:
                cursor.execute("""SELECT config->>'drop_after' FROM timescaledb_information.jobs
                    WHERE hypertable_name=%s AND proc_name='policy_retention'""",
                               (config['DB_PRODUCTION_TABLE'],))
                row = cursor.fetchone()
        if row is None:
            return jsonify({'saved_days': config.get('DB_RETENTION_DAYS', 30),
                            'message': 'No active production retention policy'}), 503
        return jsonify({'saved_days': config.get('DB_RETENTION_DAYS', 30), 'effective': row[0]})
    except Exception as exc:
        return jsonify({'saved_days': config.get('DB_RETENTION_DAYS'),
                        'message': f'Could not read retention policy: {exc}'}), 503

def _test_destination(settings):
    import urllib.error
    import urllib.parse
    import urllib.request

    saved = read_config()
    value = lambda key, default='': settings[key] if key in settings else saved.get(key, default)
    destination = settings.get('DESTINATION', settings.get('destination', saved.get('DESTINATION', 'postgresql')))

    if destination in ('postgresql', 'timescaledb', 'database'):
        import psycopg2

        dsn = value('DB_DSN')
        if dsn:
            connection = psycopg2.connect(dsn, connect_timeout=3)
        else:
            connection = psycopg2.connect(
                host=value('DB_HOST', 'localhost'), port=value('DB_PORT', 5432),
                user=value('DB_USER', 'admin'), password=value('DB_PASSWORD'),
                dbname=value('DB_NAME', 'daq_db'), connect_timeout=3,
            )
        try:
            with connection.cursor() as cursor:
                cursor.execute('SELECT 1')
                cursor.fetchone()
        finally:
            connection.close()
        return 'PostgreSQL connection and query succeeded. No sample data was written.'

    if destination == 'influxdb':
        url = str(value('INFLUX_URL')).rstrip('/')
        org = str(value('INFLUX_ORG'))
        bucket = str(value('INFLUX_BUCKET'))
        token = str(value('INFLUX_TOKEN'))
        parsed = urllib.parse.urlsplit(url)
        if parsed.scheme not in ('http', 'https') or not parsed.hostname:
            raise ValueError('Enter a valid InfluxDB HTTP(S) URL.')
        if not org or not bucket or not token:
            raise ValueError('InfluxDB organization, bucket, and token are required.')
        headers = {'Authorization': f'Token {token}', 'Accept': 'application/json'}

        def get_resource(path, query):
            target = f"{url}{path}?{urllib.parse.urlencode(query)}"
            probe = urllib.request.Request(target, headers=headers, method='GET')
            try:
                with urllib.request.urlopen(probe, timeout=4.0) as response:
                    return json.load(response)
            except urllib.error.HTTPError as exc:
                if exc.code in (401, 403):
                    raise ValueError(
                        f'InfluxDB denied metadata access (HTTP {exc.code}). '
                        'Check the token and grant read access to organizations and buckets.'
                    ) from exc
                raise

        orgs = get_resource('/api/v2/orgs', {'org': org}).get('orgs', [])
        selected_org = next((entry for entry in orgs if entry.get('name') == org), None)
        if not selected_org:
            raise ValueError('InfluxDB organization is unavailable to this token.')
        buckets = get_resource('/api/v2/buckets', {'name': bucket, 'orgID': selected_org['id']}).get('buckets', [])
        if not any(entry.get('name') == bucket and entry.get('orgID') == selected_org['id'] for entry in buckets):
            raise ValueError('InfluxDB bucket is unavailable to this token.')
        return 'InfluxDB connection, token, organization, and bucket verified. No sample data was written.'

    if destination == 'mqtt':
        import paho.mqtt.client as mqtt

        broker = str(value('MQTT_BROKER'))
        if not broker:
            raise ValueError('MQTT broker host is required.')
        port = int(value('MQTT_PORT', 1883))
        if not 1 <= port <= 65535:
            raise ValueError('MQTT port must be between 1 and 65535.')
        client = mqtt.Client(
            mqtt.CallbackAPIVersion.VERSION2,
            client_id=f'daq-connection-test-{uuid.uuid4().hex[:8]}',
            reconnect_on_failure=False,
        )
        client.connect_timeout = 4.0
        username = value('MQTT_USERNAME')
        if username:
            client.username_pw_set(username, value('MQTT_PASSWORD'))
        if value('MQTT_TLS_ENABLED', False):
            client.tls_set(
                ca_certs=value('MQTT_CA_CERTS') or None,
                certfile=value('MQTT_CLIENT_CERT') or None,
                keyfile=value('MQTT_CLIENT_KEY') or None,
            )
        connected = threading.Event()
        result = {'reason': None}

        def on_connect(_client, _userdata, _flags, reason_code, _properties):
            result['reason'] = reason_code
            connected.set()

        client.on_connect = on_connect
        loop_started = False
        try:
            rc = client.connect(broker, port, keepalive=10)
            if rc != mqtt.MQTT_ERR_SUCCESS:
                raise ConnectionError(f'MQTT transport error: {mqtt.error_string(rc)}')
            client.loop_start()
            loop_started = True
            if not connected.wait(4.0):
                raise TimeoutError('MQTT broker did not acknowledge the connection.')
            if result['reason'] != 0:
                raise ConnectionError(f'MQTT broker refused the connection: {result["reason"]}')
        finally:
            if loop_started:
                client.loop_stop()
            client.disconnect()
        return 'MQTT broker accepted the connection. No message was published.'

    raise ValueError('Unsupported destination.')


@app.route('/api/test_destination', methods=['POST'])
@app.route('/api/test_db', methods=['POST'])
def test_destination():
    settings = request.get_json(silent=True)
    if not isinstance(settings, dict):
        return jsonify({'success': False, 'message': 'Request must be a JSON object.'}), 400
    try:
        message = _test_destination(settings)
        return jsonify({'success': True, 'message': message})
    except (ValueError, TypeError) as exc:
        return jsonify({'success': False, 'message': str(exc)}), 400
    except Exception as exc:
        return jsonify({'success': False, 'message': f'Connection failed: {exc}'}), 502

@app.route('/api/status', methods=['GET'])
def get_status():
    pid, mode = get_running_process()
    is_running = pid is not None
    config = read_config()
    try:
        recorded_mode = Path(MODE_PATH).read_text(encoding='utf-8').strip()
    except OSError:
        recorded_mode = None
    mode_val = mode or recorded_mode or config.get('AUTO_START_MODE', 'production')
    dest = config.get('DESTINATION', 'postgresql')
    runtime = read_runtime_status(config) if mode_val == 'production' else {}
    stale_pid = os.path.exists(PID_PATH) and not is_running
    fault = runtime.get('last_fault') or ('acquisition_process_exited' if stale_pid else None)
    expected = mode_val == 'production' and (
        bool(config.get('AUTO_START_ON_STARTUP', False)) or os.path.exists(PID_PATH))
    fresh = time.time_ns() - runtime.get('checked_at_ns', 0) < 10_000_000_000
    status = {
        'service_name': 'DAQ USB-4716',
        'port': 8081,
        'is_running': is_running,
        'status': ('faulted' if fault else
                   'buffering' if is_running and runtime.get('last_writer_error') else
                   'running' if is_running else 'stopped'),
        'mode': mode_val,
        'run_mode': mode_val,
        'pid': pid,
        'destination': dest,
        'expected_running': expected,
        'healthy': (not fault and not runtime.get('last_writer_error') and
                    (not expected or (is_running and fresh and runtime.get('state') == 'running'))),
        'fault': fault,
        'pending_batches': runtime.get('pending_batches', 0),
        'pending_bytes': runtime.get('pending_bytes', 0),
        'spool_bytes': runtime.get('spool_bytes', 0),
        'last_sample_ns': runtime.get('last_sample_ns'),
        'writer_error': runtime.get('last_writer_error'),
        'gaps': read_recent_gaps(config),
        'retention_days': config.get('DB_RETENTION_DAYS', 30),
    }
    return jsonify(status)


def read_runtime_status(config):
    path = Path(config.get('SPOOL_DIR', '/var/lib/daq_navi/spool')) / 'status.json'
    try:
        return json.loads(path.read_text(encoding='utf-8'))
    except (OSError, ValueError):
        return {}


def read_recent_gaps(config):
    import sqlite3
    path = Path(config.get('SPOOL_DIR', '/var/lib/daq_navi/spool')) / 'production-spool.sqlite3'
    if not path.exists():
        return []
    try:
        with sqlite3.connect(f'file:{path}?mode=ro', uri=True, timeout=1) as conn:
            rows = conn.execute('SELECT start_ns,end_ns,cause FROM gaps ORDER BY start_ns DESC LIMIT 20').fetchall()
        return [{'start_ns': start, 'end_ns': end, 'cause': cause} for start, end, cause in rows]
    except (OSError, sqlite3.Error):
        return []


@app.route('/api/health', methods=['GET'])
def get_health():
    status = get_status().get_json()
    return jsonify(status), 200 if status['healthy'] else 503


@app.route('/api/samples', methods=['GET'])
def get_samples():
    try:
        channel = int(request.args.get('channel', '0'))
        if not 0 <= channel < 16:
            raise ValueError('channel must be 0–15')
    except ValueError as exc:
        return jsonify({'message': str(exc)}), 400
    config = read_config()
    from psycopg2 import sql
    table = config.get('DB_PRODUCTION_TABLE', 'daq_production_samples')
    try:
        import psycopg2
        with psycopg2.connect(config['DB_DSN'], connect_timeout=3) as conn:
            with conn.cursor() as cursor:
                cursor.execute(sql.SQL('''SELECT time_bucket('1 second', time),
                    avg(raw_voltage), avg(calibrated_value), unit, calibration_revision
                    FROM {} WHERE channel=%s AND time > now() - INTERVAL '2 minutes'
                    AND provenance='physical_daq'
                    GROUP BY 1,4,5 ORDER BY 1''').format(sql.Identifier(table)), (channel,))
                points = [{'time': row[0].isoformat() if hasattr(row[0], 'isoformat') else str(row[0]),
                           'raw_voltage': row[1],
                           'calibrated_value': row[2], 'unit': row[3],
                           'calibration_revision': row[4]} for row in cursor.fetchall()]
    except Exception as exc:
        return jsonify({'message': f'Production samples unavailable: {exc}'}), 503
    return jsonify({'channel': channel, 'points': points,
                    'gaps': read_recent_gaps(config)})

@app.route('/api/scan_usb', methods=['GET'])
def api_scan_usb():
    """Return installed DAQ hardware and serial ports on the host PC."""
    devices, warnings = scan_host_usb_devices()
    return jsonify({
        'status': 'error' if warnings and not devices else 'success',
        'count': len(devices),
        'devices': devices,
        'warnings': warnings,
    }), 503 if warnings and not devices else 200


@socketio.on('connect')
def handle_connect():
    """Fires when browser client opens or refreshes the page."""
    pid, mode = get_running_process()
    is_active = pid is not None
    config = read_config()
    dest = config.get('DESTINATION', 'database')
    try:
        recorded_mode = Path(MODE_PATH).read_text(encoding='utf-8').strip()
    except OSError:
        recorded_mode = None
    mode_val = mode or recorded_mode or config.get('AUTO_START_MODE', 'production')
    
    # 1. Update client running status immediately
    emit('status_change', {'is_running': is_active, 'mode': mode_val, 'destination': dest})
    
    # 2. Feed last stats if process is active
    if is_active and last_stats:
        emit('stats_update', last_stats)
        
    # 3. Stream historical logs so terminal console is populated
    logs = get_last_logs(50)
    for log_line in logs:
        emit('log_update', {'log': log_line})
        
    # Start tailing if a process is already running
    if is_active:
        start_tailing()

@socketio.on('start_daq')
def handle_start(data):
    req_mode = (data or {}).get('mode')
    result = start_acquisition(req_mode)
    emit('control_result', result)


def start_acquisition(mode=None):
    if mode is None:
        mode = read_config().get('AUTO_START_MODE', 'production')
    if mode == 'real':
        mode = 'production'
    if mode not in ('production', 'mockup'):
        return {'started': False, 'message': 'mode must be production or mockup'}
    pid, _ = get_running_process()
    if pid is not None:
        return {'started': False, 'message': 'Acquisition is already running'}
    config = read_config()
    if mode == 'production':
        try:
            validate_production_config(DaqNaviConfig(config, allow_env_overrides=False))
        except (ValueError, TypeError, KeyError) as exc:
            return {'started': False, 'message': str(exc)}
    script = 'stream_to_db.py' if mode == 'production' else 'mockup_stream_to_db.py'
    args = [sys.executable, os.path.join(CORE_DIR, script)]
    if mode == 'production':
        args += ['--config', CONFIG_PATH]
    try:
        with open(LOG_PATH, 'a', encoding='utf-8') as output:
            process = subprocess.Popen(args, stdout=output, stderr=subprocess.STDOUT,
                                       env={**os.environ, 'PYTHONUNBUFFERED': '1',
                                            'DAQ_CONFIG_PATH': CONFIG_PATH},
                                       close_fds=sys.platform != 'win32')
        Path(PID_PATH).write_text(str(process.pid), encoding='utf-8')
        Path(MODE_PATH).write_text(mode, encoding='utf-8')
        start_tailing()
        socketio.emit('status_change', {'is_running': True, 'mode': mode,
                                        'destination': config.get('DESTINATION')})
        return {'started': True, 'pid': process.pid, 'mode': mode}
    except (OSError, ValueError) as exc:
        return {'started': False, 'message': str(exc)}


@app.route('/api/start', methods=['POST'])
def api_start():
    req_data = request.get_json(silent=True) or {}
    mode = req_data.get('mode')
    result = start_acquisition(mode)
    return jsonify(result), 200 if result['started'] else 400

@socketio.on('stop_daq')
def handle_stop():
    emit('control_result', stop_acquisition(manual=True))


def stop_acquisition(manual=True):
    pid, mode = get_running_process()
    if pid is None:
        stop_tail_event.set()
        for path in (PID_PATH, MODE_PATH):
            try:
                os.unlink(path)
            except FileNotFoundError:
                pass
        config = read_config()
        runtime = read_runtime_status(config)
        pending = runtime.get('pending_batches', 0)
        return {'stopped': True, 'pending_batches': pending, 'pending_replay': pending > 0,
                'drained': pending == 0, 'writer_error': runtime.get('last_writer_error')}
    stopped = terminate_pid(pid)
    if not stopped:
        return {'stopped': False, 'message': 'Drain timeout; acquisition is still stopping'}
    stop_tail_event.set()
    for path in (PID_PATH, MODE_PATH):
        try:
            os.unlink(path)
        except FileNotFoundError:
            pass
    config = read_config()
    runtime = read_runtime_status(config)
    socketio.emit('status_change', {'is_running': False, 'mode': mode or config.get('AUTO_START_MODE', 'production')})
    pending = runtime.get('pending_batches', 0)
    return {'stopped': True, 'pending_batches': pending,
            'pending_replay': pending > 0,
            'drained': pending == 0,
            'writer_error': runtime.get('last_writer_error')}


@app.route('/api/stop', methods=['POST'])
def api_stop():
    result = stop_acquisition(manual=True)
    return jsonify(result), 200 if result['stopped'] else 503

def init_application():
    """Initial recovery check on Web GUI startup."""
    pid, mode = get_running_process()
    if pid is not None:
        print(f"[SYSTEM] Detected active background process running (PID: {pid}). Re-attaching...")
        start_tailing()
    else:
        cfg = read_config()
        if cfg.get('AUTO_START_ON_STARTUP', False):
            target_mode = cfg.get('AUTO_START_MODE', 'production')
            print(f"[SYSTEM] Auto-starting saved acquisition mode={target_mode}...")
            result = start_acquisition(target_mode)
            if not result['started']:
                print(f"[SYSTEM] Auto-start failed: {result['message']}")
        else:
            print("[SYSTEM] Auto-start is disabled. Awaiting manual start.")

def handle_shutdown(sig, frame):
    print("[SYSTEM] Gracefully shutting down Web GUI and sub-pipeline...")
    pid, _ = get_running_process()
    if pid is not None:
        terminate_pid(pid)
    sys.exit(0)

signal.signal(signal.SIGINT, handle_shutdown)
signal.signal(signal.SIGTERM, handle_shutdown)

if __name__ == '__main__':
    init_application()
    # Enable Werkzeug auto-reload in dev mode when FLASK_DEBUG=1 is set (docker-compose.override.yml)
    _debug = os.getenv("FLASK_DEBUG", "0").strip() == "1"
    # Served on Port 8081
    socketio.run(app, host='0.0.0.0', port=8081, debug=_debug, use_reloader=_debug, reloader_type='stat')
