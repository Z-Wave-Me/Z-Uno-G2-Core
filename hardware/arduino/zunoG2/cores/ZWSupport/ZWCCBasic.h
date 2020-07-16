#ifndef BASIC_CC_H
#define BASIC_CC_H
#include "Arduino.h"

/* Basic command class commands */
#define BASIC_VERSION                                                                    0x01
#define BASIC_GET                                                                        0x02
#define BASIC_REPORT                                                                     0x03
#define BASIC_SET                                                                        0x01

/************************************************************/
/* Basic Set command class structs */                       
/************************************************************/
typedef struct								ZwBasicSetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									value;/**/
}											ZwBasicSetFrame_t;

int zuno_CCBasicHandler(byte channel, ZUNOCommandPacket_t * cmd);
#endif // BASIC_CC_H