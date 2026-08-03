# Hardware Requirements & Constraints
## Cooperative Microgrid Energy Orchestrator — Hardware Domain

**Author:** [Waad]
**Role:** Hardware & Embedded Hardware Engineer
**Date:** 4/8/2026
**Status:** Draft v1 — Milestone M0
**Mode:** 🔵 SIMULATION-ONLY (see Section 6)

---

## 1. System Overview

The system under design is a DC-based monitoring system for a small-scale microgrid,
covering solar panel input, battery storage, and DC/AC load stages. Each microgrid is
represented by one ESP32-based node that senses local electrical conditions and
communicates with a central backend over MQTT.

This document defines *what* each node must sense and control — electrical selection
of specific components happens in the next phase (Component Selection Trade Studies),
not here.

---

## 2. Electrical Requirements

### 2.1 Voltage Range

| Stage | Voltage Range |
|---|---|
| Solar panel output | 11 V – 18 V DC |
| Battery voltage (12 V system) | 10 V – 14.5 V DC |
| Load side | 12 V – 24 V DC |

- **Minimum voltage:** 0 V (required for calibration and safety checks)
- **Maximum voltage (design ceiling):** 30 V DC — includes a 20–30% safety margin
  above the highest expected stage voltage (24 V load side)

### 2.2 Current Range

| Stage | Current Range |
|---|---|
| 10 W solar panel | 0.3 A – 0.6 A |
| Battery charging | 0.5 A – 1.4 A |
| Small load (LED) | 0.03 A – 0.5 A |
| General monitoring (with sensor) | 0 A – 5 A |

- **Minimum current:** 0 A
- **Maximum current (design ceiling):** 5 A DC — sized for small-to-medium scale
  applications, with margin above the highest measured stage (battery charging)

### 2.3 Accuracy Target

| Measurement | Accuracy |
|---|---|
| Voltage measurement | ±1–2.5% |
| Current measurement | ±1.75–22% (sensor-dependent) |
| Power calculation | ±2–5% (typical) |

**Overall accuracy target: ±2–5%** — a moderate, reasonable target for a hackathon-scale
prototype (not lab-grade instrumentation).

---

## 3. Monitoring Node Requirements

Recommended configuration: **2–3 nodes.**

| Node | Responsibility |
|---|---|
| Node 1 | Solar Panel Monitoring (V, I, P) |
| Node 2 | Battery Monitoring (V, I, P, Temperature) |
| Node 3 (optional) | AC Load Monitoring (after the inverter) |

---

## 4. Processing & Communication Requirements

- **Microcontroller:** ESP32 (variant selection = separate trade study, Milestone 1)
- **Analog sensing:** ADC1 only (GPIO32–39) — ADC2 is unreliable while Wi-Fi is active
- **Digital sensing/communication:** I2C bus (shared between current/voltage IC and
  optional environmental sensor)
- **Wireless communication:** Wi-Fi → MQTT to central FastAPI backend
- **Optional actuation:** GPIO-controlled MOSFET/relay for flexible load control
  (in scope only if project timeline allows — to be confirmed by Milestone 1)

---

## 5. Power Supply Requirement (Node-Level)

Recommended architecture (from system-level design):

```
Solar Panel → Charge Controller → Battery → Buck/LDO Converter (5V/3.3V) → ESP32
```

- ESP32 must be powered from the same microgrid it measures (self-powered node concept)
- Power design must account for Wi-Fi TX current bursts (300–500 mA peaks) — this is a
  known failure mode (brownouts/resets) if under-budgeted; see Component Selection phase

---

## 6. Simulation-Only Scope (Project-Specific Constraint)

**This project's hardware work will be conducted entirely through simulation/EDA tools
until (and unless) a competition win justifies physical fabrication.**

| Real Hardware Step | Our Equivalent |
|---|---|
| Bench build & soldering | Wokwi simulation |
| Multimeter validation | LTspice analog simulation + Wokwi logic simulation |
| PCB fabrication | KiCad layout, DRC/ERC clean, **not sent to fabricator** |
| Physical calibration (Section 8.4/8.5 of Hardware Handbook) | Theoretical calibration formulas derived from datasheets + simulated behavior |

**Implication:** All accuracy figures in Section 2.3 above are *component-rated* (from
datasheets), not *measured*. This distinction must be stated explicitly in every
downstream document (BOM, calibration notes, final report) so reviewers/judges
understand the validation boundary. A full simulation-vs-physical divergence log is
maintained separately in `Documentation/simulation-scope-and-limitations.md`.

---

## 7. Cross-Team Commitments (Hardware ↔ Firmware Interface)

Per coordination with the Firmware Engineer (as of 5/8/2026), the following are locked
and **should not change without immediate notification**:

- **ESP32 Variant:** ESP32-DevKitC (WROOM-32) — pending final confirmation in
  Milestone 1 trade study
- **Sensor count:** 2–3 (Voltage, Current, optional Environmental)
- **Communication:** I2C + Analog ADC (ADC1 only, GPIO32–39)
- **Power:** 3.3 V regulated rail (from battery/solar)

Pending from Firmware Engineer (expected within 2 days of 5/8/2026):
- MQTT topic structure (e.g. `microgrid/node1/voltage`)
- JSON payload schema
- Sampling rate
- Power management states (Active / Deep Sleep / etc.)
- GPIO control logic (LEDs, relays)

---

## 8. Constraints (Budget, Timeline, Availability)

- **Timeline:** Hardware work begins 5/8/2026, all deliverables must be complete by
  1/9/2026 (~27 days)
- **Budget/procurement:** N/A for this phase — no physical components purchased
  (see Section 6)
- **Tooling:** Wokwi (ESP32 + circuit simulation), KiCad (schematic + PCB),
  LTspice (analog circuit simulation), Tinkercad Circuits (basic circuit sanity checks)

---

## 9. Out of Scope (Explicit Non-Requirements)

Per the Hardware/Firmware boundary defined in the Hardware Engineering Handbook, the
following are **not** hardware-domain requirements and are not addressed in this
document:

- ESP32 application/firmware code (Arduino/ESP-IDF logic, RTOS tasks)
- MQTT broker configuration and topic/payload implementation
- Backend services, dashboard, database
- OTA update logic

---

## Revision Log

| Date | Change | Author |
|---|---|---|
| 4/8/2026 | Initial draft (Milestone M0) | [Waad] |