#include "ZWCCWakeup.h"

extern uint8_t     g_outgoing_data[];

static uint8_t    g_wup_sended_notify = 0;
static uint8_t    g_wup_inclusion = 0;

void zuno_sendWUP_Notification(){
    g_zuno_odhw_cfg.bWUPReport = true;
}
extern uint8_t g_outgoing_report_data[];
void zuno_sendWUP_NotificationReport(){
    if(zunoNID() == 0)
        return;
    if(!g_zuno_odhw_cfg.bWUPReport)
        return;
    
    uint32_t wakeup_data;

    zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&wakeup_data);

    //Serial0.print("\n\nWUP DATA:");
    //Serial0.println(wakeup_data, HEX);
    uint8_t wake_nodeid = wakeup_data & 0xFF;
    if((wake_nodeid < 1) || (wake_nodeid > MAX_NODEID) ){
        wake_nodeid = 1;
    }
    fillOutgoingRawPacket(&g_outgoing_report_packet, g_outgoing_report_data, 0, 0, wake_nodeid);
    g_outgoing_report_packet.src_zw_channel  = 0; 
	// !!! DBG
    Serial0.println("SENDING WUP NOTIFICATION!");
    CMD_REPORT_CC = COMMAND_CLASS_WAKE_UP;
    CMD_REPORT_CMD = WAKE_UP_NOTIFICATION;
    CMD_REPORT_LEN = 2;
	zunoSendZWPackage(&g_outgoing_report_packet);
    zunoKickSleepTimeout(WAKEUP_MAXIMUM_CONTROLLER_TIMEOUT);
    g_zuno_odhw_cfg.bWUPReport = false;
}
/*
void zuno_CCWakeup_OnAnyRx(){
    // go on waiting...
    if(g_wup_sended_notify){
        return; // Controller directs this timer
    }
    if(g_wup_inclusion){
        return; // Inclusion in process
    }
    #ifdef LOGGING_DBG
    LOGGING_UART.print("Kick WUP Timer");
    #endif
    zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, WAKEUP_SLEEP_TIMEOUT);
}*/
void zuno_CCWakeup_OnSetup(){
    
    if ((zunoGetWakeReason() == ZUNO_WAKEUP_REASON_POR) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_PIN) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_SOFTRESET) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_WATCH_DOG) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_WUP_EM4)
      ){
        uint32_t wakeup_data;
        zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&wakeup_data);
        wakeup_data >>= 8;
        //Serial0.println(wakeup_data);
        zunoSetWUPTimer(wakeup_data);
        //Serial0.println("WUP NOTIFY");
        zuno_sendWUP_Notification();
        return;
        //zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, WAKEUP_SLEEP_TIMEOUT);
    }    
    //zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, WAKEUP_SLEEP_TIMEOUT);
}
void zuno_CCWakeup_OnDefault(){
    // Serial0.println("WUP DEFAULT");
    uint32_t wakeup_data = (WAKEUP_INTERVAL_DEFAULT << 8) | 0x01; 
    zunoEEPROMWrite(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&wakeup_data);
}
int zuno_CCWakeupHandler(ZUNOCommandPacket_t * cmd) {
    int rs = ZUNO_UNKNOWN_CMD;
    switch(ZW_CMD){
        case WAKE_UP_INTERVAL_CAPABILITIES_GET:
            CMD_REPLY_DATA(0) = (WAKEUP_INTERVAL_MIN >> 16) & 0xFF;
            CMD_REPLY_DATA(1) = (WAKEUP_INTERVAL_MIN >> 8) & 0xFF;
            CMD_REPLY_DATA(2) = (WAKEUP_INTERVAL_MIN & 0xFF);
            CMD_REPLY_DATA(3) = (WAKEUP_INTERVAL_MAX >> 16) & 0xFF;
            CMD_REPLY_DATA(4) = (WAKEUP_INTERVAL_MAX >> 8) & 0xFF;
            CMD_REPLY_DATA(5) = (WAKEUP_INTERVAL_MAX & 0xFF);
            CMD_REPLY_DATA(6) = (WAKEUP_INTERVAL_DEFAULT >> 16) & 0xFF;
            CMD_REPLY_DATA(7) = (WAKEUP_INTERVAL_DEFAULT >> 8) & 0xFF;
            CMD_REPLY_DATA(8) = (WAKEUP_INTERVAL_DEFAULT & 0xFF);
            CMD_REPLY_DATA(9) = (WAKEUP_INTERVAL_STEP >> 16) & 0xFF;
            CMD_REPLY_DATA(10)= (WAKEUP_INTERVAL_STEP >> 8) & 0xFF;
            CMD_REPLY_DATA(11)= (WAKEUP_INTERVAL_STEP & 0xFF);
            CMD_REPLY_LEN = 15;
            return ZUNO_COMMAND_ANSWERED;
        case WAKE_UP_INTERVAL_GET:{
                zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&CMD_REPLY_DATA(0));
                CMD_REPLY_LEN = 6;
            }
            return ZUNO_COMMAND_ANSWERED;
        case WAKE_UP_INTERVAL_SET:{
                uint32_t wakeup_data;
                wakeup_data = ZW_CMD_BPARAM(0);
                wakeup_data <<= 8;
                wakeup_data |= ZW_CMD_BPARAM(1);
                wakeup_data <<= 8;
                wakeup_data |= ZW_CMD_BPARAM(2);
                wakeup_data <<= 8;
                wakeup_data |= ZW_CMD_BPARAM(3);
                zunoEEPROMWrite(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&wakeup_data);
                zunoSetWUPTimer(wakeup_data >> 8);
            }
            return ZUNO_COMMAND_PROCESSED;
        case WAKE_UP_NO_MORE_INFORMATION:
            g_wup_sended_notify = false;
            if(g_wup_inclusion){
                g_wup_inclusion = false;
                #ifdef LOGGING_DBG
                LOGGING_UART.print("Inclusion timer stop");
                #endif
            }
            zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, ZUNO_AWAKETIMEOUT_SLEEPNOW);
            return ZUNO_COMMAND_PROCESSED; 
    }
    return rs;
}