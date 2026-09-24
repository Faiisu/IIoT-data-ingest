# Control production acquisition from the web UI without mockup fallback

Operators start and stop production acquisition and manage its settings through the web UI. A hardware or driver failure must stop production acquisition and report the fault; the system must never switch that run to synthetic mockup data. An explicitly started mockup run uses a separate table or database. This keeps the required operator workflow while preventing simulated values from entering operational records as physical measurements.
