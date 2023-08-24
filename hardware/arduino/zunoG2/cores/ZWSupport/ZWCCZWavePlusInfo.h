#ifndef ZWCC_ZWAVE_PLUS_INFO
#define ZWCC_ZWAVE_PLUS_INFO

#include "ZWSupport.h"

/* Zwaveplus Info command class commands */
#define ZWAVEPLUS_INFO_VERSION                                                           0x02
#define ZWAVEPLUS_INFO_GET                                                               0x01
#define ZWAVEPLUS_INFO_REPORT                                                            0x02

/* Values used for Zwaveplus Info Report command */
#define ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_CONTROLLER_CENTRAL_STATIC                        0x00
#define ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_CONTROLLER_SUB_STATIC                            0x01
#define ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_CONTROLLER_PORTABLE                              0x02
#define ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_CONTROLLER_PORTABLE_REPORTING                    0x03
#define ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_PORTABLE                                   0x04
#define ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_ALWAYS_ON                                  0x05
#define ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_SLEEPING_REPORTING                         0x06
#define ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_SLEEPING_LISTENING                         0x07
#define ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_NODE                                   0x00
#define ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_FOR_IP_ROUTER                          0x01
#define ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_FOR_IP_GATEWAY                         0x02
#define ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_FOR_IP_CLIENT_IP_NODE                  0x03
#define ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_FOR_IP_CLIENT_ZWAVE_NODE               0x04

/************************************************************/
/* Zwaveplus Info Report command class structs */        
/************************************************************/
typedef struct								ZwZwavePlusInfoReportV1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									zWaveVersion;/**/
	uint8_t									roleType;/**/
	uint8_t									nodeType;/**/
}											ZwZwavePlusInfoReportV1Frame_t;

typedef struct								ZwZwavePlusInfoReportV2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									zWaveVersion;/**/
	uint8_t									roleType;/**/
	uint8_t									nodeType;/**/
	uint8_t									installerIconType1;/* MSB */
	uint8_t									installerIconType2;/* LSB */
	uint8_t									userIconType1;/* MSB */
	uint8_t									userIconType2;/* LSB */
}											ZwZwavePlusInfoReportV2Frame_t;

typedef union								ZwZwavePlusInfoReportFrame_u {//For more convenient support, several versions of commands
	ZwZwavePlusInfoReportV1Frame_t			v1;
	ZwZwavePlusInfoReportV2Frame_t			v2;
}											ZwZwavePlusInfoReportFrame_t;

typedef struct								ZwZwavePlusInfoIcon_s
{
	uint16_t								installerIconType;
	uint16_t								userIconType;
}											ZwZwavePlusInfoIcon_t;

typedef struct								ZwZwavePlusInfoType_s
{
	uint8_t									genericDeviceClass;/**/
	uint8_t									specificDeviceClass;/**/
}											ZwZwavePlusInfoType_t;

int zuno_CCZWavePlusInfoHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);
void __zuno_CCZWavePlusGetIcon(uint8_t channel, ZwZwavePlusInfoIcon_t *icon);
void __zuno_CCZWavePlusGetType(uint8_t channel, ZwZwavePlusInfoType_t *info_type);

#endif//ZWCC_ZWAVE_PLUS_INFO