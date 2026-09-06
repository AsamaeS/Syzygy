#ifndef INA226_READER_H
#define INA226_READER_H

#include <Wire.h>
#include <INA226_WE.h>
#include "config.h"

#define INA226_I2C_ADDR 0x40

class INA226Reader {
private:
    INA226_WE ina226;

public:
    INA226Reader() : ina226(INA226_I2C_ADDR) {}

    void begin() {
        Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
        if (!ina226.init()) {
            Serial.println("Failed to initialize INA226 sensor!");
        }
        ina226.waitUntilConversionCompleted();
    }

    float readVoltage() {
        return ina226.getBusVoltage_V();
    }

    float readCurrent() {
        return ina226.getCurrent_mA() / 1000.0; // Convert mA to Amperes
    }

    float readPower() {
        return ina226.getBusPower();
    }
};

#endif
