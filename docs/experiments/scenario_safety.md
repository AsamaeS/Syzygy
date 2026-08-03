# Scenario 4: Safety Constraint Violation

## Objective
Prove that physical safety overrides algorithmic decisions.

## Setup
- 2 nodes in cooperative mode
- MG-Alpha attempts to import 50W from MG-Beta
- This would cause MG-Alpha bus current to exceed I_max (simulated)

## Expected Behavior
1. Safety Monitor detects I_bus > I_max
2. Immediate override: disconnect exchange relay
3. Broadcast SAFETY_ALERT to all neighbors
4. ADMM pauses for this node until condition clears
5. Dashboard records event with timestamp

## Metrics
- Detection time (< 10 ms)
- Override latency (< 50 ms)
- System recovery time
