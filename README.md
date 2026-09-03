# ⚡ Syzygy - Cooperative Microgrid Energy Orchestrator

> **Distributed Cooperative Energy Management for Multi-Microgrid Systems, validated on real embedded hardware.**

Built at **VoltHacks 2026**. Syzygy is a research-driven prototype (not a generic AI dashboard) that tackles **renewable energy curtailment** by letting multiple microgrids negotiate energy sharing *before* excess solar power is wasted using game-theoretic, distributed optimization running directly on ESP32 nodes.

📄 [Project inspiration & research strategy](#-research-foundation) · 🚀 [Quick start](#-quick-start)

---

## 📌 Table of Contents

1. [The Problem](#-the-problem)
2. [Our Approach](#-our-approach)
3. [System Architecture](#-system-architecture)
4. [Repository Structure](#-repository-structure)
5. [Quick Start](#-quick-start)
   - [1. Backend (FastAPI + Dashboard)](#1-backend-fastapi--dashboard)
   - [2. Firmware (ESP32 nodes)](#2-firmware-esp32-nodes)
   - [3. Hardware Simulation (Wokwi)](#3-hardware-simulation-wokwi-no-hardware-needed)
   - [4. Running an Experiment](#4-running-an-experiment)
6. [Communication Protocol](#-communication-protocol)
7. [Hardware](#-hardware)
8. [Demo Scenarios](#-demo-scenarios)
9. [Research Foundation](#-research-foundation)
10. [Metrics We Track](#-metrics-we-track)
11. [Team](#-team)
12. [License](#-license)

---

## 🧩 The Problem

Renewable energy is routinely **curtailed** production is throttled or wasted — because:
- Local demand is lower than local generation,
- Batteries are already full,
- The grid can't absorb the excess.

Most academic and commercial solutions optimize **one microgrid in isolation**. Nobody lets neighboring microgrids talk to each other and trade power *before* that energy is thrown away.

## 💡 Our Approach

Syzygy treats each microgrid as an **autonomous negotiating agent**, not a passive node reporting to a central brain:

- **Distributed, not centralized.** Every ESP32 node makes its own decisions. There is no single point of failure or control.
- **Game theory for negotiation.** Nodes bid to buy/sell surplus power using a **Censored ADMM** (Alternating Direction Method of Multipliers) optimization, cutting communication overhead by 60–80%.
- **Physically grounded.** Every decision respects real constraints: battery State of Charge (SoC), inverter/bus current limits, and line capacity — enforced by a hardware-level Safety Monitor that can override any economic decision in milliseconds.
- **Runs on real embedded hardware**, not just a MATLAB simulation this is the gap we found across the IEEE literature (see [Research Foundation](#-research-foundation)).
- **LLM used only to *explain* decisions to humans on the dashboard never to make them.** All control logic is deterministic and auditable.

---

## 🏗 System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│  BACKEND (FastAPI) -  Observer, NOT controller               │
│  • Historical storage, live dashboard, WebSocket stream       │
│  • Nash Bargaining fairness calculation (offline, daily)      │
│  • REST API for nodes / telemetry / metrics                   │
└────────────────────┬──────────────────────────────────────── ┘
                      │  MQTT (telemetry, bids, consensus, control)
                      ▼
┌─────────────────────────────────────────────────────────────┐
│  ESP32 NODES  — Autonomous, peer-to-peer decision-makers      │
│                                                                │
│   Local Control Agent (LCA)                                   │
│    ├── Generation Agent   → curtail / schedule backup          │
│    ├── Storage Agent      → charge / discharge scheduling      │
│    ├── Load Agent         → shed non-critical load             │
│    ├── Trading Agent      → negotiate P_exchange & price (ADMM)│
│    └── Safety Monitor     → hard override (SoC / current)      │
└─────────────────────────────────────────────────────────────┘
```

### Decision layers (fast → slow)

| Layer | Algorithm | Frequency | Latency |
|---|---|---|---|
| **Safety** | Rule-based hard override | Continuous | < 10 ms |
| **Consensus** | Distributed SoC balancing | Every 30 s | < 500 ms |
| **Economic** | Censored ADMM negotiation | Every 5 min | 3–5 iterations |
| **Fairness** | Nash Bargaining (offline) | Daily, on backend | — |

The full mathematical formulation (power balance, ADMM update rules, censoring threshold, consensus convergence proof) is in [`docs/math/problem_formulation.md`](docs/math/problem_formulation.md).

---

## 📁 Repository Structure

```
Syzygy/
├── backend/              # FastAPI backend: dashboard, REST API, MQTT listener, fairness calc
│   ├── app/
│   │   ├── main.py            # API routes & WebSocket entrypoint
│   │   ├── api/                # Route/model definitions
│   │   ├── services/           # mqtt_listener.py, fairness_calculator.py
│   │   └── database/           # oracle_connector.py
│   └── dashboard/               # Static assets + HTML templates
├── firmware/
│   ├── esp32_agent/            # PlatformIO project (Arduino framework)
│   │   ├── src/agents/          # Generation / Storage / Load / Trading / LocalControl agents
│   │   ├── src/optimization/    # ADMMCensored.h, ConsensusProtocol.h
│   │   ├── src/safety/          # SafetyMonitor.h
│   │   ├── src/sensors/         # INA219Reader.h, ACS712Reader.h
│   │   ├── src/communication/   # MQTTClient.h
│   │   └── wokwi/                # Browser-based simulation (no hardware needed)
│   └── shared/protocol/         # SyzygyProtocol.h — shared message schema
├── hardware/              # KiCad schematics, BOM, GPIO map, LTspice analysis, Wokwi sim
├── experiments/
│   ├── scenarios/               # 4 reproducible demo scenarios (see below)
│   ├── data/                    # Synthetic load/generation profiles + real datasets
│   └── analysis/evaluation_metrics.py  # Curtailment / fairness / convergence metrics
├── docs/
│   ├── literature_review/       # literature_matrix.md, limitation_matrix.md
│   ├── math/problem_formulation.md
│   ├── architecture/            # system_architecture.md, communication_protocol.md
│   └── experiments/             # Scenario write-ups
└── scripts/               # run_backend.sh, flash_esp32.sh, generate_report.py
```

---

## 🚀 Quick Start

### 1. Backend (FastAPI + Dashboard)

```bash
cd backend
python -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt

# Syzygy needs a local MQTT broker (Mosquitto) — install once:
#   macOS:   brew install mosquitto
#   Ubuntu:  sudo apt install mosquitto mosquitto-clients
sudo systemctl start mosquitto   # or: mosquitto -v

uvicorn app.main:app --reload --host 0.0.0.0 --port 8000
```

Or simply run the helper script from the repo root:
```bash
bash scripts/run_backend.sh
```

Open the live dashboard at **http://localhost:8000** - it shows active nodes, live telemetry, curtailment/self-consumption/fairness metrics, and the current negotiation topology (via WebSocket at `/ws`).

Key REST endpoints:
| Endpoint | Purpose |
|---|---|
| `GET /api/nodes` | List active microgrid nodes |
| `GET /api/telemetry/{node_id}` | Historical telemetry for one node |
| `GET /api/metrics` | Curtailment, self-consumption, Jain fairness index, topology graph |
| `POST /api/nodes/{node_id}/mode` | Force a node into `AUTO` / `ISLAND` / `SAFE` mode |
| `WS /ws` | Live push of the latest telemetry frame (1 Hz) |

> **Note:** `backend/requirements.txt` includes `oracledb` for persistent storage. For a hackathon demo you can run without a database connection — the MQTT listener keeps recent telemetry in memory, which is enough to power the dashboard live.

### 2. Firmware (ESP32 nodes)

Requires [PlatformIO](https://platformio.org/) (CLI or VS Code extension).

```bash
cd firmware/esp32_agent
pio run --target upload      # flash a single node over USB
pio device monitor -b 115200 # view serial logs
```

To flash **all three demo nodes** at once (mg-alpha, mg-beta, mg-gamma) on `/dev/ttyUSB0-2`:
```bash
bash scripts/flash_esp32.sh
```
This script auto-patches `firmware/esp32_agent/include/config.h` with the correct `NODE_ID` for each board before flashing — update the `NODES` / `PORTS` arrays inside the script if your ports differ.

Each node needs Wi-Fi + MQTT broker credentials set in `config.h` (point it at the machine running the backend/Mosquitto).

### 3. Hardware Simulation (Wokwi — no hardware needed)

Don't have physical ESP32 boards on hand? Run the whole thing in-browser:
```bash
cd firmware/esp32_agent/wokwi
# open diagram.json at https://wokwi.com — click "Start Simulation"
```
This is exactly how the project was validated during the hackathon (see [`hardware/Documentation/design-decisions.md`](hardware/Documentation/design-decisions.md) — hardware design was **simulation-first**, using KiCad + Wokwi + LTspice).

### 4. Running an Experiment

Each scenario in [`experiments/scenarios/`](experiments/scenarios) is reproducible against the synthetic profiles in `experiments/data/synthetic_profiles/`. After a run, generate a metrics report:

```bash
python scripts/generate_report.py --scenario cooperative
```

This uses [`experiments/analysis/evaluation_metrics.py`](experiments/analysis/evaluation_metrics.py) to compute curtailment rate, self-consumption rate, Jain's fairness index, communication overhead, and ADMM convergence time.

---

## 📡 Communication Protocol

All nodes and the backend communicate over **MQTT**, topic-namespaced per node:

```
syzygy/
├── global/clock                    # Time sync (backend → all)
├── mg{ID}/telemetry/{power,safety,heartbeat}
├── mg{ID}/optimization/{bid,consensus,ack}   # ADMM negotiation messages
└── mg{ID}/control/{mode,config}              # External overrides
```

- **Heartbeat**: every 5 s, 15 s timeout → neighbor marked `OFFLINE` and the topology graph is recomputed live.
- **Censored ADMM**: a node only broadcasts an updated bid if it changed by more than `epsilon_censor`, cutting MQTT traffic ~60–80%.
- Full message schemas and JSON examples: [`docs/architecture/communication_protocol.md`](docs/architecture/communication_protocol.md).

---

## 🔧 Hardware

Reference node (one design, replicated per microgrid):

| Component | Part | Notes |
|---|---|---|
| MCU | ESP32-WROOM-32 (DevKitC) | Wi-Fi + MQTT client |
| Voltage/Current sensor | INA226 (I2C, addr `0x40`) | Primary sensing |
| Shunt resistor | 0.01 Ω | Rated for ~5 A max |
| Control outputs | GPIO25 (Curtail) · GPIO26 (Export) · GPIO27 (Import) | All boot `LOW`; safety-forced `LOW` on heartbeat loss |
| Status LEDs | 4× | Status, Curtail, Export, Import |

Full BOM: [`hardware/bom/bill_of_materials.md`](hardware/bom/bill_of_materials.md) · GPIO map: [`hardware/Pinout/gpio-map.md`](hardware/Pinout/gpio-map.md) · KiCad schematic + Wokwi simulation: [`hardware/`](hardware).

Hardware development was **simulation-first** - see [`hardware/Reports/final-hardware-report.md`](hardware/Reports/final-hardware-report.md) for the complete rationale and what's left for a physical build.


---

## 📚 Research Foundation

Syzygy isn't "an AI app" — it's a small-scale hardware implementation of a gap found across 6 IEEE papers (2022–2026) reviewed for this project.

**Identified research gap:**
> No existing work validates distributed multi-microgrid optimization on ESP32 hardware with peer-to-peer MQTT communication and real-time topology adaptation.

| Limitation across the literature | Papers affected | Syzygy's answer |
|---|---|---|
| Simulation only, no hardware | 4/6 | Real ESP32 firmware, Wokwi-validated |
| Centralized controller | 2/6 | Fully peer-to-peer MQTT |
| No communication constraints modeled | 5/6 | Censored ADMM + heartbeat protocol |
| No battery degradation / SoC awareness | 6/6 | SoC-aware scheduling per node |
| Static, one-shot optimization | 3/6 | Rolling ADMM + real-time consensus |
| No renewable uncertainty | 4/6 | Stochastic synthetic load/generation profiles |

Full matrices: [`docs/literature_review/literature_matrix.md`](docs/literature_review/literature_matrix.md) and [`limitation_matrix.md`](docs/literature_review/limitation_matrix.md).

---

## 📊 Metrics We Track

Computed via [`experiments/analysis/evaluation_metrics.py`](experiments/analysis/evaluation_metrics.py):

- **Curtailment rate** — % of generated renewable energy wasted
- **Self-consumption rate** — % of generation used locally or shared (not exported/curtailed)
- **Jain's fairness index** — how evenly the benefit of sharing is distributed across nodes
- **Communication overhead** — MQTT messages/hour (shows the effect of censoring)
- **ADMM convergence time** — iterations/time to reach a negotiated agreement
- **Safety response time** — detection + override latency

---

## 👥 Team
 
| Member | Area | Responsibility |
|---|---|---|
| **Waad** | Hardware & Embedded | Reference node design, KiCad schematic, INA226/sensor integration, GPIO map, Wokwi simulation, LTspice analysis, BOM |
| **Hoor** | Firmware | ESP32 agents (Generation/Storage/Load/Trading/Local Control), Safety Monitor, MQTT client, Censored ADMM & consensus protocol on-device |
| **Asamae** | Research Direction, Literature Review, Backend & Optimization, Dashboard & Demo, Integration, Final Presentation | IEEE paper collection & research-gap synthesis, FastAPI backend, Nash Bargaining fairness, live dashboard, experiment scenarios, tying all subsystems together, Devpost/demo delivery |
 

---

## 📄 License

MIT License — see [LICENSE](LICENSE).

```bibtex
@inproceedings{syzygy2026,
  title={Syzygy: A Distributed Cooperative EMS for Multi-Microgrid Systems on Embedded IoT},
  author={VoltHacks Team},
  year={2026}
}
```