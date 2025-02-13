#include "ZWCCBattery.h"
#include "ZWSupport.h"
#include "Debug.h"

static uint8_t _batteryLevel = 0x0;

static bool _zunoSendBatteryReportHandler(bool report_test);
void zuno_CCBattery_OnSetup(){
    _zunoSendBatteryReportHandler(true);
}


static uint8_t batteryReportValue(){
	#ifdef WITH_CUSTOM_BATTERY_HANDLER
	return ((uint32_t)(void*)zunoSysHandlerCall(ZUNO_HANDLER_ZW_BATTERY, 0))&0xFF;
	#else
	return defaultBatteryHandler();
    #endif // WITH_CUSTOM_BATTERY_HANDLER
}

__WEAK uint8_t zunoBattery(ZunoBattery_t *out) {
	uint8_t											batteryLevel;

	batteryLevel = batteryReportValue();
	if (batteryLevel == 0x0)
		out->replaced_recharged_soon = true;
	return (batteryLevel);
}

static uint8_t _ZunoBattery(bool async, ZunoBattery_t *out) {
	static const ZunoBattery_t						init = 
	{
		.charging_status = ZunoBatteryChargingStatusDischarging,
		.replaced_recharged_soon = false,
		.replaced_recharged_now = false,
		.temperature_low = false,
	};
	uint8_t											batteryLevel;

	out[0x0] = init;
	batteryLevel = zunoBattery(out);
	if (out->replaced_recharged_now == true)
		out->replaced_recharged_soon = true;
	if (out->temperature_low == true)
		out->charging_status = ZunoBatteryChargingStatusDischarging;
	if (batteryLevel >= 100)
		batteryLevel = 100;
	if (out->replaced_recharged_soon == true) {
		if (batteryLevel >= 100)
			batteryLevel = 0x0;
		if (async == true)
			return (0xFF);
	}
	return (batteryLevel);
}

static bool _battery_report_common_test_send(bool report_test, uint8_t batteryLevel) {
	uint8_t											old;
	uint8_t											hysteresis;

	if (report_test == false || batteryLevel == 0x0)
		return (true);
	old = _batteryLevel;
	if (old > batteryLevel)
		hysteresis = old - batteryLevel;
	else
		hysteresis = batteryLevel - old;
	if (hysteresis >= 0x3)
		return (true);
	return (false);
}

static bool _battery_report_common(bool async, bool report_test, ZUNOCommandPacketReport_t *frame) {
	ZwBatteryReportFrame_t							*report;
	ZunoBattery_t									out;
	uint8_t											batteryLevel;
	uint8_t											properties1;

	batteryLevel = _ZunoBattery(async, &out);
	if (_battery_report_common_test_send(report_test, batteryLevel) == false)
		return (false);
	_batteryLevel = batteryLevel;
	#ifdef LOGGING_DBG
	LOGGING_UART.print("*** Battery report: ");
	LOGGING_UART.println(batteryLevel);
	#endif
	report = (ZwBatteryReportFrame_t *)&frame->info.packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_BATTERY;
	report->cmd = BATTERY_REPORT;
	report->batteryLevel = batteryLevel;
	properties1 = BATTERY_REPORT_PROPERTIES1_RECHARGEABLE_BIT_MASK | ((out.charging_status << BATTERY_REPORT_PROPERTIES1_CHARGING_STATUS_SHIFT) & BATTERY_REPORT_PROPERTIES1_CHARGING_STATUS_MASK);
	if (out.replaced_recharged_soon == true)
		properties1 = properties1 | (0x1 << 0x0);
	if (out.replaced_recharged_now == true)
		properties1 = properties1 | (0x1 << 0x1);
	if (out.temperature_low == true)
		properties1 = properties1 | BATTERY_REPORT_PROPERTIES2_LOW_TEMPERATURE_STATUS_BIT_MASK;
	report->properties1 = properties1;
	report->properties2 = 0x0;
	frame->info.packet.len = sizeof(report[0x0]);
	return (true);
}

static bool _zunoSendBatteryReportHandler(bool report_test) {
	ZUNOCommandPacketReport_t						frame;

	if (zunoIsSleepingMode() == false)
		return (false);
	fillOutgoingReportPacketAsync(&frame, 0x0);
	if (_battery_report_common(true, report_test, &frame) == false)
		return (false);
	zunoSendZWPacketAdd(&frame);
	return (true);
}

bool zunoSendBatteryReportHandler() {
	return _zunoSendBatteryReportHandler(false);
}

static int _battery_report(ZUNOCommandPacketReport_t *frame_report) {
	_zunoMarkSystemClassRequested(SYSREQUEST_MAP_BATTERY_BIT);
	_battery_report_common(false, false, frame_report);
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct _ZW_BATTERY_HEALTH_REPORT_1BYTE_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   maximumCapacity;              /**/
    uint8_t   properties1;                  /* masked byte */
    uint8_t   batteryTemperature[];          
} ZW_BATTERY_HEALTH_REPORT_1BYTE_V3_FRAME;

static int _battery_healt_report(ZUNOCommandPacketReport_t *frame_report) {
	ZW_BATTERY_HEALTH_REPORT_1BYTE_V3_FRAME			*report;

	report = (ZW_BATTERY_HEALTH_REPORT_1BYTE_V3_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_BATTERY; set in - fillOutgoingPacket
	// report->cmd = BATTERY_HEALTH_REPORT; set in - fillOutgoingPacket
	report->maximumCapacity = 0xFF;//This field MUST be in the range 0x00..0x64 or set to 0xFF. If the maximum capacity of the battery is unknown the value MUST set to 0xFF.
	report->properties1 = 0x0;//The value 0 MUST indicate that the battery temperature is unknown. In this case, the Scale and Precision fields MUST be set to 0 and the Battery Temperature field MUST be omitted.
	frame_report->info.packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCBattery(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	if (zunoIsSleepingMode() == false)
		return (ZUNO_COMMAND_BLOCKED_NO_SUPPORT);
	switch(ZW_CMD) {
		case BATTERY_GET:
			rs = _battery_report(frame_report);
			break ;
		case BATTERY_HEALTH_GET:
			rs = _battery_healt_report(frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}
