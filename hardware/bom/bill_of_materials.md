# Bill of Materials — Reference Node (v0.1)

**Project:** Syzygy  
**Date:** 13 Aug 2026  
**Status:** Initial (Simulation)

| Ref     | Component              | Value / Part          | Qty | Notes                          | Status      |
|---------|------------------------|-----------------------|-----|--------------------------------|-------------|
| U1      | ESP32 Module           | ESP32-WROOM-32        | 1   | DevKitC preferred              | Selected    |
| U2      | Current/Voltage Sensor | INA226                | 1   | I2C, Address 0x40              | Selected    |
| R5      | Shunt Resistor         | 0.01 Ω                | 1   | For ~5A max                    | Selected    |
| R1–R4   | LED Resistors          | 220Ω – 470Ω           | 4   | For status & control LEDs      | Selected    |
| D1–D4   | LEDs                   | Any color             | 4   | Status, Curtail, Export, Import| Selected    |
| —       | Decoupling Caps        | 100nF + 10µF          | 2–4 | Near ESP32 & INA226 (to add)   | Planned     |
| —       | Power Input            | TBD                   | 1   | Buck or regulated 3.3V         | Open        |

## Notes
- This BOM is for the simulation / schematic stage only.
- No physical purchasing yet.
- Will be updated when protection and power stage are finalized.