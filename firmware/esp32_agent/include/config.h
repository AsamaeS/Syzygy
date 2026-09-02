#ifndef CONFIG_H
#define CONFIG_H

// ===================================================
// SYZYGY – Node Configuration
// ===================================================

#define NODE_ID                 "ESP32_Microgrid_Node1_Hoor_99812"
#define NODE_TYPE               RESIDENTIAL

#define WIFI_SSID               "Wokwi-GUEST"
#define WIFI_PASS               ""

#define MQTT_BROKER             "broker.hivemq.com"
#define MQTT_PORT               1883
#define CLIENT_ID               "ESP32_Microgrid_Node1_Hoor_99812"

#define TELEMETRY_TOPIC         "syzygy/mg-alpha/telemetry/power"
#define COMMAND_TOPIC           "microgrid/node1/command"

#define TELEMETRY_INTERVAL_MS   5000
#define HEARTBEAT_INTERVAL_MS   5000
#define HEARTBEAT_TIMEOUT_MS    15000
#define CONSENSUS_INTERVAL_MS   30000
#define ADMM_INTERVAL_MS        300000

#define SOC_MIN                 20.0
#define SOC_MAX                 95.0

// GPIO Mapping
#define STATUS_LED_PIN          2
#define EXPORT_RELAY_PIN        26
#define IMPORT_RELAY_PIN        27
#define CURTAILMENT_LED         25
#define VOLTAGE_PIN             34
#define CURRENT_PIN             35

#endif
