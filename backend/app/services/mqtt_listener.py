import asyncio
import json
from datetime import datetime
from typing import Dict, List
import aiomqtt

class MQTTListener:
    def __init__(self, broker="localhost", port=1883):
        self.broker = broker
        self.port = port
        self.telemetry: Dict[str, List[dict]] = {}
        self.active_nodes: Dict[str, dict] = {}
        self.topology: Dict[str, List[str]] = {}
        self.client = None

    async def connect(self):
        self.client = aiomqtt.Client(hostname=self.broker, port=self.port)
        await self.client.__aenter__()

    async def consume(self):
        await self.client.subscribe("syzygy/+/telemetry/#")
        await self.client.subscribe("syzygy/+/heartbeat")
        async for message in self.client.messages:
            await self._handle_message(message)

    async def _handle_message(self, message):
        topic = message.topic.value
        payload = json.loads(message.payload)
        node_id = topic.split("/")[1]

        if "telemetry" in topic:
            if node_id not in self.telemetry:
                self.telemetry[node_id] = []
            self.telemetry[node_id].append({"timestamp": datetime.utcnow().isoformat(), **payload})
            self.telemetry[node_id] = self.telemetry[node_id][-1000:]

        elif "heartbeat" in topic:
            self.active_nodes[node_id] = {
                "last_seen": datetime.utcnow().isoformat(),
                "neighbors": payload.get("neighbors", [])
            }
            self.topology[node_id] = payload.get("neighbors", [])

    def get_active_nodes(self) -> List[str]:
        return list(self.active_nodes.keys())

    def get_telemetry(self, node_id: str, limit: int = 100) -> List[dict]:
        return self.telemetry.get(node_id, [])[-limit:]

    def get_topology_graph(self) -> dict:
        return {"nodes": list(self.topology.keys()), "edges": self._edges()}

    def _edges(self):
        edges = []
        for node, neighbors in self.topology.items():
            for neighbor in neighbors:
                key = f"{neighbor}-{node}"
                if key not in [f"{e['from']}-{e['to']}" for e in edges]:
                    edges.append({"from": node, "to": neighbor})
        return edges

    async def publish_mode(self, node_id: str, mode: str):
        topic = f"syzygy/{node_id}/control/mode"
        await self.client.publish(topic, json.dumps({"mode": mode}))

    def get_latest_frame(self):
        frame = {}
        for node, data in self.telemetry.items():
            if data:
                frame[node] = data[-1]
        return frame
