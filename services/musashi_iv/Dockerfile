FROM python:3.12-slim

WORKDIR /app

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc \
    libpq5 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

COPY --from=ghcr.io/astral-sh/uv:latest /uv /uvx /bin/

COPY requirements.txt /app/requirements.txt
RUN uv pip install --system --no-cache -r /app/requirements.txt || \
    pip install --no-cache-dir --default-timeout=30 --retries=3 -r /app/requirements.txt

COPY . /app
ENV PYTHONPATH="/app"

EXPOSE 8083

CMD ["python3", "app.py"]
