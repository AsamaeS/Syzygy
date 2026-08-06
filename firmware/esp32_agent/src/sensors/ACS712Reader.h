#ifndef ACS712_READER_H
#define ACS712_READER_H

#include <Arduino.h>

class ACS712Reader {
private:
    uint8_t voltagePin;
    uint8_t currentPin;

public:
    ACS712Reader(uint8_t vPin = 34, uint8_t cPin = 35) : voltagePin(vPin), currentPin(cPin) {}

    void begin() {
        analogSetAttenuation(ADC_11db);
    }

    float readVoltage() {
        int raw = analogRead(voltagePin);
        return (raw / 4095.0) * 25.0; // Scaled to 0-25V
    }

    float readCurrent() {
        int raw = analogRead(currentPin);
        return (raw / 4095.0) * 5.0; // Scaled to 0-5A
    }

    float readPower() {
        return readVoltage() * readCurrent();
    }
};

#endif
