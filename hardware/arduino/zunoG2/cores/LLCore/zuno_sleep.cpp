#include "Arduino.h"
#include "zuno_sleep.h"
#include "Debug.h"
#include "CommandQueue.h"

#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)

// static void __monitorMainThread(){
//   #ifdef LOGGING_DBG
//   uint32_t tlb_ptr = zmeExtractSketchTLB();
//   LOGGING_UART.println("--- loop()");
//   LOGGING_UART.print("TLB:");
//   LOGGING_UART.println(tlb_ptr, HEX);
//   irq_reg_stack_t * regs =  extractThreadIRQStack((void*)&tlb_ptr);
//   LOGGING_UART.print("  PC:");
//   LOGGING_UART.println(regs->pc, HEX);
//   LOGGING_UART.print("  LR:");
//   LOGGING_UART.println(regs->lr, HEX);
//   #endif
// }

__WEAK bool zunoSysServiceCanSleep();
static uint8_t __zunoSleepingUpd(){
    #ifndef NO_BTN_CHECK_BEFORE_SLEEP
	if(!digitalRead(BUTTON_PIN)){
        return 1; // Never spleep until button released
    }
    if(!zunoSysServiceCanSleep()){
        return 1;
    }
	#endif
    if(g_sleep_data.latch) {
        return 2;
    }
    if(g_sleep_data.indicator_latch){
        return 3;
    }
    if(g_sleep_data.user_latch){
        return 4;
    }
    if(g_sleep_data.inclusion_latch){
        return 5;
    }
    if(g_sleep_data.fwupd_latch){
        return 6;
    }
    if(_zunoHasPendingReports()){
        return 7;
    }
    if(!ZWQIsEmpty()){
        return 8;
    }
    if(g_sleep_data.wup_latch){
        if(millis() > g_sleep_data.wup_timeout){
            #ifdef LOGGING_DBG
            LOGGING_UART.println("***WUP LOCK RELEASED (TIMEOUT)!");
            #endif
            g_sleep_data.wup_latch = false;
        }
        else{
            return 9;
        }
    }
    uint32_t timeout;
    zunoEnterCritical();
    timeout = g_sleep_data.timeout;
    zunoExitCritical();
    
    if(timeout >= millis()){
        return 10; 
    }
    
    #ifdef LOGGING_DBG
    LOGGING_UART.print("CORE CODE (");
    LOGGING_UART.print((uint32_t)zunoGetCurrentThreadHandle(), HEX);
    LOGGING_UART.println(") GO SLEEP!");
    #endif
    g_zuno_sys->sleep_latches = SLEEP_UNLOCKED;
    return 0;
    /*
    zunoSetSleepTimeout(ZUNO_SLEEPLOCK_CUSTOM, ZUNO_AWAKETIMEOUT_SLEEPNOW);
    zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, ZUNO_AWAKETIMEOUT_SLEEPNOW);
    */
}

static void _zunoSleepOnFWUpgradeStart(){
    zunoEnterCritical();
    g_sleep_data.fwupd_latch = true;
    zunoExitCritical();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***FWUPD LOCK ARMED!");
    #endif
}

static void _zunoSleepOnFWUpgradeStop(){
    zunoEnterCritical();
    g_sleep_data.fwupd_latch = false;
    zunoExitCritical();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***FWUPD LOCK RELEASED!");
    #endif

}

static void _zunoSleepOnInclusionStart(){
    #ifdef LOGGING_DBG
    LOGGING_UART.println("INCLUDE STARTED");
    #endif
    zunoEnterCritical();
    g_sleep_data.inclusion_latch = true;
    zunoExitCritical();
}

void _zunoSleepingUpd();
static void _zunoSleepOnInclusionComplete(){
    if(g_sleep_data.inclusion_latch){
        #ifdef LOGGING_DBG
        LOGGING_UART.println("INCLUSION COMPLETED");
        #endif
    }
    #if ZUNO_AFTER_INCLUSION_SLEEP_TIMEOUT > 0
    zunoKickSleepTimeout(ZUNO_AFTER_INCLUSION_SLEEP_TIMEOUT);
    #endif
    zunoEnterCritical();
    g_sleep_data.inclusion_latch = false;
    zunoExitCritical();
    _zunoSleepingUpd();
}

