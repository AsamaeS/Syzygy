# Communication Protocol

## MQTT Topic Hierarchy

```
syzygy/
├── global/
│   └── clock          # Time sync (backend -> all)
├── mg{ID}/
│   ├── telemetry/     # Periodic state broadcast
│   │   ├── power      # {P_gen, P_load, P_bat, SoC}
│   │   ├── safety     # {I_bus, V_bus, T_board}
│   │   └── heartbeat  # {timestamp, neighbor_list}
│   ├── optimization/  # ADMM messages
│   │   ├── bid        # {quantity, price, direction}
│   │   ├── consensus  # {P_ex_ij, u_ij, iteration}
│   │   └── ack        # Acknowledgment
│   └── control/       # External commands
│       ├── mode       # AUTO / ISLAND / SAFE
│       └── config     # Parameter updates
```

## Message Format (JSON)

### Telemetry
```json
{
  "node_id": "mg-alpha",
  "timestamp": 1722723600,
  "power": {"P_gen": 85.3, "P_load": 42.1, "P_bat": -30.2, "P_grid": 0.0},
  "soc": 67.4,
  "safety": {"I_bus": 2.1, "V_bus": 12.4, "status": "OK"}
}
```

### ADMM Consensus
```json
{
  "node_id": "mg-alpha",
  "iteration": 3,
  "neighbor": "mg-beta",
  "P_ex": 15.5,
  "u": 0.02,
  "censored": false
}
```

## Heartbeat & Topology Detection

- Period: 5 seconds
- Timeout: 15 seconds -> neighbor marked OFFLINE
- On topology change: ADMM resets with new neighbor set
- Safety override triggers immediate broadcast to all neighbors
