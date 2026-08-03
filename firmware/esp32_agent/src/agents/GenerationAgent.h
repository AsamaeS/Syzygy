#ifndef GENERATION_AGENT_H
#define GENERATION_AGENT_H

#include <Arduino.h>
#include "../config.h"

class GenerationAgent {
public:
    void update(float P_gen_measured);
    float getCurtailment(float P_load, float P_bat_max_charge, float SoC);
    float getForecast();
private:
    float history[3] = {0, 0, 0};
    int idx = 0;
};

#endif
