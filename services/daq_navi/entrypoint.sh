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

# Resolve MOCKUP_MODE from environment variable or local config.json
MOCKUP="${MOCKUP_MODE}"
if [ -z "$MOCKUP" ] && [ -f "config.json" ]; then
    MOCKUP=$($PY -c "import json; print(json.load(open('config.json')).get('MOCKUP_MODE', 'false'))" 2>/dev/null || echo "false")
fi

# Web GUI mode vs Headless Daemon mode
# When ENABLE_WEB_UI is true (default), launches app.py which binds port 8081 and manages streaming
if [ "${ENABLE_WEB_UI:-true}" = "true" ] && [ "${HEADLESS:-false}" != "true" ]; then
    echo "[DAQ-Navi Entrypoint] Launching DAQ Control Panel Web GUI on port 8081 (app.py)..."
    exec $PY app.py "$@"
fi

STREAM_SCRIPT="core/stream_to_db.py"
[ -f "$STREAM_SCRIPT" ] || STREAM_SCRIPT="stream_to_db.py"

MOCKUP_SCRIPT="core/mockup_stream_to_db.py"
[ -f "$MOCKUP_SCRIPT" ] || MOCKUP_SCRIPT="mockup_stream_to_db.py"

# If hardware mode is requested but driver library is missing, fallback to mockup with warning
case "$MOCKUP" in
    [Tt][Rr][Uu][Ee]|1)
        echo "[DAQ-Navi Entrypoint] Launching synthetic mockup pipeline ($MOCKUP_SCRIPT)..."
        exec $PY $MOCKUP_SCRIPT "$@"
        ;;
    *)
        if [ ! -f "/usr/lib/libbiodaq.so" ] && [ ! -f "/opt/advantech/libs/libbiodaq.so" ] && [ ! -f "/usr/local/lib/libbiodaq.so" ]; then
            echo "[DAQ-Navi Entrypoint] WARNING: Advantech driver library (libbiodaq.so) not found in container paths."
            echo "[DAQ-Navi Entrypoint] Falling back to synthetic mockup mode ($MOCKUP_SCRIPT)..."
            exec $PY $MOCKUP_SCRIPT "$@"
        else
            echo "[DAQ-Navi Entrypoint] Launching hardware DAQ streaming pipeline ($STREAM_SCRIPT)..."
            if ! $PY $STREAM_SCRIPT "$@"; then
                EXIT_CODE=$?
                echo "[DAQ-Navi Entrypoint] Hardware streaming pipeline exited with code $EXIT_CODE."
                if [ "${AUTO_FALLBACK:-true}" = "true" ]; then
                    echo "[DAQ-Navi Entrypoint] AUTO_FALLBACK is enabled. Falling back to synthetic mockup pipeline ($MOCKUP_SCRIPT)..."
                    exec $PY $MOCKUP_SCRIPT "$@"
                else
                    exit $EXIT_CODE
                fi
            fi
        fi
        ;;
esac
