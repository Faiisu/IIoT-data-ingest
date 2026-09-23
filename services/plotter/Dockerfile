FROM python:3.12-slim

WORKDIR /app

COPY services/plotter/requirements.txt /app/requirements.txt
RUN pip install --no-cache-dir -r /app/requirements.txt

COPY shared /app/shared
COPY services/plotter /app/services/plotter

WORKDIR /app/services/plotter
ENV PYTHONPATH="/app"

EXPOSE 8084
CMD ["python3", "app.py"]
