# Scenario 3: Topology Change (The "Coup de Theatre")

## Objective
Validate adaptation when a node fails or leaves the network.

## Setup
- Start with 3 nodes in cooperative mode
- At t = 15 min, MG-Beta is powered off (simulated failure)

## Expected Behavior
1. MG-Alpha & MG-Gamma detect missing heartbeat from Beta
2. Topology graph updates: 3-node -> 2-node line
3. ADMM resets with new neighbor sets
4. No crash, adaptation completes in < 2 seconds
5. Curtailment may rise temporarily, then stabilizes

## Metrics
- Detection latency (heartbeat timeout)
- Reconfiguration time
- Curtailment spike amplitude
- System stability (no oscillations)
