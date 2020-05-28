#ifndef ZWCC_SWITCH_COLOR_H
#define ZWCC_SWITCH_COLOR_H

#include "Arduino.h"

/* Switch Color command class commands */
#define SWITCH_COLOR_VERSION                                                             0x01
#define SWITCH_COLOR_SUPPORTED_GET                                                       0x01
#define SWITCH_COLOR_SUPPORTED_REPORT                                                    0x02
#define SWITCH_COLOR_GET                                                                 0x03
#define SWITCH_COLOR_REPORT                                                              0x04
#define SWITCH_COLOR_SET                                                                 0x05
#define SWITCH_COLOR_START_LEVEL_CHANGE                                                  0x06
#define SWITCH_COLOR_STOP_LEVEL_CHANGE                                                   0x07

int zuno_CCSwitchColorHandler(uint8_t channel, ZUNOCommandPacket_t *cmd);
int zuno_CCSwitchColorReport(uint8_t channel, ZUNOCommandPacket_t *cmd);
void zuno_CCSwitchColorTimer(uint32_t ticks);

#endif // ZWCC_SWITCH_COLOR_H