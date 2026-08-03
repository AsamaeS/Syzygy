#ifndef TRADING_AGENT_H
#define TRADING_AGENT_H

#include <Arduino.h>
#include "../config.h"

class TradingAgent {
public:
    void init(const String& nodeId);
    float proposeExchange(float P_excess, float P_deficit, float neighborSoC);
    float evaluateBid(float quantity, float price, bool isSell);
    void updatePrice(float marketClearingPrice);
private:
    String id;
    float localPrice;
    float lastMCP;
};

#endif
