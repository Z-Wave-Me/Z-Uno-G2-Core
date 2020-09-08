#include "ZWCCBattery.h"
#ifdef WITH_CC_BATTERY
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
void    zunoSendBatteryReport(){
    fillOutgoingReportPacket(0);
    CMD_REPLY_CC = COMMAND_CLASS_BATTERY;
    CMD_REPLY_CMD = BATTERY_REPORT;
    #ifdef WITH_CUSTOM_BATTERY_HANDLER
    CMD_REPLY_DATA(0) = ((uint32_t)(void*)zunoSysHandlerCall(ZUNO_HANDLER_ZW_BATTERY, 0))&0xFF;
    #else
    CMD_REPLY_DATA(0) = defaultBatteryHandler();
    #endif // WITH_CUSTOM_BATTERY_HANDLER 
    CMD_REPLY_LEN = 3;
    zunoSendZWPackage(&g_outgoing_packet);
}
int     zuno_CCBattery(ZUNOCommandPacket_t * cmd){
    int rs = ZUNO_UNKNOWN_CMD;
    switch(ZW_CMD){
        case BATTERY_GET:
            zunoSendBatteryReport();
            return ZUNO_COMMAND_PROCESSED;
    }
    return rs;
}
#endif // WITH_CC_BATTERY