#ifndef ZWCC_METER_H
#define ZWCC_METER_H
#include "Arduino.h"

#define METER_GET 0x01
#define METER_SUPPORTED_GET 0x03
#define METER_RATE_IMPORT 0x20
#define METER_PROPERTIES_COMBINER(SCALE,SIZE,PRECISION) \
			(((SIZE-1) & 0x03) << 6)| \
			((SCALE & 0x07)) | \
			((PRECISION & 0x07) << 3)

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t * cmd);

#endif