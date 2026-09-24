# 11: Edit supported acquisition settings through the web UI

**What to build:** Operators can view, validate, save, and read back every supported acquisition setting through typed web controls, including per-channel enabled state, name, unit, calibration, and rate. The latest saved configuration is the effective source for the standalone script.

**Blocked by:** 10: Qualify the standalone acquisition script before web development.

**Status:** resolved

- [x] The channel editor initially opens on channel 0 and subsequently shows the latest saved channel states and values.
- [x] Saving one setting preserves unrelated supported settings; invalid values are rejected with a useful message, and valid zero values remain zero.
- [x] The web UI shows the effective saved configuration; environment defaults and the setup wizard cannot silently override web-managed production settings after initial setup.
- [x] Web/API tests verify round-trip editing and production-start validation for enabled channels.

## Answer

All four acceptance criteria have been verified and validated:
1. **Initial Channel 0 and Latest States**: `services/daq_navi/web/static/app.js` (`loadConfig()`, `loadScaleChannelToInputs()`, and `handleScaleChannelTargetChange()`) initializes target channel selection to channel 0 and retrieves the latest saved states from `/api/config`. Switching channels preserves unsaved edits in memory and presents saved/configured states.
2. **Partial Preservation, Zero Values, and Error Handling**: `merge_config()` in `services/daq_navi/web/app.py` ensures partial updates to a channel or scalar setting preserve existing channels and database settings. Valid zero values (`0.0`) are explicitly retained and verified in `test_partial_channel_save_preserves_other_settings_and_zero`. Invalid values (missing units, out-of-span channels, malformed types) return HTTP 400 with actionable messages and do not persist to disk.
3. **Effective Saved Configuration Authority**: Configuration saved via `/api/config` sets `_WEB_MANAGED: true`. `core/config_loader.py` enforces `allow_env_overrides=False` on loaded configurations, and `scripts/setup_wizard.sh` checks `_WEB_MANAGED` to prevent the wizard from overwriting web-managed production settings.
4. **Web/API Round-Trip and Start Validation**: Added `test_full_round_trip_channel_editing_and_production_start_validation` to `tests.test_production_web`. The test verifies round-trip editing and readback of all channel parameters (`enabled`, `label`, `unit`, `signal_type`, `value_range`, calibration revision, and scale values) along with `CLOCK_RATE`, and confirms production-start validation succeeds when configured properly. All 12 tests in `tests.test_production_web` pass cleanly via `docker exec daq_navi python3 -m unittest tests.test_production_web -v`.

