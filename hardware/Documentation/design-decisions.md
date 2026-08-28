# Hardware Design Decisions

**Project:** Syzygy 
**Subsystem:** Hardware Engineering  
**Status:** Final for Hackathon  
**Last Updated:** 28 Aug 2026

## 1. Project Scope

Hardware development followed a **simulation-first** approach during the hackathon.  
No physical components were purchased or assembled. The design remains suitable for future fabrication.

## 2. Reference Node

One reusable ESP32-based microgrid node was designed as the reference.  
The same architecture can be replicated for additional nodes (Solar / Battery / Load).

## 3. Core Functions

- DC voltage sensing
- DC current sensing
- ESP32 processing + Wi-Fi
- Regulated 3.3 V rail
- Basic input/signal protection principles
- Clear Hardware ↔ Firmware interface

Optional (not implemented in this version):
- Environmental sensing
- Physical relay/MOSFET drivers (control signals are present)

## 4. Hardware–Firmware Boundary

**Hardware owns:** Architecture, component selection, power & protection design, GPIO allocation, schematic, Wokwi, documentation.

**Firmware owns:** Application code, sensor drivers, MQTT, JSON telemetry, backend communication.

**Shared:** GPIO map, calibration, integration testing.

## 5. Locked Decisions

| Item                    | Decision                                      |
|-------------------------|-----------------------------------------------|
| MCU                     | ESP32-WROOM-32 (DevKitC)                      |
| Primary Sensor          | INA226 (I2C)                                  |
| I2C Pins                | SDA = GPIO21, SCL = GPIO22                    |
| I2C Address             | 0x40 (A0 & A1 to GND)                         |
| Control Outputs         | GPIO25 = CURTAIL, GPIO26 = EXPORT, GPIO27 = IMPORT |
| Status LED              | GPIO2                                         |
| Backup Voltage ADC      | GPIO34 (reserved)                             |
| Shunt Resistor          | 0.01 Ω                                        |
| Default / Safe State    | All control outputs = LOW                     |

## 6. Design Principles

- Simulation-first
- One solid reference node before duplication
- Prefer I2C digital sensors
- ADC1 only for analog
- Clear documentation of every major decision
- Design remains fabricable later