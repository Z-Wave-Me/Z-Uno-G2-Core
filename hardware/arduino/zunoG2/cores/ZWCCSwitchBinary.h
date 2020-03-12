#ifndef SWITCHBINARY_CC_H
#define SWITCHBINARY_CC_H
#include "Arduino.h"

/* Switch Binary command class commands */
#define SWITCH_BINARY_VERSION                                                            0x01
#define SWITCH_BINARY_GET                                                                0x02
#define SWITCH_BINARY_REPORT                                                             0x03
#define SWITCH_BINARY_SET                                                                0x01

 
int zuno_CCSwitchBinaryHandler(byte channel, ZUNOCommandPacket_t * cmd);
#endif // SWITCHBINARY_CC_H