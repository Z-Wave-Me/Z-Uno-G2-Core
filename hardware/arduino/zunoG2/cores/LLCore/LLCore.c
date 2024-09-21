#include "Arduino.h"
#include "LLCore.h"
#include "Stub.h"
#include <stdarg.h>
#include "Tone.h"
#include "Debug.h"
#include "errno.h"
#include "sys/stat.h"
#include "Custom_timestamp.h"
#include "em_device.h"
#include "em_adc.h"
#include "em_gpio.h"
#include <CommandQueue.h>
#include <SysService.h>

static_assert(sizeof(ZwEepromSketh_t) <= EEPROM_MAX_SIZE, "EEPROM - overflow!!!");
static_assert(sizeof(ZwEepromSkethCommon_t) == EEPROM_SKETH_SIZE, "EEPROM USER CODE - overflow!!!");

#ifndef SKETCH_FLAGS_LOOP_DELAY
    #define SKETCH_FLAGS_LOOP_DELAY			32
#endif
#ifndef ZUNO_BUTTON_NONSLEEP_TIMEOUT
#define ZUNO_BUTTON_NONSLEEP_TIMEOUT         5000
#endif

#ifndef ZUNO_DEFAULT_PIN_STATE
#define ZUNO_DEFAULT_PIN_STATE DISABLED
#endif

#ifdef LOGGING_DBG
    #pragma message "LOGGING_DBG: ON"
#endif

#ifdef ASSERT_DBG
    #pragma message "ASSERT_DBG: ON"
#endif

#ifndef SKETCH_FWID
#define SKETCH_FWID 0x0101
#endif
#ifndef SKETCH_FLAGS
#define SKETCH_FLAGS (HEADER_FLAGS_REBOOT_CFG | 0x00)
#endif
#ifndef SKETCH_VERSION
#define SKETCH_VERSION 0x0101
#endif

extern unsigned long __etext;
extern unsigned long __data_start__;
extern unsigned long __data_end__;
extern unsigned long __bss_start__;
extern unsigned long __bss_end__;
extern unsigned long __HeapBase;
extern unsigned long __HeapLimit;

#ifndef ZUNO_HWID
    #if (ZUNO_PIN_V == 6 || ZUNO_PIN_V == 0x704)
    #define ZUNO_HWID (0x704)
    #else
    #define ZUNO_HWID (ZUNO_PIN_V)
    #endif
#endif
#ifndef ZUNO_SKETCH_BUILD_TS
#define ZUNO_SKETCH_BUILD_TS 0
#endif
#ifndef DBG_CONSOLE_PIN
#ifdef LOGGING_DBG
#define DBG_CONSOLE_PIN 0xFE //  Use a default one for the board

#else
    #define DBG_CONSOLE_PIN 0xFF
#endif // LOGGING_DBG
#endif // DBG_CONSOLE_PIN
#ifndef ZUNO_EXT_FIRMWARES_COUNT
#define ZUNO_EXT_FIRMWARES_COUNT 0
#endif
#ifndef ZUNO_EXT_FIRMWARES_DESCR_PTR
#define ZUNO_EXT_FIRMWARES_DESCR_PTR ((ZUNOOTAFWDescr_t*)NULL)
#endif
#ifndef ZUNO_OTA_PIN
#define ZUNO_OTA_PIN 0UL
#endif
#ifndef ZUNO_CUSTOM_OTA_OFFSET
#define ZUNO_CUSTOM_OTA_OFFSET 0UL
#endif 
#ifndef ZUNO_SKETCH_NAME
#define ZUNO_SKETCH_NAME ""
#endif
void * zunoJumpTable(int vec, void * data);
ZUNOCodeHeader_t g_zuno_codeheader __attribute__((section(".sketch_struct"))) =  {
                                                                                    {'Z','M','E','Z','U','N','O','C'}, 
                                                                                    ZUNO_CORE_VERSION_MAJOR, ZUNO_CORE_VERSION_MINOR, 
                                                                                    0x0000, 0x0000, 
                                                                                    SKETCH_FLAGS, 
                                                                                    SKETCH_FWID, 
                                                                                    (uint32_t)&zunoJumpTable, 
                                                                                    ZUNO_SKETCH_BUILD_TS,
                                                                                    DBG_CONSOLE_PIN,
                                                                                    DBG_CONSOLE_BAUDRATE,
                                                                                    SKETCH_VERSION,
                                                                                    ZUNO_EXT_FIRMWARES_COUNT,
                                                                                    ZUNO_EXT_FIRMWARES_DESCR_PTR,
                                                                                    ZUNO_OTA_PIN,
                                                                                    ZUNO_CUSTOM_OTA_OFFSET,
                                                                                    ZUNO_SKETCH_NAME,
                                                                                    ZUNO_HWID};

