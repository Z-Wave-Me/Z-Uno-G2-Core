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
#include "em_rtcc.h"
#include "em_adc.h"
#include "em_gpio.h"


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

#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
    #pragma message "ZUNO_ASSEMBLY_TYPE == ZUNO_UNO"
#elif ZUNO_ASSEMBLY_TYPE == ZUNO_RASBERI
    #pragma message "ZUNO_ASSEMBLY_TYPE == ZUNO_RASBERI"
#elif ZUNO_ASSEMBLY_TYPE == ZUNO_BOOTLOADER
    #pragma message "ZUNO_ASSEMBLY_TYPE == ZUNO_BOOTLOADER"
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

#ifndef ZUNO_SKETCH_BUILD_TS
#define ZUNO_SKETCH_BUILD_TS 0
#endif
#ifndef DBG_CONSOLE_PIN
#ifdef LOGGING_DBG
    #if ZUNO_PIN_V == 0
    #define DBG_CONSOLE_PIN 0x27 // C7
    #elif ZUNO_PIN_V == 1
    #define DBG_CONSOLE_PIN 0x00 // A0  
    #elif ZUNO_PIN_V == 2
    #define DBG_CONSOLE_PIN 0x00 // A0
    #elif ZUNO_PIN_V == 3
    #define DBG_CONSOLE_PIN 0x2B // C11
    #elif ZUNO_PIN_V == 4
    #define DBG_CONSOLE_PIN 0x3D // D13
    #elif ZUNO_PIN_V == 6
    #define DBG_CONSOLE_PIN 0x3D // D13
    #else
    #define DBG_CONSOLE_PIN 0xFF
    #endif 
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
                                                                                    SKETCH_VERSION,
                                                                                    ZUNO_EXT_FIRMWARES_COUNT,
                                                                                    ZUNO_EXT_FIRMWARES_DESCR_PTR,
                                                                                    ZUNO_OTA_PIN,
                                                                                    ZUNO_CUSTOM_OTA_OFFSET,
                                                                                    ZUNO_SKETCH_NAME};

// from ZWSupport.c
int zuno_CommandHandler(ZUNOCommandPacket_t * cmd); 
void zuno_CCTimer(uint32_t);
// A = 0
// B = 1
// C = 2
// D = 3
// E = 4
// F = 5
#if ZUNO_PIN_V == 0
// "SDKBOARD" map
#pragma message "ZUNO_PIN_V==0. SDK BOARD"
const PinDef_t ZUNO_PIN_DEFS[] = {
   // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {5, 2},//2 - PF2  - 2 
    {5, 3},//3 - PF6 - A0 
    {5, 6},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {0, 0},//7 - PF4 - 7
    {0, 1},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {3, 14},//11 - PD14 - 11
    {3, 15},//12 - PD15 - 12
    {0, 0},//13 - PA0 - PWM1 and ARDURINO LED
    {0, 1},//14 - PA1 - PWM2
    {0, 2},//15 - PA2 - PWM3
    {0, 3},//16 - PA3 - PWM4
    {0, 4},//17 - PA4 - 17
    {1, 13},//18 - PB13 - 18
    {1, 12},//19 - PB12 - 19 
    {1, 11},//20 - PB11 - 20 
    {2, 6},//21 - PC6 - 21
    {0, 0},//22 - PC7 - 22
    {5, 7},//23 - PF7 - BTN
    {2, 7},//24 - PD13 - TX0
    {2, 11},//25 - PC11 - RX0
    // DO NOT USE !!!
    {0, 1},//26 - PA5 - USB Serial rx
    {0, 0},//27 - PF3 - USB Serial tx
    {5, 4},//28 - PB15 - green
    {5, 5}//29 - PB14 - red
};

