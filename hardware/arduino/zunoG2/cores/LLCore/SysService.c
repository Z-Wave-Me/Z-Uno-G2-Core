#include <SysService.h>
#include "ZUNO_LEDS.h"
#include "ZUNO_Buttons.h"
#include "ZWCCResetLocally.h"
#include "Debug.h"

ZunoLedMode_t SYSLED_ACTIVITY_MODES[] = {
                                            {50, 0x55555555}, // SYSLED_ACTIVITY_MODE_BLINK
                                            
                                        }; 
ZunoLedMode_t SYSLED_LEARN_MODES[] = {  {10, 0x55555555},  // SYSLED_LEARN_MODE_INCLUSION
                                        {10, 0x35353535},  // SYSLED_LEARN_MODE_SUBMENU_READY
                                        {20, 0x00FF0F35},  // SYSLED_LEARN_MODE_IDENTITY
                                        {20, 0x00AA00AA},  // SYSLED_LEARN_MODE_WAITING_RST
                                        {100,0x00010001},  // SYSLED_LEARN_MODE_SYSERROR_MEMORY
                                        {100,0x00050005},  // SYSLED_LEARN_MODE_SYSERROR_HW
                                        {100,0x00150015},  // SYSLED_LEARN_MODE_SYSERROR_WDOG
                                        {100,0x00550055}, 
                                        };
typedef struct ServiceData_s{
    uint8_t cntrl_mode;
    uint32_t cntrl_timeout;
    uint32_t led_learn_timeout;
    uint32_t led_active_timeout;
}ServiceData_t;
ServiceData_t g_service_data;
ButtonsClass  serviceBtn;
ZunoLed       serviceLeds;
void SysReconfigLeds(){
    if(g_zuno_sys->p_config->flags & ZUNO_CFGFILE_FLAG_LED_OFF) {
        serviceLeds.off(SYSLED_ACTIVITY);
    } else {
        if(zunoGetSleepingMode()){
            serviceLeds.on(SYSLED_ACTIVITY);
        } else {
            serviceLeds.setMode(SYSLED_ACTIVITY, SYSLED_ACTIVITY_MODE_BLINK);
        }
    }
}
void SysSetLearnLedMode(uint8_t mode, uint32_t timeout){
    #ifdef LOGGING_DBG
    LOGGING_UART.print("***LEARN LED MODE:");
    LOGGING_UART.print(mode);
    LOGGING_UART.print(" TIMEOUT:"); 
    LOGGING_UART.println(timeout, HEX);
    #endif
    serviceLeds.setMode(SYSLED_LEARN, mode);
    g_service_data.led_learn_timeout = millis()+timeout;
}
void SysStopLearnLed(){
    g_service_data.led_learn_timeout = 0;
    serviceLeds.off(SYSLED_LEARN);
}
void SysServiceInit(){
    serviceLeds.addLed(SYSLED_LEARN, SYSLED_LEARN_MODES, sizeof(SYSLED_LEARN_MODES)/sizeof(ZunoLedMode_t));
    serviceLeds.addLed(SYSLED_ACTIVITY, SYSLED_ACTIVITY_MODES, sizeof(SYSLED_ACTIVITY_MODES)/sizeof(ZunoLedMode_t));
    serviceBtn.addButton(SYSBUTTON);
    memset(&g_service_data, 0, sizeof(ServiceData_t));
    g_service_data.cntrl_mode = SYS_SVC_MODE_NORMAL;
    SysReconfigLeds();
    if(g_zuno_sys->start_error_code != 0){
        #ifdef LOGGING_DBG
        LOGGING_UART.print("(!) HARDWARE FAULT CODE:");
        LOGGING_UART.print(g_zuno_sys->start_error_code, HEX);
        LOGGING_UART.print(" PC:"); 
        LOGGING_UART.println(g_zuno_sys->error_pc_value, HEX);
        #endif
        if(g_zuno_sys->start_error_code & (SYSFAULT_HARDWARE | SYSFAULT_USAGE| SYSFAULT_BUS | SYSFAULT_SUPERVISOR_CALL)){
            SysSetLearnLedMode(SYSLED_LEARN_MODE_SYSERROR_HW, ERROR_IDENTITY_TIMEOUT);
        } else if (g_zuno_sys->start_error_code & (SYSFAULT_MEMORY)) {
            SysSetLearnLedMode(SYSLED_LEARN_MODE_SYSERROR_MEMORY, ERROR_IDENTITY_TIMEOUT);
        } else if (g_zuno_sys->start_error_code & (SYSLED_LEARN_MODE_SYSERROR_WDOG)) {
            SysSetLearnLedMode(SYSLED_LEARN_MODE_SYSERROR_WDOG, ERROR_IDENTITY_TIMEOUT);
        }
        delay(ERROR_IDENTITY_DELAY);
    }
}
static void _setSysCntrlState(uint8_t mode, uint32_t timeout){
    g_service_data.cntrl_mode = mode;
    g_service_data.cntrl_timeout = millis()+timeout;
}
void SysServiceTimer(){
    switch(g_service_data.cntrl_mode){
        case SYS_SVC_MODE_NORMAL:
            if(serviceBtn.isTripleClick(SYSBUTTON)){
                zunoStartLearn(SYS_LEARN_TIMEOUT, true);
            }
            if(serviceBtn.isLongClick(SYSBUTTON)){
                _setSysCntrlState(SYS_SVC_MODE_SUBMENU, SUBMENU_TIMEOUT);
                SysSetLearnLedMode(SYSLED_LEARN_MODE_SUBMENU_READY, SUBMENU_TIMEOUT);
            }
            break;
        case SYS_SVC_MODE_SUBMENU:
            if(serviceBtn.isTripleClick(SYSBUTTON)){
                zunoResetLocally();
            }
            if(serviceBtn.isSingleClick(SYSBUTTON)){
                zunoStartLearn(SYS_LEARN_TIMEOUT, false);
            }
            break;
        case SYS_SVC_MODE_LEARN:
            if(serviceBtn.isSingleClick(SYSBUTTON)){
                zunoStartLearn(0xFF, true); // Cancel learn mode
            }
            break;
    }
    if((g_service_data.cntrl_timeout != 0) && 
        (millis() > g_service_data.cntrl_timeout)){
        g_service_data.cntrl_mode = SYS_SVC_MODE_NORMAL;
        g_service_data.cntrl_timeout = 0;
    }
    if((g_service_data.led_learn_timeout != 0) && 
        (millis() > g_service_data.led_learn_timeout)){
        #ifdef LOGGING_DBG
        LOGGING_UART.println("***LEARN LED STOPPED");
        #endif
        SysStopLearnLed();
    }
}
void SysServiceEvent(ZUNOSysEvent_t * ev){
    switch(ev->event){
        case ZUNO_SYS_EVENT_LEARNSTARTED:
            SysSetLearnLedMode(SYSLED_LEARN_MODE_INCLUSION, SYS_LEARN_TIMEOUT * 1000UL);
            _setSysCntrlState(SYS_SVC_MODE_LEARN, SYS_LEARN_TIMEOUT * 1000UL);
            break;
        case ZUNO_SYS_EVENT_LEARNSTATUS:
            g_service_data.cntrl_mode = SYS_SVC_MODE_NORMAL;
            SysStopLearnLed();
            break;
    }
}
void SysServiceSleep(){
    serviceLeds.off(SYSLED_LEARN);
    serviceLeds.off(SYSLED_ACTIVITY);
}