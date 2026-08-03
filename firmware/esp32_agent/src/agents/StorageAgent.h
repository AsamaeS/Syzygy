#ifndef STORAGE_AGENT_H
#define STORAGE_AGENT_H

#include <Arduino.h>
#include "../config.h"

class StorageAgent {
public:
    void init(float initialSoC);
    float decidePower(float P_gen, float P_load, float gridPrice, float SoC);
    float updateSoC(float P_bat, float dt_hours);
    bool isCritical(float SoC);
private:
    float capacityWh;
    float soc;
};

#endif
