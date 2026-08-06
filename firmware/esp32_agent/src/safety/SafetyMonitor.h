#ifndef SAFETY_MONITOR_H
#define SAFETY_MONITOR_H

#include <Arduino.h>
#include "../agents/LocalControlAgent.h"

class SafetyMonitor {
private:
    unsigned long lastHeartbeat;
    const unsigned long timeoutMs = 10000; // 10-second watchdog

public:
    SafetyMonitor() : lastHeartbeat(0) {}

    void updateHeartbeat() {
        lastHeartbeat = millis();
    }

    void checkTimeout(LocalControlAgent& lca) {
        if (lastHeartbeat > 0 && (millis() - lastHeartbeat > timeoutMs)) {
            lca.setIdle(); // Force hardware into safe state if backend disconnects
        }
    }
};

#endif