#elif ZUNO_PIN_V == 1
// "NIKBOARD" map
#pragma message "ZUNO_PIN_V==1"
const PinDef_t ZUNO_PIN_DEFS[] = {
    // LEFT SIDE
    {1, 14},  //  0 - B14
    {1, 15}, //  1 - B15
    {2, 6},  //  2 - C6
    {2, 7},  //  3 - C7
    {2, 8},  //  4 - C8
    {2, 9},  //  5 - C9 (UART_USB_RX)
    {2, 10}, //  6 - C10
    {2, 11}, //  7 - C11
    {5, 0},  //  8 - F0 (SCLK)
    {5, 1},  //  9 - F1 (SDIO)
    {5, 2},  // 10 - F2 (SWO)
    {5, 3},  // 11 - F3 (UART_USB_TX)
    {5, 4},  // 12 - F4 (LED)
    {5, 5},  // 13 - F5
    {5, 6},  // 14 - F6
    {5, 7},  // 15 - F7 (BTN)
    // RIGHT SIDE
    {3, 9},  //  16 - D9
    {3, 10}, //  17 - D10
    {3, 11}, //  18 - D11
    {3, 12}, //  19 - D12
    {3, 13}, //  20 - D13
    {3, 14}, //  21 - D14
    {3, 15}, //  22 - D15
    {0, 0},  //  23 - A0 (tX)
    {0, 1},  //  24 - A1 (rX)
    {0, 2},  //  25 - A2 (ADC0)
    {0, 3},  //  26 - A3 
    {0, 4},  //  27 - A4
    {0, 5},  //  28 - A5
    {1, 11}, //  29 - B11 
    {1, 12}, //  30 - B12
    {1, 13}, //  31 - B13
    
};
#elif ZUNO_PIN_V == 2
#pragma message "ZUNO_PIN_V==2"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {2, 10},//2 - PC10 - 2 
    {5, 6},//3 - PF6 - A0 
    {5, 7},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {5, 4},//7 - PF4 - 7
    {5, 5},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {0, 0},//11 - PA0
    {0, 1},//12 - PA1
    {0, 2},//13 - PA2 - ARDURINO LED - blue and PWM1
    {0, 3},//14 - PA3 - PWM2
    {0, 4},//15 - PA4 - PWM3 
    {0, 5},//16 - PA5 - PWM4
    {1, 11},//17 - PB11 - 17 
    {1, 12},//18 - PB12 - 18 
    {1, 13},//19 - PB13 - 19 
    {1, 14},//20 - PB14 - 20 
    {1, 15},//21 - PB15 - 21 
    {2, 6},//22 - PC6 - 22 
    {2, 7},//23 - PC7 - BTN
    {2, 11},//24 - PC11 - TX0 
    {5, 3},//25 - PF3 - RX0 
    // DO NOT USE !!!
    {3, 13},//26 - PD13 - USB Serial rx
    {5, 2},//27 - PF2 - USB Serial tx
    {3, 15},//28 - PD15 - green
    {3, 14}//29 - PD14 - red
};
#elif ZUNO_PIN_V == 3
#pragma message "ZUNO_PIN_V==3"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {2, 10},//2 - PC10 - 2 
    {5, 6},//3 - PF6 - A0 
    {5, 7},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {5, 4},//7 - PF4 - 7
    {5, 5},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {3, 14},//11 - PD14 - 11
    {3, 15},//12 - PD15 - 12
    {0, 0},//13 - PA0 - PWM1  
    {0, 1},//14 - PA1 - PWM2
    {0, 2},//15 - PA2 - PWM3 and ARDURINO LED
    {0, 3},//16 - PA3 - PWM4
    {0, 4},//17 - PA4 - 17
    {0, 5},//18 - PA5 - 18
    {1, 11},//19 - PB11 - 19 
    {1, 12},//20 - PB12 - 20 
    {1, 13},//21 - PB13 - 21 
    {1, 14},//22 - PB14 - 22 
    {2, 7},//23 - PC7 - BTN
    {2, 11},//24 - PC11 - TX0
    {3, 13},//25 - PD13 - RX0
    // DO NOT USE !!!
    {5, 2},//26 - PF2 - USB Serial tx
    {5, 3},//27 - PF3 - USB Serial rx
    {2, 6},//28 - PC6 - green
    {1, 15}//29 - PB15 - red
};
#elif ZUNO_PIN_V == 4
#pragma message "ZUNO_PIN_V==4"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {5, 2},//2 - PF2  - 2 
    {5, 6},//3 - PF6 - A0 
    {5, 7},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {5, 4},//7 - PF4 - 7
    {5, 5},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {3, 14},//11 - PD14 - 11
    {3, 15},//12 - PD15 - 12
    {0, 0},//13 - PA0 - PWM1 and ARDURINO LED
    {0, 1},//14 - PA1 - PWM2
    {0, 2},//15 - PA2 - PWM3
    {0, 3},//16 - PA3 - PWM4
    {0, 4},//17 - PA4 - 17
    {1, 11},//18 - PB11 - 18
    {1, 12},//19 - PB12 - 19 
    {1, 13},//20 - PB13 - 20 
    {2, 6},//21 - PC6 - 21
    {2, 7},//22 - PC7 - 22
    {2, 10},//23 - PC10 - BTN
    {3, 13},//24 - PD13 - TX0
    {2, 11},//25 - PC11 - RX0
    // DO NOT USE !!!
    {0, 5},//26 - PA5 - USB Serial rx
    {5, 3},//27 - PF3 - USB Serial tx
    {1, 15},//28 - PB15 - green
    {1, 14}//29 - PB14 - red
};
#elif ZUNO_PIN_V == 6
#pragma message "ZUNO_PIN_V==6"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    // LEFT SIDE
    {2, 8},//0 - PC8 - 0 
    {2, 9},//1 - PC9 - 1 
    {5, 2},//2 - PF2  - 2 
    {5, 6},//3 - PF6 - A0 
    {5, 7},//4 - PF7 - A1 
    {3, 9},//5 - PD9 - A2 
    {3, 10},//6 - PD10 -A3
    {5, 4},//7 - PF4 - 7
    {5, 5},//8 - PF5 - 8
    // RIGHT SIDE
    {3, 11},//9 - PD11 - 9
    {3, 12},//10 - PD12 - 10
    {3, 14},//11 - PD14 - 11
    {3, 15},//12 - PD15 - 12
    {0, 0},//13 - PA0 - PWM1 and ARDURINO LED
    {0, 1},//14 - PA1 - PWM2
    {0, 2},//15 - PA2 - PWM3
    {0, 3},//16 - PA3 - PWM4
    {0, 4},//17 - PA4 - 17
    {1, 13},//18 - PB13 - 18
    {1, 12},//19 - PB12 - 19 
    {1, 11},//20 - PB11 - 20 
    {2, 6},//21 - PC6 - 21
    {2, 7},//22 - PC7 - 22
    {2, 10},//23 - PC10 - BTN
    {3, 13},//24 - PD13 - TX0
    {2, 11},//25 - PC11 - RX0
    // DO NOT USE !!!
    {0, 5},//26 - PA5 - USB Serial rx
    {5, 3},//27 - PF3 - USB Serial tx
    {1, 15},//28 - PB15 - green
    {1, 14}//29 - PB14 - red
};
#elif ZUNO_PIN_V == 1000
// Rasberi v0
#pragma message "ZUNO_PIN_V==1000"
const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
    {0, 0},//0 - A0 (tX)
    {0, 1},//1 - A1 (rX)
    {2, 7},//2 - PC7 - green
    {2, 8},//3 - PC8 - red
};
#else
    #error ZUNO_PIN_V
