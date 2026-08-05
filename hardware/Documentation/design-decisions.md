# Hardware Design Decisions
Project: Syzygy
Subsystem: Hardware Engineering
Status: Draft

## 1. Project Scope
This hardware work will follow a simulation-first workflow during the hackathon.
No physical hardware components will be purchased during this phase.
The design will still be prepared in a manufacturable way so it can be built later if the team decides to fabricate a real prototype.

## 2. Reference Node Strategy
We will design one reference ESP32-based microgrid node first.
After the reference node is completed, the same architecture can be duplicated for additional nodes if needed.

## 3. Core Hardware Functions
The hardware scope includes:
- DC voltage sensing.
- DC current sensing.
- Optional environmental sensing.
- Power regulation and protection.
- GPIO mapping for firmware integration.
- Schematic capture.
- Simulation support in Wokwi and LTspice.
- Future-ready PCB design in KiCad.

## 4. Optional Functions
The following features are optional at this stage:
- Environmental sensing.
- Load control / actuation.
- Multiple node variants.

These features may be added later if they improve the demo or final system value.

## 5. Hardware-Firmware Boundary
Hardware is responsible for:
- Sensor selection.
- Power design.
- Protection circuitry.
- GPIO allocation.
- Electrical interface definition.
- Schematic design.
- Simulation setup.
- Validation and documentation.

Firmware is responsible for:
- MQTT topics.
- JSON payloads.
- Sampling logic.
- Telemetry handling.
- Backend communication.
- ESP32 application logic.

## 6. Tools
The following tools will be used:
- Wokwi for ESP32 and circuit simulation.
- KiCad for schematic and PCB design.
- LTspice for analog circuit analysis.
- Tinkercad Circuits for basic concept-level circuit checks only.

## 7. Design Principles
The design will follow these principles:
- Use ADC1 only for analog sensing on the classic ESP32.
- Prefer I2C whenever possible for digital sensors.
- Keep the design modular and easy to expand.
- Make the schematic clean and fabrication-ready.
- Document every important decision for the rest of the team.

## 8. Expected Output
The hardware phase will produce:
- A clear hardware architecture.
- A finalized component strategy.
- A GPIO pinout draft.
- A schematic design.
- Simulation files.
- Validation notes.
- A future-ready BOM.
- Hardware documentation for firmware handoff.

## 9. Notes
This document is a design decision record, not the final schematic.
It will be updated as the hardware architecture becomes more detailed.
