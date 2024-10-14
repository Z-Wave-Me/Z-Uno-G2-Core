#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCEntryControl.h"

#define ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_MINIMUM					0x1
#define ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_MAXMIMUM				0x20
#define ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_DEFAULT					0x4

#define ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_MINIMUM				0x1
#define ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_MAXMIMUM				0xA
#define ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_DEFAULT				0x4

__WEAK uint8_t zuno_CCEntryControlAsiiMask(uint8_t *mask) {
	return (0x0);
	(void)mask;
}

extern __WEAK const volatile uint32_t __g_zuno_entry_control_data_type_mask = 0x0;

extern __WEAK const volatile uint32_t __g_zuno_entry_control_event_mask = 0x0;

static uint8_t __g_zuno_entry_control_cached_size = ENTRY_CONTROL_CACHED_SIZE_SUPPORTED_DEFAULT;

static uint8_t __g_zuno_entry_control_cached_timout = ENTRY_CONTROL_CACHED_TIMOUT_SUPPORTED_DEFAULT;

static int _entry_control_key_supported_report(ZUNOCommandPacketReport_t *frame_report) {
	ZwEntryControlKeySupportedReportFrame_t		*report;
	size_t										len;

	report = (ZwEntryControlKeySupportedReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_ENTRY_CONTROL; //set in - fillOutgoingPacket
	// report->cmd = ENTRY_CONTROL_KEY_SUPPORTED_REPORT; //set in - fillOutgoingPacket
	len = zuno_CCEntryControlAsiiMask(&report->keySupportedBitMask[0x0]);
	report->keySupportedBitMaskLength = len;
	frame_report->info.packet.len = sizeof(ZwEntryControlKeySupportedReportFrame_t) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _entry_control_event_supported_report(ZUNOCommandPacketReport_t *frame_report) {
	ZwEntryControlKeySupportedReportFrameStart_t		*start;
	ZwEntryControlKeySupportedReportFrameMidle_t		*midle;
	ZwEntryControlKeySupportedReportFrameEnd_t			*end;
	size_t												len;

	start = (ZwEntryControlKeySupportedReportFrameStart_t *)frame_report->info.packet.cmd;
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
	frame_report->info.packet.len = (uint8_t *)end - frame_report->info.packet.cmd + sizeof(end[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _entry_control_configuration_report(ZUNOCommandPacketReport_t *frame_report) {
	ZW_ENTRY_CONTROL_CONFIGURATION_REPORT_FRAME		*report;

	report = (ZW_ENTRY_CONTROL_CONFIGURATION_REPORT_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_ENTRY_CONTROL; //set in - fillOutgoingPacket
	// report->cmd = ENTRY_CONTROL_CONFIGURATION_REPORT; //set in - fillOutgoingPacket
	report->keyCacheSize = __g_zuno_entry_control_cached_size;
	report->keyCacheTimeout = __g_zuno_entry_control_cached_timout;
	frame_report->info.packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _entry_control_configuration_set(const ZW_ENTRY_CONTROL_CONFIGURATION_SET_FRAME *packet) {
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

int zuno_CCEntryControlHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
		case ENTRY_CONTROL_KEY_SUPPORTED_GET:
			rs = _entry_control_key_supported_report(frame_report);
			break ;
		case ENTRY_CONTROL_EVENT_SUPPORTED_GET:
			rs = _entry_control_event_supported_report(frame_report);
			break ;
		case ENTRY_CONTROL_CONFIGURATION_GET:
			rs = _entry_control_configuration_report(frame_report);
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

bool zuno_CCEntryControlNotification(uint8_t data_type, uint8_t event_type, uint8_t *b, size_t len) {
	ZwEntryControlNotificationFrame_t		*report;
	static uint8_t							sequenceNumber = 0x0;
	ZUNOCommandPacketReport_t				frame;

	if ((__g_zuno_entry_control_data_type_mask & (0x1 << data_type)) == 0x0)
		return (false);
	if ((__g_zuno_entry_control_event_mask & (0x1 << event_type)) == 0x0)
		return (false);
	switch (data_type) {
		case ENTRY_CONTROL_NOTIFICATION_DATA_NA:
			if (b != 0x0 || len != 0x0)
				return (false);
			break ;
		case ENTRY_CONTROL_NOTIFICATION_DATA_RAW:
			if (len < 0x1 || len > 0x20)
				return (false);
			break ;
		case ENTRY_CONTROL_NOTIFICATION_DATA_MD5:
			if (len != 0x10)
				return (false);
			break ;
	}
	fillOutgoingReportPacketAsync(&frame, 0x0);
	report = (ZwEntryControlNotificationFrame_t *)&frame.info.packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_ENTRY_CONTROL; 
	report->cmd = ENTRY_CONTROL_NOTIFICATION;
	report->sequenceNumber = sequenceNumber++;
	report->properties1 = data_type;
	report->eventType = event_type;
	report->eventDataLength = len;
	memcpy(&report->eventData[0x0], b, len);
	frame.info.packet.len = sizeof(report[0x0]) + len;
	zunoSendZWPackage(&frame.info);
	return (true);
}