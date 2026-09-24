let socket = null;
if (typeof io !== 'undefined') {
    socket = io();
} else {
    console.warn('Socket.IO library not loaded; realtime updates disabled.');
}
let channelConfigs = {};
let currentScaleChannel = '0';

document.addEventListener('DOMContentLoaded', () => {
    updateClock();
    setInterval(updateClock, 1000);

    loadConfig();
    checkProcessStatus();
    refreshRetentionPolicy();
    setInterval(checkProcessStatus, 4000);
    resolveBackLink();

    const form = document.getElementById('config-form');
    form.addEventListener('submit', handleConfigSave);
    setupConfigNavigation();

    document.getElementById('SCALE_ENABLED').addEventListener('change', toggleScalingFields);
    document.getElementById('SCALE_CHANNEL_TARGET').addEventListener('change', handleScaleChannelTargetChange);
    document.getElementById('graph-channel').addEventListener('change', refreshProductionGraphs);
    const destEl = document.getElementById('DESTINATION');
    if (destEl) {
        destEl.addEventListener('change', toggleDestinationFields);
    }
    const tlsEl = document.getElementById('MQTT_TLS_ENABLED');
    if (tlsEl) {
        tlsEl.addEventListener('change', toggleTlsFields);
    }
    ['DB_HOST', 'DB_PORT', 'DB_USER', 'DB_PASSWORD', 'DB_NAME'].forEach(id => {
        document.getElementById(id).addEventListener('input', syncPostgresDsn);
    });

    document.getElementById('start-btn').addEventListener('click', handleStartProcess);
    document.getElementById('stop-btn').addEventListener('click', handleStopProcess);
    document.getElementById('clear-console-btn').addEventListener('click', clearConsole);
    
    const scanBtn = document.getElementById('btn-scan-usb');
    if (scanBtn) {
        scanBtn.addEventListener('click', handleScanUsbDevices);
    }

    document.addEventListener('click', (e) => {
        const menu = document.getElementById('scanned-devices-menu');
        const scanBtn = document.getElementById('btn-scan-usb');
        if (menu && !menu.classList.contains('hidden')) {
            if (!menu.contains(e.target) && !scanBtn.contains(e.target)) {
                menu.classList.add('hidden');
            }
        }
    });

    bindSocketEvents();

    refreshProductionGraphs();
    setInterval(refreshProductionGraphs, 10000);
});

function setupConfigNavigation() {
    const links = [...document.querySelectorAll('.config-nav a[href^="#config-"]')];
    const sections = links.map(link => document.querySelector(link.getAttribute('href')));
    if (!links.length || sections.some(section => !section)) return;

    const setActive = activeIndex => {
        links.forEach((link, index) => {
            if (index === activeIndex) link.setAttribute('aria-current', 'location');
            else link.removeAttribute('aria-current');
        });
    };
    const updateActive = () => {
        let activeIndex = 0;
        sections.forEach((section, index) => {
            if (section.getBoundingClientRect().top <= 110) activeIndex = index;
        });
        setActive(activeIndex);
    };
    links.forEach((link, index) => link.addEventListener('click', () => setActive(index)));
    window.addEventListener('scroll', updateActive, {passive: true});
    updateActive();
}

