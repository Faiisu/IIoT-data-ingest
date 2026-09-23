#!/usr/bin/env bash
#
# deploy/linux/watchdog.sh
# Health-check & watchdog daemon for MDDP IIoT Data Ingestion Suite.
# Verifies container health, port availability, and handles timeout/stall recovery.
#
# Usage:
#   ./deploy/linux/watchdog.sh              # One-shot health check (cron-friendly)
#   ./deploy/linux/watchdog.sh --daemon     # Persistent daemon loop (every 30s)
#   ./deploy/linux/watchdog.sh --interval 15 # Custom check interval

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
LOG_DIR="$PROJECT_ROOT/logs"
LOG_FILE="$LOG_DIR/watchdog.log"

mkdir -p "$LOG_DIR"

INTERVAL=30
DAEMON_MODE=false
TIMEOUT_SEC=20
CHECK_ONLY=false

for ((i=1; i<=$#; i++)); do
  case "${!i}" in
    --daemon|-d)
      DAEMON_MODE=true
      ;;
    --check|-c)
      CHECK_ONLY=true
      ;;
    --interval|-i)
      ((i++))
      INTERVAL="${!i}"
      ;;
    --timeout|-t)
      ((i++))
      TIMEOUT_SEC="${!i}"
      ;;
    --help|-h)
      echo "Usage: $0 [options]"
      echo "  --daemon, -d       Run as a persistent background loop"
      echo "  --check, -c        Run one-shot check and exit with code (0=healthy, 1=recovered/issues)"
      echo "  --interval, -i N   Check interval in seconds (default: 30)"
      echo "  --timeout, -t N    Timeout threshold in seconds for recovery actions (default: 20)"
      exit 0
      ;;
  esac
done

write_log() {
  local timestamp
  timestamp="$(date '+%Y-%m-%d %H:%M:%S')"
  printf '[%s] %s\n' "$timestamp" "$*" | tee -a "$LOG_FILE"
}

get_compose_cmd() {
  if docker compose version >/dev/null 2>&1; then
    echo "docker compose"
  elif command -v docker-compose >/dev/null 2>&1; then
    echo "docker-compose"
  else
    echo ""
  fi
}

check_port() {
  local host="$1" port="$2"
  if command -v nc >/dev/null 2>&1; then
    nc -z -w 2 "$host" "$port" >/dev/null 2>&1
  elif command -v timeout >/dev/null 2>&1; then
    timeout 2 bash -c "cat < /dev/null > /dev/tcp/$host/$port" >/dev/null 2>&1
  else
    (echo > "/dev/tcp/$host/$port") >/dev/null 2>&1
  fi
}

check_and_recover() {
  local compose_cmd
  compose_cmd="$(get_compose_cmd)"
  local had_issues=0

  # 1. Docker Compose Stack Inspection
  if [[ -n "$compose_cmd" ]] && [[ -f "$PROJECT_ROOT/docker-compose.yml" ]]; then
    local ps_output
    ps_output="$($compose_cmd -f "$PROJECT_ROOT/docker-compose.yml" ps 2>/dev/null || true)"

    if [[ -n "$ps_output" ]]; then
      # Check for unhealthy or exited containers
      local unhealthy_services
      unhealthy_services="$($compose_cmd -f "$PROJECT_ROOT/docker-compose.yml" ps --filter "health=unhealthy" --format '{{.Service}}' 2>/dev/null || true)"
      local exited_services
      exited_services="$($compose_cmd -f "$PROJECT_ROOT/docker-compose.yml" ps --filter "status=exited" --format '{{.Service}}' 2>/dev/null || true)"

      local needs_restart=()
      for svc in $unhealthy_services $exited_services; do
        [[ -n "$svc" ]] && needs_restart+=("$svc")
      done

      if (( ${#needs_restart[@]} )); then
        had_issues=1
        write_log "⚠ [WATCHDOG ALARM] Unhealthy or stalled containers detected: ${needs_restart[*]}"
        for svc in "${needs_restart[@]}"; do
          write_log "↻ [RECOVERY] Restarting service '$svc' with timeout ${TIMEOUT_SEC}s..."
          if timeout "$TIMEOUT_SEC" $compose_cmd -f "$PROJECT_ROOT/docker-compose.yml" restart "$svc" 2>&1 | tee -a "$LOG_FILE"; then
            write_log "✓ [RECOVERY] Service '$svc' restart triggered."
          else
            write_log "✗ [ERROR] Restart of '$svc' timed out or failed. Running compose up -d --force-recreate..."
            timeout "$TIMEOUT_SEC" $compose_cmd -f "$PROJECT_ROOT/docker-compose.yml" up -d "$svc" 2>&1 | tee -a "$LOG_FILE" || true
          fi
        done
      fi
    fi
  fi

  # 2. Port Availability Checks
  # Ports: 5432 (TimescaleDB), 8080 (Portal), 8081 (DAQ Panel), 8084 (Plotter)
  local down_ports=()
  local required_ports=(5432 8080 8081 8084)

  for p in "${required_ports[@]}"; do
    if ! check_port "127.0.0.1" "$p"; then
      down_ports+=("$p")
    fi
  done

  if (( ${#down_ports[@]} )); then
    had_issues=1
    write_log "⚠ [WATCHDOG ALARM] Service ports unreachable: ${down_ports[*]}"
    if [[ -n "$compose_cmd" ]] && [[ -f "$PROJECT_ROOT/docker-compose.yml" ]]; then
      write_log "↻ [RECOVERY] Triggering docker compose up -d to revive missing endpoints..."
      timeout "$TIMEOUT_SEC" $compose_cmd -f "$PROJECT_ROOT/docker-compose.yml" up -d 2>&1 | tee -a "$LOG_FILE" || true
    elif [[ -x "$PROJECT_ROOT/deploy/linux/run.sh" ]]; then
      write_log "↻ [RECOVERY] Triggering native run.sh..."
      "$PROJECT_ROOT/deploy/linux/run.sh" >/dev/null 2>&1 &
    fi
  else
    if [[ $had_issues -eq 0 ]]; then
      write_log "♥ [HEARTBEAT] All primary endpoints UP (Ports: ${required_ports[*]}). Stack healthy."
    fi
  fi

  return "$had_issues"
}

# Main Execution Loop
if [[ "$DAEMON_MODE" == "true" ]]; then
  write_log "🚀 [WATCHDOG START] Daemon initiated (Interval: ${INTERVAL}s, Timeout: ${TIMEOUT_SEC}s)"
  while true; do
    check_and_recover || true
    sleep "$INTERVAL"
  done
else
  set +e
  check_and_recover
  status=$?
  set -e
  if [[ "$CHECK_ONLY" == "true" ]]; then
    exit "$status"
  fi
fi
