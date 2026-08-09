# GPIO Mapping — Cooperative Microgrid Energy Orchestrator
**Node:** Reference Node (mg-alpha)
**ESP32 Variant:** ESP32-DevKitC (WROOM-32)
**Last Updated:** 9 August 2026
**Status:** Locked (Hardware ↔ Firmware Interface)

---

## 1. Final Pin Assignment

| ESP32 Pin | Signal Name | Direction | Function | Notes |
|-----------|-------------------|---------------|-----------------------------------|--------------------------------------------|
| GPIO34 | ADC_VOLTAGE_BACKUP| Analog Input | Backup voltage sensing | Input-only. Reserved (primary voltage comes from INA226) |
| GPIO35 | — | — | Free / Reserved | Previously used for ACS712 |
| GPIO21 | I2C_SDA | Bidirectional | I2C Data | Shared bus (INA226) |
| GPIO22 | I2C_SCL | Output | I2C Clock | Shared bus (INA226) |
| GPIO25 | CURTAIL_CTRL | Digital Out | Curtailment Control / Indicator | Default = LOW |
| GPIO26 | EXPORT_CTRL | Digital Out | Export Relay | Default = LOW |
| GPIO27 | IMPORT_CTRL | Digital Out | Import Relay | Default = LOW |
| GPIO2 | STATUS_LED | Digital Out | System Status LED | Driven HIGH on startup (reserved) |
| 3V3 | — | Power | 3.3V Rail | Shared |
| GND | — | Power | Ground | Common ground |

---

## 2. Sensor Decisions

| Sensor | Interface | Address / Pin | Status | Notes |
|---------------------|-----------|--------------------|-------------|--------------------------------------------|
| INA226 | I2C | 0x40 (default) | **Primary** | Measures both Bus Voltage + Current |
| Voltage Divider | Analog | GPIO34 | Backup only | Kept as fallback if needed |
| ACS712 | Analog | GPIO35 | Deprecated | Replaced by INA226 |

---

## 3. Safety & Boot Behavior

- All control outputs (**GPIO25, GPIO26, GPIO27**) must boot in **LOW** state (IDLE / OFF).
- On Backend Heartbeat loss (10 seconds): SafetyMonitor forces **all three outputs back to LOW**.
- GPIO34 and GPIO35 are **input-only** pins (no internal pull-up/pull-down) → ideal for analog.
- Boot strapping pins (**GPIO0, GPIO2, GPIO12, GPIO15**) are **not** used for any relay/control signals.

---

## 4. I2C Configuration

- Bus: I2C0
- SDA: GPIO21
- SCL: GPIO22
- Pull-ups: External 4.7kΩ recommended (most INA226 modules already include them)
- Primary device: INA226 at address `0x40`

---

## 5. Notes for Firmware

- Primary voltage and current readings should come from the **INA226**.
- GPIO34 is kept only as a backup analog voltage channel.
- Control pins are final for the demo.
