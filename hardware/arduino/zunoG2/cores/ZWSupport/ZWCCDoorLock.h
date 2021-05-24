#ifndef ZWCC_DOOOR_LOCK_H
#define ZWCC_DOOOR_LOCK_H

#include "Arduino.h"

/* Door Lock command class commands */
#define DOOR_LOCK_VERSION                                                                0x01
#define DOOR_LOCK_CONFIGURATION_GET                                                      0x05
#define DOOR_LOCK_CONFIGURATION_REPORT                                                   0x06
#define DOOR_LOCK_CONFIGURATION_SET                                                      0x04
#define DOOR_LOCK_OPERATION_GET                                                          0x02
#define DOOR_LOCK_OPERATION_REPORT                                                       0x03
#define DOOR_LOCK_OPERATION_SET                                                          0x01
#define DOOR_LOCK_CAPABILITIES_GET                                                       0x07
#define DOOR_LOCK_CAPABILITIES_REPORT                                                    0x08

/************************************************************/
/* Door Lock Operation Set command class structs */      
/************************************************************/
typedef struct							ZwDoorLockOperationSet_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								doorLockMode;/**/
}										ZwDoorLockOperationSet_t;//_ZW_DOOR_LOCK_OPERATION_SET_V4_FRAME_

int zuno_CCDoorLockHandler(uint8_t channel, ZUNOCommandPacket_t *cmd);
int zuno_CCDoorLockReport(uint8_t channel, bool reply);

#endif // ZWCC_DOOOR_LOCK_H