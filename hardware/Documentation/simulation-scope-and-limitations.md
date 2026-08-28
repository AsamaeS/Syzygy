# Simulation Scope and Limitations

**Project:** Syzygy  
**Last Updated:** 28 Aug 2026

## Scope
This hardware track is **simulation-first**.

What is included:
- KiCad schematic of the reference node
- Wokwi simulation (ESP32 + control LEDs)
- Basic LTspice analysis of the shunt resistor
- GPIO mapping and interface documentation
- Design calculations (shunt + voltage divider)

What is intentionally out of scope for the hackathon:
- Physical PCB fabrication
- Component purchasing and assembly
- Full analog fidelity simulation of the INA226
- Complete power-input stage with real connectors
- Environmental sensors
- Physical actuation hardware (relays/MOSFETs)

## Limitations
- Wokwi does not fully model the INA226; control outputs are demonstrated with LEDs.
- Power input is assumed clean 3.3 V in simulation.
- Protection components are designed at concept level only.
- The design is ready for future real hardware implementation but has not been validated on physical boards.