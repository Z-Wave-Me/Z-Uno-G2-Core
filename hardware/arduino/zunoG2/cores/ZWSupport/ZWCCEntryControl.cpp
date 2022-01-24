#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCEntryControl.h"

#define ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_MINIMUM					0x1
#define ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_MAXMIMUM				0x20
#define ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_DEFAULT					0x4

#define ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_MINIMUM				0x1
#define ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_MAXMIMUM				0xA
#define ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_DEFAULT				0x4

__WEAK uint8_t __g_zuno_entry_control_asii_mask[0x10] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

static const uint32_t __g_zuno_entry_control_data_type_mask = ((0x1 << ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_NA) | (0x1 << ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_RAW) | (0x1 << ENTRY_CONTROL_NOTIFICATION_DATA_TYPE_ASCII));
static const uint32_t __g_zuno_entry_control_event_mask = 0x0;//((0x1 << ENTRY_CONTROL_NOTIFICATION_ENTER) | (0x1 << ENTRY_CONTROL_NOTIFICATION_CANCEL) | (0x1 << ENTRY_CONTROL_NOTIFICATION_POLICE));
static uint8_t __g_zuno_entry_control_cached_size = ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_DEFAULT;
static uint8_t __g_zuno_entry_control_cached_timout = ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_DEFAULT;

static int _entry_control_key_supported_report(void) {
	ZwEntryControlKeySupportedReportFrame_t		*report;

	report = (ZwEntryControlKeySupportedReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_ENTRY_CONTROL; //set in - fillOutgoingPacket
	// report->cmd = ENTRY_CONTROL_KEY_SUPPORTED_REPORT; //set in - fillOutgoingPacket
	report->keySupportedBitMaskLength = sizeof(__g_zuno_entry_control_asii_mask);
	memcpy(&report->keySupportedBitMask[0x0], &__g_zuno_entry_control_asii_mask[0x0], sizeof(__g_zuno_entry_control_asii_mask));
	CMD_REPLY_LEN = sizeof(ZwEntryControlKeySupportedReportFrame_t) + sizeof(__g_zuno_entry_control_asii_mask);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _entry_control_event_supported_report(void) {
	ZwEntryControlKeySupportedReportFrameStart_t		*start;
	ZwEntryControlKeySupportedReportFrameMidle_t		*midle;
	ZwEntryControlKeySupportedReportFrameEnd_t			*end;
	size_t												len;

	start = (ZwEntryControlKeySupportedReportFrameStart_t *)&CMD_REPLY_CC;
	// start->cmdClass = COMMAND_CLASS_ENTRY_CONTROL; //set in - fillOutgoingPacket
	// start->cmd = ENTRY_CONTROL_EVENT_SUPPORTED_REPORT; //set in - fillOutgoingPacket
	len = ((((sizeof(__g_zuno_entry_control_data_type_mask) * 0x8) - __builtin_clz(__g_zuno_entry_control_data_type_mask)) >> 0x3) + 0x1);
	start->properties1 = len;
	memcpy(&start->dataTypeSupportedBitMask[0x0], (uint8_t *)&__g_zuno_entry_control_data_type_mask, len);
	midle = (ZwEntryControlKeySupportedReportFrameMidle_t *)((uint8_t *)start + len + sizeof(start[0x0]));
	len = ((((sizeof(__g_zuno_entry_control_event_mask) * 0x8) - __builtin_clz(__g_zuno_entry_control_event_mask)) >> 0x3) + 0x1);
	midle->properties2 = len;
	memcpy(&midle->eventTypeSupportedBitMask[0x0], (uint8_t *)&__g_zuno_entry_control_event_mask, len);
	end = (ZwEntryControlKeySupportedReportFrameEnd_t *)((uint8_t *)midle + len + sizeof(midle[0x0]));
	end->keyCachedSizeSupportedMinimum = ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_MINIMUM;
	end->keyCachedSizeSupportedMaximum = ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_MAXMIMUM;
	end->keyCachedTimeoutSupportedMinimum = ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_MINIMUM;
	end->keyCachedTimeoutSupportedMaximum = ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_MAXMIMUM;
	CMD_REPLY_LEN = (uint8_t *)end - &CMD_REPLY_CC + sizeof(end[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _entry_control_configuration_report(void) {
	ZW_ENTRY_CONTROL_CONFIGURATION_REPORT_FRAME		*report;

	report = (ZW_ENTRY_CONTROL_CONFIGURATION_REPORT_FRAME *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_ENTRY_CONTROL; //set in - fillOutgoingPacket
	// report->cmd = ENTRY_CONTROL_CONFIGURATION_REPORT; //set in - fillOutgoingPacket
	report->keyCacheSize = __g_zuno_entry_control_cached_size;
	report->keyCacheTimeout = __g_zuno_entry_control_cached_timout;
	CMD_REPLY_LEN = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _entry_control_configuration_set(ZW_ENTRY_CONTROL_CONFIGURATION_SET_FRAME *packet) {
	size_t										keyCacheSize;
	size_t										keyCacheTimeout;
	int											rs;

	rs = ZUNO_COMMAND_PROCESSED;
	if ((keyCacheSize = packet->keyCacheSize) >= ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_MINIMUM && keyCacheSize <= ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_MAXMIMUM)
		__g_zuno_entry_control_cached_size = keyCacheSize;
	else
		rs = ZUNO_COMMAND_BLOCKED_FAILL;
	if ((keyCacheTimeout = packet->keyCacheTimeout) >= ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_MINIMUM && keyCacheTimeout <= ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_MAXMIMUM)
		__g_zuno_entry_control_cached_timout = keyCacheTimeout;
	else
		rs = ZUNO_COMMAND_BLOCKED_FAILL;
	return (rs);
}

int zuno_CCEntryControlHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case ENTRY_CONTROL_KEY_SUPPORTED_GET:
			rs = _entry_control_key_supported_report();
			break ;
		case ENTRY_CONTROL_EVENT_SUPPORTED_GET:
			rs = _entry_control_event_supported_report();
			break ;
		case ENTRY_CONTROL_CONFIGURATION_GET:
			rs = _entry_control_configuration_report();
			break ;
		case ENTRY_CONTROL_CONFIGURATION_SET:
			rs = _entry_control_configuration_set((ZW_ENTRY_CONTROL_CONFIGURATION_SET_FRAME *)&cmd->cmd[0x0]);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

void zuno_CCEntryControlNotification(uint8_t date_type, uint8_t event_type, uint8_t *b, size_t len) {
	ZwEntryControlNotificationFrame_t		*report;
	static uint8_t							sequenceNumber = 0x0;

	report = (ZwEntryControlNotificationFrame_t *)&CMD_REPLY_CC;
	report->cmdClass = COMMAND_CLASS_ENTRY_CONTROL; 
	report->cmd = ENTRY_CONTROL_NOTIFICATION;
	report->sequenceNumber = sequenceNumber++;
	report->properties1 = date_type;
	report->eventType = event_type;
	report->eventDataLength = len;
	memcpy(&report->eventData[0x0], b, len);
	CMD_REPLY_LEN = sizeof(report[0x0]) + len;
	zunoSendZWPackage(&g_outgoing_main_packet);
}