#include <SysService.h>
#include "ZUNO_LEDS.h"
#ifdef ZUNO_OLD_BUTTONS
#include "ZUNO_Buttons.h"
#define BTN_OBJ Btn
#else
#include "ZMEButtons.h"
#define BTN_OBJ ZBtn
#endif
#include "ZWCCResetLocally.h"
#include "Debug.h"
#include "em_core.h"

ZunoLedMode_t SYSLED_MODES[] = {  {10, 0x55555555},  // SYSLED_LEARN_MODE_INCLUSION
                                        {10, 0x35353535},  // SYSLED_LEARN_MODE_SUBMENU_READY
                                        {20, 0x00FF0F35},  // SYSLED_LEARN_MODE_IDENTITY
                                        {20, 0x00AA00AA},  // SYSLED_LEARN_MODE_WAITING_RST
                                        {100,0x00010001},  // SYSLED_LEARN_MODE_SYSERROR_MEMORY
                                        {100,0x00050005},  // SYSLED_LEARN_MODE_SYSERROR_HW
                                        {100,0x00150015},  // SYSLED_LEARN_MODE_SYSERROR_WDOG
                                        {50, 0x55555555}, // SYSLED_LEARN_MODE_BLINK
                                        };
typedef struct ServiceData_s{
    uint8_t cntrl_mode;
    uint32_t cntrl_timeout;
    uint32_t led_learn_timeout;
    uint32_t led_active_timeout;
}ServiceData_t;
ServiceData_t g_service_data;

#define _SYSBUTTON          SYSBUTTON       //g_zuno_sys->fw_static_header->hw_button_pin
#define _SYSLED_ACTIVITY    SYSLED_ACTIVITY //g_zuno_sys->fw_static_header->hw_led1_pin
#define _SYSLED_LEARN       SYSLED_LEARN    //g_zuno_sys->fw_static_header->hw_led2_pin

__WEAK void zunoSysServiceLedInit(void) {
	Led.addLed(_SYSLED_ACTIVITY, 
               SYSLED_MODES, sizeof(SYSLED_MODES)/sizeof(ZunoLedMode_t), 
               SYS_LED_INVERT);
	Led.addLed(_SYSLED_LEARN, 
               SYSLED_MODES, sizeof(SYSLED_MODES)/sizeof(ZunoLedMode_t),
               SYS_LED_INVERT);
    
}

__WEAK void zunoSysServiceLedOff(uint8_t pin) {
	Led.off(pin);
}

__WEAK void zunoSysServiceLedOn(uint8_t pin) {
	Led.on(pin);
}

__WEAK void zunoSysServiceLedSetMode(uint8_t pin, uint8_t mode) {
	Led.setMode(pin, mode);
}

