#ifndef LOAD_AGENT_H
#define LOAD_AGENT_H

#include <Arduino.h>
#include "../config.h"

class LoadAgent {
public:
    void setNonCriticalLoad(float P_noncritical);
    float decideShedding(float gridPrice, float P_deficit);
    bool isShedding();
private:
    float P_noncrit;
    bool shedding;
};

#endif
