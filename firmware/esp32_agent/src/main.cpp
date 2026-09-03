#include <Arduino.h>
#include "config.h"
#include "communication/MQTTClient.h"
#include "sensors/ACS712Reader.h"
#include "agents/LocalControlAgent.h"
#include "safety/SafetyMonitor.h"

MQTTClient mqtt;
ACS712Reader sensors(VOLTAGE_PIN, CURRENT_PIN);
LocalControlAgent lca(EXPORT_RELAY_PIN, IMPORT_RELAY_PIN, CURTAILMENT_LED);
SafetyMonitor safety;

unsigned long lastTelemetry = 0;

void setup() {
    Serial.begin(115200);
    
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, HIGH);

    sensors.begin();
    lca.begin();
    mqtt.connect();
    
    safety.updateHeartbeat();
}

void loop() {
    mqtt.loop();

    // 5-second interval for sensor reading & telemetry publishing
    if (millis() - lastTelemetry >= TELEMETRY_INTERVAL_MS) {
        lastTelemetry = millis();

        SystemState currentState;
        currentState.voltage = sensors.readVoltage();
        currentState.current = sensors.readCurrent();
        currentState.power = sensors.readPower();
        currentState.mode = "NORMAL";

        mqtt.publishTelemetry(currentState);
    }

    // Check 10-second backend safety watchdog
    safety.checkTimeout(lca);
    
    delay(10);
}
