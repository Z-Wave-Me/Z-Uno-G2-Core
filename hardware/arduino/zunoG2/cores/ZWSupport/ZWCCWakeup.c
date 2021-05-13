#include "ZWCCWakeup.h"
#ifdef WITH_CC_WAKEUP
extern uint8_t     g_outgoing_data[];
void zuno_sendWUP_Notification(){
    if(zunoNID() == 0)
        return;
    uint32_t wakeup_data;
    zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&wakeup_data);

    //Serial0.print("\n\nWUP DATA:");
    //Serial0.println(wakeup_data, HEX);
    if((wakeup_data & 0xFF) == 0){
        //wakeup_data &= ~0xFF;
        //return;
        wakeup_data |= 0x01;
    }
    fillOutgoingReportPacket(0);
    g_outgoing_packet.src_zw_channel  = 0; 
	// !!! DBG
    Serial0.println("SENDING WUP NOTIFICATION!");
    CMD_REPLY_CC = COMMAND_CLASS_WAKE_UP;
    CMD_REPLY_CMD = WAKE_UP_NOTIFICATION;
    CMD_REPLY_LEN = 2;
	zunoSendZWPackage(&g_outgoing_packet);
	
}
void zuno_CCWakeup_OnAnyRx(){
    // go on waiting...
    Serial0.println("Kick WUP Timer");
    zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, WAKEUP_SLEEP_TIMEOUT);
}
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
        zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, WAKEUP_SLEEP_TIMEOUT);
    }    
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
            zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, ZUNO_AWAKETIMEOUT_SLEEPNOW);
            return ZUNO_COMMAND_PROCESSED; 
    }
    return rs;
}
#endif // WITH_CC_WAKEUP