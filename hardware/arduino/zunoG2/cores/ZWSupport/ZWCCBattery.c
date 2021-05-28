#include "ZWCCBattery.h"

#ifndef BATTERY_LOW
#define BATTERY_LOW 2500
#endif
#ifndef BATTERY_HIGH
#define BATTERY_HIGH 3000
#endif

#if !defined(WITH_CUSTOM_BATTERY_HANDLER)
uint8_t defaultBatteryHandler(){
    dword res = analogRead(BATTERY);
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
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_WUP_EM4) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_EXT_EM4)){
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
void zunoSendBatteryReportHandler() {
	fillOutgoingReportPacket(0);
	CMD_REPORT_CC = COMMAND_CLASS_BATTERY;
	CMD_REPORT_CMD = BATTERY_REPORT;
	CMD_REPORT_DATA(0) = batteryReportValue();
	CMD_REPORT_LEN = 3;
	zunoSendZWPackage(&g_outgoing_report_packet);
}

int     zuno_CCBattery(ZUNOCommandPacket_t * cmd){
    int rs = ZUNO_UNKNOWN_CMD;
    switch(ZW_CMD){
        case BATTERY_GET:
            _zunoMarkSystemClassRequested(SYSREQUEST_MAP_BATTERY_BIT);
            CMD_REPLY_DATA(0) = batteryReportValue();
            CMD_REPLY_LEN = 3;
            
            return ZUNO_COMMAND_ANSWERED;
    }
    return rs;
}