async function handleScanUsbDevices() {
    const scanBtn = document.getElementById('btn-scan-usb');
    const menu = document.getElementById('scanned-devices-menu');
    if (!scanBtn || !menu) return;

    scanBtn.classList.add('scanning');
    const loading = document.createElement('div');
    loading.className = 'scan-loading';
    loading.textContent = 'Scanning host USB bus and DAQ ports…';
    menu.replaceChildren(loading);
    menu.classList.remove('hidden');

    try {
        const response = await fetch('/api/scan_usb');
        const data = await response.json();

        if (data.status === 'success' && data.devices && data.devices.length > 0) {
            menu.replaceChildren();
            const header = document.createElement('div');
            header.className = 'scan-menu-header';
            const count = document.createElement('span');
            count.textContent = `Detected hardware ports (${data.devices.length})`;
            const close = document.createElement('button');
            close.type = 'button';
            close.className = 'close-scan-btn';
            close.setAttribute('aria-label', 'Close detected hardware ports');
            close.textContent = '×';
            header.append(count, close);
            menu.appendChild(header);

            const span = (className, value) => {
                const element = document.createElement('span');
                element.className = className;
                element.textContent = value ?? '';
                return element;
            };
            data.devices.forEach(dev => {
                const item = document.createElement('button');
                item.type = 'button';
                item.className = 'scan-item';
                const badgeClass = dev.is_daq ? 'badge-daq' : 'badge-serial';
                const main = span('scan-item-main', '');
                main.append(span('scan-item-name', dev.name), span('scan-item-id monospace', dev.id));
                const meta = span('scan-item-meta', '');
                meta.append(span(`badge ${badgeClass}`, dev.type), span('text-muted', dev.port));
                item.append(main, meta);

                item.addEventListener('click', () => {
                    const devInput = document.getElementById('DEVICE_DESCRIPTION');
                    if (devInput) {
                        devInput.value = dev.id;
                        devInput.classList.add('highlight-flash');
                        setTimeout(() => devInput.classList.remove('highlight-flash'), 1200);
                        devInput.focus();
                    }
                    menu.classList.add('hidden');
                    showToast(`Selected device: ${dev.id}`);
                });

                menu.appendChild(item);
            });

            close.addEventListener('click', () => {
                menu.classList.add('hidden');
                scanBtn.focus();
            });
        } else {
            const empty = document.createElement('div');
            empty.className = 'scan-empty';
            empty.textContent = 'No USB/DAQ devices detected on host PC.';
            menu.replaceChildren(empty);
        }
    } catch (err) {
        console.error('Error scanning USB devices:', err);
        const error = document.createElement('div');
        error.className = 'scan-error';
        error.textContent = `Failed to scan USB ports: ${err.message}`;
        menu.replaceChildren(error);
    } finally {
        scanBtn.classList.remove('scanning');
    }
}

async function refreshProductionGraphs() {
    const message = document.getElementById('sample-graph-message');
    try {
        const channel = document.getElementById('graph-channel').value || '0';
        const response = await fetch(`/api/samples?channel=${encodeURIComponent(channel)}`);
        const data = await response.json();
        if (!response.ok) throw new Error(data.message || 'Samples unavailable');
        const revisions = [...new Set(data.points.map(point => point.calibration_revision))].filter(Boolean);
        const units = [...new Set(data.points.map(point => point.unit))].filter(Boolean);
        document.getElementById('calibrated-graph-label').textContent = `Calibrated measurement (${units.join(', ') || 'unit unknown'}; calibration ${revisions.join(', ') || 'unknown'})`;
        message.textContent = data.points.length ? `${data.points.length} one-second aggregates · shaded areas are acquisition gaps` : 'No physical DAQ samples in the last 2 minutes';
        drawProductionGraph('raw-sample-graph', data.points, data.gaps, 'raw_voltage');
        drawProductionGraph('calibrated-sample-graph', data.points, data.gaps, 'calibrated_value');
    } catch (error) {
        message.textContent = error.message;
        drawProductionGraph('raw-sample-graph', [], [], 'raw_voltage');
        drawProductionGraph('calibrated-sample-graph', [], [], 'calibrated_value');
    }
}

function drawProductionGraph(canvasId, points, gaps, field) {
    const canvas = document.getElementById(canvasId);
    const ctx = canvas.getContext('2d');
    const end = Date.now();
    const start = end - 2 * 60 * 1000;
    const x = timestamp => (timestamp - start) / (end - start) * canvas.width;
    const values = points.map(point => Number(point[field])).filter(Number.isFinite);
    const low = values.length ? Math.min(...values) : 0;
    const high = values.length ? Math.max(...values) : 1;
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = '#f8faf9';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = '#f5dfdf';
    gaps.forEach(gap => {
        const left = Math.max(0, x(gap.start_ns / 1e6));
        const right = Math.min(canvas.width, x(gap.end_ns ? gap.end_ns / 1e6 : end));
        if (right > left) ctx.fillRect(left, 0, right - left, canvas.height);
    });
    ctx.strokeStyle = field === 'raw_voltage' ? '#146b53' : '#386da5';
    ctx.lineWidth = 2;
    ctx.beginPath();
    let previous = null;
    points.forEach(point => {
        const timestamp = Date.parse(point.time);
        const value = Number(point[field]);
        if (!Number.isFinite(value)) return;
        const px = x(timestamp);
        const py = canvas.height - 8 - (value - low) / (high - low || 1) * (canvas.height - 16);
        const gapBetween = gaps.some(gap => gap.start_ns / 1e6 <= timestamp &&
            (gap.end_ns === null || gap.end_ns / 1e6 >= previous));
        if (previous === null || timestamp - previous > 2000 || gapBetween) ctx.moveTo(px, py);
        else ctx.lineTo(px, py);
        previous = timestamp;
    });
    ctx.stroke();
}

