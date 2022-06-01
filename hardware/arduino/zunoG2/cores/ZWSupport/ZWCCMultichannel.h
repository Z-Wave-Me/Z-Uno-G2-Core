#ifndef MULTICHANNEL_CC_H
#define MULTICHANNEL_CC_H

#include "Arduino.h"
#include "ZWSupport.h"

/* Multi Channel command class commands */
#define MULTI_CHANNEL_VERSION                                                          0x03
#define MULTI_CHANNEL_CAPABILITY_GET                                                   0x09
#define MULTI_CHANNEL_CAPABILITY_REPORT                                                0x0A
#define MULTI_CHANNEL_CMD_ENCAP                                                        0x0D
#define MULTI_CHANNEL_END_POINT_FIND                                                   0x0B
#define MULTI_CHANNEL_END_POINT_FIND_REPORT                                            0x0C
#define MULTI_CHANNEL_END_POINT_GET                                                    0x07
#define MULTI_CHANNEL_END_POINT_REPORT                                                 0x08
#define MULTI_INSTANCE_CMD_ENCAP                                                       0x06
#define MULTI_INSTANCE_GET                                                             0x04
#define MULTI_INSTANCE_REPORT                                                          0x05
/* Values used for Multi Channel Capability Get command */
#define MULTI_CHANNEL_CAPABILITY_GET_PROPERTIES1_END_POINT_MASK                        0x7F
#define MULTI_CHANNEL_CAPABILITY_GET_PROPERTIES1_RES_BIT_MASK                          0x80
/* Values used for Multi Channel Capability Report command */
#define MULTI_CHANNEL_CAPABILITY_REPORT_PROPERTIES1_END_POINT_MASK                     0x7F
#define MULTI_CHANNEL_CAPABILITY_REPORT_PROPERTIES1_DYNAMIC_BIT_MASK                   0x80
/* Values used for Multi Channel Cmd Encap command */
#define MULTI_CHANNEL_CMD_ENCAP_PROPERTIES1_SOURCE_END_POINT_MASK                      0x7F
#define MULTI_CHANNEL_CMD_ENCAP_PROPERTIES1_RES_BIT_MASK                               0x80
#define MULTI_CHANNEL_CMD_ENCAP_PROPERTIES2_DESTINATION_END_POINT_MASK                 0x7F
#define MULTI_CHANNEL_CMD_ENCAP_PROPERTIES2_BIT_ADDRESS_BIT_MASK                       0x80
/* Values used for Multi Channel End Point Report command */
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES1_RES_MASK                            0x3F
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES1_IDENTICAL_BIT_MASK                  0x40
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES1_DYNAMIC_BIT_MASK                    0x80
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES2_END_POINTS_MASK                     0x7F
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES2_RES_BIT_MASK                        0x80
/* Values used for Multi Instance Cmd Encap command */
#define MULTI_INSTANCE_CMD_ENCAP_PROPERTIES1_INSTANCE_MASK                             0x7F
#define MULTI_INSTANCE_CMD_ENCAP_PROPERTIES1_RES_BIT_MASK                              0x80
/* Values used for Multi Instance Report command */
#define MULTI_INSTANCE_REPORT_PROPERTIES1_INSTANCES_MASK                               0x7F
#define MULTI_INSTANCE_REPORT_PROPERTIES1_RES_BIT_MASK                                 0x80

/************************************************************/
/* Multi Channel Capability Get command class structs */ 
/************************************************************/
typedef struct						ZwMultiChannelCapabilityGetFrame_s
{
	uint8_t							cmdClass;/* The command class */
	uint8_t							cmd;/* The command */
	uint8_t							properties1;/* masked byte */
}									ZwMultiChannelCapabilityGetFrame_t;

/************************************************************/
/* Multi Channel Capability Report command class structs */
/************************************************************/
typedef struct						ZwMultiChannelCapabilityReportFrame_s
{
	uint8_t							cmdClass;/* The command class */
	uint8_t							cmd;/* The command */
	uint8_t							properties1;/* masked byte */
	uint8_t							genericDeviceClass;/**/
	uint8_t							specificDeviceClass;/**/
	uint8_t							commandClass[];/* MSB  LSB */
}									ZwMultiChannelCapabilityReportFrame_t;

