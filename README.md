# Syzygy

> **Distributed Cooperative Energy Management for Multi-Microgrid Systems under Realistic Physical and Communication Constraints**

## Vision

Syzygy is a research-driven prototype inspired by recent IEEE literature on multi-microgrid coordination. It demonstrates a **distributed cooperative energy management system** running on embedded IoT devices (ESP32), where multiple microgrids negotiate energy sharing under realistic physical constraints to reduce avoidable renewable curtailment.

This is not another AI dashboard. It is a small-scale implementation of an IEEE research paper.

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│  BACKEND (FastAPI + Oracle) — Observer, NOT controller       │
│  • Historical storage & visualization                        │
│  • Nash Bargaining fairness (offline)                        │
│  • Dashboard & metrics                                       │
└────────────────────┬────────────────────────────────────────┘
                     │ MQTT telemetry
                     ▼
┌─────────────────────────────────────────────────────────────┐
│  ESP32 NODES (Peer-to-Peer) — Autonomous decision-makers     │
│  • Local Control Agent (LCA)                                 │
│  • Generation / Storage / Load / Trading Agents              │
│  • ADMM Censored (economic layer)                            │
│  • Consensus Protocol (real-time SoC balancing)              │
│  • Safety Monitor (hard constraints override)                │
└─────────────────────────────────────────────────────────────┘
```

## Quick Start

### Firmware (ESP32)
```bash
cd firmware/esp32_agent
pio run --target upload
```

### Backend
```bash
cd backend
pip install -r requirements.txt
uvicorn app.main:app --reload
```

### Hardware Simulation (Wokwi)
```bash
cd firmware/esp32_agent/wokwi
# Open diagram.json in https://wokwi.com
```

## Research Artifacts

| Artifact | Location |
|----------|----------|
| Literature Matrix | `docs/literature_review/literature_matrix.md` |
| Limitation Matrix | `docs/literature_review/limitation_matrix.md` |
| Problem Formulation | `docs/math/problem_formulation.md` |
| System Architecture | `docs/architecture/system_architecture.md` |
| Experiment Scenarios | `docs/experiments/` |

## Citation

```bibtex
@inproceedings{syzygy2026,
  title={Syzygy: A Distributed Cooperative EMS for Multi-Microgrid Systems on Embedded IoT},
  author={VoltHacks Team},
  year={2026}
}
```

## License

MIT License — see [LICENSE](LICENSE) for details.
