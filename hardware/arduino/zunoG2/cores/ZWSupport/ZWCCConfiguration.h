#ifndef ZWCC_CONFIGURATION_H
#define ZWCC_CONFIGURATION_H

#include "Arduino.h"

# define ZUNO_CONFIGURATION_CHANNEL_NUMBER		13
# define WITH_CC_CONFIGURATION				13

/* Configuration command class commands */
#define CONFIGURATION_VERSION                                                            0x01
#define CONFIGURATION_GET                                                                0x05
#define CONFIGURATION_REPORT                                                             0x06
#define CONFIGURATION_SET                                                                0x04

int zuno_CCConfigurationHandler(uint8_t channel, ZUNOCommandPacket_t *cmd);
uint16_t zunoLoadCFGParam(uint8_t param);
void zunoSaveCFGParam(uint8_t param, uint16_t value);

#endif // ZWCC_CONFIGURATION_H