static void _zunoMarkDeviceToSleep(uint8_t mode){
    // Store time mark
    g_sleep_data.user_sleep_ts = millis();
    g_zuno_sys->sleep_highest_mode = mode;
    g_sleep_data.user_latch = false;
    #ifdef LOGGING_DBG
    //LOGGING_UART.println("UNBLOCK ULATCH");
    #endif
    #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
    _zunoSleepingUpd();
    #endif
}

void zunoKickSleepTimeout(uint32_t ms){
    if (zunoIsSleepingMode() == false)
        return ;
    uint32_t new_timeout = millis() + ms;
    if(g_sleep_data.timeout < new_timeout)
        g_sleep_data.timeout = new_timeout;
    #ifdef LOGGING_DBG
    //LOGGING_UART.print("NEW SLEEP TIMEOUT:");
    //LOGGING_UART.print(g_sleep_data.timeout);
    #endif
}

bool zunoIsIclusionLatchClosed(){
    return g_sleep_data.inclusion_latch;
}

void _zunoSleepOnWUPStop(){
    if (zunoIsSleepingMode() == false)
        return ;
    zunoEnterCritical();
    g_sleep_data.wup_latch = false;
    zunoExitCritical();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***WUP LOCK RELEASED!");
    #endif

}

void _zunoSleepOnWUPStart(){
    if (zunoIsSleepingMode() == false)
        return ;
    zunoEnterCritical();
    g_sleep_data.wup_latch = true;
    g_sleep_data.wup_timeout = millis() + ZUNO_MAX_CONTROLLER_WUP_TIMEOUT;
    zunoExitCritical();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***WUP LOCK ARMED!");
    #endif
}

void _zunoSleepingUpd(){
    if (zunoIsSleepingMode() == false)
        return ;
    static uint32_t count =0;
    uint8_t v = __zunoSleepingUpd();
    (void)v;
    #ifdef LOGGING_DBG
    if((count & 0x3F) == 0){
        
        LOGGING_UART.print("***SLP (");
        LOGGING_UART.print((uint32_t)zunoGetCurrentThreadHandle(), HEX);
        LOGGING_UART.print("):");
        LOGGING_UART.println(v);
    }   
    // if((count & 0xFF) == 0)
    //     __monitorMainThread();
    #endif
    count++;
}

bool _zunoIsWUPLocked(){
    if (zunoIsSleepingMode() == false)
        return (false);
    bool res = false;
    zunoEnterCritical();
    res =  g_sleep_data.wup_latch;
    zunoExitCritical();
    return res;
}

void _zunoSysSleep(){
    if (zunoIsSleepingMode() == false)
        return ;
    GPIO_IntClear(g_sleep_data.em4_map);
    // Initialize wakeup timers
    uint32_t df = (millis() - g_sleep_data.user_sleep_ts) / 1000;
    for(int i=0;i<MAX_SLEEP_TIMERS;i++)
        if(g_sleep_data.sleep_timers[i]){
            uint32_t val = (g_sleep_data.sleep_timers[i] > df)? g_sleep_data.sleep_timers[i] - df : 1;
            zunoSysCall(ZUNO_SYSFUNC_PERSISTENT_TIMER_CONTROL, 2, i,  val);
        }
}

void _zunoCheckWakeupBtn(){
    if (zunoIsSleepingMode() == false)
        return ;
    #ifndef NO_BTN_WAKEUP
    uint8_t reason = zunoGetWakeReason();
    bool on_button = false;
    uint32_t base_map = zunoMapPin2EM4Int(BUTTON_PIN);
    on_button = ((g_zuno_sys->gpio_em4flags & base_map) && 
                  ((reason == ZUNO_WAKEUP_REASON_EXT_EM2) ||
	    (reason == ZUNO_WAKEUP_REASON_EXT_EM4)));
	if(on_button){
		#if(ZUNO_BUTTON_NONSLEEP_TIMEOUT > 0)
		zunoKickSleepTimeout(ZUNO_BUTTON_NONSLEEP_TIMEOUT);
		#endif
	}
    #endif
}

