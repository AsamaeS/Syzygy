#!/bin/bash
# flash_esp32.sh — Flash all Syzygy nodes

NODES=("mg-alpha" "mg-beta" "mg-gamma")
PORTS=("/dev/ttyUSB0" "/dev/ttyUSB1" "/dev/ttyUSB2")

echo "Flashing Syzygy firmware to all nodes..."

for i in "${!NODES[@]}"; do
    NODE="${NODES[$i]}"
    PORT="${PORTS[$i]}"
    echo "-> Flashing $NODE on $PORT..."
    sed -i "s/#define NODE_ID.*/#define NODE_ID             \"$NODE\"/" firmware/esp32_agent/include/config.h
    pio run --target upload --upload-port "$PORT"
    echo "OK $NODE flashed"
done

echo "All nodes flashed."
