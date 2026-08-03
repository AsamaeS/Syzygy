from fastapi import FastAPI, WebSocket
from fastapi.staticfiles import StaticFiles
from fastapi.responses import HTMLResponse
import asyncio
import json
from app.services.mqtt_listener import MQTTListener
from app.services.fairness_calculator import FairnessCalculator

app = FastAPI(title="Syzygy Backend", version="0.1.0")
app.mount("/static", StaticFiles(directory="dashboard/static"), name="static")

mqtt = MQTTListener()
fairness = FairnessCalculator()

@app.on_event("startup")
async def startup():
    await mqtt.connect()
    asyncio.create_task(mqtt.consume())

@app.get("/", response_class=HTMLResponse)
async def dashboard():
    with open("dashboard/templates/index.html") as f:
        return f.read()

@app.get("/api/nodes")
async def get_nodes():
    return mqtt.get_active_nodes()

@app.get("/api/telemetry/{node_id}")
async def get_telemetry(node_id: str, limit: int = 100):
    return mqtt.get_telemetry(node_id, limit)

@app.get("/api/metrics")
async def get_metrics():
    return {
        "total_curtailment_kwh": fairness.total_curtailment(),
        "self_consumption_rate": fairness.self_consumption_rate(),
        "jain_fairness_index": fairness.jain_index(),
        "active_nodes": len(mqtt.get_active_nodes()),
        "topology_graph": mqtt.get_topology_graph()
    }

@app.post("/api/nodes/{node_id}/mode")
async def set_mode(node_id: str, mode: str):
    await mqtt.publish_mode(node_id, mode)
    return {"status": "ok", "node": node_id, "mode": mode}

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    try:
        while True:
            data = await mqtt.get_latest_frame()
            await websocket.send_json(data)
            await asyncio.sleep(1)
    except Exception:
        await websocket.close()

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