function toggleDestinationFields() {
    const dest = document.getElementById('DESTINATION')?.value || 'postgresql';
    const postgresGroup = document.getElementById('postgres-config-group');
    const influxGroup = document.getElementById('influx-config-group');
    const mqttGroup = document.getElementById('mqtt-config-group');

    if (postgresGroup && influxGroup && mqttGroup) {
        if (dest === 'mqtt') {
            postgresGroup.style.display = 'none';
            influxGroup.style.display = 'none';
            mqttGroup.style.display = 'flex';
        } else if (dest === 'influxdb') {
            postgresGroup.style.display = 'none';
            influxGroup.style.display = 'flex';
            mqttGroup.style.display = 'none';
        } else {
            postgresGroup.style.display = 'flex';
            influxGroup.style.display = 'none';
            mqttGroup.style.display = 'none';
        }
    }
}

function syncPostgresDsn() {
    const host = document.getElementById('DB_HOST')?.value.trim() || 'localhost';
    const port = document.getElementById('DB_PORT')?.value.trim() || '5432';
    const user = document.getElementById('DB_USER')?.value.trim() || 'admin';
    const pass = document.getElementById('DB_PASSWORD')?.value.trim() || 'admin';
    const name = document.getElementById('DB_NAME')?.value.trim() || 'daq_db';
    const dsnEl = document.getElementById('DB_DSN');
    if (dsnEl) dsnEl.value = `postgresql://${user}:${pass}@${host}:${port}/${name}`;
}

function toggleTlsFields() {
    const tlsChecked = document.getElementById('MQTT_TLS_ENABLED')?.checked || false;
    const tlsGroup = document.getElementById('mqtt-tls-group');
    if (tlsGroup) {
        tlsGroup.style.display = tlsChecked ? 'flex' : 'none';
    }
}

function updateClock() {
    const clockEl = document.getElementById('realtime-clock');
    if (!clockEl) return;
    const now = new Date();
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    clockEl.textContent = `${hours}:${minutes}:${seconds}`;
}

async function loadConfig() {
    try {
        const res = await fetch('/api/config');
        if (!res.ok) throw new Error("Failed to load config.");
        const config = await res.json();
        
        Object.keys(config).forEach(key => {
            const input = document.getElementById(key);
            if (input) {
                if (input.type === 'checkbox') {
                    input.checked = config[key];
                } else {
                    input.value = config[key];
                }
            }
        });
        
        channelConfigs = structuredClone(config.CHANNELS || {});
        document.getElementById('mode-select').value = config.AUTO_START_MODE || 'production';
        const graphChannel = document.getElementById('graph-channel');
        const selectedGraphChannel = graphChannel.value;
        graphChannel.replaceChildren();
        Object.entries(channelConfigs).filter(([, channel]) => channel.enabled).forEach(([number, channel]) => {
            graphChannel.add(new Option(`${number}: ${channel.label}`, number));
        });
        graphChannel.value = selectedGraphChannel && channelConfigs[selectedGraphChannel]?.enabled ? selectedGraphChannel : (graphChannel.options[0]?.value || '0');
        currentScaleChannel = '0';
        document.getElementById('SCALE_CHANNEL_TARGET').value = '0';
        loadScaleChannelToInputs(currentScaleChannel);
        toggleDestinationFields();
        toggleTlsFields();
        
        appendLog('INFO', 'System configuration loaded from config.json.');
    } catch (e) {
        appendLog('ERROR', `Failed to load config: ${e.message}`);
    }
}

