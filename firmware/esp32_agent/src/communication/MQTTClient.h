#include "MQTTClient.h"
#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient client(espClient);

void MQTTClient::connect() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    client.setServer(MQTT_BROKER, MQTT_PORT);
    
    while (!client.connected()) {
        if (client.connect(CLIENT_ID)) {
            client.subscribe(COMMAND_TOPIC);
        } else {
            delay(2000);
        }
    }
}

void MQTTClient::loop() {
    if (!client.connected()) {
        connect();
    }
    client.loop();
}

void MQTTClient::publishTelemetry(const SystemState& state) {
    StaticJsonDocument<256> doc;
    doc["node_id"] = CLIENT_ID;
    doc["voltage"] = state.voltage;
    doc["current"] = state.current;
    doc["power"] = state.power;
    doc["mode"] = state.mode;

    char buffer[256];
    serializeJson(doc, buffer);
    client.publish(TELEMETRY_TOPIC, buffer);
}
