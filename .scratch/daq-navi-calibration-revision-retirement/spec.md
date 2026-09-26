# Retire DAQ calibration revision metadata

Calibration revision metadata is no longer needed in the DAQ production sample record. Remove it consistently from newly captured and stored samples, APIs, and operator displays. Existing database data may be removed as part of a documented, one-time schema migration; service startup must not silently repeat destructive schema changes.