void _zunoInitDefaultWakeup(){
    if (zunoIsSleepingMode() == false)
        return ;
    // EM4 Wakeup using BTN/INT1
    #ifndef NO_INT1_WAKEUP
    zunoEM4EnablePinWakeup(INT1);
    // to have an ability to wake up from EM2 mode configure interrupt controller
    attachInterrupt(INT1, NULL, FALLING);
    #endif
    #ifndef NO_BTN_WAKEUP
    zunoEM4EnablePinWakeup(BUTTON_PIN);
    // to have an ability to wake up from EM2 mode configure interrupt controller
    attachInterrupt(BUTTON_PIN, NULL, FALLING);
    #endif
    _zunoCheckWakeupBtn();
    
}

void _zunoInitSleepingData(){
    if (zunoIsSleepingMode() == false)
        return ;
    g_sleep_data.timeout = ZUNO_SLEEP_INITIAL_TIMEOUT;
    g_sleep_data.user_latch = true;
    g_sleep_data.inclusion_latch = false;
    g_sleep_data.wup_latch = false;
    g_sleep_data.wup_timeout = 0;
    g_sleep_data.em4_map = 0;
    memset(g_sleep_data.sleep_timers, 0, sizeof(g_sleep_data.sleep_timers));
    g_sleep_data.user_sleep_ts = millis();
}

void processEnergySaveEvents(ZUNOSysEvent_t * evnt){
    if (zunoIsSleepingMode() == false)
        return ;
    switch(evnt->event){
            case ZUNO_SYS_EVENT_LEARNSTARTED:
                zunoKickSleepTimeout(ZUNO_SLEEP_INCLUSION_TIMEOUT);
                _zunoSleepOnInclusionStart();
                break;
            case ZUNO_SYS_EVENT_OTA_STARTED:
                _zunoSleepOnFWUpgradeStart();
                break;
            case ZUNO_SYS_EVENT_OTA_FINISHED:
                _zunoSleepOnFWUpgradeStop();
                break;
            case ZUNO_SYS_EVENT_LEARNSTATUS:
                if(evnt->params[0] == INCLUSION_STATUS_SUCESS)
                        zunoKickSleepTimeout(ZUNO_SLEEP_INTERVIEW_TIMEOUT);
                _zunoSleepOnInclusionComplete();
                break;
            case ZUNO_SYS_EVENT_STAY_AWAKE:
                if(zunoGetSleepingMode() & DEVICE_CONFIGURATION_FLAGS_FLIRS)
                    zunoKickSleepTimeout(ZUNO_SLEEP_FLIRS_TIMEOUT);
                break;
    }
}
#endif

void zunoSetSleepingMode(byte mode) {
  g_zuno_sys->zw_protocol_data->flags &= ~(DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP);
	mode &= DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP;
	g_zuno_sys->zw_protocol_data->flags |= mode;
}

uint8_t zunoGetSleepingMode(void) {
  return (g_zuno_sys->zw_protocol_data->flags & DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP);
}

bool zunoIsSleepingMode(void) {
    if (zunoGetSleepingMode() == 0x0)
        return (false);
    return (true);
}

void zunoSendDeviceToSleep(uint8_t mode) {
    #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
    if (zunoIsSleepingMode() == false)
        return ;
  // we inform the system that device is ready for sleep
  _zunoMarkDeviceToSleep(mode);
  // suspend the main tread
  /*
  // !!! FIX
  if((g_zuno_sys->zwave_cfg->flags & DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP) != 0){
    zunoSuspendThread(g_zuno_sys->hMainThread);
  }*/
  #else
  (void)mode;
  #endif
}

void zunoLockSleep(void){
    #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
    #ifdef LOGGING_DBG
    //LOGGING_UART.println("***BLOCK SLEEP!");
    #endif
    if (zunoIsSleepingMode() == false)
        return ;
    zunoEnterCritical();
    g_sleep_data.user_latch = true;
    zunoExitCritical();
    #endif
}

bool zunoIsSleepLocked(){
    #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
    bool res = false;
    if (zunoIsSleepingMode() == false)
        return (false);
    zunoEnterCritical();
    res = g_sleep_data.user_latch;
    zunoExitCritical();
    return res;
    #else
    return (false);
    #endif
}
