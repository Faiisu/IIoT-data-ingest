#!/bin/bash
set -e

# Select Python interpreter: prefer PYTHON_BIN or virtualenv if present, otherwise system python3
if [ -n "$PYTHON_BIN" ]; then
    PY="$PYTHON_BIN"
elif [ -f "../../.venv/bin/python" ]; then
    PY="../../.venv/bin/python"
elif [ -f ".venv/bin/python" ]; then
    PY=".venv/bin/python"
else
    PY="python3"
fi

# The saved file is authoritative after initial setup.
MOCKUP="false"
if [ -f "config.json" ]; then
    MOCKUP=$($PY -c "import json; print(json.load(open('config.json')).get('MOCKUP_MODE', False))" 2>/dev/null || echo "false")
fi

# Pass through custom command if invoked with python, bash, sh, etc.
if [ "$#" -gt 0 ] && [ "$1" != "app.py" ]; then
    if [ "$1" = "python" ] || [ "$1" = "python3" ] || [ "$1" = "bash" ] || [ "$1" = "sh" ] || [ "$1" = "/bin/bash" ] || [ "$1" = "/bin/sh" ]; then
        exec "$@"
    fi
fi

# Web GUI mode vs Headless Daemon mode
# When ENABLE_WEB_UI is true (default), launches app.py which binds port 8081 and manages streaming
if [ "${ENABLE_WEB_UI:-true}" = "true" ] && [ "${HEADLESS:-false}" != "true" ]; then
    echo "[DAQ-Navi Entrypoint] Launching DAQ Control Panel Web GUI on port 8081 (app.py)..."
    exec $PY app.py "$@"
fi

STREAM_SCRIPT="core/buffered_daq_to_timescaledb.py"
[ -f "$STREAM_SCRIPT" ] || STREAM_SCRIPT="buffered_daq_to_timescaledb.py"

MOCKUP_SCRIPT="core/mockup_stream_to_db.py"
[ -f "$MOCKUP_SCRIPT" ] || MOCKUP_SCRIPT="mockup_stream_to_db.py"

# Hardware acquisition must fail visibly if the driver is unavailable.
case "$MOCKUP" in
    [Tt][Rr][Uu][Ee]|1)
        echo "[DAQ-Navi Entrypoint] Launching synthetic mockup pipeline ($MOCKUP_SCRIPT)..."
        exec "$PY" "$MOCKUP_SCRIPT" "$@"
        ;;
    *)
        if [ ! -f "/usr/lib/libbiodaq.so" ] && [ ! -f "/opt/advantech/libs/libbiodaq.so" ] && [ ! -f "/usr/local/lib/libbiodaq.so" ]; then
            echo "[DAQ-Navi Entrypoint] ERROR: Advantech driver library (libbiodaq.so) not found in container paths." >&2
            exit 1
        fi
        echo "[DAQ-Navi Entrypoint] Launching hardware DAQ streaming pipeline ($STREAM_SCRIPT)..."
        exec "$PY" "$STREAM_SCRIPT" "$@"
        ;;
esac
