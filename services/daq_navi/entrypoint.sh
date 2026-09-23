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

case "$MOCKUP" in
    [Tt][Rr][Uu][Ee]|1)
        echo "[DAQ-Navi Entrypoint] Launching synthetic mockup pipeline (mockup_stream_to_db.py)..."
        exec $PY mockup_stream_to_db.py "$@"
        ;;
    *)
        echo "[DAQ-Navi Entrypoint] Launching hardware DAQ streaming pipeline (stream_to_db.py)..."
        exec $PY stream_to_db.py "$@"
        ;;
esac
