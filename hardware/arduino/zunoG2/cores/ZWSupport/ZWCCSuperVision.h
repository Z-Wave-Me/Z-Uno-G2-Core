#ifndef ZWCC_SUPER_VISION_H
#define ZWCC_SUPER_VISION_H

#define APPLICATION_STATUS_VERSION                                                             0x01

#include "ZWSupport.h"
#include "ZWCCTimer.h"

typedef struct zuno_cc_supervision_data_s{
	uint32_t last_ms;
	node_id_t _node_id;
	uint8_t _prev_id;
	bool    _unpacked;
	uint8_t  properties1;
} zuno_cc_supervision_data_t;

extern zuno_cc_supervision_data_t __cc_supervision;

/* Supervision command class commands */
#define SUPERVISION_VERSION                                                             0x02
#define SUPERVISION_GET                                                                 0x01
#define SUPERVISION_REPORT                                                              0x02
/* Values used for Supervision Get command */
#define SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK                                     0x3F
#define SUPERVISION_GET_PROPERTIES1_RESERVED_BIT_MASK                                   0x40
#define SUPERVISION_GET_PROPERTIES1_STATUS_UPDATES_BIT_MASK                             0x80
/* Values used for Supervision Report command */
#define SUPERVISION_REPORT_PROPERTIES1_SESSION_ID_MASK                                  0x3F
#define SUPERVISION_REPORT_PROPERTIES1_WAKE_UP_REQUEST_BIT_MASK                         0x40
#define SUPERVISION_REPORT_PROPERTIES1_MORE_STATUS_UPDATES_BIT_MASK                     0x80
#define SUPERVISION_REPORT_NO_SUPPORT                                                   0x00
#define SUPERVISION_REPORT_WORKING                                                      0x01
#define SUPERVISION_REPORT_FAIL                                                         0x02
#define SUPERVISION_REPORT_BUSY                                                         0x03
#define SUPERVISION_REPORT_SUCCESS                                                      0xFF

/************************************************************/
/* Supervision Get command class structs */                 
/************************************************************/
typedef struct								ZwCSuperVisionGetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									encapsulatedCommandLength;/**/
	uint8_t									data[];
}											ZwCSuperVisionGetFrame_t;

/************************************************************/
/* Supervision Report command class structs */              
/************************************************************/
typedef struct								ZwCSuperVisionReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									status;/**/
	uint8_t									duration;/**/
}											ZwCSuperVisionReportFrame_t;

typedef struct						ZwCSuperVisionReportAsyncProcessed_s
{
	node_id_t						dst;
	uint8_t							src_zw_channel;
	uint8_t							dst_zw_channel;
	uint8_t							id;
}									ZwCSuperVisionReportAsyncProcessed_t;

uint8_t zuno_CCSupervisionUnpack(uint8_t process_result, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);

node_id_t zunoGetSupervisionHost();
void zuno_CCSupervisionAsyncProcessedSet(const ZUNOCommandPacket_t *packet, ZwCSuperVisionReportAsyncProcessed_t *super_vision);

int zuno_CCSupervisionApp(int result, ZUNOCommandPacketReport_t *frame_report);

void zuno_CCSupervisionReportSyncProcessed(ZUNOCommandPacketReport_t *frame_report);
int zuno_CCSupervisionReportSyncDefault(ZUNOCommandPacketReport_t *frame_report, uint8_t process_result);
bool zuno_CCSupervisionReportSyncWorking(ZUNOCommandPacketReport_t *frame_report, uint8_t duration_table_8);

void zuno_CCSupervisionReportAsyncProcessed(ZUNOCommandPacketReport_t *frame_report, const ZwCSuperVisionReportAsyncProcessed_t *super_vision);

#endif//ZWCC_SUPER_VISION_H