async function checkProcessStatus() {
    try {
        const res = await fetch('/api/status');
        if (!res.ok) throw new Error("Failed to get status.");
        const status = await res.json();
        updateUIState(status.is_running, status.run_mode, status.destination, status);
        showProductionStatus(status);
    } catch (e) {
        appendLog('ERROR', `Failed to query process status: ${e.message}`);
    }
}

function showProductionStatus(status) {
    const summary = document.getElementById('production-health-summary');
    const buffer = document.getElementById('production-health-buffer');
    const gaps = document.getElementById('production-health-gaps');
    if (!summary || !buffer || !gaps) return;
    const detail = status.fault || status.writer_error || (status.healthy ? 'healthy' : (status.is_running ? 'waiting for data' : 'acquisition stopped'));
    summary.textContent = `${status.status.toUpperCase()} · ${status.mode} · ${detail}`;
    buffer.textContent = `Buffer: ${(status.spool_bytes / (1024 ** 2)).toFixed(1)} MiB · pending replay: ${status.pending_batches} batches · retention: ${status.retention_days} days`;
    document.getElementById('telemetry-polled').textContent = status.last_sample_ns ? new Date(status.last_sample_ns / 1e6).toLocaleTimeString() : '—';
    document.getElementById('telemetry-written').textContent = status.pending_batches;
    document.getElementById('telemetry-loss').textContent = (status.gaps || []).length;
    document.getElementById('telemetry-queue').textContent = `${(status.spool_bytes / (1024 ** 2)).toFixed(1)} MiB`;
    gaps.replaceChildren();
    if (!status.gaps || status.gaps.length === 0) {
        const item = document.createElement('div');
        item.className = 'text-muted';
        item.textContent = 'No recorded acquisition gaps in buffer.';
        gaps.appendChild(item);
    } else {
        status.gaps.forEach(gap => {
            const item = document.createElement('div');
            item.textContent = `Gap: ${new Date(gap.start_ns / 1e6).toLocaleString()} – ${gap.end_ns ? new Date(gap.end_ns / 1e6).toLocaleString() : 'ongoing'} · ${gap.cause}`;
            gaps.appendChild(item);
        });
    }
}

async function refreshRetentionPolicy() {
    const element = document.getElementById('production-retention-policy');
    if (!element) return;
    try {
        const response = await fetch('/api/retention');
        const data = await response.json();
        element.textContent = response.ok ? `Effective TimescaleDB retention: ${data.effective}` :
            `Retention policy error: ${data.message}`;
    } catch (error) {
        element.textContent = `Retention policy error: ${error.message}`;
    }
}

function updateUIState(running, mode = 'mockup', destination = 'database', status = null) {
    const startBtn = document.getElementById('start-btn');
    const stopBtn = document.getElementById('stop-btn');
    const modeSelect = document.getElementById('mode-select');
    const statusDot = document.getElementById('status-dot');
    const statusText = document.getElementById('status-text');
    const statusIndicator = document.getElementById('system-status-indicator');

    const destLabel = (destination || 'database').toUpperCase();

    if (status && status.status === 'faulted') {
        startBtn.disabled = false;
        stopBtn.disabled = true;
        modeSelect.disabled = false;
        statusIndicator.classList.remove('active');
        statusDot.className = 'pulse-dot offline';
        statusText.textContent = `FAULTED (${(status.fault || 'ERROR').toUpperCase()})`;
    } else if (status && status.status === 'buffering') {
        startBtn.disabled = true;
        stopBtn.disabled = false;
        modeSelect.disabled = true;
        statusIndicator.classList.add('active');
        statusDot.className = 'pulse-dot buffering';
        statusText.textContent = `BUFFERING (${(mode || '').toUpperCase()} - ${destLabel})`;
    } else if (running) {
        startBtn.disabled = true;
        stopBtn.disabled = false;
        modeSelect.disabled = true;
        
        statusIndicator.classList.add('active');
        if (mode === 'mockup' || mode === 'mock') {
            statusDot.className = 'pulse-dot mock';
        } else {
            statusDot.className = 'pulse-dot online green';
        }
        statusText.textContent = `RUNNING (${mode.toUpperCase()} - ${destLabel})`;
    } else {
        startBtn.disabled = false;
        stopBtn.disabled = true;
        modeSelect.disabled = false;
        
        statusIndicator.classList.remove('active');
        statusDot.className = 'pulse-dot offline';
        statusText.textContent = 'OFFLINE';
    }
}

