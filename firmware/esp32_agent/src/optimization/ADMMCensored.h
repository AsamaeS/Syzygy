#ifndef ADMM_CENSORED_H
#define ADMM_CENSORED_H

#include <Arduino.h>
#include "../config.h"

class ADMMCensored {
public:
    void init(int numNeighbors);
    float localUpdate(float P_gen, float P_load, float P_bat_max,
                      float SoC, float c_grid, float c_curt,
                      const float neighbor_P_ex[], const float neighbor_u[]);
    bool shouldTransmit(float new_P_ex, float old_P_ex);
    float consensusStep(float my_P_ex, float neighbor_P_ex);
    float dualUpdate(float u, float P_ex, float P_ex_avg);
    bool hasConverged(float P_ex_old, float P_ex_new);
private:
    int n;
    float rho;
    float epsilon;
    float u[3];
    float P_ex[3];
    float P_ex_prev[3];
};

#endif
