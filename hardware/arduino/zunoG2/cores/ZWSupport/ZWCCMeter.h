#ifndef __ZWCC_METER_H__
#define __ZWCC_METER_H__
#include "Arduino.h"

#define METER_GET               0x01
#define METER_SUPPORTED_GET     0x03
#define METER_RESET             0x05
#define METER_RATE_IMPORT       0x20

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t * cmd);

#endif // __ZWCC_METER_H__