#ifndef ZWCC_CONFIGURATION_H
#define ZWCC_CONFIGURATION_H

#include "Arduino.h"

#define MAX_CFGUPDATE_LISTENERS 2
/* Configuration command class commands */
#define CONFIGURATION_VERSION                                                            0x01
#define CONFIGURATION_BULK_REPORT                                                        0x09
#define CONFIGURATION_BULK_SET                                                           0x07
#define CONFIGURATION_GET                                                                0x05
#define CONFIGURATION_REPORT                                                             0x06
#define CONFIGURATION_SET                                                                0x04
#define CONFIGURATION_NAME_GET                                                           0x0A
#define CONFIGURATION_NAME_REPORT                                                        0x0B
#define CONFIGURATION_INFO_GET                                                           0x0C
#define CONFIGURATION_INFO_REPORT                                                        0x0D
#define CONFIGURATION_PROPERTIES_GET                                                     0x0E
#define CONFIGURATION_PROPERTIES_REPORT                                                  0x0F
#define CONFIGURATION_DEFAULT_RESET                                                      0x01


int zuno_CCConfigurationHandler(ZUNOCommandPacket_t *cmd);

#endif // ZWCC_CONFIGURATION_H