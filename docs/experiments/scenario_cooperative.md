# Scenario 2: Cooperative Distributed (Syzygy)

## Objective
Demonstrate curtailment reduction via peer-to-peer energy sharing.

## Setup
- Same 3 nodes
- Full MQTT peer-to-peer enabled
- ADMM Censored active
- Consensus SoC balancing active

## Flow
1. MG-Beta detects excess PV (SoC > 90%, P_gen > P_load + P_bat_max)
2. Broadcasts bid to neighbors: {sell: 40W, price: 0.08 $/kWh}
3. MG-Alpha has deficit: accepts bid
4. ADMM converges in 3 iterations -> exchange agreed
5. MG-Beta battery discharges less, Alpha imports less from grid

## Expected Results
- Curtailment rate: ~5%
- Self-consumption: ~85%
- Communication overhead: < 20 messages/hour (censored)
- Fairness index: > 0.8 (Jain's index)
