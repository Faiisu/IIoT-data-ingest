# Industrial data acquisition

This context covers sensor acquisition through a physical DAQ card and the telemetry recorded from it.

## Language

**Production acquisition**:
A run that measures physical sensor values through the DAQ card for operational records.
_Avoid_: Real mode

**Mockup acquisition**:
A run that generates synthetic sensor values for demonstration or testing.
_Avoid_: Fallback data

**DAQ sample**:
One measurement from one physical input channel at a particular sampling instant.

**Raw voltage**:
The electrical value read from a DAQ input channel before sensor calibration.

**Calibrated measurement**:
A DAQ sample converted from raw voltage into the physical unit defined by that channel's calibration.

**Acquisition gap**:
An interval during which production acquisition could not record physical samples. It must be visible as missing data rather than represented by synthetic values.
