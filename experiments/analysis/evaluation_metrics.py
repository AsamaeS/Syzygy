"""
Evaluation Metrics for Syzygy Experiments

Metrics derived from IEEE literature review:
1. Curtailment Rate
2. Self-Consumption Rate
3. Fairness Index (Jain)
4. Communication Overhead
5. Convergence Time
6. Safety Response Time
"""

import json
import numpy as np
from typing import List, Dict

class SyzygyMetrics:
    def __init__(self, log_file: str = None):
        self.frames: List[Dict] = []
        if log_file:
            with open(log_file) as f:
                self.frames = json.load(f)

    def curtailment_rate(self) -> float:
        total_gen = sum(f.get('P_gen', 0) for f in self.frames)
        total_curt = sum(f.get('P_curt', 0) for f in self.frames)
        return total_curt / total_gen if total_gen > 0 else 0.0

    def self_consumption_rate(self) -> float:
        total_gen = sum(f.get('P_gen', 0) for f in self.frames)
        total_curt = sum(f.get('P_curt', 0) for f in self.frames)
        total_export = sum(f.get('P_grid_export', 0) for f in self.frames)
        return 1.0 - (total_curt + total_export) / total_gen if total_gen > 0 else 0.0

    def peak_demand_reduction(self, baseline_peak: float) -> float:
        coop_peak = max(f.get('P_load', 0) for f in self.frames)
        return (baseline_peak - coop_peak) / baseline_peak

    def jain_fairness(self, node_utilities: List[float]) -> float:
        n = len(node_utilities)
        if n == 0:
            return 1.0
        sum_x = sum(node_utilities)
        sum_x2 = sum(x**2 for x in node_utilities)
        return (sum_x ** 2) / (n * sum_x2)

    def communication_overhead(self, msg_count: int, duration_hours: float) -> float:
        return msg_count / duration_hours

    def admm_convergence_time(self, iteration_times: List[float]) -> float:
        return sum(iteration_times)

    def safety_response_time(self, detection_ms: float, action_ms: float) -> float:
        return detection_ms + action_ms

    def generate_report(self) -> Dict:
        return {
            "curtailment_rate_pct": round(self.curtailment_rate() * 100, 2),
            "self_consumption_rate_pct": round(self.self_consumption_rate() * 100, 2),
            "fairness_index": round(self.jain_fairness([100, 85, 90]), 3),
            "notes": "Replace with actual experimental data"
        }

if __name__ == "__main__":
    m = SyzygyMetrics()
    print(m.generate_report())
