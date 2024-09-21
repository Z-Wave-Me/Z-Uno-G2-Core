#ifndef ZWCC_ENTRY_CONTROL_H
#define ZWCC_ENTRY_CONTROL_H

#include "ZWSupport.h"

#define ENTRY_CONTROL_NOTIFICATION_DATA_NA												ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_NA
#define ENTRY_CONTROL_NOTIFICATION_DATA_RAW												ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_RAW
#define ENTRY_CONTROL_NOTIFICATION_DATA_ASCII											ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_ASCII
#define ENTRY_CONTROL_NOTIFICATION_DATA_MD5												ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_MD5

#define ENTRY_CONTROL_NOTIFICATION_DATA_NA_MASK											(0x1 << ENTRY_CONTROL_NOTIFICATION_DATA_NA)
#define ENTRY_CONTROL_NOTIFICATION_DATA_RAW_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_DATA_RAW)
#define ENTRY_CONTROL_NOTIFICATION_DATA_ASCII_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_DATA_ASCII)
#define ENTRY_CONTROL_NOTIFICATION_DATA_MD5_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_DATA_MD5)
#define ENTRY_CONTROL_NOTIFICATION_DATA_MASK											(ENTRY_CONTROL_NOTIFICATION_DATA_NA_MASK | ENTRY_CONTROL_NOTIFICATION_DATA_RAW_MASK | ENTRY_CONTROL_NOTIFICATION_DATA_ASCII_MASK | ENTRY_CONTROL_NOTIFICATION_DATA_MD5_MASK)

#define ENTRY_CONTROL_NOTIFICATION_EVENT_CACHING										ENTRY_CONTROL_NOTIFICATION_CACHING
#define ENTRY_CONTROL_NOTIFICATION_EVENT_CACHED_KEYS									ENTRY_CONTROL_NOTIFICATION_CACHED_KEYS
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ENTER											ENTRY_CONTROL_NOTIFICATION_ENTER
#define ENTRY_CONTROL_NOTIFICATION_EVENT_DISARM_ALL										ENTRY_CONTROL_NOTIFICATION_DISARM_ALL
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_ALL										ENTRY_CONTROL_NOTIFICATION_ARM_ALL
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_AWAY										ENTRY_CONTROL_NOTIFICATION_ARM_AWAY
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_HOME										ENTRY_CONTROL_NOTIFICATION_ARM_HOME
#define ENTRY_CONTROL_NOTIFICATION_EVENT_EXIT_DELAY										ENTRY_CONTROL_NOTIFICATION_EXIT_DELAY
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_1											ENTRY_CONTROL_NOTIFICATION_ARM_1
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_2											ENTRY_CONTROL_NOTIFICATION_ARM_2
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_3											ENTRY_CONTROL_NOTIFICATION_ARM_3
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_4											ENTRY_CONTROL_NOTIFICATION_ARM_4
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_5											ENTRY_CONTROL_NOTIFICATION_ARM_5
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_6											ENTRY_CONTROL_NOTIFICATION_ARM_6
#define ENTRY_CONTROL_NOTIFICATION_EVENT_RFID											ENTRY_CONTROL_NOTIFICATION_RFID
#define ENTRY_CONTROL_NOTIFICATION_EVENT_BELL											ENTRY_CONTROL_NOTIFICATION_BELL
#define ENTRY_CONTROL_NOTIFICATION_EVENT_FIRE											ENTRY_CONTROL_NOTIFICATION_FIRE
#define ENTRY_CONTROL_NOTIFICATION_EVENT_POLICE											ENTRY_CONTROL_NOTIFICATION_POLICE
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ALERT_PANIC									ENTRY_CONTROL_NOTIFICATION_ALERT_PANIC
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ALERT_MEDICAL									ENTRY_CONTROL_NOTIFICATION_ALERT_MEDICAL
#define ENTRY_CONTROL_NOTIFICATION_EVENT_GATE_OPEN										ENTRY_CONTROL_NOTIFICATION_GATE_OPEN
#define ENTRY_CONTROL_NOTIFICATION_EVENT_GATE_CLOSE										ENTRY_CONTROL_NOTIFICATION_GATE_CLOSE
#define ENTRY_CONTROL_NOTIFICATION_EVENT_LOCK											ENTRY_CONTROL_NOTIFICATION_LOCK
#define ENTRY_CONTROL_NOTIFICATION_EVENT_UNLOCK											ENTRY_CONTROL_NOTIFICATION_UNLOCK
#define ENTRY_CONTROL_NOTIFICATION_EVENT_TEST											ENTRY_CONTROL_NOTIFICATION_TEST
#define ENTRY_CONTROL_NOTIFICATION_EVENT_CANCEL											ENTRY_CONTROL_NOTIFICATION_CANCEL

