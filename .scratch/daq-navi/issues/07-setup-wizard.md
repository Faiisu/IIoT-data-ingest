# 07: Production setup wizard

**What to build:** An interactive bash wizard script that walks a human operator through setting up a fresh Linux server for DAQ Navi production deployment. The wizard checks prerequisites (kernel version, PCI slot detection), guides DAQNavi driver installation (downloading and running the Advantech installer), installs Docker and Docker Compose if missing, configures `config.json` interactively (device description, DB credentials, channel count), and runs a verification `docker-compose up` to confirm everything works. The wizard handles only steps that require human judgment or root access — things the agent cannot do itself.

**Blocked by:** 06: Docker Compose full stack

**Status:** resolved

- [x] Wizard detects OS (Ubuntu/Debian) and kernel version
- [x] Checks for PCI-1716 card presence via `lspci`
- [x] Guides DAQNavi driver installation (download URL, dpkg/rpm install, kernel module load verification)
- [x] Installs Docker and Docker Compose if not present
- [x] Walks through `config.json` customization (device description, DB host/credentials, channel count)
- [x] Runs `docker-compose up -d` and verifies all containers are healthy
- [x] Provides clear error messages and recovery steps at each stage

## Answer

Implemented the interactive production setup wizard at `scripts/setup_wizard.sh` (with symlink at `deploy/linux/setup_wizard.sh`) conforming to the `/wizard` skill template:

1. **System & Kernel Verification (Stage 1)**:
   - Detects OS name, ID, and version via `/etc/os-release`.
   - Checks kernel version (`uname -r`) and system architecture (`x86_64`).
   - Verifies required build tools and kernel headers (`gcc`, `make`, `linux-headers-$(uname -r)`), with automated `apt-get` installation option and clear recovery commands.
2. **PCI Hardware Card Detection (Stage 2)**:
   - Scans PCI expansion bus via `lspci -nn` for Advantech vendor `13fe` (e.g., PCI-1716 `13fe:00b5`).
   - Displays device bus information and details.
   - Provides clear hardware inspection, chassis seating, and BIOS setup recovery steps with option to continue in driverless mockup mode.
3. **Advantech DAQNavi Driver & SDK (Stage 3)**:
   - Checks for `libbiodaq.so` in `/usr/lib`, `/opt/advantech/libs`, and `/usr/local/lib`.
   - Verifies kernel module status via `lsmod`.
   - Guides installation across package formats (`.deb` via `dpkg -i`, `.rpm` via `rpm -ivh`, and `.run` binary installer).
   - Opens official Advantech driver portal via cross-platform browser opener (`open_url`).
   - Verifies and configures user hardware permissions (`dialout`, `plugdev`) and device enumeration (`/opt/advantech/tools/dev_enum`).
4. **Docker & Docker Compose Runtime (Stage 4)**:
   - Checks presence of Docker CLI and Docker Compose (`docker compose` plugin or `docker-compose` standalone).
   - Provides automated or manual installation instructions (`get.docker.com`, `docker-compose-v2`).
   - Audits `/var/run/docker.sock` permissions and offers to add the user to the `docker` group.
5. **Configuration Customization (Stage 5)**:
   - Probes hardware via `dev_enum` for sensible defaults (`PCI-1716,BID#0`).
   - Prompts for `DEVICE_DESCRIPTION`, `DEVICE_ID`, `CHANNEL_COUNT`, `CLOCK_RATE`, `DESTINATION`, `DB_HOST`, `DB_PORT`, `POSTGRES_USER`, hidden `POSTGRES_PASSWORD`, and `MOCKUP_MODE`.
   - Updates `.env` via `write_env` and safely synchronizes `services/daq_navi/config.json` via Python `sys.argv` (preventing shell injection).
6. **Stack Launch & Health Verification (Stage 6)**:
   - Launches stack in detached mode (`docker compose -f docker-compose.yml up -d`).
   - Polls container status and inspects health checks across services.
   - Displays service endpoints (Portal :8080, Plotter :8084, TimescaleDB :5432, Mosquitto :1883, InfluxDB :8086).
   - Provides targeted recovery steps and container log commands if services fail.
7. **Non-Interactive Prerequisite Check (`--check-only`)**:
   - Fast dry-run inspection suitable for automation and CI, printing status of OS, Kernel, PCI hardware, Driver, and Docker without blocking.
8. **Verification & Testing**:
   - Authoring validated with `bash -n`.
   - 10 automated unit tests in `services/daq_navi/test_setup_wizard.py` covering script syntax, structure, stages, argument parsing, and `--check-only` execution.
   - Dual-axis code review (Standards & Spec) conducted and addressed.
   - Full test suite (47 tests across `services/daq_navi`) passing cleanly.