#endif

/*
typedef void zuno_user_systimer_handler(uint32_t);
typedef void zuno_user_sysevent_handler(ZUNOSysEvent_t * ev);
*/

ZUNOSetupSysState_t * g_zuno_sys;
ZUNOOnDemandHW_t g_zuno_odhw_cfg;
ZUNOSleepData_t g_sleep_data;
// prototypes 
void loop();
void setup();

extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));
extern void (*__fini_array_start []) (void) __attribute__((weak));
extern void (*__fini_array_end []) (void) __attribute__((weak));

void LLInit() {  
    #ifndef NO_DEFAULT_PIN_SETUP
    for (int i=0; i <= ZUNO_PIN_LAST_INDEX; i++){
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
    for (uint32_t * b = (uint32_t *)&__preinit_array_start; b < ((uint32_t *)&__preinit_array_end); b++) {
        ((void (*)())b[0])();
        WDOG_Feed();
    }
    for (uint32_t * b = (uint32_t *)&__init_array_start; b < ((uint32_t *)&__init_array_end); b++) {
        ((void (*)())b[0])();
        WDOG_Feed();
    }
    // default configuration values
    g_zuno_odhw_cfg.adc_reference  = adcRef5V;
    g_zuno_odhw_cfg.adc_resolution = 10; // 
    g_zuno_odhw_cfg.adc_acqtime = adcAcqTime256;
    g_zuno_odhw_cfg.pwm_resolution = 8;
    g_zuno_odhw_cfg.pwm_freq = PWM_FREQ_DEFAULT;

}

void LLDestroy() {
}

#ifdef WITH_AUTOSETUP
// this is managing using "preproc" util
void zuno_static_autosetup();
#endif

#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
void _zunoSysSleep();
#endif

#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
static void _zunoInitSleepingData();
static void _zunoSleepingUpd();
static void _zunoInitDefaultWakeup();
static void _zunoCheckWakeupBtn();

#endif
void zunoKickSleepTimeout(uint32_t ms);
void _zunoSleepOnInclusionStart();
void _zunoSleepOnInclusionComplete();



#ifdef LOGGING_DBG
bool g_logging_inited = false;
#endif
bool g_sketch_inited = false;
#ifdef WITH_CC_WAKEUP
void zuno_CCWakeup_OnInclusionStart();
void zuno_CCWakeup_OnInclusionComplete();
void zuno_CCWakeup_OnSetup();
#endif
#ifdef WITH_CC_BATTERY
void _zunoSleepOnFWUpgradeStop();
void _zunoSleepOnFWUpgradeStart();
#endif
void initCCSDataDefault();
void * zunoJumpTable(int vec, void * data) {
  
    byte sub_handler_type = 0x00;
    /*
    // DBG CODE
    static uint32_t pl = 0;
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    delayMicroseconds(50000);
    //delayMicroseconds(50000);
    //delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delayMicroseconds(50000);
    //delayMicroseconds(50000);
    //delay(100);
    pl++;
    return (void*)pl; // 
    */
    switch(vec){
        case ZUNO_JUMPTBL_SETUP:
            LLInit();
            g_zuno_sys = (ZUNOSetupSysState_t*)data;
            #ifdef WITH_AUTOSETUP
            zuno_static_autosetup();
            #endif
            #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
            _zunoInitSleepingData();
            _zunoInitDefaultWakeup();
            #endif
            #ifdef LOGGING_DBG
            LOGGING_UART.begin(115200);
            #endif
            g_sketch_inited = false;
            break;
        case ZUNO_JUMPTBL_LOOP:
            if(!g_sketch_inited){
                ZWCCSetup();
                setup();
                g_sketch_inited = true;
            }
            loop();
            #if (SKETCH_FLAGS_LOOP_DELAY>0)
            delay(SKETCH_FLAGS_LOOP_DELAY); // to avoid starvation
            #endif
            break;
        case ZUNO_JUMPTBL_CMDHANDLER:
            return (void*)zuno_CommandHandler((ZUNOCommandPacket_t *) data);
        
        case ZUNO_JUMPTBL_SYSEVENT:{
                ZUNOSysEvent_t * evnt = (ZUNOSysEvent_t *)data;
                #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
                if(evnt->event == ZUNO_SYS_EVENT_LEARNSTARTED){
                    zunoKickSleepTimeout(ZUNO_SLEEP_INCLUSION_TIMEOUT);
                     _zunoSleepOnInclusionStart();
                }
                if(evnt->event == ZUNO_SYS_EVENT_OTA_STARTED){
                    _zunoSleepOnFWUpgradeStart();
                }
                if(evnt->event == ZUNO_SYS_EVENT_OTA_FINISHED){
                    _zunoSleepOnFWUpgradeStop();
                }
                if(evnt->event == ZUNO_SYS_EVENT_LEARNSTATUS){
                    //if(evnt->params[0] == INCLUSION_STATUS_IN_PROGRESS)
                    //else 
                    if(evnt->params[0] == INCLUSION_STATUS_SUCESS)
                        zunoKickSleepTimeout(ZUNO_SLEEP_INTERVIEW_TIMEOUT);
                    _zunoSleepOnInclusionComplete();
                       
                }
                #endif
                // Clean when device was excluded
                if( (evnt->event == ZUNO_SYS_EVENT_LEARNSTATUS) && 
                    (evnt->params[0] == INCLUSION_STATUS_SUCESS) && 
                    (evnt->params[1] == 0)){
                    initCCSDataDefault();
                }
                #ifdef LOGGING_DBG
                LOGGING_UART.print("[");
                LOGGING_UART.print(millis());
                LOGGING_UART.print("] "); 
                LOGGING_UART.print("SYSEVENT: ");
                LOGGING_UART.print(evnt->event, HEX);
                LOGGING_UART.print(" ARGS: ");
                LOGGING_UART.print(evnt->params[0], HEX);
                LOGGING_UART.print(" ");
                LOGGING_UART.println(evnt->params[1], HEX);
                #endif
                (void)evnt;
            }
            break;
       
        case ZUNO_JUMPTBL_SYSTIMER:
            zuno_CCTimer((uint32_t)data);
            #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
            _zunoSleepingUpd();
            #endif
            break;
        case ZUNO_JUMPTBL_IRQ:{
                IOQueueMsg_t * p_msg = (IOQueueMsg_t *)data;
                sub_handler_type = p_msg->type;
            }
            break;
        case ZUNO_JUMPTBL_SLEEP:
            #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
            _zunoSysSleep();
            #endif
            #ifdef LOGGING_DBG
            //LOGGING_UART.println("!SLEEP");
            #endif
            break;
        case ZUNO_JUMPTBL_WUP:
            #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
            _zunoInitSleepingData();
            _zunoCheckWakeupBtn();
            #endif
            ZWCCSetup();

            break;
        default:
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
void zunoStartLearn(byte timeout, bool secured){
    zunoSysCall(ZUNO_SYSFUNC_LEARN, 2, timeout, secured);
}
void zunoResetLocally(){
    zunoSysCall(ZUNO_SYSFUNC_SETDEFAULT, 1, 0);   
}
void zunoSendNIF(){
    zunoSysCall(ZUNO_SYSFUNC_SENDNIF, 0);   
}

/* time */
void delay(dword ms){
    zunoSysCall(ZUNO_SYSFUNC_DELAY_MS, 1, ms);
}


uint64_t rtcc_micros(void) {
	uint32_t			tic1;
	uint32_t			tic2;
	uint32_t			overflow;
	uint64_t			out;

	tic1 = RTCC_CounterGet();
	overflow = RTCC->RET[0x1F].REG;// overflow = RTCC->RET[0x1F].REG;
	tic2 = RTCC_CounterGet();
	if (tic2 < tic1) {
		tic1 = tic2;
		overflow++;
	}
	out = overflow;
	out = (out << 0x20) | tic1;
	out = (out * 1000000) >> 0xF;//DIV1 - 32768 - freq
	return (out);
}

bool zunoIsValidDate(void) {
	if (RTCC->RET[0x1E].REG == 0x0)
		return (false);
	return (true);
}

time_t zunoGetTimeStamp(void) {
	return (RTCC->RET[0x1E].REG + ZUNO_SKETCH_BUILD_TS + (rtcc_micros() / 1000000));
}

void zunoSetTimeStamp(time_t timeUnix) {
	RTCC->RET[0x1E].REG = timeUnix - ZUNO_SKETCH_BUILD_TS -  (rtcc_micros() / 1000000);
}

dword millis(void){
	return (dword)(rtcc_micros() / 1000);
}
// JUST A STUB...
dword micros(void){
	return (dword)(rtcc_micros());
}

void delayMicroseconds(word tdelay){
    while(tdelay--){
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
   }
}


/* pin */
void pinMode(uint8_t pin, int mode){
    GPIO_PinModeSet((GPIO_Port_TypeDef)getRealPort(pin), getRealPin(pin), (GPIO_Mode_TypeDef)(mode & 0x0F), ((mode & 0x100) != 0) ? true : false);
}

uint8_t pin2HWPin(uint8_t pin) {
    return ((ZUNO_PIN_DEFS[pin].port << 4) | (ZUNO_PIN_DEFS[pin].pin));
}

void digitalWrite(uint8_t pin, uint8_t mode) {
    uint8_t						real_port;
    uint8_t						real_pin;

    real_port = getRealPort(pin);
    real_pin = getRealPin(pin);
    if (mode == true)
        GPIO_PinOutSet((GPIO_Port_TypeDef)real_port, real_pin);
    else
        GPIO_PinOutClear((GPIO_Port_TypeDef)real_port, real_pin);
}

uint8_t getPin(uint8_t port, uint8_t pin) {
    const PinDef_t			*lp_b;
    const PinDef_t			*lp_e;

    lp_b = &ZUNO_PIN_DEFS[0];
    lp_e = &ZUNO_PIN_DEFS[sizeof(ZUNO_PIN_DEFS) / sizeof(PinDef_t)];
    while (lp_b < lp_e) {
        if (lp_b->port == port && lp_b->pin == pin)
            return (lp_b - &ZUNO_PIN_DEFS[0]);
        lp_b++;
    }
    return (INVALID_PIN_INDEX);
}

uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin) {
    size_t				i;

    i = 0;
    pin = (getRealPort(pin) << 4) | getRealPin(pin);
    while (i < count) {
        if (location[i] == pin)
            return (i);
        i++;
    }
    return 0xFF;
}

size_t getLocationTimer0AndTimer1Chanell(uint8_t pin, uint8_t ch) {
    size_t				loc;

    loc = getLocation(&g_loc_pa0_pf7_all[0], sizeof(g_loc_pa0_pf7_all), pin);
    loc = (loc + 32 - ch) & 0x1F;
    ch <<= 3;
    return (loc << ch);
}
inline ADC_Res_TypeDef  __adc_resolution2Mode(uint8_t res){
    if(res > 8)
        return adcRes12Bit;
    if(res > 6)
        return adcRes8Bit;
    return 	adcRes6Bit;
}
inline uint8_t  __adc_resolution2RealBits(uint8_t res){
    if(res > 8)
        return 12;
    if(res > 6)
        return 8;
    return 	6;
} 
inline uint32_t __oversampleValue(uint32_t v, uint8_t src, uint8_t dst){
    if(src > dst)
        return v >> (src - dst);
    return v << (dst - src);
}
void analogReference(ADC_Ref_TypeDef ref){
    g_zuno_odhw_cfg.adc_reference = ref;
}
void analogReadResolution(uint8_t bits){
    g_zuno_odhw_cfg.adc_resolution = bits;
}
void analogAcqTime(ADC_AcqTime_TypeDef acqtime){
    g_zuno_odhw_cfg.adc_acqtime = acqtime;
}

ADC_PosSel_TypeDef zme_ADC_PIN2Channel(uint8_t pin) {
	ADC_PosSel_TypeDef				out;

	switch(pin) {
		case 21://PC6
			out = adcPosSelAPORT1XCH6;
			break ;
		case 22://PC7
			out = adcPosSelAPORT1YCH7;
			break ;
		case 0://PC8
			out = adcPosSelAPORT1XCH8;
			break ;
		case 1://PC9
			out = adcPosSelAPORT1YCH9;
			break ;
		case 23://PC10
			out = adcPosSelAPORT1XCH10;
			break ;
		case 25://PC11
			out = adcPosSelAPORT1YCH11;
			break ;
		case 2://PF2
			out = adcPosSelAPORT1XCH18;
			break ;
		case 7://PF4
			out = adcPosSelAPORT1XCH20;
			break ;
		case 8://PF5
			out = adcPosSelAPORT1YCH21;
			break ;
		case 3://PF6
			out = adcPosSelAPORT1XCH22;
			break ;
		case 4://PF7
			out = adcPosSelAPORT1YCH23;
			break ;
		case 5://PD9
			out = adcPosSelAPORT3YCH1;
			break ;
		case 6://PD10
			out = adcPosSelAPORT3XCH2;
			break ;
		case 9://PD11
			out = adcPosSelAPORT3YCH3;
			break ;
		case 10://PD12
			out = adcPosSelAPORT3XCH4;
			break ;
		case 24://PD13
			out = adcPosSelAPORT3YCH5;
			break ;
		case 11://PD14
			out = adcPosSelAPORT3XCH6;
			break ;
		case 12://PD15
			out = adcPosSelAPORT3YCH7;
			break ;
		case 13://PA0
			out = adcPosSelAPORT3XCH8;
			break ;
		case 14://PA1
			out = adcPosSelAPORT3YCH9;
			break ;
		case 15://PA2
			out = adcPosSelAPORT3XCH10;
			break ;
		case 16://PA3
			out = adcPosSelAPORT3YCH11;
			break ;
		case 17://PA4
			out = adcPosSelAPORT3XCH12;
			break ;
		default:
			out = adcPosSelAVDD;
			break ;
	}
	return (out);
}

void zmeADCInit() {
	ADC_Init_TypeDef				adcInit;

	if(!g_zuno_odhw_cfg.ADCInitialized){
		adcInit = ADC_INIT_DEFAULT;
		CMU_ClockEnable(cmuClock_HFPER, true);
		CMU_ClockEnable(cmuClock_ADC0, true);
		CMU->ADCCTRL = CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO;// Select AUXHFRCO for ADC ASYNC mode so that ADC can run on EM2
		CMU_AUXHFRCOBandSet(cmuAUXHFRCOFreq_4M0Hz);
		adcInit.timebase = ADC_TimebaseCalc(0);
		adcInit.prescale = ADC_PrescaleCalc(CMU_AUXHFRCOBandGet(), 0);
		adcInit.em2ClockConfig = adcEm2ClockOnDemand;
		ADC_Init(ADC0, &adcInit);
		g_zuno_odhw_cfg.ADCInitialized = true;
	}
}

int analogRead(uint8_t pin) {
	uint32_t								sampleValue;
	ADC_InitSingle_TypeDef					singleInit;

	zmeADCInit();
	singleInit = ADC_INITSINGLE_DEFAULT;
	// Init for single conversion use, use 5V reference
	singleInit.reference  = (ADC_Ref_TypeDef)g_zuno_odhw_cfg.adc_reference;
	singleInit.posSel     = zme_ADC_PIN2Channel(pin);
	singleInit.resolution = __adc_resolution2Mode(g_zuno_odhw_cfg.adc_resolution);
	singleInit.acqTime    = (ADC_AcqTime_TypeDef)g_zuno_odhw_cfg.adc_acqtime;
	ADC_InitSingle(ADC0, &singleInit);
	ADC_Start(ADC0, adcStartSingle);
	while (ADC0->STATUS & ADC_STATUS_SINGLEACT)
		;
	sampleValue = ADC_DataSingleGet(ADC0);
	ADC0->CMD = ADC_CMD_SINGLESTOP;
	return (__oversampleValue(sampleValue, __adc_resolution2RealBits(g_zuno_odhw_cfg.adc_resolution), g_zuno_odhw_cfg.adc_resolution));
}


/* Handler */
ZunoError_t zunoAttachSysHandler(byte type, byte sub_type, void *handler) {
    HandlerFunc_t				*lp_b;
    HandlerFunc_t				*lp_e;
    uint16_t					code_offset;

    code_offset = (uint16_t)((uint32_t)(((byte*)handler) - ZUNO_CODE_START)) & 0xFFFF;
    lp_e = &g_zuno_odhw_cfg.h_sys_handler[MAX_AVAILIABLE_SYSHANDLERS];
    lp_b = lp_e - MAX_AVAILIABLE_SYSHANDLERS;
    while (lp_b < lp_e) {
        if (lp_b->main_type == type && lp_b->sub_type == sub_type && lp_b->code_offset == code_offset)
            return (ZunoErrorOk);
        lp_b++;
    }
    lp_b = lp_e - MAX_AVAILIABLE_SYSHANDLERS;
    while (lp_b < lp_e) {
        if (lp_b->code_offset == 0) {
            lp_b->main_type = type;
            lp_b->sub_type = sub_type;
            lp_b->code_offset = code_offset;
            return (ZunoErrorOk);
        }
        lp_b++;
    }
    return (ZunoErrorAttachSysHandler);
}

ZunoError_t zunoDetachSysHandler(byte type, byte sub_type, void *handler) {
    HandlerFunc_t				*lp_b;
    HandlerFunc_t				*lp_e;
    uint16_t					code_offset;

    code_offset = (uint16_t)((uint32_t)(((byte*)handler) - ZUNO_CODE_START)) & 0xFFFF;
    lp_e = &g_zuno_odhw_cfg.h_sys_handler[MAX_AVAILIABLE_SYSHANDLERS];
    lp_b = lp_e - MAX_AVAILIABLE_SYSHANDLERS;
    while (lp_b < lp_e) {
        if (lp_b->main_type == type && lp_b->sub_type == sub_type && lp_b->code_offset == code_offset) {
            lp_b->code_offset = 0;
            return (ZunoErrorOk);
        }
        lp_b++;
    }
    return (ZunoErrorAttachSysHandler);
}

ZunoError_t zunoDetachSysHandlerAllSubType(byte type, byte sub_type) {
    HandlerFunc_t				*lp_b;
    HandlerFunc_t				*lp_e;
    ZunoError_t					out;

    out = ZunoErrorAttachSysHandler;
    lp_e = &g_zuno_odhw_cfg.h_sys_handler[MAX_AVAILIABLE_SYSHANDLERS];
    lp_b = lp_e - MAX_AVAILIABLE_SYSHANDLERS;
    while (lp_b < lp_e) {
        if (lp_b->main_type == type && lp_b->sub_type == sub_type) {
            lp_b->code_offset = 0;
            out = ZunoErrorOk;
        }
        lp_b++;
    }
    return (out);
}

void * zunoSysHandlerCall(uint8_t type, uint8_t sub_type, ...){
    uint8_t i;
    void * result = NULL;
    byte * base_addr;
    va_list args;
    for(i=0;i<MAX_AVAILIABLE_SYSHANDLERS;i++){
        if(g_zuno_odhw_cfg.h_sys_handler[i].code_offset == 0) // Empty handler
            continue;
        if((g_zuno_odhw_cfg.h_sys_handler[i].main_type == type) && 
            (g_zuno_odhw_cfg.h_sys_handler[i].sub_type  == sub_type || 
            g_zuno_odhw_cfg.h_sys_handler[i].sub_type == 0xFF)) // 0xFF is "wild card"
            {
                base_addr = (byte*) ZUNO_CODE_START;
                base_addr += g_zuno_odhw_cfg.h_sys_handler[i].code_offset;
                switch(type){
                    case ZUNO_HANDLER_SYSTIMER:
                        va_start (args, sub_type);
                        ((zuno_user_systimer_handler*)(base_addr))(va_arg(args,uint32_t));
                        va_end (args);
                        break;
                    #if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
                    case ZUNO_HANDLER_REPORT:
                        va_start (args, sub_type);
                        ((zuno_user_zuno_handler_report*)(base_addr))(va_arg(args,ReportAuxData_t *));
                        va_end (args);
                        break;
                    #endif
                    case ZUNO_HANDLER_SYSEVENT:
                        va_start (args, sub_type);
                        ((zuno_user_sysevent_handler*)(base_addr))(va_arg(args,ZUNOSysEvent_t*));
                        va_end (args);
                        break;
                    case ZUNO_HANDLER_IRQ:{
                            va_start (args, sub_type);
                            IOQueueMsg_t * p_msg = va_arg(args,IOQueueMsg_t *);
                            ((zuno_irq_handler*)(base_addr))((void*)p_msg->param);
                            va_end (args);
                        }
                        break;
                    case ZUNO_HANDLER_EXTINT:
                        va_start (args, sub_type);
                        ((zuno_void_handler_ext_int*)(base_addr))((uint8_t)va_arg(args,size_t));
                        va_end (args);
                        break;
                    case ZUNO_HANDLER_GPT:
                    case ZUNO_HANDLER_SLEEP:
                    case ZUNO_HANDLER_WUP:
                    case ZUNO_HANDLER_NOTIFICATON_TIME_STAMP:
                        ((zuno_void_handler*)(base_addr))();
                        break;
                    case ZUNO_HANDLER_ZW_CFG:
                        va_start (args, sub_type);
                        ((zuno_configuartionhandler_t*)(base_addr))((uint8_t)va_arg(args,uint32_t), va_arg(args,uint32_t));
                        va_end (args);
                        break;
                    case ZUNO_HANDLER_ZW_BATTERY:
                        result = (void*)(((zuno_battery_handler_t*)(base_addr))());
                        break;
                }
        }
    }
    return result;
}

void WDOG_Feed(){
  WDOG_TypeDef *wdog = WDOG0; // the default SDK watchdog
  /* The watchdog should not be fed while it is disabled */
  if (!(wdog->CTRL & WDOG_CTRL_EN)) {
    return;
  }

  /* If a previous clearing is being synchronized to LF domain, then there */
  /* is no point in waiting for it to complete before clearing over again. */
  /* This avoids stalling the core in the typical use case where some idle loop */
  /* keeps clearing the watchdog. */
  if (wdog->SYNCBUSY & WDOG_SYNCBUSY_CMD) {
    return;
  }
  /* Before writing to the WDOG_CMD register we also need to make sure that
   * any previous write to WDOG_CTRL is complete. */
  while ( (wdog->SYNCBUSY & WDOG_SYNCBUSY_CTRL) != 0U ) {
  }

  wdog->CMD = WDOG_CMD_CLEAR;
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

void zunoCommitCfg(){
    zunoSysCall(ZUNO_SYSFUNC_COMMIT_CONFIG, 0);
}

/*
bool 	 b_write = va_arg(lst, uint32_t) > 0;
            uint16_t addr  	 = va_arg(lst, uint32_t)&0x0ffff;
            uint16_t size  	 = va_arg(lst, uint32_t)&0x0ffff;
            uint8_t * p_data = va_arg(lst,uint8_t *);
            zme_EEPROM_io(g_zuno_state.file_system, addr, p_data, size, b_write);
*/


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
void zunoClearEm4Wakeup(){
  GPIO->EXTILEVEL = _GPIO_EXTILEVEL_RESETVALUE;
  GPIO->EM4WUEN  = 0;                /* Disable wakeup. */
}
ZunoError_t zunoEM4EnablePinWakeup(uint8_t em4_pin) {
    return zunoEM4EnablePinWakeup(em4_pin, INPUT_PULLUP_FILTER, 0);
}

#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
static void _zunoInitSleepingData(){
    g_sleep_data.timeout = ZUNO_SLEEP_INITIAL_TIMEOUT;
    g_sleep_data.user_latch = true;
    g_sleep_data.inclusion_latch = false;
    g_sleep_data.wup_latch = false;
    g_sleep_data.wup_timeout = 0;
    g_sleep_data.em4_map = 0;
    memset(g_sleep_data.sleep_timers, 0, sizeof(g_sleep_data.sleep_timers));
    g_sleep_data.user_sleep_ts = millis();
}
#endif

#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
static void _zunoCheckWakeupBtn(){
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
static void _zunoInitDefaultWakeup(){
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
void _zunoSysSleep(){
    GPIO_IntClear(g_sleep_data.em4_map);
    // Initialize wakeup timers
    uint32_t df = (millis() - g_sleep_data.user_sleep_ts) / 1000;
    for(int i=0;i<MAX_SLEEP_TIMERS;i++)
        if(g_sleep_data.sleep_timers[i]){
            uint32_t val = (g_sleep_data.sleep_timers[i] > df)? g_sleep_data.sleep_timers[i] - df : 1;
            zunoSysCall(ZUNO_SYSFUNC_PERSISTENT_TIMER_CONTROL, 2, i,  val);
        }
}

static void _zunoSleepingUpd(){
    #ifndef NO_BTN_CHECK_BEFORE_SLEEP
	if(!digitalRead(BUTTON_PIN))
        return; // Never spleep until button released
	#endif
    if(g_sleep_data.latch) {
        #ifdef LOGGING_DBG
        //LOGGING_UART.println("CAN'T SLEEP: INDICATOR ON");
        #endif
        return;
    }
    if(g_sleep_data.indicator_latch){
        #ifdef LOGGING_DBG
        //LOGGING_UART.println("CAN'T SLEEP: INDICATOR ON");
        #endif
        return;
    }
    if(g_sleep_data.user_latch){
        #ifdef LOGGING_DBG
        //LOGGING_UART.println("CAN'T SLEEP: ULATCH");
        #endif
        return;
    }
    if(g_sleep_data.inclusion_latch){
        #ifdef LOGGING_DBG
        //LOGGING_UART.println("CAN'T SLEEP: INCLUSION IN PROCESS");
        #endif
        return;
    }
    if(g_sleep_data.fwupd_latch){
        #ifdef LOGGING_DBG
        //LOGGING_UART.println("CAN'T SLEEP: FWU IN PROCESS");
        #endif
        return;
    }
    if(_zunoHasPendingReports()){
        #ifdef LOGGING_DBG
        //LOGGING_UART.println("CAN'T SLEEP: PENDING REPORTS");
        #endif
        return;
    }
    if(g_sleep_data.wup_latch){
        if(millis() > g_sleep_data.wup_timeout){
            #ifdef LOGGING_DBG
            //LOGGING_UART.println("***WUP LOCK RELEASED (TIMEOUT)!");
            #endif
            g_sleep_data.wup_latch = false;
        }
        else{
            #ifdef LOGGING_DBG
            //LOGGING_UART.println("CAN'T SLEEP: WAITING SLEEP AGREEMENT FROM CONTROLLER");
            #endif
            return;
        }
    }
    uint32_t timeout;
    zunoEnterCritical();
    timeout = g_sleep_data.timeout;
    zunoExitCritical();
    
    if(timeout >= millis()){
        #ifdef LOGGING_DBG
        //LOGGING_UART.println("CAN'T SLEEP: USER SIDE TIMEOUT!");
        #endif
        return;
    }
    
    #ifdef LOGGING_DBG
    //LOGGING_UART.println("CORE CODE: GO SLEEP>>>");
    #endif
    g_zuno_sys->sleep_latches = SLEEP_UNLOCKED;
    /*
    zunoSetSleepTimeout(ZUNO_SLEEPLOCK_CUSTOM, ZUNO_AWAKETIMEOUT_SLEEPNOW);
    zunoSetSleepTimeout(ZUNO_SLEEPLOCK_SYSTEM, ZUNO_AWAKETIMEOUT_SLEEPNOW);
    */
}

bool _zunoIsWUPLocked(){
    bool res = false;
    zunoEnterCritical();
    res =  g_sleep_data.wup_latch;
    zunoExitCritical();
    return res;
}
void _zunoSleepOnFWUpgradeStart(){
    zunoEnterCritical();
    g_sleep_data.fwupd_latch = true;
    zunoExitCritical();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***FWUPD LOCK ARMED!");
    #endif
}
void _zunoSleepOnFWUpgradeStop(){
    zunoEnterCritical();
    g_sleep_data.fwupd_latch = false;
    zunoExitCritical();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***FWUPD LOCK RELEASED!");
    #endif

}
void _zunoSleepOnWUPStart(){
    zunoEnterCritical();
    g_sleep_data.wup_latch = true;
    g_sleep_data.wup_timeout = millis() + ZUNO_MAX_CONTROLLER_WUP_TIMEOUT;
    zunoExitCritical();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***WUP LOCK ARMED!");
    #endif
}
void _zunoSleepOnWUPStop(){
    zunoEnterCritical();
    g_sleep_data.wup_latch = false;
    zunoExitCritical();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***WUP LOCK RELEASED!");
    #endif

}
void _zunoSleepOnInclusionStart(){
    #ifdef LOGGING_DBG
    LOGGING_UART.println("INCLUDE STARTED");
    #endif
    zunoEnterCritical();
    g_sleep_data.inclusion_latch = true;
    zunoExitCritical();
}
void _zunoSleepOnInclusionComplete(){
    if(g_sleep_data.inclusion_latch){
        #ifdef LOGGING_DBG
        LOGGING_UART.println("INCLUSION COMPLETED");
        #endif
    }
    zunoEnterCritical();
    g_sleep_data.inclusion_latch = false;
    zunoExitCritical();
    #if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
    _zunoSleepingUpd();
    #endif
}
void zunoKickSleepTimeout(uint32_t ms){
    uint32_t new_timeout = millis() + ms;
    if(g_sleep_data.timeout < new_timeout)
        g_sleep_data.timeout = new_timeout;
    #ifdef LOGGING_DBG
    LOGGING_UART.print("NEW SLEEP TIMEOUT:");
    LOGGING_UART.print(g_sleep_data.timeout);
    #endif
}
#endif
void zunoSendDeviceToSleep(uint8_t mode) { 
  // we inform the system that device is ready for sleep
  zunoMarkDeviceToSleep(mode);
  // suspend the main tread
  if((g_zuno_sys->zwave_cfg->flags & DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP) != 0){
    zunoSuspendThread(g_zuno_sys->hMainThread);
  }
}
void zunoMarkDeviceToSleep(uint8_t mode){
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
void zunoLockSleep(void){
    #ifdef LOGGING_DBG
    LOGGING_UART.println("***BLOCK SLEEP!");
    #endif
    zunoEnterCritical();
    g_sleep_data.user_latch = true;
    zunoExitCritical();
}
bool zunoIsSleepLocked(){
    bool res = false;
    zunoEnterCritical();
    res = g_sleep_data.user_latch;
    zunoExitCritical();
    return res;
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

extern "C" void __cxa_pure_virtual() { 
    #ifdef LOGGING_DBG
    LOGGING_UART.println("ZUNO:PURE VIRTUAL CALL!");
    #endif
    while (1); 	
}

int main(){

    return 0;

}