#include "ZWCCWakeup.h"

extern uint8_t     g_outgoing_data[];

static uint8_t    g_wup_sended_notify = 0;
static uint8_t    g_wup_inclusion = 0;
extern uint8_t g_outgoing_report_data[];

void _zunoSleepOnWUPStart();
void _zunoSleepOnWUPStop();

static void __zunoSetupWUPTimeout(){
    uint32_t wakeup_data;
    zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&wakeup_data);
    wakeup_data >>= 8;
    #ifdef LOGGING_DBG
    LOGGING_UART.print("Wakeup timer was set to:");
    LOGGING_UART.print(wakeup_data);
    LOGGING_UART.print("seconds");
    #endif
    zunoSetWUPTimer(wakeup_data);
}
void zuno_sendWUP_NotificationReport(){
    if(zunoNID() == 0)
        return;
    uint32_t wakeup_data;

    zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&wakeup_data);
    uint8_t wake_nodeid = wakeup_data & 0xFF;
    if((wake_nodeid < 1) || (wake_nodeid > MAX_NODEID) ){
        wake_nodeid = 1;
    }
    fillOutgoingRawPacket(&g_outgoing_report_packet, g_outgoing_report_data, 0, 0, wake_nodeid);
    g_outgoing_report_packet.src_zw_channel  = 0; 
	// !!! DBG
    #ifdef LOGGING_DBG
    LOGGING_UART.print("SENDING WUP NOTIFICATION! NodeID:");
    LOGGING_UART.println(wake_nodeid);
    #endif
    CMD_REPORT_CC = COMMAND_CLASS_WAKE_UP;
    CMD_REPORT_CMD = WAKE_UP_NOTIFICATION;
    CMD_REPORT_LEN = 2;
	zunoSendZWPackage(&g_outgoing_report_packet);
    _zunoSleepOnWUPStart();
}

void zunoSendWakeUpNotification(void);

void zuno_CCWakeup_OnSetup(){
    
    if ((zunoGetWakeReason() == ZUNO_WAKEUP_REASON_POR) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_PIN) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_SOFTRESET) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_WATCH_DOG) ||
      (zunoGetWakeReason() == ZUNO_WAKEUP_REASON_WUP_EM4)
      ){
       
        __zunoSetupWUPTimeout();
        zunoSendWakeUpNotification();
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
            __zunoSetupWUPTimeout();
            _zunoSleepOnWUPStop();
            //zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, ZUNO_AWAKETIMEOUT_SLEEPNOW);
            return ZUNO_COMMAND_PROCESSED; 
    }
    return rs;
}