async function handleConfigSave(e) {
    e.preventDefault();
    
    saveInputsToScaleChannel(currentScaleChannel);
    
    const configData = {};
    const elements = e.target.elements;
    
    for (let el of elements) {
        if (!el.name) continue;
        
        if (el.type === 'checkbox') {
            configData[el.name] = el.checked;
        } else if (el.name === 'ANCHOR_RECALIBRATE_INTERVAL_HR') {
            configData[el.name] = parseFloat(el.value);
        } else if (['START_CHANNEL', 'CHANNEL_COUNT', 'CLOCK_RATE', 'SECTION_LENGTH', 'SECTION_COUNT', 'QUEUE_MAXSIZE', 'DB_PAGE_SIZE', 'DB_RETENTION_DAYS', 'STATS_INTERVAL_SEC', 'MQTT_PORT', 'MQTT_QOS'].includes(el.name)) {
            configData[el.name] = parseInt(el.value, 10);
        } else {
            configData[el.name] = el.value;
        }
    }

    configData.CHANNELS = channelConfigs;

    try {
        const res = await fetch('/api/config', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(configData)
        });
        
        const saved = await res.json();
        if (!res.ok) throw new Error(saved.message || 'Failed to save');
        showToast(`Saved. Raw retention: ${saved.retention_days} days.`);
        appendLog('SUCCESS', 'Configuration changes committed to config.json.');
        await loadConfig();
        await checkProcessStatus();
        await refreshRetentionPolicy();
    } catch (e) {
        showToast(`Save failed: ${e.message}`, true);
        appendLog('ERROR', `Failed to write config: ${e.message}`);
    }
}

async function handleStartProcess() {
    const mode = document.getElementById('mode-select').value;
    const response = await fetch('/api/start', {method: 'POST', headers: {'Content-Type': 'application/json'}, body: JSON.stringify({mode})});
    const result = await response.json();
    if (!response.ok) showToast(result.message || 'Start failed', true);
    await checkProcessStatus();
}

async function handleStopProcess() {
    const response = await fetch('/api/stop', {method: 'POST'});
    const result = await response.json();
    showToast(response.ok ? (result.pending_replay ? 'Stopped; batches pending replay' : 'Stopped; buffer drained') : result.message, !response.ok);
    await checkProcessStatus();
}

function clearConsole() {
    const consoleBody = document.getElementById('console-output');
    if (consoleBody) {
        const line = document.createElement('div');
        line.className = 'log-line text-muted';
        line.textContent = '[CONSOLE] Logs cleared.';
        consoleBody.replaceChildren(line);
    }
}

function appendLog(level, message) {
    const consoleBody = document.getElementById('console-output');
    if (!consoleBody) return;

    const now = new Date();
    const timeStr = `[${String(now.getHours()).padStart(2, '0')}:${String(now.getMinutes()).padStart(2, '0')}:${String(now.getSeconds()).padStart(2, '0')}]`;
    
    const logLine = document.createElement('div');
    logLine.className = 'log-line';
    
    let tagClass = 'text-muted';
    if (level === 'SUCCESS') tagClass = 'text-success';
    if (level === 'ERROR' || level === 'WARN') tagClass = 'text-error';
    
    const time = document.createElement('span');
    time.className = 'log-time';
    time.textContent = timeStr;
    const body = document.createElement('span');
    body.className = tagClass;
    body.textContent = message;
    logLine.append(time, body);
    consoleBody.appendChild(logLine);
    
    consoleBody.scrollTop = consoleBody.scrollHeight;
}

function showToast(message, isError = false) {
    const toast = document.getElementById('toast');
    if (!toast) return;
    toast.textContent = message;
    
    toast.classList.toggle('error', isError);
    toast.classList.add('show');
    setTimeout(() => {
        toast.classList.remove('show');
    }, 3000);
}