// from ZWSupport.c
int zuno_CommandHandler(ZUNOCommandCmd_t * cmd); 
void zuno_CCTimer(uint32_t);

/*
typedef void zuno_user_systimer_handler(uint32_t);
typedef void zuno_user_sysevent_handler(ZUNOSysEvent_t * ev);
*/

ZUNOSetupSysState_t * g_zuno_sys;
ZUNOSleepData_t g_sleep_data;
// prototypes 
void loop();
void setup();

void LLDestroy() {
}

#ifdef WITH_AUTOSETUP
// this is managing using "preproc" util
void zuno_static_autosetup();
#endif
void zunoReconfigStaticChannels(void) __attribute__ ((weak));
void zunoReconfigStaticChannels(void) {
    #ifdef WITH_AUTOSETUP
    zuno_static_autosetup();
    #endif
}

#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
void _zunoSysSleep();
void _zunoInitSleepingData();
void _zunoSleepingUpd();
void _zunoInitDefaultWakeup();
void _zunoCheckWakeupBtn();
#endif

#ifdef LOGGING_DBG
bool g_logging_inited = false;
#endif
bool g_sketch_inited = false;

void initCCSDataDefault();

extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));
extern void (*__fini_array_start []) (void) __attribute__((weak));
extern void (*__fini_array_end []) (void) __attribute__((weak));

