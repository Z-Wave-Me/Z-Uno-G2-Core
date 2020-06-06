#include "ZWCCNotification.h"
#include "ZWSupport.h"

static const byte NOTIFICATION_MAPPER[] = {
    0,0,
    NOTIFICATION_TYPE_BURGLAR_ALARM, NOTIFICATION_EVENT_INTRUSION_UL,   // SENSOR_BINARY_REPORT_TYPE_GENERAL_PURPOSE       
    NOTIFICATION_TYPE_SMOKE_ALARM,   NOTIFICATION_EVENT_SMOKE_UL,       // SENSOR_BINARY_REPORT_TYPE_SMOKE                 
    NOTIFICATION_TYPE_CO_ALARM,      NOTIFICATION_EVENT_CO_UL,          // SENSOR_BINARY_REPORT_TYPE_CO                  
    NOTIFICATION_TYPE_CO2_ALARM,     NOTIFICATION_EVENT_CO2_UL,         // SENSOR_BINARY_REPORT_TYPE_CO2                     
    NOTIFICATION_TYPE_HEAT_ALARM,    NOTIFICATION_EVENT_OVERHEAT_UL,    // SENSOR_BINARY_REPORT_TYPE_HEAT                  
    NOTIFICATION_TYPE_WATER_ALARM,   NOTIFICATION_EVENT_WATER_LEAK_UL,  // SENSOR_BINARY_REPORT_TYPE_WATER                 
    NOTIFICATION_TYPE_HEAT_ALARM,    NOTIFICATION_EVENT_UNDERHEAT_UL,   // SENSOR_BINARY_REPORT_TYPE_FREEZE                 
    NOTIFICATION_TYPE_BURGLAR_ALARM, NOTIFICATION_EVENT_TAMPER_REMOVED, // SENSOR_BINARY_REPORT_TYPE_TAMPER              
    NOTIFICATION_TYPE_BURGLAR_ALARM,        NOTIFICATION_EVENT_INTRUSION_UL,       // SENSOR_BINARY_REPORT_TYPE_AUX                    
    NOTIFICATION_TYPE_ACCESS_CONTROL_ALARM, NOTIFICATION_EVENT_WINDOW_DOOR_OPENED, // SENSOR_BINARY_REPORT_TYPE_DOOR_WINDOW         
    NOTIFICATION_TYPE_BURGLAR_ALARM,        NOTIFICATION_EVENT_INTRUSION_UL,       // SENSOR_BINARY_REPORT_TYPE_TILT                   
    NOTIFICATION_TYPE_BURGLAR_ALARM,        NOTIFICATION_EVENT_MOTION_DETECTION_UL,// SENSOR_BINARY_REPORT_TYPE_MOTION              
    NOTIFICATION_TYPE_BURGLAR_ALARM,        NOTIFICATION_EVENT_GLASS_BREAK_UL ,     // SENSOR_BINARY_REPORT_TYPE_GLASSBREAK         
    NOTIFICATION_TYPE_HOME_HEALTH,          0x02,
    NOTIFICATION_TYPE_SIREN,                0x02,
    NOTIFICATION_TYPE_WATER_VALVE,          0x02,
    NOTIFICATION_TYPE_WEATHER_ALAR,         0x02,
    NOTIFICATION_TYPE_IRRIGATION,           0x02,
    NOTIFICATION_TYPE_GAS_ALARM,            NOTIFICATION_EVENT_GAS_COMBUSTIBLE,
    NOTIFICATION_TYPE_GAS_ALARM,            NOTIFICATION_EVENT_GAS_TOXIC
};

