#ifndef ZWCC_CONFIGURATION_H
#define ZWCC_CONFIGURATION_H

#include "Arduino.h"

#define MAX_CFGUPDATE_LISTENERS 2
/* Configuration command class commands */
#define CONFIGURATION_VERSION                                                            0x01
#define CONFIGURATION_GET                                                                0x05
#define CONFIGURATION_REPORT                                                             0x06
#define CONFIGURATION_SET                                                                0x04



int zuno_CCConfigurationHandler(ZUNOCommandPacket_t *cmd);

#endif // ZWCC_CONFIGURATION_H