static void LLInit(void *data) {
    // default configuration values
    #ifndef NO_DEFAULT_PIN_SETUP
    for (int i=0; i <= ZUNO_PIN_LAST_INDEX; i++){
		#ifdef LOGGING_DBG
			#if DBG_CONSOLE_PIN != 0xFF
			if (((getRealPort(i) << 0x4) | getRealPin(i)) == DBG_CONSOLE_PIN)
				continue ;
			#endif
		#endif
        if(i == BUTTON_PIN)
            continue;
        pinMode(i, ZUNO_DEFAULT_PIN_STATE);//set default state
    }
    #endif
    // Constructors....
    // Global values initialization
    for(uint32_t *p=&__data_start__, *cd = (uint32_t *)&__etext; p<((uint32_t *)&__data_end__); p++, cd++){
        *p = *cd; 
    }
    for(uint32_t * p=&__bss_start__; p<&__bss_end__; p++){
        *p = 0;
    }
    g_zuno_sys = (ZUNOSetupSysState_t*)data;
    for (uint32_t * b = (uint32_t *)&__preinit_array_start; b < ((uint32_t *)&__preinit_array_end); b++) {
        ((void (*)())b[0])();
        WDOG_Feed();
    }
    for (uint32_t * b = (uint32_t *)&__init_array_start; b < ((uint32_t *)&__init_array_end); b++) {
        ((void (*)())b[0])();
        WDOG_Feed();
    }
	switch (zunoGetWakeReason()) {
		case ZUNO_WAKEUP_REASON_WUT_EM4:
		case ZUNO_WAKEUP_REASON_EXT_EM4:
		case ZUNO_WAKEUP_REASON_EXT_EM2:
		case ZUNO_WAKEUP_REASON_WUT_EM2:
		case ZUNO_WAKEUP_REASON_RADIO_EM2:
			break ;
		default:
			zunoSetTimeStamp(ZUNO_SKETCH_BUILD_TS);
			break ;
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.begin(DBG_CONSOLE_BAUDRATE);
	#endif
	zunoReconfigStaticChannels();
	#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
	_zunoInitSleepingData();
	_zunoInitDefaultWakeup();
	#endif
	void __g_zuno_indicator_init(void);
	__g_zuno_indicator_init();
	#if defined(WITH_CC_CENTRAL_SCENE)
	void zunoCentralSceneSaveLoad(void);
	zunoCentralSceneSaveLoad();
	#endif
	g_sketch_inited = false;
}
#ifdef LOGGING_DBG
void checkSystemCriticalStat();
#endif
void _zunoRegisterTimerThread();
void _zunoRegisterCommandThread();
uint32_t g_sys_timer_counter = 0;
#ifdef LOGGING_DBG
void printSystemEvent(ZUNOSysEvent_t * evnt ){
    LOGGING_UART.print("[");
    LOGGING_UART.print(millis());
    LOGGING_UART.print("] "); 
    switch(evnt->event){
        case ZUNO_SYS_EVENT_STACK_OVERFLOW:
            LOGGING_UART.print("***ERROR: STACKOVERFLOW:");
            LOGGING_UART.println(evnt->params[0], HEX);
            break;
        case ZUNO_SYS_EVENT_QUEUE_OVERLOAD:
            LOGGING_UART.println("***ERROR: SYSTEM QUEUE OVERLOAD");
            break;
        case ZUNO_SYS_EVENT_INVALID_TX_REQUEST:
            LOGGING_UART.println("***ERROR: INVALID TX REQUEST");
            break;
        case ZUNO_SYS_EVENT_INVALID_MEMORYAREA_IN_SYSCALL:
            LOGGING_UART.print("***ERROR: INVALID MEMORY AREA AS SYSCALL PARAMETER:");
            LOGGING_UART.print(evnt->params[0], HEX);
            LOGGING_UART.print(" ");
            LOGGING_UART.println(evnt->params[1], HEX);
            break;
        case ZUNO_SYS_EVENT_INVALID_PARAMNUM_IN_SYSCALL:
            LOGGING_UART.print("***ERROR: WRONG PARAMETER COUNT IN SYSCALL:");
            LOGGING_UART.print(evnt->params[0], HEX);
            LOGGING_UART.print(" ");
            LOGGING_UART.println(evnt->params[1], HEX);
            break;
        case ZUNO_SYS_EVENT_INVALID_SYSCALL_PARAM_VALUE:
            LOGGING_UART.print("***ERROR: WRONG PARAMETER VALUE IN SYSCALL:");
            LOGGING_UART.print(evnt->params[0], HEX);
            LOGGING_UART.print(" ");
            LOGGING_UART.println(evnt->params[1], HEX);
            break;
        case ZUNO_SYS_EVENT_SYSTEM_FAULT:
            LOGGING_UART.print("***ERROR: SYSTEM FAULT DURING PREV. BOOT:");
            LOGGING_UART.print(evnt->params[0], HEX);
            LOGGING_UART.print(" ");
            LOGGING_UART.println(evnt->params[1], HEX);
            break;
        default:
            LOGGING_UART.print("SYSEVENT: ");
            LOGGING_UART.print(evnt->event, HEX);
            LOGGING_UART.print(" ARGS: ");
            LOGGING_UART.print(evnt->params[0], HEX);
            LOGGING_UART.print(" ");
            LOGGING_UART.println(evnt->params[1], HEX);
            break;
    }
}
#endif

static void _zunoAwakeUsrCode(){
    zunoLockSleep();
    #ifdef LOGGING_DBG
    /*
    uint8_t val = zunoThreadIsRunning(g_zuno_sys->hMainThread);
    LOGGING_UART.print("Tread running:");
    LOGGING_UART.println(val);*/
    #endif
    //if(!zunoThreadIsRunning(g_zuno_sys->hMainThread)){
        zunoResumeThread(g_zuno_sys->hMainThread);
    //}
}


void * zunoJumpTable(int vec, void * data) {
  
    byte sub_handler_type = 0x00;
    switch(vec){
        case ZUNO_JUMPTBL_SETUP:
            LLInit(data);
            break;
        case ZUNO_JUMPTBL_LOOP:
            if(!g_sketch_inited){
                #ifndef NO_SYS_SVC
                SysServiceInit();
                #endif
                ZWCCSetup();
                setup();
                g_sketch_inited = true;
            }
            loop();
            #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
            _zunoSleepingUpd();
            #endif
            #ifdef LOGGING_DBG
            checkSystemCriticalStat(); // Self check after each loop
            #endif
            #if (SKETCH_FLAGS_LOOP_DELAY>0)
            #if defined(LOGGING_DBG) && defined(DGB_LOOP_ACTIVITY)
	        LOGGING_UART.print("*** LOOP DL:");
            LOGGING_UART.println(SKETCH_FLAGS_LOOP_DELAY);
	        #endif
            delay(SKETCH_FLAGS_LOOP_DELAY); // to avoid starvation
            #endif
            break;
        case ZUNO_JUMPTBL_CMDHANDLER:
            _zunoRegisterCommandThread();
            // Awake code if user had sent device to sleep, but z-wave message has arrived
            _zunoAwakeUsrCode();
            return (void*)zuno_CommandHandler((ZUNOCommandCmd_t *) data);
        
        case ZUNO_JUMPTBL_SYSEVENT:{
                ZUNOSysEvent_t * evnt = (ZUNOSysEvent_t *)data;
                #ifdef LOGGING_DBG
                printSystemEvent(evnt);
                #endif
                #ifndef NO_SYS_SVC
                SysServiceEvent(evnt);
                #endif
                #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
                void processEnergySaveEvents(ZUNOSysEvent_t * evnt);
                processEnergySaveEvents(evnt);
                #endif
                // Clean when device was excluded
                if( (evnt->event == ZUNO_SYS_EVENT_LEARNSTATUS) && 
                    (evnt->params[0] == INCLUSION_STATUS_SUCESS) && 
                    (evnt->params[1] == 0)){
                    initCCSDataDefault();
                }
                zunoRFLogger(evnt);
            }
            break;
       
        case ZUNO_JUMPTBL_SYSTIMER:{
            static uint32_t counter = 0;
            //_zunoRegisterTimerThread();
            #ifndef NO_SYS_SVC  
            SysServiceTimer();
            #endif
            zuno_CCTimer((uint32_t)data);
            #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
            _zunoSleepingUpd();
            #endif
            #ifdef LOGGING_DBG
            //if((((uint32_t)counter) & 0x7F) == 0)
            //    LOGGING_UART.println("***TMR:PULSE");
            #endif
            counter++;
            }
            break;
        case ZUNO_JUMPTBL_IRQ:{
                IOQueueMsg_t * p_msg = (IOQueueMsg_t *)data;
                sub_handler_type = p_msg->type;
                // #ifdef LOGGING_DBG
	            // LOGGING_UART.print("*** _IRQ:");
                // LOGGING_UART.print(p_msg->type);
                // LOGGING_UART.print(" P:");
                // LOGGING_UART.print(p_msg->param);
	            // #endif
                // Awake code if user had sent device to sleep, but interrupt has triggered
                _zunoAwakeUsrCode();
            }
            break;
        /*    
        case ZUNO_JUMPTBL_SYSTIMER:
            g_sys_timer_counter ++;
            break;
        */
        case ZUNO_JUMPTBL_SLEEP:
            #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
            #ifndef NO_SYS_SVC 
            SysServiceSleep();
            #endif
            _zunoSysSleep();
            #endif
            #ifdef LOGGING_DBG
            //LOGGING_UART.println("!SLEEP");
            #endif
            break;
        case ZUNO_JUMPTBL_WUP:
            // Awake code if user had sent device to sleep, but wakeup timer triggered
            _zunoAwakeUsrCode();
            #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
            #ifndef NO_SYS_SVC 
            SysServiceWUP();
            #endif
            _zunoInitSleepingData();
            _zunoCheckWakeupBtn();
            #endif
            ZWCCSetup();
            break;
        case ZUNO_JUMPTBL_WTIMER:
            break;
        default:
            #ifdef LOGGING_DBG
	        LOGGING_UART.print("*** UNKNOWN JMPTBL VEC");
            LOGGING_UART.print(vec);
	        #endif
            break; // UNKNOWN VECTOR
    }
    if(vec >= ZUNO_JUMPTBL_SYSTIMER){
        zunoSysHandlerCall(vec-ZUNO_JUMPTBL_SYSTIMER,sub_handler_type, data);
    }
    return (void*)0;
}

void zunoSetWUPTimer(uint32_t timeout){
    g_sleep_data.sleep_timers[0] = timeout;
    //zunoSysCall(ZUNO_SYSFUNC_PERSISTENT_TIMER_CONTROL, 2, 0,  timeout);
}
void zunoSetCustomWUPTimer(uint32_t timeout){
    g_sleep_data.sleep_timers[1] = timeout;
    //zunoSysCall(ZUNO_SYSFUNC_PERSISTENT_TIMER_CONTROL, 2, 1,  timeout);
}
void _fillZWaveData(uint8_t secure_param);
void zunoStartLearn(byte timeout, bool secured){
    uint8_t secure_param = secured ? ZUNO_SECUREPARAM_ON : ZUNO_SECUREPARAM_OFF;
    _fillZWaveData(secure_param);
    zunoSysCall(ZUNO_SYSFUNC_LEARN, 2, timeout, secured);
}
void zunoSendNIF(){
    zunoSysCall(ZUNO_SYSFUNC_SENDNIF, 0);   
}
void zunoReboot(bool force){
    zunoSysCall(ZUNO_SYSFUNC_REBOOT, 1, force);   
	(void)force;
}

/* time */
extern SysCryticalStat_t  g_sys_crytical_stat;
bool zunoIsSystemThread(void * handle);
void delay(dword ms){
    if(zunoIsSystemThread(NULL)){
        g_sys_crytical_stat.systhread_delay_count++;
        return;
    }
    zunoSysCall(ZUNO_SYSFUNC_DELAY_MS, 1, ms);
}
#ifdef LOGGING_DBG
void checkSystemCriticalStat(){
    static uint32_t reported_delay_cnt = 0;
    static uint32_t reported_lock_timeout_cnt = 0;
    static uint32_t reported_open_timeout_cnt = 0;
    static uint32_t reported_max_lock_wait = 0;
    static uint32_t reported_max_open_wait = 0;
    
    if(g_sys_crytical_stat.systhread_delay_count != reported_delay_cnt){
        LOGGING_UART.print("[");
        LOGGING_UART.print(millis());
        LOGGING_UART.print("] (!!!) delay() call in system thread. Count:");
        LOGGING_UART.println(g_sys_crytical_stat.systhread_delay_count);
        reported_delay_cnt = g_sys_crytical_stat.systhread_delay_count;
    }
    if(g_sys_crytical_stat.lock_timeout_count != reported_lock_timeout_cnt){
        LOGGING_UART.print("[");
        LOGGING_UART.print(millis());
        LOGGING_UART.print("] (!!!) Sync lock() timeout . Count:");
        LOGGING_UART.println(g_sys_crytical_stat.lock_timeout_count);
        reported_lock_timeout_cnt = g_sys_crytical_stat.lock_timeout_count;
    }
    if(g_sys_crytical_stat.open_timeout_count != reported_open_timeout_cnt){
        LOGGING_UART.print("[");
        LOGGING_UART.print(millis());
        LOGGING_UART.print("] (!!!) zunoSyncOpen() timeout . Count:");
        LOGGING_UART.println(g_sys_crytical_stat.open_timeout_count);
        reported_open_timeout_cnt = g_sys_crytical_stat.lock_timeout_count;
    }
    if(g_sys_crytical_stat.max_lock_wait != reported_max_lock_wait){
        LOGGING_UART.print("[");
        LOGGING_UART.print(millis());
        LOGGING_UART.print("] (INFO) max_lock_wait:");
        LOGGING_UART.println(g_sys_crytical_stat.max_lock_wait);
        reported_max_lock_wait = g_sys_crytical_stat.max_lock_wait;
    }
    if(g_sys_crytical_stat.max_open_wait != reported_max_open_wait){
        LOGGING_UART.print("[");
        LOGGING_UART.print(millis());
        LOGGING_UART.print("] (INFO) max_open_wait:");
        LOGGING_UART.println(g_sys_crytical_stat.max_lock_wait);
        reported_max_open_wait = g_sys_crytical_stat.max_open_wait;
    }
}
#endif

// MULTI_CHIP
extern "C" void WDOGn_Feed(WDOG_TypeDef *wdog);
void WDOG_Feed() {
	WDOGn_Feed(WDOG0);
}

inline void WDOGWR(unsigned int currloop)
{
    if (!(currloop % 4096))
        WDOG_Feed();
}

inline unsigned long loopsToMcs(unsigned long loops)
{
    if (!loops)
        return 0;
    /*
    loops *= 366UL;
    loops -= 1110UL;
    loops /= 1000UL;*/
    loops *= 443;
    loops -= 6482;
    loops /= 1000;
    return loops;
}

inline unsigned long mcsToLoops(unsigned long mcs)
{
    if (!mcs)
        return 0;
    
    mcs *= 1000UL;
    mcs += 1110UL;
    mcs /= 366UL;
    /*mcs *= 1000;
    mcs -= 7080;
    mcs /= 443;*/
    return mcs;
}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    //timeout = mcsToLoops(timeout);
    unsigned long maxloops = mcsToLoops(timeout) * 3;
    unsigned long width = 0;
    int real_port = ZUNO_PIN_DEFS[pin].port;
    int real_pin = ZUNO_PIN_DEFS[pin].pin;
    int mask = 1<<real_pin;

    // wait for any previous pulse to end
    while (((GPIO->P[real_port].DIN & mask) != 0) == state)
    {
        WDOGWR(maxloops);
        if (--maxloops == 0)
            return 0;
    }

    // wait for the pulse to start
    while (((GPIO->P[real_port].DIN & mask) != 0) != state)
    {
        //WDOGWR(maxloops);
        WDOGWR(maxloops);
        if (--maxloops == 0)
            return 0;
    }
    // wait for the pulse to stop
    while (((GPIO->P[real_port].DIN & mask) != 0) == state) 
    {
        WDOGWR(maxloops);
        if (++width == maxloops)
            return 0;
    }
    return loopsToMcs(width);
}


