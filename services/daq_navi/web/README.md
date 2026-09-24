# DAQ Config Center

The DAQ Navi Flask service serves the Config Center at port `8081`. Its REST API is available under `/api/` on the same port. The page template is `templates/index.html`; the JavaScript and CSS are in `static/config_center/`.

## Configuration workflow

1. Set the start channel and number of AI channels to read. The sensor table follows that span. The current production service accepts AI0–AI15. Enabled inputs outside a changed span remain visible so they can be disabled.
2. Edit Enabled, sensor label, engineering unit, signal type, and input range directly in the sensor table. On PCI-1716, differential pairs start on an even channel and reserve the following odd channel.
3. Turn calibration on or off in each sensor row. Select **Edit** on a row to set its linear conversion and revision. Production acquisition requires calibration on every enabled sensor.
4. Configure and test the destination, then save. PostgreSQL can use host and credentials or a custom connection string. Saving while acquisition runs stops and restarts that run after confirmation.

Configuration errors appear in the header of the section that contains them, with details directly below that header. The page scrolls to the first affected section after an unsuccessful save.

In development mode, Compose mounts `services/daq_navi` into the DAQ container. Static asset edits become visible immediately. Restart `daq-navi` after changing the page template if its Flask process has cached the template.
