#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "../config.h"
#include "../agents/LocalControlAgent.h"

class MQTTClient {
public:
    void connect();
    void loop();
    void publishTelemetry(const SystemState& state);
    void publishHeartbeat(const String neighbors[], int count);
    void publishConsensus(const String& neighbor, int iter, float P_ex, float u);
    void publishSafetyAlert(const SystemState& state);
    void onBidReceived(void (*callback)(const BidMsg&));
    void onConsensusReceived(void (*callback)(const ConsensusMsg&));
private:
    WiFiClient wifiClient;
    PubSubClient client;
    void callback(char* topic, byte* payload, unsigned int length);
    String topicPrefix();
};

#endif
