# Plotter Development Notes

The Plotter is a Flask service with a browser interface built around Plotly charts. It runs on port `8084` in Compose and uses `DB_DSN` to connect to the Compose TimescaleDB/PostgreSQL service. Compose mounts the Plotter source, shared code, and DAQNavi configuration into the container for development.

## Local workflow

```bash
docker compose up -d timescaledb plotter
docker compose logs -f plotter
```

Open `http://localhost:8084`. If a mounted source edit is not reflected, restart the service with `docker compose restart plotter`. Rebuild after changing the image or Python dependencies:

```bash
docker compose build plotter
docker compose up -d --force-recreate plotter
```

## Data and API

The Plotter's available routes and query behavior are defined in [`app.py`](app.py); the UI and chart interactions are in [`static/app.js`](static/app.js). Database tables are not interchangeable: production acquisition writes to its configured production table, while `daq_telemetry` belongs to the legacy schema initialized by `scripts/sql/db_setup.sql`. Confirm which table a Plotter query uses before assuming production samples are visible. No compatibility view should be assumed unless it is explicitly created in the deployed database.

Use a development database with representative schema/data when changing query behavior. Keep database credentials in `.env` and never commit secrets.
