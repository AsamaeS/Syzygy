#ifndef SAFETY_MONITOR_H
#define SAFETY_MONITOR_H

#include <Arduino.h>
#include "../config.h"
#include "../agents/LocalControlAgent.h"

class SafetyMonitor {
public:
    bool check(const SystemState& state);
    void triggerOverride();
    void releaseOverride();
    bool isOverridden();
    String getLastViolation();
private:
    bool overridden;
    String lastViolation;
    unsigned long overrideStartTime;
};

#endif
