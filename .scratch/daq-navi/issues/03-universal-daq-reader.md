# 03: Universal DAQ hardware reader

**What to build:** A refactored `daq_reader_thread` that configures `WaveformAiCtrl` entirely from `config.json`, making it work with any BDaq-supported card (PCI-1716, USB-4716, iDAQ-801, etc.) without code changes. The thread reads `DEVICE_DESCRIPTION` to select the device, iterates `CHANNELS` to apply per-channel `signal_type` and `value_range` via the BDaq `AiChannel` API, and sets acquisition parameters (`CLOCK_RATE`, `SECTION_LENGTH`, `SECTION_COUNT`) from config. Changing from PCI-1716 to USB-4716 requires only editing `config.json`.

**Blocked by:** 01: Config schema + DB schema + config loader

**Status:** resolved

- [x] `daq_reader_thread` reads `DEVICE_DESCRIPTION` from config (no hardcoded device string)
- [x] Per-channel `signal_type` applied from config via `wf.channels[i].signalType`
- [x] Per-channel `value_range` applied from config via `wf.channels[i].valueRange`
- [x] Acquisition parameters (`clockRate`, `sectionLength`, `sectionCount`) read from config
- [x] `loadProfile` is optional: skipped gracefully if `PROFILE_PATH` is empty or missing
- [x] Startup log clearly shows device description, per-channel config summary, and acquisition parameters
- [x] Verified live on real hardware: tested on `mic-770` with physical PCI-1716 card (`03:00.0 Advantech Co. Ltd Device 00b5`), reading ch0 and ch1 (SingleEnded / common ground with DP-101A sensors) streaming 20,000 samples at 2000 Hz into containerized TimescaleDB with 0 dropped batches and clean shutdown.

## Answer
Implemented in:
- `services/daq_navi/stream_to_db.py`: `daq_reader_thread` refactored to dynamically read `DEVICE_DESCRIPTION`, per-channel `signalType` and `valueRange`, and acquisition parameters from `config.json`. Safely handles missing profile XML and cleans up device handles on termination.
- Verified on remote machine `mic-770@100.85.124.109` with physical PCI-1716 hardware card writing live samples to `daq_telemetry`.
