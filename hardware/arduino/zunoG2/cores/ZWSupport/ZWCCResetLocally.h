#ifndef CC_RESET_LOCALLY
#define CC_RESET_LOCALLY
#include "Arduino.h"
#define DEVICE_RESET_LOCALLY_VERSION                                                     0x01
#define DEVICE_RESET_LOCALLY_NOTIFICATION                                                0x01
#ifndef RST_LOCALLY_TIMEOUT
    #define RST_LOCALLY_TIMEOUT                                                          3000
#endif // RST_LOCALLY_TIMEOUT
#ifndef RST_LOCALLY_QUEUE_CHANNEL
    #define RST_LOCALLY_QUEUE_CHANNEL                                                    QUEUE_CHANNEL_CONTROL
#endif // RST_LOCALLY_QUEUE_CHANNEL
void zunoResetLocally();
void RSTLocallyTick();
#endif // CC_RESET_LOCALLY