void _zme_memcpy(byte * dst, byte * src, byte count)
{
    // Serial0.println(*src);
    src += (count - 1);
    while(count--) 
    {
        *dst = *src;
        // Serial0.println(*src);
        src--;
        dst++;
    }
}
uint32_t    zunoMapPin2EM4Int(uint8_t em4_pin){
    uint32_t real_pin = getRealPin(em4_pin);
    return (1 << real_pin);
}

// MULTI_CHIP
#if defined(_GPIO_EM4WUPOL_MASK)
uint32_t zunoMapPin2EM4Bit(uint8_t em4_pin) {
	uint8_t								real_pin;
	uint32_t							mask;
	static constexpr uint32_t			mask_default = 0x0;

	real_pin = getRealPin(em4_pin);
	switch (getRealPort(em4_pin)) {
		case gpioPortB:
			switch (real_pin) {
				case 0x1://PB01
					mask = GPIO_IEN_EM4WUIEN3;
					break ;
				case 0x3://PB03
					mask = GPIO_IEN_EM4WUIEN4;
					break ;
				default:
					mask = mask_default;
					break ;
			}
			break ;
		case gpioPortC:
			switch (real_pin) {
				case 0x0://PC00
					mask = GPIO_IEN_EM4WUIEN6;
					break ;
				case 0x5://PC05
					mask = GPIO_IEN_EM4WUIEN7;
					break ;
				case 0x7://PC07
					mask = GPIO_IEN_EM4WUIEN8;
					break ;
				default:
					mask = mask_default;
					break ;
			}
			break ;
		case gpioPortD:
			switch (real_pin) {
				case 0x2://PD02
					mask = GPIO_IEN_EM4WUIEN9;
					break ;
				case 0x5://PD05
					mask = GPIO_IEN_EM4WUIEN10;
					break ;
				default:
					mask = mask_default;
					break ;
			}
			break ;
		default:
			mask = mask_default;
			break ;
	}
	return (mask);
}
#elif defined(_GPIO_EXTILEVEL_MASK)
uint32_t    zunoMapPin2EM4Bit(uint8_t em4_pin){
    uint32_t real_pin = getRealPin(em4_pin);
    switch (getRealPort(em4_pin)) {
        case 0:// PA3
            if (real_pin == 3)
                return GPIO_EXTILEVEL_EM4WU8;
            break ;
        case 1://PB13
            if (real_pin == 13)
                return GPIO_EXTILEVEL_EM4WU9;
            break ;
        case 2://PC10
            if (real_pin == 10)
                return GPIO_EXTILEVEL_EM4WU12;
            break ;
        case 3://PD14
            if (real_pin == 14)
                return GPIO_EXTILEVEL_EM4WU4;
            break ;
        case 5:
            if (real_pin == 2) //PF2
                return GPIO_EXTILEVEL_EM4WU0;
            if (real_pin == 7) //PF7
                return GPIO_EXTILEVEL_EM4WU1;
            break ;
    }
    return 0;
}
#endif

