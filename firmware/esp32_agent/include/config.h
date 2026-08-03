#ifndef CONFIG_H
#define CONFIG_H

// ============================================================
// SYZYGY — Node Configuration
// ============================================================

#define NODE_ID             "mg-alpha"
#define NODE_TYPE           RESIDENTIAL

#define WIFI_SSID           "SyzygyMesh"
#define WIFI_PASS           "volt2026"

#define MQTT_BROKER         "192.168.1.100"
#define MQTT_PORT           1883

#define TELEMETRY_INTERVAL_MS   5000
#define HEARTBEAT_INTERVAL_MS   5000
#define HEARTBEAT_TIMEOUT_MS    15000
#define CONSENSUS_INTERVAL_MS   30000
#define ADMM_INTERVAL_MS        300000

#define SOC_MIN                 20.0
#define SOC_MAX                 95.0
#define I_BUS_MAX               10.0
#define V_BUS_MIN               10.5
#define V_BUS_MAX               14.5
#define T_BOARD_MAX             70.0

#define BATTERY_CAPACITY_AH     7.0
#define BATTERY_VOLTAGE_NOM     12.8
#define P_BAT_MAX_CHARGE        50.0
#define P_BAT_MAX_DISCHARGE     80.0
#define ETA_CHARGE              0.92
#define ETA_DISCHARGE           0.92

#define ADMM_RHO                0.5
#define ADMM_EPSILON_CENSOR     1.0
#define ADMM_MAX_ITERATIONS     10
#define ADMM_TOLERANCE          0.5

#define CONSENSUS_EPSILON       0.1
#define CONSENSUS_MAX_ITER      10

#define C_GRID_PEAK             0.20
#define C_GRID_OFFPEAK          0.08
#define C_CURTAILMENT           0.15
#define C_BATTERY_DEG           0.02

#define PIN_RELAY_EXCHANGE      25
#define PIN_RELAY_LOAD_SHED     26
#define PIN_I2C_SDA             21
#define PIN_I2C_SCL             22
#define PIN_ACS712              34

enum NodeType { RESIDENTIAL, COMMERCIAL, COMMUNITY };

#endif
