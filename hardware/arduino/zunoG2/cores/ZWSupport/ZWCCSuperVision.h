#ifndef ZWCC_SUPER_VISION_H
#define ZWCC_SUPER_VISION_H

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

uint8_t zuno_CCSupervisionUnpack(ZUNOCommandPacket_t *cmd);
uint8_t zuno_CCSupervisionReport(uint8_t process_result);

#endif//ZWCC_SUPER_VISION_H