void SysReconfigLeds(){
    if(g_zuno_sys->p_config->flags & ZUNO_CFGFILE_FLAG_LED_OFF) {
        zunoSysServiceLedOff(_SYSLED_ACTIVITY);
    } else {
        #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
        if(zunoIsSleepingMode() == true){
            #ifdef LOGGING_DBG
            //LOGGING_UART.println("*** DEVICE IS SLEEPING");
            #endif
            zunoSysServiceLedOn(_SYSLED_ACTIVITY);
        } else {
        #endif
            zunoSysServiceLedSetMode(_SYSLED_ACTIVITY, SYSLED_LEARN_MODE_BLINK);
        #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
        }
        #endif
    }
}
void SysSetLearnLedMode(uint8_t mode, uint32_t timeout){
    #ifdef LOGGING_DBG
    LOGGING_UART.print("***LEARN LED MODE:");
    LOGGING_UART.print(mode);
    LOGGING_UART.print(" TIMEOUT:"); 
    LOGGING_UART.println(timeout, HEX);
    #endif
    zunoSysServiceLedSetMode(_SYSLED_LEARN, mode);
    g_service_data.led_learn_timeout = millis()+timeout;
}
void SysStopLearnLed(){
    g_service_data.led_learn_timeout = 0;
    zunoSysServiceLedOff(_SYSLED_LEARN);
}
void SysServiceInit(){
    #ifndef NO_SYS_LEDS
	zunoSysServiceLedInit();
    #endif
    if(_SYSBUTTON != 0xFF) // The button is enabled for this configuration
        BTN_OBJ.addButton(_SYSBUTTON);
    memset(&g_service_data, 0, sizeof(ServiceData_t));
    g_service_data.cntrl_mode = SYS_SVC_MODE_NORMAL;
    #ifndef NO_SYS_LEDS
    SysReconfigLeds();
    #endif
}
static void _setSysCntrlState(uint8_t mode, uint32_t timeout){
    g_service_data.cntrl_mode = mode;
    g_service_data.cntrl_timeout = millis()+timeout;
}
void SysServiceTimer(){
    if(_SYSBUTTON != 0xFF){
        switch(g_service_data.cntrl_mode){
            case SYS_SVC_MODE_NORMAL:
                if(BTN_OBJ.isTripleClick(_SYSBUTTON)){
                    zunoStartLearn(SYS_LEARN_TIMEOUT, true);
                }
                #if ZUNO_OLD_BUTTONS
                if(Btn.isLongClick(_SYSBUTTON)){
                    _setSysCntrlState(SYS_SVC_MODE_SUBMENU, SUBMENU_TIMEOUT);
                    #ifndef NO_SYS_LEDS
                    SysSetLearnLedMode(SYSLED_LEARN_MODE_SUBMENU_READY, SUBMENU_TIMEOUT);
                    #endif
                }
                #else 
                if(ZBtn.isHoldReleased(_SYSBUTTON)){
                    if(ZBtn.currentHoldTime(_SYSBUTTON) >= ZUNO_ADV_MENU_TIMEOUT){
                        _setSysCntrlState(SYS_SVC_MODE_SUBMENU, SUBMENU_TIMEOUT);
                        #ifndef NO_SYS_LEDS
                        SysSetLearnLedMode(SYSLED_LEARN_MODE_SUBMENU_READY, SUBMENU_TIMEOUT);
                        #endif
                    }
                }
                #endif
                break;
            case SYS_SVC_MODE_SUBMENU:
                if(BTN_OBJ.isTripleClick(_SYSBUTTON)){
                    zunoResetLocally();
                }
                if(BTN_OBJ.isSingleClick(_SYSBUTTON)){
                    zunoStartLearn(SYS_LEARN_TIMEOUT, false);
                }
                break;
            case SYS_SVC_MODE_LEARN:
                if(BTN_OBJ.isSingleClick(_SYSBUTTON)){
                    zunoStartLearn(0xFF, true); // Cancel learn mode
                }
                break;
        }
    }
    if((g_service_data.cntrl_timeout != 0) && 
        (millis() > g_service_data.cntrl_timeout)){
        g_service_data.cntrl_mode = SYS_SVC_MODE_NORMAL;
        g_service_data.cntrl_timeout = 0;
    }
    if((g_service_data.led_learn_timeout != 0) && 
        (millis() > g_service_data.led_learn_timeout)){
        #ifndef NO_SYS_LEDS
            #ifdef LOGGING_DBG
            LOGGING_UART.println("***LEARN LED STOPPED");
            #endif
        SysStopLearnLed();
        #endif
    }
}
void SysServiceEvent(ZUNOSysEvent_t * ev){
    switch(ev->event){
        case ZUNO_SYS_EVENT_LEARNSTARTED:
            #ifndef NO_SYS_LEDS
            SysSetLearnLedMode(SYSLED_LEARN_MODE_INCLUSION, SYS_LEARN_TIMEOUT * 1000UL);
            #endif
            _setSysCntrlState(SYS_SVC_MODE_LEARN, SYS_LEARN_TIMEOUT * 1000UL);
            break;
        case ZUNO_SYS_EVENT_LEARNSTATUS:
            g_service_data.cntrl_mode = SYS_SVC_MODE_NORMAL;
            #ifndef NO_SYS_LEDS
            SysStopLearnLed();
            #endif
            break;
    }
}
void SysServiceSleep(){
    #ifndef NO_SYS_LEDS
    if(zunoIsSleepingMode() == true) {
        zunoSysServiceLedOff(_SYSLED_LEARN);
        zunoSysServiceLedOff(_SYSLED_ACTIVITY);
    }
    #endif
}
void SysServiceWUP(){
    #ifndef NO_SYS_LEDS
    SysReconfigLeds();
    #endif
}

CORE_irqState_t CORE_EnterAtomic(void) __attribute__ ((alias("CORE_EnterCritical")));
CORE_irqState_t CORE_EnterCritical(void) {
	zunoSysCall(ZUNO_SYSFUNC_ENTER_CRITICAL, 0);
	return (0x0);
}

void CORE_ExitAtomic(CORE_irqState_t irqState) __attribute__ ((alias("CORE_ExitCritical")));
void CORE_ExitCritical(CORE_irqState_t irqState) {
	zunoSysCall(ZUNO_SYSFUNC_EXIT_CRITICAL, 0);
	(void)irqState;
}
