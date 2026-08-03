# Limitation Matrix

| Limitation | Count | Papers | Syzygy Solution |
|------------|-------|--------|-----------------|
| Simulation only | 6/6 | All except 5,6 | **Prototype on ESP32** |
| Centralized controller | 2/6 | 2 (EMMC) | **Peer-to-peer MQTT** |
| No hardware validation | 4/6 | 1,2,3,4 | **Physical ESP32 nodes** |
| No embedded implementation | 4/6 | 1,2,3,4 | **Firmware on ESP32** |
| No communication constraints | 5/6 | 1,2,3,4,5 | **Censored ADMM + heartbeat** |
| No battery degradation | 6/6 | All | **SoC-aware scheduling** |
| Static optimization | 3/6 | 2,5,6 | **Rolling ADMM + consensus** |
| Unrealistic assumptions | 5/6 | 1,2,3,4,5 | **Physical sensors + safety monitor** |
| No renewable uncertainty | 4/6 | 2,5,6 | **Stochastic profiles in experiments** |
