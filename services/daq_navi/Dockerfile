FROM python:3.12-slim

WORKDIR /app

# Install system dependencies needed for PostgreSQL client & runtime
RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc \
    libpq5 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Copy and install python dependencies
COPY services/daq_navi/requirements.txt /app/requirements.txt
RUN pip install --no-cache-dir -r /app/requirements.txt

# Copy service and shared application code
COPY services/daq_navi /app/services/daq_navi
COPY shared /app/shared

WORKDIR /app/services/daq_navi
ENV PYTHONPATH="/app:/app/services/daq_navi"

RUN chmod +x /app/services/daq_navi/entrypoint.sh

ENTRYPOINT ["/app/services/daq_navi/entrypoint.sh"]
