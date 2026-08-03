# Mathematical Problem Formulation

## Notation

| Symbol | Description | Unit |
|--------|-------------|------|
| N | Set of microgrid nodes | — |
| P_gen,i(t) | Renewable generation at node i | W |
| P_load,i(t) | Local load at node i | W |
| P_bat,i(t) | Battery power (+ charge, - discharge) | W |
| P_ex,ij(t) | Power exchanged from i to j | W |
| P_curt,i(t) | Curtailed renewable power | W |
| SoC_i(t) | State of charge | % |
| c_grid(t) | Grid electricity price | $/kWh |
| c_curt | Curtailment penalty | $/kWh |
| rho | ADMM penalty parameter | — |

## Global Problem (Centralized — Reference Only)

Minimize sum over i in N, sum over t of:
    c_grid(t) * P_grid,i(t) + c_curt * P_curt,i(t)

Subject to:
1. Power balance: P_gen,i + P_bat,i + sum_j P_ex,ji = P_load,i + P_curt,i + sum_j P_ex,ij
2. SoC dynamics: SoC_i(t+1) = SoC_i(t) - eta * P_bat,i(t) * dt / E_nom
3. SoC limits: SoC_min <= SoC_i(t) <= SoC_max
4. Battery power: P_bat,min <= P_bat,i(t) <= P_bat,max
5. Exchange symmetry: P_ex,ij = -P_ex,ji (coupling constraint)
6. Current limit: |I_bus,i(t)| <= I_max

## Distributed ADMM Formulation

Each node i solves locally:

Minimize f_i(x_i) + (rho/2) * sum_j || P_ex,ij - P_bar_ex,ij + u_ij ||^2

Where:
- x_i = [P_bat,i, {P_ex,ij}_{j in N_i}, P_curt,i]
- f_i(x_i) = c_grid * P_grid,i + c_curt * P_curt,i
- P_bar_ex,ij : average from neighbor's last iteration
- u_ij : scaled dual variable

### ADMM Iteration (at node i)

1. Local minimization (x-update):
   x_i^{k+1} = argmin { f_i(x_i) + (rho/2) * sum_j || P_ex,ij - P_bar_ex,ij^k + u_ij^k ||^2 }

2. Consensus (z-update / averaging):
   P_bar_ex,ij^{k+1} = (P_ex,ij^{k+1} - P_ex,ji^{k+1}) / 2

3. Dual ascent (u-update):
   u_ij^{k+1} = u_ij^k + P_ex,ij^{k+1} - P_bar_ex,ij^{k+1}

## Censored ADMM (Communication Reduction)

Node i only sends P_ex,ij to neighbor j if:
   |P_ex,ij^{k+1} - P_ex,ij^k| > epsilon_censor

This reduces MQTT traffic by ~60-80%.

## Consensus Protocol (Real-Time Layer)

For SoC balancing between neighbors (fast, < 10 iterations):
   SoC_i^{k+1} = SoC_i^k + epsilon * sum_{j in N_i} (SoC_j^k - SoC_i^k)

Convergence guaranteed if epsilon < 1 / max_i |N_i|.
