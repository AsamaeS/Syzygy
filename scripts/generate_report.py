#!/usr/bin/env python3
"""generate_report.py — Generate experiment report from data."""

import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent / "experiments" / "analysis"))
from evaluation_metrics import SyzygyMetrics

def main(data_file: str):
    metrics = SyzygyMetrics(data_file)
    report = metrics.generate_report()
    output = Path("experiments/reports")
    output.mkdir(parents=True, exist_ok=True)
    report_file = output / f"report_{Path(data_file).stem}.json"
    with open(report_file, "w") as f:
        json.dump(report, f, indent=2)
    print(f"Report generated: {report_file}")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python generate_report.py <data_file.json>")
        sys.exit(1)
    main(sys.argv[1])