ZunoError_t zunoEM4EnablePinWakeup(uint8_t em4_pin, uint32_t mode, uint32_t polarity){
    pinMode(em4_pin, mode);
    uint32_t wu_map = zunoMapPin2EM4Bit(em4_pin);
    if(wu_map == 0){
        return ZunoErrorInvalidPin;
    }
    g_sleep_data.em4_map |= wu_map;
    GPIO_EM4EnablePinWakeup(wu_map, polarity);
    return ZunoErrorOk;
}

// MULTI_CHIP
void zunoClearEm4Wakeup() {
	#if defined(_GPIO_EM4WUPOL_MASK)
	GPIO->EM4WUPOL = _GPIO_EM4WUPOL_RESETVALUE;
	#elif defined(_GPIO_EXTILEVEL_MASK)
	GPIO->EXTILEVEL = _GPIO_EXTILEVEL_RESETVALUE;
	#endif
  GPIO->EM4WUEN  = 0;                /* Disable wakeup. */
}
ZunoError_t zunoEM4EnablePinWakeup(uint8_t em4_pin) {
    return zunoEM4EnablePinWakeup(em4_pin, INPUT_PULLUP_FILTER, 0);
}


long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
long random(long min, long max){
    long t = (long)rand();
    return min + t % (max-min);
}
long random(long max){
    return random(0, max);
}
void randomSeed(long seed){
    srand(seed);
}
bool zunoPTIConfigUART(uint8_t tx_pin, uint32_t baud){
    RAIL_PtiConfig_t cfg;
    memset(&cfg, 0, sizeof(RAIL_PtiConfig_t));
    cfg.mode = RAIL_PTI_MODE_UART_ONEWIRE; //RAIL_PTI_MODE_UART; //RAIL_PTI_MODE_UART_ONEWIRE;
    cfg.baud = baud;

    cfg.doutPort = getRealPort(tx_pin);
    cfg.doutPin = getRealPin(tx_pin);
    uint8_t loc  = getLocation(g_loc_pa0_pf7_all, sizeof(g_loc_pa0_pf7_all), tx_pin);
    if(loc == INVALID_PIN_INDEX)
        return false;
    loc = loc ? loc - 1 : MAX_VALID_PINLOCATION;
    cfg.doutLoc = loc;
    uint8_t test_pin = 13;
    cfg.dframePort = getRealPort(test_pin);
    cfg.dframePin = getRealPin(test_pin);
    loc  = getLocation(g_loc_pa0_pf7_all, sizeof(g_loc_pa0_pf7_all), test_pin);
    loc = (loc>=2) ? loc-2 : 30 + loc;
    cfg.dframeLoc = loc;
    uint32_t res =  (uint32_t)zunoSysCall(ZUNO_SYSFUNC_PTI_CONFIG, 1, &cfg);
    #ifdef LOGGING_DBG
    LOGGING_UART.print("ZUNO PTI LOC:");
    LOGGING_UART.println(loc);
    LOGGING_UART.print("ZUNO PTI RES:");
    LOGGING_UART.println(res);
    #endif
    return res == 0;
}
void zunoPTIDisable(){
    zunoSysCall(ZUNO_SYSFUNC_PTI_CONFIG, 1, NULL);
}
void zunoStartRadioTest(RadioTestType_t mode, ZWaveRegion_t region, uint32_t timeout, uint8_t power, uint8_t channel) {
    RadioTestFuncParams_t rt_params;
    rt_params.mode = mode;
    rt_params.region = region;
    rt_params.power = power;
    rt_params.channel = channel;
    rt_params.timeout_ms = timeout;
    zunoSysCall(ZUNO_SYSFUNC_RADIOTEST, 1, &rt_params);
}
uint8_t zmeMapDict(uint8_t * dict, uint8_t size, uint8_t key, bool back){
	for(int i=0;i<size;i+=2){
		if(back){
			if(dict[i+1] == key)
				return dict[i];
		} else {
			if(dict[i] == key)
				return dict[i+1];
		}
	}
	return INVALID_VALUE;
}
void zunoUpdateSysConfig(bool deffered, bool force){
	uint32_t flags = 0;
	if(deffered)
		flags |= 0x01;
	if(force)
		flags |= 0x02;
	zunoSysCall(ZUNO_SYSFUNC_COMMIT_DEVCFG, 1, flags);
}
extern "C" void __cxa_pure_virtual() { 
    #ifdef LOGGING_DBG
    LOGGING_UART.println("ZUNO:PURE VIRTUAL CALL!");
    #endif
    while (1); 	
}

int main(){

    return 0;

}