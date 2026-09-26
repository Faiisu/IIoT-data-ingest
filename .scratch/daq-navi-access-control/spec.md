# DAQ Navi operator access control

DAQ Navi is the first ingestion service to receive login. It owns its login page, operator credentials, session signing key, and session lifecycle. Its login does not sign an operator in to MUSASHI II or MUSASHI IV; those services will receive separate login pages and independent credentials and sessions in later phases. Portal remains a public directory of links to the services and does not require login.

Protect the DAQ Config Center and its API so only authenticated DAQ operators can read or change acquisition configuration, view sensitive runtime data, or control acquisition. Credentials must not be exposed by configuration readback, and browser-origin protections must match the deployment model. An unauthenticated Portal link opens the DAQ login page. The Portal may receive only a minimal DAQ health signal for its service link; that signal must not expose configuration or acquisition details.

The current deployment uses one host with services on separate ports. Browser cookies are scoped to a hostname rather than a port, so DAQ must use a distinct session cookie name and signing key, and no service may accept another service's session as authentication.

## First release decisions

- Start with one locally provisioned DAQ operator account. Its password is stored only as a salted password hash in a private deployment secret, separate from the DAQ acquisition configuration. Do not ship a working default account or password. The session signing key is another private, persistent secret. Missing or invalid authentication secrets prevent the protected web service from starting.
- DAQ serves its own login and logout pages. An unauthenticated visit to its Config Center redirects to login; API calls receive an unauthorized response instead of HTML. After login, the operator returns to the original local page. Sessions expire and logout invalidates the session.
- Use a DAQ-specific cookie name and signing key. Set HttpOnly and SameSite attributes, and Secure for HTTPS. Require HTTPS for remote production login; deployment guidance must cover TLS termination and private secret provisioning. Protect state-changing HTTP and Socket.IO actions against cross-site requests.
- The Config Center, its configuration and sample APIs, device scan, destination test, runtime status, acquisition controls, buffer controls, and Socket.IO events require DAQ authentication. Only login assets and a minimal health endpoint are public. The health endpoint exposes availability without configuration, credentials, samples, logs, or detailed acquisition state.
- The public Portal continues linking to DAQ. Its DAQ badge uses the minimal health endpoint through an explicitly allowed Portal origin and shows availability only. Portal neither reads DAQ's protected status API nor holds DAQ credentials.
- Configuration responses and error messages never include database passwords, DSNs containing passwords, Influx tokens, MQTT passwords, or other secrets. The Config Center shows an unchanged/replace state for saved secrets; omitting an unchanged secret during an edit preserves it. An explicit replacement updates it.

## Delivery sequence

1. Add private credential and session-secret provisioning, fail-closed startup validation, and DAQ-owned login/logout with session expiry.
2. Apply one authentication boundary to DAQ pages, HTTP APIs, and Socket.IO connection and control events; add cross-site request protection and narrow browser origins.
3. Redact saved secrets in API responses and adapt the Config Center to preserve or replace them without reading them back.
4. Split the public health contract from authenticated runtime status and update Portal polling and the container health check.
5. Document HTTPS deployment, initial credential setup, rotation, logout, and recovery; verify the full operator path and denied access paths before rollout.

MUSASHI II and MUSASHI IV will get their own login pages, credentials, signing keys, and sessions in later work. They do not depend on a shared identity service or on a DAQ session. Portal remains public.
