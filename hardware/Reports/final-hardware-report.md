# Final Hardware Report  
**Syzygy 
**Role:** Hardware & Embedded Hardware Engineering  
**Approach:** Simulation-First  
**Date:** 28 August 2026

## 1. Summary
A complete reference microgrid node was designed around an ESP32.  
The node measures voltage and current (via INA226), exposes three control outputs (Export / Import / Curtailment), and communicates over Wi-Fi/MQTT.  
All work was performed in simulation (KiCad + Wokwi + LTspice) with clear documentation for future physical implementation.

## 2. Key Achievements
- Locked and documented GPIO map
- Selected and integrated INA226 as primary sensor
- Produced working KiCad schematic (v1.2+)
- Created Wokwi simulation demonstrating control outputs
- Performed shunt resistor calculation and LTspice verification
- Produced supporting documentation (decisions, calculations, BOM, scope)

## 3. System Overview
Each node:
- Reads local electrical state
- Publishes telemetry via MQTT
- Receives sharing / curtailment commands
- Applies local control actions

## 4. Design Decisions (Highlights)
- ESP32-WROOM-32
- INA226 on I2C (GPIO21/22)
- Control pins: 25, 26, 27 (all default LOW)
- Shunt = 0.01 Ω
- Simulation-first workflow

## 5. Deliverables Produced
- `gpio-map.md` + `pinout.json`
- KiCad schematic source + PDF exports
- Wokwi project
- LTspice shunt analysis
- Design decisions, calculations, BOM, glossary, scope document

## 6. Limitations & Future Work
- No physical prototype was built
- Full input protection and power stage remain conceptual
- PCB layout not started (not required by hackathon rules)
- Ready for future hardware realization

## 7. Conclusion
The hardware foundation is solid, well-documented, and ready for firmware integration and demonstration.  
The simulation-first approach allowed complete interface definition and design validation within the available time.