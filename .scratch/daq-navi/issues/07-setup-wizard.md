# 07: Production setup wizard

**What to build:** An interactive bash wizard script that walks a human operator through setting up a fresh Linux server for DAQ Navi production deployment. The wizard checks prerequisites (kernel version, PCI slot detection), guides DAQNavi driver installation (downloading and running the Advantech installer), installs Docker and Docker Compose if missing, configures `config.json` interactively (device description, DB credentials, channel count), and runs a verification `docker-compose up` to confirm everything works. The wizard handles only steps that require human judgment or root access — things the agent cannot do itself.

**Blocked by:** 06: Docker Compose full stack

**Status:** ready-for-agent

- [ ] Wizard detects OS (Ubuntu/Debian) and kernel version
- [ ] Checks for PCI-1716 card presence via `lspci`
- [ ] Guides DAQNavi driver installation (download URL, dpkg/rpm install, kernel module load verification)
- [ ] Installs Docker and Docker Compose if not present
- [ ] Walks through `config.json` customization (device description, DB host/credentials, channel count)
- [ ] Runs `docker-compose up -d` and verifies all containers are healthy
- [ ] Provides clear error messages and recovery steps at each stage
