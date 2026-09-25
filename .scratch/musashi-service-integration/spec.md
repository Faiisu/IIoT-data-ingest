# MUSASHI service integration

Bring MUSASHI II and MUSASHI IV from their current standalone implementations into the project's supported Linux Docker deployment. Each service keeps its own acquisition path, configuration, process control, and storage schema. Work begins with an audit of the existing behavior and ends with a repeatable deployment and evidence that real and mock modes report their actual acquisition and delivery state.

The two implementation tickets are independent. Shared changes to Compose, Portal, documentation, and database configuration must preserve the working DAQ stack. Do not delete or migrate existing telemetry as part of these tickets without a separate, explicit data migration decision.

Open configuration choices, including the production dispenser endpoint, serial device, credentials, destination, and startup mode, should be recorded during the audit and exposed as deployment settings. Example machine-specific values in checked-in JSON are not production defaults.