#define ENTRY_CONTROL_NOTIFICATION_EVENT_CACHING_MASK									(0x1 << ENTRY_CONTROL_NOTIFICATION_CACHING)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_CACHED_KEYS_MASK								(0x1 << ENTRY_CONTROL_NOTIFICATION_CACHED_KEYS)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ENTER_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_ENTER)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_DISARM_ALL_MASK								(0x1 << ENTRY_CONTROL_NOTIFICATION_DISARM_ALL)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_ALL_MASK									(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_ALL)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_AWAY_MASK									(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_AWAY)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_HOME_MASK									(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_HOME)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_EXIT_DELAY_MASK								(0x1 << ENTRY_CONTROL_NOTIFICATION_EXIT_DELAY)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_1_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_1)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_2_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_2)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_3_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_3)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_4_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_4)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_5_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_5)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_6_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_ARM_6)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_RFID_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_RFID)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_BELL_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_BELL)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_FIRE_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_FIRE)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_POLICE_MASK									(0x1 << ENTRY_CONTROL_NOTIFICATION_POLICE)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ALERT_PANIC_MASK								(0x1 << ENTRY_CONTROL_NOTIFICATION_ALERT_PANIC)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_ALERT_MEDICAL_MASK								(0x1 << ENTRY_CONTROL_NOTIFICATION_ALERT_MEDICAL)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_GATE_OPEN_MASK									(0x1 << ENTRY_CONTROL_NOTIFICATION_GATE_OPEN)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_GATE_CLOSE_MASK								(0x1 << ENTRY_CONTROL_NOTIFICATION_GATE_CLOSE)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_LOCK_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_LOCK)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_UNLOCK_MASK									(0x1 << ENTRY_CONTROL_NOTIFICATION_UNLOCK)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_TEST_MASK										(0x1 << ENTRY_CONTROL_NOTIFICATION_TEST)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_CANCEL_MASK									(0x1 << ENTRY_CONTROL_NOTIFICATION_CANCEL)
#define ENTRY_CONTROL_NOTIFICATION_EVENT_MASK											(ENTRY_CONTROL_NOTIFICATION_EVENT_CACHING_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_CACHED_KEYS_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_ENTER_MASK | \
																						ENTRY_CONTROL_NOTIFICATION_EVENT_DISARM_ALL_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_ALL_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_AWAY_MASK | \
																						ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_HOME_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_EXIT_DELAY_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_1_MASK | \
																						ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_2_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_3_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_4_MASK | \
																						ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_5_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_ARM_6_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_RFID_MASK | \
																						ENTRY_CONTROL_NOTIFICATION_EVENT_BELL_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_FIRE_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_POLICE_MASK | \
																						ENTRY_CONTROL_NOTIFICATION_EVENT_ALERT_PANIC_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_ALERT_MEDICAL_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_GATE_OPEN_MASK | \
																						ENTRY_CONTROL_NOTIFICATION_EVENT_GATE_CLOSE_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_LOCK_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_UNLOCK_MASK | \
																						ENTRY_CONTROL_NOTIFICATION_EVENT_TEST_MASK | ENTRY_CONTROL_NOTIFICATION_EVENT_CANCEL_MASK) \

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

#define ZUNO_SETUP_ENTRY_CONTROL_EVENT(EVENT_MASK)	\
										extern const volatile uint32_t __g_zuno_entry_control_event_mask = (EVENT_MASK & ENTRY_CONTROL_NOTIFICATION_EVENT_MASK);\

#define ZUNO_SETUP_ENTRY_CONTROL_DATA(DATA_MASK)	\
										extern const volatile uint32_t __g_zuno_entry_control_data_type_mask = (DATA_MASK & ENTRY_CONTROL_NOTIFICATION_DATA_MASK);\

#define ZUNO_SETUP_ENTRY_CONTROL_KEYS_COMMON(...)	\
								uint8_t zuno_CCEntryControlAsiiMask(uint8_t *mask){\
									size_t					tempos; \
									size_t					i; \
									size_t					len; \
									len = 0x0; \
									__VA_ARGS__ ;\
									return (len + 0x1); \
								} \

#define ZUNO_SETUP_ENTRY_CONTROL_KEYS_SET(KEY)		\
									if (KEY <= 0x7F) { \
									tempos = KEY; \
									i = tempos / 0x8; \
									if (i > len) \
										len = i; \
									mask[i] = mask[i] | (0x1 << (tempos % 0x8)); \
									} \

#define ZUNO_SETUP_ENTRY_CONTROL_KEYS_INTERVAL(START, END) \
									if (START <= 0x7F && END <= 0x7F && START <= END) { \
										tempos = START; \
										while (tempos <= END) { \
											i = tempos / 0x8; \
											if (i > len) \
												len = i; \
											mask[i] = mask[i] | (0x1 << (tempos % 0x8)); \
											tempos++; \
										} \
									} \

bool zuno_CCEntryControlNotification(uint8_t data_type, uint8_t event_type, uint8_t *b, size_t len);
int zuno_CCEntryControlHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);

#endif// ZWCC_ENTRY_CONTROL_H