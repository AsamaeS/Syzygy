# Voltage Divider Calculation (Backup on GPIO34)

**Project:** Syzygy - Reference Node  
**Date:** 14 Aug 2026  
**Status:** Calculated

## Purpose

GPIO34 is reserved as a **backup analog voltage sensing** channel in case we need a simple resistive divider alongside (or instead of) the INA226 bus voltage reading.

## Design Requirements

- Maximum expected input voltage: **30 V**
- ESP32 ADC maximum safe input: **3.3 V**
- Target: Keep maximum voltage at the ADC pin around **2.7 – 3.0 V** for safety margin

## Formula

\[
V_{out} = V_{in} \times \frac{R2}{R1 + R2}
\]

Where:
- R1 = upper resistor (from voltage source)
- R2 = lower resistor (to GND)
- Vout goes to GPIO34

## Selected Values

| Resistor | Value  | Role                  |
|----------|--------|-----------------------|
| R1       | 100 kΩ | Upper resistor        |
| R2       | 10 kΩ  | Lower resistor (GND)  |

## Result

At 30 V input:

\[
V_{out} = 30 \times \frac{10k}{100k + 10k} = 30 \times 0.0909 ≈ 2.73 V
\]

This value is safely below 3.3 V.

## Notes

- These values are standard and easy to source.
- Power dissipation in the divider is very low (acceptable for this application).
- This divider is currently documented only. It is not yet added to the schematic (INA226 remains the primary measurement method).