/************************************************************/
/* Multi Channel End Point Report command class structs */
/************************************************************/
typedef struct						ZwMultiChannelEndPointReportV2Frame_s
{
	uint8_t							cmdClass;/* The command class */
	uint8_t							cmd;/* The command */
	uint8_t							properties1;/* masked byte */
	uint8_t							properties2;/* masked byte */
}									ZwMultiChannelEndPointReportV2Frame_t;

typedef struct						ZwMultiChannelEndPointReportV4Frame_s
{
	uint8_t							cmdClass;/* The command class */
	uint8_t							cmd;/* The command */
	uint8_t							properties1;/* masked byte */
	uint8_t							properties2;/* masked byte */
	uint8_t							properties3;/* masked byte */
}									ZwMultiChannelEndPointReportV4Frame_t;

typedef union								ZwMultiChannelEndPointReportFrame_u {//For more convenient support, several versions of commands
	ZwMultiChannelEndPointReportV2Frame_t	v2;
	ZwMultiChannelEndPointReportV4Frame_t	v4;
}											ZwMultiChannelEndPointReportFrame_t;

/************************************************************/
/* Multi Channel End Point Find command class structs */ 
/************************************************************/
typedef struct								ZwMultiChannelEndPointFindFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									genericDeviceClass;/**/
	uint8_t									specificDeviceClass;/**/
}											ZwMultiChannelEndPointFindFrame_t;


/************************************************************/
/* Multi Channel End Point Find Report command class structs */
/************************************************************/
typedef struct								ZwMultiChannelEndPointFindReportByte1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									reportsToFollow;/**/
	uint8_t									genericDeviceClass;/**/
	uint8_t									specificDeviceClass;/**/
	uint8_t									variantgroup1;/**/
}											ZwMultiChannelEndPointFindReportByte1Frame_t;

typedef struct								ZwMultiChannelEndPointFindReportByte2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									reportsToFollow;/**/
	uint8_t									genericDeviceClass;/**/
	uint8_t									specificDeviceClass;/**/
	uint8_t									variantgroup1;/**/
	uint8_t									variantgroup2;/**/
}											ZwMultiChannelEndPointFindReportByte2Frame_t;

typedef struct								ZwMultiChannelEndPointFindReportByte3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									reportsToFollow;/**/
	uint8_t									genericDeviceClass;/**/
	uint8_t									specificDeviceClass;/**/
	uint8_t									variantgroup1;/**/
	uint8_t									variantgroup2;/**/
	uint8_t									variantgroup3;/**/
}											ZwMultiChannelEndPointFindReportByte3Frame_t;

typedef struct								ZwMultiChannelEndPointFindReportByte4Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									reportsToFollow;/**/
	uint8_t									genericDeviceClass;/**/
	uint8_t									specificDeviceClass;/**/
	uint8_t									variantgroup1;/**/
	uint8_t									variantgroup2;/**/
	uint8_t									variantgroup3;/**/
	uint8_t									variantgroup4;/**/
}											ZwMultiChannelEndPointFindReportByte4Frame_t;

typedef struct								ZwMultiChannelEndPointFindReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									reportsToFollow;/**/
	uint8_t									genericDeviceClass;/**/
	uint8_t									specificDeviceClass;/**/
	uint8_t									variantgroup[];/**/
}											ZwMultiChannelEndPointFindReportFrame_t;

// typedef union										ZwMultiChannelEndPointFindReportFrame_u {//For more convenient support, several versions of commands
// 	ZwMultiChannelEndPointFindReportByte1Frame_t	byte1;
// 	ZwMultiChannelEndPointFindReportByte2Frame_t	byte2;
// 	ZwMultiChannelEndPointFindReportByte3Frame_t	byte3;
// 	ZwMultiChannelEndPointFindReportByte4Frame_t	byte4;
// }													ZwMultiChannelEndPointFindReportFrame_t;

int zuno_CCMultichannel(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);
#endif // MULTICHANNEL_CC_H