#include "ZWCCBattery.h"
#include "ZWSupport.h"
#include "Debug.h"

static uint8_t _save_batteryLevel = 0xFF;

void zuno_CCBattery_OnSetup(){
    if ((zunoGetWakeReason() == ZUNO_WAKEUP_REASON_POR) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_WUT_EM4) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_EXT_EM4) ||
    (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_WUT_EM2) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_EXT_EM2)
      ){
        zunoSendBatteryReport();
    }
}


static uint8_t batteryReportValue(){
	#ifdef WITH_CUSTOM_BATTERY_HANDLER
	return ((uint32_t)(void*)zunoSysHandlerCall(ZUNO_HANDLER_ZW_BATTERY, 0))&0xFF;
	#else
	return defaultBatteryHandler();
    #endif // WITH_CUSTOM_BATTERY_HANDLER
}

bool zunoSendBatteryReportHandler() {
	size_t											batteryLevel;
	ZwBatteryReportFrame_t							*report;
	ZUNOCommandPacketReport_t						frame;

   
	batteryLevel = batteryReportValue();
	#ifdef LOGGING_DBG
	LOGGING_UART.print("*** Battery report");
    LOGGING_UART.println(batteryLevel);
	#endif
	if (batteryLevel == _save_batteryLevel) {
		#ifdef LOGGING_DBG
		LOGGING_UART.println("Battery: Send canceled. The same level.");
		#endif
		return false;
	}
	_save_batteryLevel = batteryLevel;
	fillOutgoingReportPacketAsync(&frame, 0x0);
	report = (ZwBatteryReportFrame_t *)&frame.packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_BATTERY;
	report->cmd = BATTERY_REPORT;
	if (batteryLevel == 0x0)
		batteryLevel = 0xFF;//The value 0xFF MUST indicate a low-battery warning.
	report->batteryLevel = batteryLevel;
	frame.packet.len = sizeof(report[0x0]);
	zunoSendZWPackage(&frame.packet);
	return true;
}

static int _battery_report(ZUNOCommandPacketReport_t *frame_report) {
	ZwBatteryReportFrame_t							*report;
	size_t											batteryLevel;

	_zunoMarkSystemClassRequested(SYSREQUEST_MAP_BATTERY_BIT);
	report = (ZwBatteryReportFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_BATTERY; set in - fillOutgoingPacket
	// report->cmd = BATTERY_REPORT; set in - fillOutgoingPacket
	batteryLevel = batteryReportValue();
	_save_batteryLevel = batteryLevel;
	report->batteryLevel = batteryLevel;
	frame_report->packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCBattery(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch(ZW_CMD) {
		case BATTERY_GET:
			rs = _battery_report(frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}
