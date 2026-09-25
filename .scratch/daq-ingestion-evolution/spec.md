# DAQ ingestion audit and multiple-device acquisition

The current production DAQ path is configured for one Advantech device and one contiguous channel span. Audit the deployed acquisition path and its guarantees first. Then support concurrent production acquisition from multiple configured devices on one Linux host, including two PCI cards or a PCI card alongside a supported USB DAQ such as USB-4716.

Preserve the existing single-device deployment during the transition. Physical and mockup samples remain distinguishable. Every stored sample, acquisition gap, runtime status, and configuration change must identify its source device. Confirm device-specific channel, wiring, range, timing, and driver capabilities against the installed SDK and vendor documentation before claiming hardware support.

The audit ticket produces evidence and decisions; the implementation ticket uses them. Hardware-specific settings and acceptance rates are based on the installed devices and chosen operating configuration rather than assuming two different DAQ models have identical limits.
