#ifndef __SENSOR_MULTILEVEL_H__
#define __SENSOR_MULTILEVEL_H__
#include "Arduino.h"

#define SENSOR_MULTILEVEL_SUPPORTED_GET             0x01
#define SENSOR_MULTILEVEL_SUPPORTED_GET_SCALE       0x03
#define SENSOR_MULTILEVEL_GET                       0x04
#define SENSOR_MULTILEVEL_REPORT                    0x05

#define SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK     0x18
#define SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT    0x03
#define SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK      0x07

int zuno_CCSensorMultilevelHandler(byte channel, ZUNOCommandPacket_t * cmd);

#endif // __SENSOR_MULTILEVEL_H__
