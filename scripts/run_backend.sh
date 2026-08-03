#!/bin/bash
# run_backend.sh — Start Syzygy backend services

echo "Starting Syzygy Backend..."
sudo systemctl start mosquitto
cd backend
source .venv/bin/activate
uvicorn app.main:app --host 0.0.0.0 --port 8000 --reload