void zuno_CCNotificationInitData(){
    uint32_t eeprom_mask = 0xFFFFFFFF; 
    zunoEEPROMWrite(NOTIFICATION_CC_EEPROM, 4, (byte*)&eeprom_mask);
}
int zuno_CCNotificationReport(byte channel, ZUNOCommandPacket_t * cmd){
    uint32_t eeprom_mask; 
    byte index = (ZUNO_CFG_CHANNEL(channel).sub_type) << 1;
    // Load report mask from EEPROM
    zunoEEPROMRead(NOTIFICATION_CC_EEPROM, 4, (byte*)&eeprom_mask);
    // If it's unsolicited report we have to check if it was turned on by user
    if(cmd == NULL){

        // Unsolicited => doesn't have incoming package
        if((eeprom_mask & (1UL << channel)) == 0)
            return ZUNO_COMMAND_BLOCKED; // User don't want this report => don't send it
        // We have to fill cc/cmd fields
        CMD_REPLY_CC = COMMAND_CLASS_NOTIFICATION;
        CMD_REPLY_CMD = NOTIFICATION_REPORT;
    }
    // Get current sensor state
    uint8_t val =  zuno_universalGetter1P(channel); // Calls or reads value from user defined hamdler or varriable
    // Initially till the report data with zeros
    memset(&(CMD_REPLY_DATA(0)), 0, NOTIFICATION_REPORT_DATA_LEN);
    if(cmd != NULL){
        if((NOTIFICATION_MAPPER[index] != ZW_CMD_BPARAM(1))  && 
            (ZW_CMD_BPARAM(1) != 0xFF)){
            // We don't support this request
            return ZUNO_COMMAND_BLOCKED;
        }
        if(ZW_CMD_BPARAM(0) == 0xFF){ // Fix the "wildcard" param
            CMD_REPLY_DATA(5) = 0xFE;
        }
    }
    CMD_REPLY_LEN = NOTIFICATION_REPORT_LEN; 
    if(CMD_REPLY_DATA(5) != 0xFE){
        CMD_REPLY_DATA(3) = (eeprom_mask & (1UL << channel)) ? NOTIFICATION_ON_VALUE : NOTIFICATION_OFF_VALUE;
        CMD_REPLY_DATA(4) = NOTIFICATION_MAPPER[index];
        if(val){
            CMD_REPLY_DATA(5) = NOTIFICATION_MAPPER[index+1];
        } else {
            // For window/door sensor we have special values => process this case
            if(NOTIFICATION_MAPPER[index+1] == NOTIFICATION_EVENT_WINDOW_DOOR_OPENED){
                CMD_REPLY_DATA(5) = NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED;
                return ZUNO_COMMAND_ANSWERED;
            }
            CMD_REPLY_DATA(5) = NOTIFICATION_OFF_VALUE;
            CMD_REPLY_DATA(6) = 1;
            CMD_REPLY_DATA(7) = NOTIFICATION_MAPPER[index+1];
        }
    }
    return ZUNO_COMMAND_ANSWERED;
}
int zuno_CCNotificationHandler(byte channel, ZUNOCommandPacket_t * cmd){
    int rs = ZUNO_UNKNOWN_CMD;
    uint32_t eeprom_mask;
    switch(ZW_CMD){
        case NOTIFICATION_SET:{
                byte index = (ZUNO_CFG_CHANNEL(channel).sub_type) << 1;
                if(ZW_CMD_BPARAM(0) != NOTIFICATION_MAPPER[index])
                    return ZUNO_COMMAND_BLOCKED;
                if((ZW_CMD_BPARAM(1) != NOTIFICATION_OFF_VALUE) && 
                   (ZW_CMD_BPARAM(1) != NOTIFICATION_ON_VALUE) )
                    return ZUNO_COMMAND_BLOCKED;
                zunoEEPROMRead(NOTIFICATION_CC_EEPROM, 4, (byte*)&eeprom_mask);
                if(ZW_CMD_BPARAM(1)){
                    eeprom_mask |= 1UL << channel;
                } else {
                    eeprom_mask &= ~(1UL << channel);
                }
                zunoEEPROMWrite(NOTIFICATION_CC_EEPROM, 4, (byte*)&eeprom_mask);
                rs = ZUNO_COMMAND_PROCESSED;
            }
            break;
        case NOTIFICATION_GET:
            return zuno_CCNotificationReport(channel, cmd);
        case NOTIFICATION_SUPPORTED_GET:{
                 byte index = (ZUNO_CFG_CHANNEL(channel).sub_type) << 1;
                 CMD_REPLY_LEN = NOTIFICATION_SUPPORTED_LEN;
                 CMD_REPLY_DATA(0) = NOTIFICATION_SUPPORTED_DATA_LEN;
                 zunoSetupBitMask(&(CMD_REPLY_DATA(1)), NOTIFICATION_MAPPER[index], NOTIFICATION_REPORT_DATA_LEN);
                 rs = ZUNO_COMMAND_ANSWERED;
            }
            break;
         case EVENT_SUPPORTED_GET:{
                 byte index = (ZUNO_CFG_CHANNEL(channel).sub_type) << 1;
                 if((NOTIFICATION_MAPPER[index] != ZW_CMD_BPARAM(0))  && 
                    (ZW_CMD_BPARAM(0) != 0xFF)){
                    // We don't support this request
                    return ZUNO_COMMAND_BLOCKED;
                 }
                 CMD_REPLY_DATA(0) = ZW_CMD_BPARAM(0);
                 CMD_REPLY_LEN = NOTIFICATION_SUPPORTED_EV_LEN;
                 CMD_REPLY_DATA(1) = NOTIFICATION_SUPPORTED_EV_DATA_LEN;
                 zunoSetupBitMask(&(CMD_REPLY_DATA(2)), NOTIFICATION_MAPPER[index+1], NOTIFICATION_SUPPORTED_EV_DATA_LEN);
                 rs = ZUNO_COMMAND_ANSWERED;
            }
            break;
    }
    return rs;
}
