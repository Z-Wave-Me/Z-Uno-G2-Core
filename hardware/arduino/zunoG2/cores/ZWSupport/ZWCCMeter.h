#ifndef __ZWCC_METER_H__
#define __ZWCC_METER_H__
#include "Arduino.h"

#define METER_GET               0x01
#define METER_REPORT            0x02
#define METER_SUPPORTED_GET     0x03
#define METER_RESET             0x05
#define METER_RATE_IMPORT       0x20

#define GET_SCALE(params) ((params & 0x03) << 3)
#define GET_SIZE(params) ((params >> 6) + 1)
#define GET_PRECISION(params) ((params << 2) & 0xE0)

#define COMBINE_PARAMS(params) (GET_SCALE(params) | GET_SIZE(params) | GET_PRECISION(params))

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t * cmd);
int zuno_CCMeterReport(byte channel);

#endif // __ZWCC_METER_H__