function bindSocketEvents() {
    if (!socket) {
        return;
    }
    socket.on('connect', () => {
        appendLog('SUCCESS', 'WebSocket bridge connected.');
    });

    socket.on('disconnect', () => {
        appendLog('ERROR', 'WebSocket bridge disconnected.');
        updateUIState(false);
    });

    socket.on('status_change', (data) => {
        updateUIState(data.is_running, data.mode, data.destination);
    });

    socket.on('log_update', (data) => {
        const line = data.log;
        let level = 'INFO';
        if (line.includes('error') || line.includes('Error') || line.includes('failed') || line.includes('Full!')) {
            level = 'ERROR';
        } else if (line.includes('started') || line.includes('connected') || line.includes('ready')) {
            level = 'SUCCESS';
        }
        appendLog(level, line);
    });

}

function toggleScalingFields() {
    const isEnabled = document.getElementById('SCALE_ENABLED').checked;
    const fields = ['SCALE_LOW_VOLTAGE', 'SCALE_HIGH_VOLTAGE', 'SCALE_LOW_VALUE', 'SCALE_HIGH_VALUE'];
    fields.forEach(id => {
        const el = document.getElementById(id);
        if (el) {
            el.disabled = !isEnabled;
            el.required = isEnabled;
        }
    });
}

function loadScaleChannelToInputs(ch) {
    const cfg = channelConfigs[ch] || {enabled: false, label: '', unit: '', signal_type: 'SingleEnded', value_range: 'V_0To5', scale: {enabled: false, low_voltage: 0, high_voltage: 5, low_value: 0, high_value: 100, revision: ''}};
    const scale = cfg.scale || {};
    document.getElementById('CHANNEL_ENABLED').checked = cfg.enabled === true;
    document.getElementById('CHANNEL_LABEL').value = cfg.label ?? '';
    document.getElementById('CHANNEL_UNIT').value = cfg.unit ?? '';
    document.getElementById('CHANNEL_SIGNAL_TYPE').value = cfg.signal_type ?? 'SingleEnded';
    document.getElementById('CHANNEL_VALUE_RANGE').value = cfg.value_range ?? 'V_0To5';
    document.getElementById('SCALE_ENABLED').checked = scale.enabled === true;
    document.getElementById('SCALE_REVISION').value = scale.revision ?? '';
    document.getElementById('SCALE_LOW_VOLTAGE').value = scale.low_voltage ?? 0;
    document.getElementById('SCALE_HIGH_VOLTAGE').value = scale.high_voltage ?? 5;
    document.getElementById('SCALE_LOW_VALUE').value = scale.low_value ?? 0;
    document.getElementById('SCALE_HIGH_VALUE').value = scale.high_value ?? 100;
    toggleScalingFields();
}

function saveInputsToScaleChannel(ch) {
    const previous = channelConfigs[ch] || {};
    const number = id => Number(document.getElementById(id).value);
    channelConfigs[ch] = {...previous,
        enabled: document.getElementById('CHANNEL_ENABLED').checked,
        label: document.getElementById('CHANNEL_LABEL').value.trim(),
        unit: document.getElementById('CHANNEL_UNIT').value.trim(),
        signal_type: document.getElementById('CHANNEL_SIGNAL_TYPE').value,
        value_range: document.getElementById('CHANNEL_VALUE_RANGE').value,
        scale: {...(previous.scale || {}), enabled: document.getElementById('SCALE_ENABLED').checked,
            revision: document.getElementById('SCALE_REVISION').value.trim(),
            low_voltage: number('SCALE_LOW_VOLTAGE'), high_voltage: number('SCALE_HIGH_VOLTAGE'),
            low_value: number('SCALE_LOW_VALUE'), high_value: number('SCALE_HIGH_VALUE')}
    };
}

function handleScaleChannelTargetChange(e) {
    saveInputsToScaleChannel(currentScaleChannel);
    currentScaleChannel = e.target.value;
    loadScaleChannelToInputs(currentScaleChannel);
}

function resolveBackLink() {
    const backLink = document.querySelector('.back-link');
    if (backLink) {
        const protocol = window.location.protocol || 'http:';
        const hostname = window.location.hostname || 'localhost';
        const targetUrl = `${protocol}//${hostname}:8080`;
        backLink.setAttribute('href', targetUrl);
    }
}
