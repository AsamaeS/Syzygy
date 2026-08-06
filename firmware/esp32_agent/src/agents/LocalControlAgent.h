#ifndef LOCAL_CONTROL_AGENT_H
#define LOCAL_CONTROL_AGENT_H

#include <Arduino.h>
#include "../config.h"

class LocalControlAgent {
private:
    uint8_t exportPin;
    uint8_t importPin;
    uint8_t curtailmentPin;

public:
    LocalControlAgent(uint8_t expPin = EXPORT_RELAY_PIN, uint8_t impPin = IMPORT_RELAY_PIN, uint8_t curtPin = CURTAILMENT_LED)
        : exportPin(expPin), importPin(impPin), curtailmentPin(curtPin) {}

    void begin() {
        pinMode(exportPin, OUTPUT);
        pinMode(importPin, OUTPUT);
        pinMode(curtailmentPin, OUTPUT);
        setIdle();
    }

    void executeAction(const String& action, bool curtailmentMode = false) {
        if (action == "EXPORT") {
            digitalWrite(exportPin, HIGH);
            digitalWrite(importPin, LOW);
        } else if (action == "IMPORT") {
            digitalWrite(exportPin, LOW);
            digitalWrite(importPin, HIGH);
        } else {
            setIdle();
        }

        digitalWrite(curtailmentPin, curtailmentMode ? HIGH : LOW);
    }

    void setIdle() {
        digitalWrite(exportPin, LOW);
        digitalWrite(importPin, LOW);
        digitalWrite(curtailmentPin, LOW);
    }
};

#endif
