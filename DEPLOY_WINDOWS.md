# Windows Development Notes

The Compose configuration in this repository mounts Linux host device and DAQNavi library paths (`/dev`, `/opt/advantech`, and related paths) into the DAQ container. Docker Desktop on Windows does not provide those Linux-host hardware mounts for a physical PCI DAQ card. Use a supported Linux host for production acquisition.

## Run the stack for UI and service development

Install Docker Desktop with Compose support, clone the repository, and prepare the environment file:

```powershell
Copy-Item .env.example .env
```

Edit `.env` and replace demo credentials/tokens before making services reachable from other computers. Then start the stack:

```powershell
docker compose up -d
docker compose ps
```

The default override enables development mounts/settings. To use only the base Compose file, run:

```powershell
docker compose -f docker-compose.yml up -d --build
```

Open Portal `http://localhost:8080` or DAQ Navi `http://localhost:8081`. Without the supported host driver and device, use mockup/demo workflows only; a successful web or database connection does not indicate physical DAQ access.

## Services

The Compose stack contains `timescaledb`, `mqtt-broker`, `influxdb`, `daq-navi`, and `portal`. The Musashi services are separate from this Compose stack. See [`services/musashi_ii/WINDOWS_SETUP.md`](services/musashi_ii/WINDOWS_SETUP.md) for the Musashi II Windows setup instructions.

## Network access

Compose publishes the configured service ports on the Docker host. For access from another machine, use the host's reachable IP address and allow only the required ports through Windows Firewall. This stack does not add authentication to the web UIs; keep it on a trusted network or place an authenticated gateway in front of it.

## Stop and preserve data

```powershell
docker compose down
```

This stops containers while preserving named volumes. `docker compose down -v` removes database and spool volumes as well.
