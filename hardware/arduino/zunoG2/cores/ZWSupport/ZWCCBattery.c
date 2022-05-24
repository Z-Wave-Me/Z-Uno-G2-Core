#include "ZWCCBattery.h"

#ifndef BATTERY_LOW
#define BATTERY_LOW 2500
#endif
#ifndef BATTERY_HIGH
#define BATTERY_HIGH 3000
#endif

static uint8_t _save_batteryLevel = 0xFF;

#if !defined(WITH_CUSTOM_BATTERY_HANDLER)
uint8_t defaultBatteryHandler(){
    uint8_t old_res  = g_zuno_odhw_cfg.adc_resolution;
    g_zuno_odhw_cfg.adc_resolution = 12;
    dword res = analogRead(BATTERY);
    g_zuno_odhw_cfg.adc_resolution = old_res;
    res *= 5000;
    res >>= 12;
    if(res >= BATTERY_HIGH)
        return 100;
    res -= BATTERY_LOW;
    res *= 100;
    return res / (BATTERY_HIGH - BATTERY_LOW);
}
#endif
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
	if (batteryLevel == _save_batteryLevel)
		return (false);
	_save_batteryLevel = batteryLevel;
	fillOutgoingReportPacketAsync(&frame, 0x0);
	report = (ZwBatteryReportFrame_t *)&frame.packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_BATTERY;
	report->cmd = BATTERY_REPORT;
	report->batteryLevel = batteryLevel;
	frame.packet.len = sizeof(report[0x0]);
	zunoSendZWPackage(&frame.packet);
	zunoReportHandler(&frame.packet);
	return (true);
}

static int _battery_report(void) {
	ZwBatteryReportFrame_t							*report;
	size_t											batteryLevel;

	_zunoMarkSystemClassRequested(SYSREQUEST_MAP_BATTERY_BIT);
	report = (ZwBatteryReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_BATTERY; set in - fillOutgoingPacket
	// report->cmd = BATTERY_REPORT; set in - fillOutgoingPacket
	batteryLevel = batteryReportValue();
	_save_batteryLevel = batteryLevel;
	report->batteryLevel = batteryLevel;
	CMD_REPLY_LEN = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCBattery(ZUNOCommandPacket_t * cmd){
	int								rs;

	switch(ZW_CMD) {
		case BATTERY_GET:
			rs = _battery_report();
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}
