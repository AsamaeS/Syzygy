# System Architecture

## Agent Model (Inspired by Sajid et al. 2024, but Distributed)

Each ESP32 runs 4 agents + 1 coordinator:

```
Local Control Agent (LCA)
 ├── Generation Agent (GA)
 ├── Storage Agent (SA)
 ├── Load Agent (LA)
 └── Trading Agent (TA)  ← NEW vs Sajid et al. (was EMMC central)
      └── Safety Monitor (Hard constraints override)
```

### Agent Responsibilities

| Agent | Role | Trigger |
|-------|------|---------|
| GA | Curtail excess generation, schedule diesel backup | Every optimization cycle |
| SA | Charge when grid price low, discharge when high | Every optimization cycle |
| LA | Shed non-critical load during peak prices | Price signal > threshold |
| TA | Negotiate P_ex and price with neighbors | ADMM iteration |
| Safety | Hard override if SoC < min or I > max | Continuous |

## Decision Layers

| Layer | Algorithm | Frequency | Latency |
|-------|-----------|-----------|---------|
| Safety | Rule-based | Continuous | < 10 ms |
| Consensus | SoC balancing | Every 30 s | < 500 ms |
| Economic | ADMM Censored | Every 5 min | 3-5 iterations |
| Fairness | Nash Bargaining | Daily (backend) | Offline |
