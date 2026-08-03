# Literature Matrix

| # | Title | Year | Problem | Method | Algo | Hardware | Sim | ESP32? | Multi-MG? | Key Limitation |
|---|-------|------|---------|--------|------|----------|-----|--------|-----------|----------------|
| 1 | GCN-ML for PSOR Assessment (Zhang et al.) | 2025 | Topology changes + source-load fluctuation | GCN + Meta-learning | GCN-ML | No | MATLAB | No | No | Offline, heavy |
| 2 | Multi-Agent MMG Reinforcement (Sajid et al.) | 2024 | Multi-microgrid energy trading | Multi-agent + ILP | MILP | No | Simulink | No | Yes | EMMC central, no hardware |
| 3 | ADMM Distributed EMS (MDPI Sensors) | 2026 | Cost minimization multi-MG | ADMM + censure | Censored ADMM | No | MATLAB | Theoretical | Yes | No comm constraints |
| 4 | Consensus-based MMG (Appl. Math. Comp.) | 2022 | Power sharing islanded MGs | Hierarchical consensus | Discrete consensus | No | MATLAB | No | Yes | No comm constraints |
| 5 | Smart Energy Mgmt ESP32 (PMC) | 2024 | Residential PV management | ESP32 + Modbus | Rules | **Yes** | Prototype | **Yes** | No | Single MG, no optimization |
| 6 | IoT Smart Metering ESP32 (IJSAT) | 2025 | Smart metering + load control | ESP32 + rules | Priority rules | **Yes** | Prototype | **Yes** | No | Fixed rules only |

## Research Gap

> **No existing work validates distributed multi-microgrid optimization on ESP32 hardware with peer-to-peer MQTT communication and real-time topology adaptation.**
