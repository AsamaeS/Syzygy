# Bill of Materials — Syzygy Microgrid Node

## Per-Node Components (x3 for 3-node prototype)

| Item | Qty | Reference | Purpose | Est. Cost |
|------|-----|-----------|---------|-----------|
| ESP32-WROOM-32D | 1 | U1 | Main controller | $4.00 |
| INA219 I2C Module | 1 | U2 | Current/Voltage sensing | $2.50 |
| ACS712-05B | 1 | U3 | AC current sensing (optional) | $3.00 |
| Relay Module 5V | 2 | K1, K2 | Exchange & load control | $3.00 |
| LiFePO4 Battery 12V 7Ah | 1 | BT1 | Energy storage | $25.00 |
| Solar Panel 20W 12V | 1 | PV1 | Renewable source | $15.00 |
| DC-DC Buck Converter | 1 | PS1 | 12V -> 5V for ESP32 | $2.00 |
| Breadboard + Jumper Wires | 1 | — | Prototyping | $3.00 |
| **Per-node total** | | | | **~$57.50** |

## Shared Infrastructure

| Item | Qty | Purpose | Est. Cost |
|------|-----|---------|-----------|
| Raspberry Pi 4 (4GB) | 1 | MQTT Broker + Backend | $55.00 |
| WiFi Router | 1 | Local network | $30.00 |
| **Shared total** | | | **~$85.00** |

## Grand Total (3 nodes)
~$257.50
