#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "agents/LocalControlAgent.h"
#include "communication/MQTTClient.h"
#include "safety/SafetyMonitor.h"

LocalControlAgent lca;
MQTTClient mqtt;
SafetyMonitor safety;

unsigned long lastTelemetry = 0;
unsigned long lastHeartbeat = 0;
unsigned long lastConsensus = 0;
unsigned long lastADMM = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("========================================");
    Serial.println("  SYZYGY — Distributed Microgrid Agent  ");
    Serial.print  ("  Node: "); Serial.println(NODE_ID);
    Serial.println("========================================");

    lca.initSensors();

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500); Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    mqtt.connect();

    mqtt.onBidReceived([](const BidMsg& bid) {
        lca.handleBid(bid);
    });
    mqtt.onConsensusReceived([](const ConsensusMsg& msg) {
        lca.handleConsensus(msg);
    });

    Serial.println("Setup complete. Entering main loop...");
}

void loop() {
    mqtt.loop();

    SystemState state = lca.readState();

    if (!safety.check(state)) {
        safety.triggerOverride();
        mqtt.publishSafetyAlert(state);
        delay(1000);
        return;
    }

    if (millis() - lastTelemetry > TELEMETRY_INTERVAL_MS) {
        mqtt.publishTelemetry(state);
        lastTelemetry = millis();
    }

    if (millis() - lastHeartbeat > HEARTBEAT_INTERVAL_MS) {
        mqtt.publishHeartbeat(state.neighbors, state.neighborCount);
        lastHeartbeat = millis();
    }

    if (millis() - lastConsensus > CONSENSUS_INTERVAL_MS) {
        lca.runConsensusStep();
        lastConsensus = millis();
    }

    if (millis() - lastADMM > ADMM_INTERVAL_MS) {
        lca.runADMMCensoredStep();
        lastADMM = millis();
    }

    delay(10);
}
