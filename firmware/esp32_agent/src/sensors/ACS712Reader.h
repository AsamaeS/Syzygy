#ifndef ACS712_READER_H
#define ACS712_READER_H

#include <Arduino.h>

class ACS712Reader {
public:
    void init(int pin);
    float readCurrent();
private:
    int analogPin;
    float offsetV;
    float sensitivity;
};

#endif
