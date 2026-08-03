# Scenario 1: Baseline (Non-Cooperative)

## Objective
Establish the reference curtailment rate when microgrids operate in isolation.

## Setup
- 3 nodes: MG-Alpha, MG-Beta, MG-Gamma
- No MQTT communication between nodes
- Each node optimizes locally only

## Expected Results
- Curtailment rate: ~30% (MG-Beta at noon, battery full)
- Self-consumption: ~60%
- Grid imports: High during evening peak
- Fairness index: N/A (no sharing)

## Metrics to Record
- P_curt per node per timestep
- SoC trajectory
- P_grid import/export
- Total operational cost
