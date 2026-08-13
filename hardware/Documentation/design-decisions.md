# Hardware Design Decisions

**Project:** Syzygy  
**Subsystem:** Hardware Engineering  
**Status:** Partially Locked  
**Last Updated:** 2026-08-13

## 1. Project Scope

The hardware development follows a simulation-first workflow during the hackathon.

No physical hardware will be purchased or assembled at this stage. The schematic and overall design remain suitable for future fabrication.

## 2. Reference Node

We are designing one reusable ESP32-based microgrid node first (Reference Node).

The same architecture can later be replicated for additional nodes (Solar / Battery / Load).

## 3. Core Functions

The reference node supports:

- DC voltage sensing
- DC current sensing
- ESP32 processing and Wi-Fi communication
- Regulated 3.3 V power
- Basic input and signal protection
- Clear hardware-to-firmware interface

Optional features (not implemented in current version):

- Environmental sensing
- Physical relay/MOSFET drivers (control signals are present)

## 4. Hardware-Firmware Boundary

### Hardware owns
- Architecture and component selection
- Power and protection design
- GPIO allocation
- KiCad schematic
- Wokwi simulation
- Documentation and validation artifacts

### Firmware owns
- Application code
- Sensor drivers
- MQTT and telemetry
- JSON payloads
- Backend communication

Shared: GPIO map, calibration constants, integration testing.

## 5. Tools

- Wokwi — circuit and GPIO simulation
- KiCad — schematic design
- LTspice — analog analysis (planned)
- Git + GitHub — version control

## 6. Locked Design Decisions

### Controller
- ESP32-DevKitC (ESP32-WROOM-32)
- Reason: Wi-Fi, community support, Wokwi compatibility, sufficient peripherals

### Current & Voltage Sensing
- Primary sensor: **INA226** (I2C)
- I2C pins: SDA = GPIO21, SCL = GPIO22
- Default I2C address: 0x40 (A0 & A1 tied to GND)
- Backup analog voltage: GPIO34 (reserved)

### Control Outputs (Required for Demo)
- GPIO25 → CURTAIL_CTRL
- GPIO26 → EXPORT_CTRL
- GPIO27 → IMPORT_CTRL
- All outputs default to LOW (safe state)
- On heartbeat loss → all forced to LOW

### Status
- GPIO2 → STATUS_LED

### Analog Rules
- Only ADC1 pins are used for any analog sensing
- ADC2 is avoided because of Wi-Fi conflict

### Power
- Regulated 3.3 V rail
- Buck converter preferred when input voltage is significantly higher than 3.3 V

### Protection (Baseline)
- Reverse polarity protection
- Local decoupling
- Safe ADC input design
- Over-current consideration

## 7. Design Principles

- Simulation-first
- One solid reference node before duplication
- Prefer I2C digital sensors
- Keep clear hardware/firmware boundary
- Document every major decision
- Design remains fabricable later

## 8. Still Open / Future Work

- Exact shunt resistor value for INA226
- Detailed power input stage (connector + protection components)
- Full protection component selection (TVS, fuse values…)
- Environmental sensor (optional)
- Physical actuation stage (MOSFET/relay drivers)
- Final BOM with part numbers and pricing
- LTspice validation
- PCB layout (if time permits)

## 9. Current Deliverables Status

| Deliverable              | Status          |
|--------------------------|-----------------|
| GPIO / Pinout Map        | Locked          |
| Wokwi basic simulation   | Done            |
| KiCad Schematic v1.0     | Done            |
| Design Decisions Doc     | Updated         |
| Power detailed design    | Pending         |
| BOM                      | Pending         |
| Final Hardware Report    | Pending         |