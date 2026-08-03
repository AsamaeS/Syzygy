import math
from typing import Dict, List

class FairnessCalculator:
    def __init__(self, db_connector=None):
        self.db = db_connector
        self.curtailment_log: Dict[str, float] = {}
        self.exchange_log: Dict[str, float] = {}

    def record_curtailment(self, node_id: str, kwh: float):
        self.curtailment_log[node_id] = self.curtailment_log.get(node_id, 0) + kwh

    def record_exchange(self, from_node: str, to_node: str, kwh: float):
        key = f"{from_node}->{to_node}"
        self.exchange_log[key] = self.exchange_log.get(key, 0) + kwh

    def total_curtailment(self) -> float:
        return sum(self.curtailment_log.values())

    def self_consumption_rate(self, total_gen: float = 1000.0) -> float:
        curtailed = self.total_curtailment()
        exported = sum(v for k, v in self.exchange_log.items() if "->" in k)
        return max(0.0, 1.0 - (curtailed + exported) / total_gen)

    def jain_index(self, node_utilities: List[float] = None) -> float:
        if node_utilities is None:
            node_utilities = list(self.exchange_log.values())
        if not node_utilities:
            return 1.0
        n = len(node_utilities)
        sum_x = sum(node_utilities)
        sum_x2 = sum(x**2 for x in node_utilities)
        if sum_x2 == 0:
            return 1.0
        return (sum_x ** 2) / (n * sum_x2)

    def nash_bargaining_solution(self, utilities: Dict[str, float], 
                                  disagreement: Dict[str, float]) -> Dict[str, float]:
        surplus = sum(utilities.values()) - sum(disagreement.values())
        n = len(utilities)
        solution = {}
        for node in utilities:
            solution[node] = disagreement[node] + surplus / n
        return solution
