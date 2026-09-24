# Interface Design Notes

The Portal and DAQ Navi interfaces use a shared light dashboard theme: warm off-white page background, white cards, dark green text, muted gray labels, fine green-gray borders, and a restrained green accent. DAQ controls keep clear grouping for device, acquisition, channels/calibration, destination, and run status.

## Current tokens

The Portal and DAQ styles define the shared values in their CSS `:root` blocks. Keep those existing variables in sync when changing the theme:

- `--paper`: page background
- `--white`: card and control background
- `--ink`: primary text
- `--muted`: supporting text
- `--line`: separators and borders
- `--green`: primary action and brand accent
- `--mint`: pale accent surface
- `--sans` and `--mono`: interface and technical-data typefaces

Use semantic status colors for running, warning, and error states. Preserve readable contrast, visible keyboard focus, responsive layouts, and labels that describe controls. Avoid decorative scanlines or a dark console treatment; they do not match the current Portal/DAQ implementation.

For component-specific behavior, the service HTML/CSS is the implementation source of truth: `services/portal/` and `services/daq_navi/web/`.
