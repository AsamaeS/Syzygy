from pydantic import BaseModel
from typing import Optional, List
from datetime import datetime

class TelemetryFrame(BaseModel):
    node_id: str
    timestamp: datetime
    P_gen: float
    P_load: float
    P_bat: float
    P_grid: float
    SoC: float
    I_bus: float
    V_bus: float
    status: str

class NodeStatus(BaseModel):
    node_id: str
    online: bool
    last_seen: datetime
    neighbors: List[str]
    mode: str
