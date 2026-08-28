# Voltage Divider Calculation (Backup - GPIO34)

**Project:** Syzygy  
**Date:** 14 Aug 2026 (confirmed 28 Aug 2026)  
**Status:** Final

## Purpose
GPIO34 is reserved as a backup analog voltage sensing channel.

## Requirements
- Max expected input: 30 V
- ESP32 ADC max: 3.3 V
- Target: ~2.7–3.0 V at maximum input for safety margin

## Selected Values
- R1 (upper) = 100 kΩ
- R2 (lower to GND) = 10 kΩ

## Result
At 30 V input:
\[
V_{out} = 30 \times \frac{10}{110} \approx 2.73\,\text{V}
\]

This value is safely below 3.3 V.

## Notes
- Standard, easy-to-source values
- Low power dissipation
- Currently documented only (INA226 is the primary measurement method)