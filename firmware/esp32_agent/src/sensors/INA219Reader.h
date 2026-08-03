#ifndef INA219_READER_H
#define INA219_READER_H

#include <Arduino.h>
#include <Wire.h>

class INA219Reader {
public:
    bool init();
    float readCurrent();
    float readVoltage();
    float readPower();
private:
    bool initialized;
};

#endif
