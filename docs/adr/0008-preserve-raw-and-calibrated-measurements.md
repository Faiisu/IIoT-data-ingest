# Preserve raw and calibrated measurements

Every production DAQ sample must retain its raw voltage and calibrated measurement, with the physical unit and calibration revision that produced the calibrated value. Each enabled channel must have a validated name, unit, and calibration before production acquisition starts. Changing calibration applies to future acquisition; historical measurements keep their original meaning, while raw voltage permits later reanalysis. This uses more storage but prevents an edited calibration from making older measurements uninterpretable.
