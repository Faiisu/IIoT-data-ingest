// app.js
// Portal Gateway Frontend Logic for LAN Edge Server Deployments
// See: docs/architecture/context.md
// English comments only

// Configuration of registered edge services
const EDGE_SERVICES = [
    { id: 'daq', name: 'DAQ USB-4716', port: '8081', rowId: 'row-daq' },
    { id: 'musashi-ii', name: 'MUSASHI II', port: '8082', rowId: 'row-musashi-ii' },
    { id: 'musashi-iv', name: 'MUSASHI IV', port: '8083', rowId: 'row-musashi-iv' }
];

let isPolling = false;

// Initialize app when DOM is ready
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initApp);
} else {
    initApp();
}

function initApp() {
    updateClock();
    setInterval(updateClock, 1000);

    // Dynamically resolve target hostnames for LAN deployments
    resolveHostnames();

    // Setup link click handling
    setupPortalLinks();

    // Initial service health poll and interval registration (every 4s)
    pollServices();
    setInterval(pollServices, 4000);
}

// Helper to construct service base URL from current window location
function getServiceBaseUrl(port) {
    const proto = (window.location.protocol === 'https:') ? 'https:' : 'http:';
    const host = window.location.hostname || '127.0.0.1';
    return `${proto}//${host}:${port}`;
}

// Dynamically construct target URLs using window.location protocol and hostname
function resolveHostnames() {
    const links = document.querySelectorAll('.module-portal-link');
    links.forEach(link => {
        const port = link.getAttribute('data-port');
        if (port) {
            link.href = getServiceBaseUrl(port);
        } else {
            const originalHref = link.getAttribute('href');
            if (originalHref && originalHref.includes('localhost')) {
                const host = window.location.hostname || '127.0.0.1';
                link.setAttribute('href', originalHref.replace('localhost', host));
            }
        }
    });
}

// Update the real-time clock in the header (local format)
function updateClock() {
    const clockEl = document.getElementById('realtime-clock');
    if (!clockEl) return;

    const now = new Date();
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');

    clockEl.textContent = `${hours}:${minutes}:${seconds}`;
}


// Setup portal link click event listeners to ensure target URL is up-to-date
function setupPortalLinks() {
    const links = document.querySelectorAll('.module-portal-link');
    links.forEach(link => {
        link.addEventListener('click', () => {
            const port = link.getAttribute('data-port');
            if (port) {
                link.href = getServiceBaseUrl(port);
            }
        });
    });
}

// Poll status of an individual edge service with a 2.5s AbortController timeout
async function fetchServiceHealth(service) {
    const controller = new AbortController();
    const timeoutId = setTimeout(() => controller.abort(), 2500);
    const statusUrl = `${getServiceBaseUrl(service.port)}/api/status`;

    try {
        const response = await fetch(statusUrl, {
            method: 'GET',
            signal: controller.signal,
            cache: 'no-store',
            headers: {
                'Accept': 'application/json'
            }
        });
        clearTimeout(timeoutId);

        if (!response.ok) {
            return {
                service,
                online: false,
                isRunning: false,
                error: `HTTP ${response.status}`
            };
        }

        const data = await response.json();
        return {
            service,
            online: true,
            isRunning: Boolean(data && data.is_running)
        };
    } catch (err) {
        clearTimeout(timeoutId);
        return {
            service,
            online: false,
            isRunning: false,
            error: (err.name === 'AbortError') ? 'Timeout (2.5s)' : (err.message || 'Offline')
        };
    }
}

// Poll all registered edge services every 4 seconds and update badges
async function pollServices() {
    if (isPolling) return;
    isPolling = true;

    try {
        const results = await Promise.all(
            EDGE_SERVICES.map(service => fetchServiceHealth(service))
        );

        results.forEach(({ service, online, isRunning }) => {
            let state;
            let badgeClass;
            let badgeText;

            if (online) {
                if (isRunning) {
                    state = 'RUNNING';
                    badgeClass = 'badge-active';
                    badgeText = `PORT_${service.port}: RUNNING`;
                } else {
                    state = 'STANDBY';
                    badgeClass = 'badge-standby';
                    badgeText = `PORT_${service.port}: STANDBY`;
                }
            } else {
                state = 'OFFLINE';
                badgeClass = 'badge-offline';
                badgeText = `PORT_${service.port}: OFFLINE`;
            }

            // Update DOM badge
            const link = document.querySelector(`.module-portal-link[data-port="${service.port}"]`);
            const row = link ? link.querySelector('.module-row') : document.getElementById(service.rowId);
            const badge = row ? row.querySelector('.status-badge') : null;

            if (badge) {
                badge.className = `status-badge ${badgeClass}`;
                badge.innerHTML = `<span class="badge-dot"></span>${badgeText}`;
            }
        });
    } catch (err) {
        console.error('Service status polling error:', err);
    } finally {
        isPolling = false;
    }
}
