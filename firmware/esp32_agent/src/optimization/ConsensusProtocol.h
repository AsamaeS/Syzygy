#ifndef CONSENSUS_PROTOCOL_H
#define CONSENSUS_PROTOCOL_H

#include <Arduino.h>
#include "../config.h"

class ConsensusProtocol {
public:
    void init(int numNeighbors);
    float step(float mySoC, const float neighborSoCs[]);
    bool isConverged(float oldSoC, float newSoC);
private:
    int n;
    float epsilon;
};

#endif
