#ifndef ZWCC_ENTRY_CONTROL_H
#define ZWCC_ENTRY_CONTROL_H

/* Entry Control command class commands */
#define ENTRY_CONTROL_VERSION                                                            0x01
#define ENTRY_CONTROL_NOTIFICATION                                                       0x01
#define ENTRY_CONTROL_KEY_SUPPORTED_GET                                                  0x02
#define ENTRY_CONTROL_KEY_SUPPORTED_REPORT                                               0x03
#define ENTRY_CONTROL_EVENT_SUPPORTED_GET                                                0x04
#define ENTRY_CONTROL_EVENT_SUPPORTED_REPORT                                             0x05
#define ENTRY_CONTROL_CONFIGURATION_SET                                                  0x06
#define ENTRY_CONTROL_CONFIGURATION_GET                                                  0x07
#define ENTRY_CONTROL_CONFIGURATION_REPORT                                               0x08
/* Values used for Entry Control Notification command */
#define ENTRY_CONTROL_NOTIFICATION_PROPERTIES1_DATA_TYPE_MASK                            0x03
#define ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_NA                                          0x00
#define ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_RAW                                         0x01
#define ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_ASCII                                       0x02
#define ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_MD5                                         0x03
#define ENTRY_CONTROL_NOTIFICATION_PROPERTIES1_RESERVED_MASK                             0xFC
#define ENTRY_CONTROL_NOTIFICATION_PROPERTIES1_RESERVED_SHIFT                            0x02
#define ENTRY_CONTROL_NOTIFICATION_CACHING                                               0x00
#define ENTRY_CONTROL_NOTIFICATION_CACHED_KEYS                                           0x01
#define ENTRY_CONTROL_NOTIFICATION_ENTER                                                 0x02
#define ENTRY_CONTROL_NOTIFICATION_DISARM_ALL                                            0x03
#define ENTRY_CONTROL_NOTIFICATION_ARM_ALL                                               0x04
#define ENTRY_CONTROL_NOTIFICATION_ARM_AWAY                                              0x05
#define ENTRY_CONTROL_NOTIFICATION_ARM_HOME                                              0x06
#define ENTRY_CONTROL_NOTIFICATION_EXIT_DELAY                                            0x07
#define ENTRY_CONTROL_NOTIFICATION_ARM_1                                                 0x08
#define ENTRY_CONTROL_NOTIFICATION_ARM_2                                                 0x09
#define ENTRY_CONTROL_NOTIFICATION_ARM_3                                                 0x0A
#define ENTRY_CONTROL_NOTIFICATION_ARM_4                                                 0x0B
#define ENTRY_CONTROL_NOTIFICATION_ARM_5                                                 0x0C
#define ENTRY_CONTROL_NOTIFICATION_ARM_6                                                 0x0D
#define ENTRY_CONTROL_NOTIFICATION_RFID                                                  0x0E
#define ENTRY_CONTROL_NOTIFICATION_BELL                                                  0x0F
#define ENTRY_CONTROL_NOTIFICATION_FIRE                                                  0x10
#define ENTRY_CONTROL_NOTIFICATION_POLICE                                                0x11
#define ENTRY_CONTROL_NOTIFICATION_ALERT_PANIC                                           0x12
#define ENTRY_CONTROL_NOTIFICATION_ALERT_MEDICAL                                         0x13
#define ENTRY_CONTROL_NOTIFICATION_GATE_OPEN                                             0x14
#define ENTRY_CONTROL_NOTIFICATION_GATE_CLOSE                                            0x15
#define ENTRY_CONTROL_NOTIFICATION_LOCK                                                  0x16
#define ENTRY_CONTROL_NOTIFICATION_UNLOCK                                                0x17
#define ENTRY_CONTROL_NOTIFICATION_TEST                                                  0x18
#define ENTRY_CONTROL_NOTIFICATION_CANCEL                                                0x19
/* Values used for Entry Control Event Supported Report command */
#define ENTRY_CONTROL_EVENT_SUPPORTED_REPORT_PROPERTIES1_DATA_TYPE_SUPPORTED_BIT_MASK_LENGTH_MASK 0x03
#define ENTRY_CONTROL_EVENT_SUPPORTED_REPORT_PROPERTIES1_RESERVED1_MASK                  0xFC
#define ENTRY_CONTROL_EVENT_SUPPORTED_REPORT_PROPERTIES1_RESERVED1_SHIFT                 0x02
#define ENTRY_CONTROL_EVENT_SUPPORTED_REPORT_PROPERTIES2_EVENT_SUPPORTED_BIT_MASK_LENGTH_MASK 0x1F
#define ENTRY_CONTROL_EVENT_SUPPORTED_REPORT_PROPERTIES2_RESERVED2_MASK                  0xE0
#define ENTRY_CONTROL_EVENT_SUPPORTED_REPORT_PROPERTIES2_RESERVED2_SHIFT                 0x05

typedef struct								ZwEntryControlNotificationFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									sequenceNumber;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									eventType;/**/
	uint8_t									eventDataLength;/**/
	uint8_t									eventData[];
}											ZwEntryControlNotificationFrame_t;

/************************************************************/
/* Entry Control Configuration Set command class structs */ 
/************************************************************/
typedef struct _ZW_ENTRY_CONTROL_CONFIGURATION_SET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   keyCacheSize;                 /**/
    uint8_t   keyCacheTimeout;              /**/
} ZW_ENTRY_CONTROL_CONFIGURATION_SET_FRAME;

/************************************************************/
/* Entry Control Configuration Report command class structs */
/************************************************************/
typedef struct _ZW_ENTRY_CONTROL_CONFIGURATION_REPORT_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   keyCacheSize;                 /**/
    uint8_t   keyCacheTimeout;              /**/
} ZW_ENTRY_CONTROL_CONFIGURATION_REPORT_FRAME;

typedef struct										ZwEntryControlKeySupportedReportFrameStart_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											properties1;/* masked byte */
	uint8_t											dataTypeSupportedBitMask[];/* MSB LSB */
}													ZwEntryControlKeySupportedReportFrameStart_t;

typedef struct										ZwEntryControlKeySupportedReportFrameMidle_s
{
	uint8_t											properties2;/* masked byte */
	uint8_t											eventTypeSupportedBitMask[];/* MSB * LSB */
}													ZwEntryControlKeySupportedReportFrameMidle_t;

typedef struct										ZwEntryControlKeySupportedReportFrameEnd_s
{
	uint8_t											keyCachedSizeSupportedMinimum;/**/
	uint8_t											keyCachedSizeSupportedMaximum;/**/
	uint8_t											keyCachedTimeoutSupportedMinimum;/**/
	uint8_t											keyCachedTimeoutSupportedMaximum;/**/
}													ZwEntryControlKeySupportedReportFrameEnd_t;

typedef struct										ZwEntryControlKeySupportedReportFrame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											keySupportedBitMaskLength;/**/
	uint8_t											keySupportedBitMask[];
}													ZwEntryControlKeySupportedReportFrame_t;

void zuno_CCEntryControlNotification(uint8_t date_type, uint8_t event_type, uint8_t *b, size_t len);
int zuno_CCEntryControlHandler(ZUNOCommandPacket_t *cmd);


#define ZUNO_SETUP_ENTRY_CONTROL_KEYS(...) 	\
								uint8_t __g_zuno_entry_control_asii_mask[0x10]; \
								uint8_t __g_zuno_entry_control_asii_function(void) { \
									size_t					tempos; \
									size_t					i; \
									const char				*b; \
																 \
									static const char asii[] = {__VA_ARGS__, 0x0}; \
									b = &asii[0x0]; \
									while ((tempos = b++[0x0]) != 0x0) { \
										i = tempos / 0x8; \
										__g_zuno_entry_control_asii_mask[i] = __g_zuno_entry_control_asii_mask[i] | (0x1 << (tempos % 0x8)); \
									} \
									return (0x0); \
								} \
								static uint8_t __g_zuno_entry_control_asii_tmp = __g_zuno_entry_control_asii_function(); \

#endif// ZWCC_ENTRY_CONTROL_H