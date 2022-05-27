#ifndef VERSION_CC_H
#define VERSION_CC_H

#include "ZWSupport.h"

/* Version command class commands */
#define VERSION_VERSION                                                                  0x03
#define VERSION_COMMAND_CLASS_GET                                                        0x13
#define VERSION_COMMAND_CLASS_REPORT                                                     0x14
#define VERSION_GET                                                                      0x11
#define VERSION_REPORT                                                                   0x12
#define VERSION_CAPABILITIES_GET                                                         0x15
#define VERSION_CAPABILITIES_REPORT                                                      0x16
#define VERSION_ZWAVE_SOFTWARE_GET                                                       0x17
#define VERSION_ZWAVE_SOFTWARE_REPORT                                                    0x18
/* Values used for Version Capabilities Report command */
#define VERSION_CAPABILITIES_REPORT_PROPERTIES1_VERSION_BIT_MASK                         0x01
#define VERSION_CAPABILITIES_REPORT_PROPERTIES1_COMMAND_CLASS_BIT_MASK                   0x02
#define VERSION_CAPABILITIES_REPORT_PROPERTIES1_Z_WAVE_SOFTWARE_BIT_MASK                 0x04
#define VERSION_CAPABILITIES_REPORT_PROPERTIES1_RESERVED1_MASK                           0xF8
#define VERSION_CAPABILITIES_REPORT_PROPERTIES1_RESERVED1_SHIFT                          0x03


/************************************************************/
/* Version Command Class Get V3 command class structs */    
/************************************************************/
typedef struct _ZW_VERSION_COMMAND_CLASS_GET_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   requestedCommandClass;        /**/
} ZW_VERSION_COMMAND_CLASS_GET_V3_FRAME;

/************************************************************/
/* Version Command Class Report V3 command class structs */ 
/************************************************************/
typedef struct _ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   requestedCommandClass;        /**/
    uint8_t   commandClassVersion;          /**/
} ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME;

int zuno_CCVersionHandler(ZUNOCommandPacket_t * cmd, ZUNOCommandPacketReport_t *frame_report);
#endif // VERSION_CC_H