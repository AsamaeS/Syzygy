#ifndef LOCAL_CONTROL_AGENT_H
#define LOCAL_CONTROL_AGENT_H

#include <Arduino.h>
#include "../config.h"
#include "GenerationAgent.h"
#include "StorageAgent.h"
#include "LoadAgent.h"
#include "TradingAgent.h"
#include "../optimization/ADMMCensored.h"
#include "../optimization/ConsensusProtocol.h"
#include "../sensors/INA219Reader.h"
#include "../sensors/ACS712Reader.h"

struct SystemState {
    float P_gen;
    float P_load;
    float P_bat;
    float P_grid;
    float SoC;
    float I_bus;
    float V_bus;
    float T_board;
    String neighbors[3];
    int neighborCount;
};

struct BidMsg {
    String from;
    float quantity;
    float price;
    bool isSell;
};

struct ConsensusMsg {
    String from;
    String to;
    int iteration;
    float P_ex;
    float u;
};

class LocalControlAgent {
public:
    void initSensors();
    SystemState readState();
    void handleBid(const BidMsg& bid);
    void handleConsensus(const ConsensusMsg& msg);
    void runConsensusStep();
    void runADMMCensoredStep();
private:
    GenerationAgent ga;
    StorageAgent sa;
    LoadAgent la;
    TradingAgent ta;
    ADMMCensored admm;
    ConsensusProtocol consensus;
    INA219Reader ina219;
    ACS712Reader acs712;
    SystemState currentState;
    float P_ex_proposed[3];
    float P_ex_agreed[3];
};

#endif
