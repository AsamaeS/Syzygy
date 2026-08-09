# Hardware Design Decisions

**Project:** Syzygy
**Subsystem:** Hardware Engineering
**Status:** Draft
**Last Updated:** 2026-08-06

## 1. Project Scope

The hardware development will follow a simulation-first workflow during the hackathon.

No physical hardware will be purchased or assembled during this phase. However, the schematic and PCB design will remain suitable for future fabrication.

## 2. Reference Node

We will design one reusable ESP32-based microgrid node first.

The same architecture can later be replicated for two or three nodes:

- Solar monitoring node.
- Battery monitoring node.
- Optional load monitoring node.

## 3. Core Functions

The reference node will support:

- DC voltage sensing.
- DC current sensing.
- ESP32 processing and Wi-Fi communication.
- Regulated power supply.
- Input and signal protection.
- Hardware-to-firmware interface definition.

The following features are optional:

- Environmental sensing.
- Load control.
- Relay or MOSFET actuation.

## 4. Hardware-Firmware Boundary

### Hardware owns

- Hardware architecture.
- Sensor and component selection.
- Power and protection design.
- GPIO and peripheral allocation.
- KiCad schematic and PCB design.
- Wokwi circuit wiring.
- LTspice analog analysis.
- Hardware validation and documentation.

### Firmware owns

- ESP32 application code.
- Sensor drivers and sampling logic.
- MQTT communication.
- JSON payloads.
- Telemetry handling.
- Backend communication.

GPIO assignments, calibration, sampling constraints, and integration testing are shared between Hardware and Firmware.

## 5. Tools

- **Wokwi:** ESP32 and circuit simulation.
- **KiCad:** Schematic and PCB design.
- **LTspice:** Analog and power-circuit analysis.
- **Tinkercad Circuits:** Basic electronics learning and quick experiments.

## 6. Main Design Decisions

### Controller

The reference node will use an ESP32-DevKitC based on the ESP32-WROOM-32.

Reason:
- Suitable for Wi-Fi communication.
- Well documented.
- Compatible with the project architecture.
- Suitable for Wokwi simulation.
- Provides enough GPIO and peripheral flexibility.

### Analog Sensing

Analog sensors will use ADC1 pins only on the classic ESP32.

ADC2 will not be used for required analog measurements because it may conflict with Wi-Fi operation.

### Voltage Sensing

The baseline voltage-sensing method will be a resistive divider.

It will be designed for the project voltage range of approximately 0–30 V DC while keeping the ESP32 ADC input within a safe range.

### Current Sensing

The preferred current-sensing method is an INA219 or INA226 I2C sensor.

ACS712 or a similar analog Hall-effect sensor will remain as a fallback option.

### Power Supply

The node will use a regulated 3.3 V rail.

A buck converter will be preferred when the input voltage is significantly higher than 3.3 V. An LDO may be considered only when the input voltage is already close to the required output voltage.

### Protection

The design will include:

- Reverse-polarity protection.
- Overcurrent protection.
- Input transient protection.
- Local decoupling capacitors.
- Safe voltage-divider and ADC-input design.

## 7. Design Principles

- Keep the design simple and modular.
- Prefer I2C for digital sensors.
- Use ADC1 only for analog sensing.
- Keep sufficient electrical safety margin.
- Design one reliable reference node before duplicating it.
- Document the reason behind every major decision.
- Keep the design ready for future PCB fabrication.

## 8. Open Decisions

The following details will be finalized in later milestones:

- Exact current-sensor variant.
- Exact voltage-divider resistor values.
- Exact ADC1 GPIO assignments.
- I2C SDA and SCL pins.
- Buck-converter implementation.
- Final protection components.
- Environmental sensor inclusion.
- Actuation and control GPIOs.
- Final number of demo nodes.

These decisions depend on datasheet review, Wokwi compatibility, LTspice analysis, and firmware-team feedback.

## 9. Expected Hardware Deliverables

- Hardware architecture diagram.
- Component selection report.
- GPIO and pinout map.
- KiCad schematic.
- PCB design files.
- Wokwi simulation.
- LTspice simulations.
- BOM.
- Validation plan.
- Hardware-firmware interface documentation.
- Final hardware report.