# DAQ Config Center save qualification — 2026-09-26

## Scope and result

The save reliability changes were built and deployed to the intended host with the private config directory mounted at `/app/config`. The web container is healthy and acquisition is stopped, matching the state observed before deployment. Config save fault injection passed in isolation. The InfluxDB org mismatch found during rollout was corrected with operator authorization and the spool owner now matches the corrected destination. A separately authorized short acquisition run and stopped-state replay emptied the durable spool, with readback from InfluxDB.

## Versions and commands

- Source base: `f54c7b1`; the committed changes for this effort include implementation and test updates.
- Final deployed image: `sha256:3b1b4fd0b7f66a1511666851634e468ce3cbf5eaeb6eb96e3a1cd49c05572226`.
- Baseline rollback image: `daq-navi-rollback:pre-config-save` (`sha256:abeeadff5eb297da78b6b85ecb5c3d055f5e8b90a1bcb7237b18a14b12c2d024`). A phase-one image is tagged `daq-navi-rollback:phase1-cutover`.
- Build: `docker compose --env-file deploy/daq-navi/.env -f deploy/daq-navi/compose.yml build daq-navi`.
- Deploy: `docker compose --env-file deploy/daq-navi/.env -f deploy/daq-navi/compose.yml up -d --no-build --force-recreate daq-navi`.
- Isolated tests: `.venv/bin/python -m unittest services.daq_navi.tests.test_config_reliability services.daq_navi.tests.test_production_web services.daq_navi.tests.test_production_runtime services.daq_navi.tests.test_access_control services.daq_navi.tests.test_docker_compose -q` — 123 passed.
- Full suite after aligning legacy tests to the current application: `.venv/bin/python -m unittest discover -s services/daq_navi/tests -p 'test_*.py' -q` — 224 run, all passed, 7 skipped.

## Deployment checks

- Config initially copied byte for byte from `deploy/daq-navi/config.local.json` into private `deploy/daq-navi/config/config.json`; file mode `0600`. After the authorized org correction, current config revision is `df67eef1ea00fc05f447a8a4d3a8600d454555b1b73d3cc11dd8c2436d32faa2`. The rollback config copy was updated to the same org and mode `0600`.
- Compose project remains `iiot-daq-navi`, with the config directory mounted at `/app/config` and the existing external spool volume at `/var/lib/daq_navi/spool`.
- `GET /api/health` returned HTTP 200 with `healthy=true`, `status=stopped`; Docker reports healthy. Saved destination is InfluxDB and `AUTO_START_ON_STARTUP=false`.
- InfluxDB bucket `daq_telemetry` exists and has unlimited retention (`everySeconds=0`); bucket retention was not changed by this effort.
- Before deployment, the external spool held 0 pending batches and 3 undelivered gaps. During qualification, acquisition was started externally and InfluxDB writes returned HTTP 404. It was stopped gracefully, leaving 10 batches and 7 gaps pending. After the org correction and explicit authorization to replay, a short acquisition run delivered the gaps; acquisition was stopped and the remaining 16 batches plus one stop gap were replayed from the spool with the production Influx writer. Final spool state: 0 pending batches, 0 pending gaps, `acquisition_active=0`. The status snapshot also reports `stopped` and 0 pending batches.
- Read-only InfluxDB API inspection found the saved org `mddpa` did not exist, while org `mddp` owns the configured bucket. With operator authorization, the config was changed to `mddp` and the spool destination identity updated. Before changing either, a byte copy of config and a consistent SQLite backup of the spool were saved privately under `deploy/daq-navi/config/recovery-20260926-org-fix/`. The final destination identity matches the spool owner; metadata preflight verifies the token, org, and bucket without writing samples.
- InfluxDB Flux readback returned HTTP 200 with `sample_id` counts by channel: channels 0–3 each had 200,000; channels 4–7 each had 80,000 in the last hour. A gap query returned 4 recent gap points. These checks establish stored samples and recorded gaps without exposing sample payloads. The API health gate returned HTTP 200 with `healthy=true`, `status=stopped` after the final deployment.

## Rollback

The pre-change image is available locally under `daq-navi-rollback:pre-config-save`. Restore the prior single-file mount in `deploy/daq-navi/compose.yml`, use the corrected `deploy/daq-navi/config.local.json`, then recreate only `daq-navi`. Keep the external spool volume mounted and do not run `docker compose down -v`. Confirm health and acquisition state afterward. The exact previous source is `f54c7b1`.

## Remaining limits

- No production sample payload was printed or read back. Readback used aggregate counts by channel and gap count only.
- A destination change to a different PostgreSQL target combined with a retention change is rejected before any side effects. The target's effective policy must already match saved retention before switching. This keeps the policy and file consistent while leaving provisioning of a new target to its operator.
- UI authenticated readback was covered by isolated tests; no live operator password was used to log in during this deployment.
- The 7 skipped tests are marked by the existing test suite; the run reported no failures or errors.
