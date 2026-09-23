# 03: Universal DAQ hardware reader

**What to build:** A refactored `daq_reader_thread` that configures `WaveformAiCtrl` entirely from `config.json`, making it work with any BDaq-supported card (PCI-1716, USB-4716, iDAQ-801, etc.) without code changes. The thread reads `DEVICE_DESCRIPTION` to select the device, iterates `CHANNELS` to apply per-channel `signal_type` and `value_range` via the BDaq `AiChannel` API, and sets acquisition parameters (`CLOCK_RATE`, `SECTION_LENGTH`, `SECTION_COUNT`) from config. Changing from PCI-1716 to USB-4716 requires only editing `config.json`.

**Blocked by:** 01: Config schema + DB schema + config loader

**Status:** ready-for-agent

- [ ] `daq_reader_thread` reads `DEVICE_DESCRIPTION` from config (no hardcoded device string)
- [ ] Per-channel `signal_type` applied from config via `wf.channels[i].signalType`
- [ ] Per-channel `value_range` applied from config via `wf.channels[i].valueRange`
- [ ] Acquisition parameters (`clockRate`, `sectionLength`, `sectionCount`) read from config
- [ ] `loadProfile` is optional: skipped gracefully if `PROFILE_PATH` is empty or missing
- [ ] Startup log clearly shows device description, per-channel config summary, and acquisition parameters
- [ ] Verified: changing `DEVICE_DESCRIPTION` in config.json switches the target device without any code modification
