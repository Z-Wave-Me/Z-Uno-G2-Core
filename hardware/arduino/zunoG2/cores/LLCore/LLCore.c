#include "Arduino.h"
#include "LLCore.h"
#include "ZGecko.h"
#include "CrtxGPIO.h"
#include "CrtxADC.h"
#include "CrtxTimer.h"
#include "Stub.h"
#include <stdarg.h>
#include "Tone.h"
#include "Debug.h"

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
#define SKETCH_FLAGS 0x00
#endif

void * __zunoJTBL(int vec, void * data) __attribute__((section(".sketch_jmptbl")));
ZUNOCodeHeader_t g_zuno_codeheader __attribute__((section(".sketch_struct"))) =  {{'Z','M','E','Z','U','N','O','C'}, ZUNO_CORE_VERSION_MAJOR, ZUNO_CORE_VERSION_MINOR, 0x0000, 0x0000, SKETCH_FLAGS, SKETCH_FWID};

// from ZWSupport.c
int zuno_CommandHandler(ZUNOCommandPacket_t * cmd); 
void zuno_CCTimer(uint32_t);

typedef struct PinDef{
    uint8_t port;
    uint8_t pin;
}PinDef_t;

// A = 0
// B = 1
// C = 2
// D = 3
// E = 4
// F = 5

#if ZUNO_PIN_V == 1
// "NIKBOARD" map
#pragma message "ZUNO_PIN_V==1"
static const PinDef_t ZUNO_PIN_DEFS[] = {
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
static const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
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
static const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
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
#elif ZUNO_PIN_V == 1000
// Rasberi v0
#pragma message "ZUNO_PIN_V==1000"
static const PinDef_t ZUNO_PIN_DEFS[] = {// A0 B1 C2 D3 E4 F5
	{0, 0},//0 - A0 (tX)
	{0, 1},//1 - A1 (rX)
	{2, 7},//2 - PC7 - green
	{2, 8},//3 - PC8 - red
	{2, 6},//4 - C6
	{2, 7}//5 - C7
};
#endif

/*
typedef void zuno_user_systimer_handler(uint32_t);
typedef void zuno_user_sysevent_handler(ZUNOSysEvent_t * ev);
*/

ZUNOSetupSysState_t * g_zuno_sys;
ZUNOOnDemandHW_t g_zuno_odhw_cfg;
// prototypes 
void loop();
void setup();

extern unsigned long  __etext; 
extern unsigned long  __data_start__;
extern unsigned long  __data_end__;
extern unsigned long  __bss_start__;
extern unsigned long  __bss_end__;

extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));
extern void (*__fini_array_start []) (void) __attribute__((weak));
extern void (*__fini_array_end []) (void) __attribute__((weak));
extern "C"{
    void _init();
    void _fini();
};
// Universal pin location index
const uint8_t g_loc_pa0_pf7_all[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05,// LOC 0-5 = PA0-PA5
		0x1B, 0x1C, 0x1D, 0x1E, 0x1F,// LOC  6-10 = PB11-PB15
		0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, // LOC 11-16 = PC6-PC11
		0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // LOC 17-23 = PD9-PD15
		0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57// LOC 24-31 = PF0-PF7
	};
const uint8_t g_loc_pa0_pf7_all_size = sizeof(g_loc_pa0_pf7_all);

uint8_t pin2HWPin(uint8_t pin){
    return (ZUNO_PIN_DEFS[pin].port << 4) | (ZUNO_PIN_DEFS[pin].pin&0x0F);
}
void LLInit() {
    // Constructors....
    size_t count, i;
    // Global values initialization
    uint32_t * cd = &__etext;
    for(uint32_t * p=&__data_start__; p<&__data_end__; p++, cd++){
        *p = *cd;
        WDOG_Feed();
    }
    for(uint32_t * p=&__bss_start__; p<&__bss_end__; p++){
        *p = 0;
        WDOG_Feed();
    }
    count = __preinit_array_end - __preinit_array_start;
    for (i = 0; i < count; i++)
        __preinit_array_start[i]();
    _init();
    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++)
        __init_array_start[i]();
}

void LLDestroy() {
   
    // Destructors....
    int count;
    int i;
    /*for (i = 0; i < atexit_count; i++) {
            atexit_funcs[i]();
    }*/
    count = __fini_array_end - __fini_array_start;
    #ifdef LOGGING_DBG
    LOGGING_UART.print("DESTROY Count:");
    LOGGING_UART.print(count);
    LOGGING_UART.println(" Items: ");
    for (i = count-1; i >= 0; i--){
        LOGGING_UART.print("ADDR:");
        LOGGING_UART.println((unsigned long)__fini_array_start[i], HEX);
    }
    #endif
    
    for (i = count-1; i >= 0; i--)
        __fini_array_start[i]();
    _fini();
    #ifdef LOGGING_DBG
    LOGGING_UART.println("DESTOY STOP!!!");
    #endif
    
}
#ifdef WITH_AUTOSETUP
// this is managing using "preproc" util
void zuno_static_autosetup();
#endif


void * zunoJumpTable(int vec, void * data) {
    byte sub_handler_type = 0x00;
    switch(vec){
        case ZUNO_JUMPTBL_SETUP:
            LLInit();
            g_zuno_sys = (ZUNOSetupSysState_t*)data;
            #ifdef WITH_AUTOSETUP
            zuno_static_autosetup();
            #endif
			#if defined(LOGGING_DBG) || defined(ASSERT_DBG)
				LOGGING_UART.begin(115200);
			#endif
            setup();
            ZWCCSetup();
            break;
        case ZUNO_JUMPTBL_LOOP:
            loop();
            delay(20); // to avoid starvation
            break;
        case ZUNO_JUMPTBL_CMDHANDLER:
            return (void*)zuno_CommandHandler((ZUNOCommandPacket_t *) data);
        #ifdef LOGGING_DBG
        case ZUNO_JUMPTBL_SYSEVENT:{
                ZUNOSysEvent_t * evnt = (ZUNOSysEvent_t *)data;
                LOGGING_UART.print("[");
                LOGGING_UART.print(millis());
                LOGGING_UART.print("] ");
                LOGGING_UART.print("SYSEVENT: ");
                LOGGING_UART.print(evnt->event, HEX);
                LOGGING_UART.print(" ARGS: ");
                LOGGING_UART.print(evnt->params[0], HEX);
                LOGGING_UART.print(" ");
                LOGGING_UART.println(evnt->params[1], HEX);
            }
            break;
        #endif
        case ZUNO_JUMPTBL_SYSTIMER:
            zuno_CCTimer((uint32_t)data);
            break;
        case ZUNO_JUMPTBL_IRQ:
            sub_handler_type = (uint8_t)((uint32_t)data)&0x0FF;
            break;
        #ifdef LOGGING_DBG
        case ZUNO_JUMPTBL_DEBUGPRINT:{
            ZUNOSysDbgMessage_t * msg = (ZUNOSysDbgMessage_t *)data;
            LOGGING_UART.print("[");
            LOGGING_UART.print(millis());
            LOGGING_UART.print("] ");
            switch(msg->type){
                case ZUNO_DBGPRT_SYS:
                    LOGGING_UART.print("SYS");
                    break;
                case ZUNO_DBGPRT_CUSTOM_ERR:
                    LOGGING_UART.print("ERR");
                    break;
                case ZUNO_DBGPRT_CUSTOM_WARN:
                    LOGGING_UART.print("WRN");
                    break;
                case ZUNO_DBGPRT_CUSTOM_INFO:
                    LOGGING_UART.print("INF");
                    break;
                case ZUNO_DBGPRT_CUSTOM_DBG:
                     LOGGING_UART.print("DBG");
                    break;
            }
            LOGGING_UART.print(" ");
            LOGGING_UART.println(msg->p_text);
            }
            break;
         #endif
        case ZUNO_JUMPTBL_SLEEP:
            #ifdef LOGGING_DBG
            LOGGING_UART.println("!SLEEP");
            #endif
            LLDestroy();
            break;
        default:
            break; // UNKNOWN VECTOR
    }
    
    if(vec >= ZUNO_JUMPTBL_SYSTIMER){
        zunoSysHandlerCall(vec-ZUNO_JUMPTBL_SYSTIMER,sub_handler_type, data);
    }
    return (void*)0;
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
					case ZUNO_HANDLER_EXTINT:
						((zuno_user_zuno_handler_extint*)(base_addr))();
						break ;
					case ZUNO_HANDLER_REPORT:
						va_start (args, sub_type);
						((zuno_user_zuno_handler_report*)(base_addr))(va_arg(args,ReportAuxData_t *));
						va_end (args);
						break;
                    case ZUNO_HANDLER_SYSEVENT:
                        va_start (args, sub_type);
                        ((zuno_user_sysevent_handler*)(base_addr))(va_arg(args,ZUNOSysEvent_t*));
                        va_end (args);
                        break;
                    case ZUNO_HANDLER_IRQ:
                    case ZUNO_HANDLER_SLEEP:
                    case ZUNO_HANDLER_WUP:
                        ((zuno_void_handler*)(base_addr))();
                        break;
                    case ZUNO_HANDLER_DEBUGPRINT:
                        va_start (args, sub_type);
  	                    ((zuno_dbgprint_handler*)(base_addr))(va_arg(args,ZUNOSysDbgMessage_t*));
	                    va_end (args);
                        break;
                    case ZUNO_HANDLER_ZW_CFG:
                        va_start (args, sub_type);
                        ((zuno_configuartionhandler_t*)(base_addr))((uint8_t)va_arg(args,uint32_t), va_arg(args,uint32_t));
                        va_end (args);
                        break;
                    case ZUNO_HANDLER_ZW_BATTERY:
                        Serial0.print("BATTERY ADDR:");
                        Serial0.println((uint32_t)base_addr, HEX);
                        
                        result = (void*)(((zuno_battery_handler_t*)(base_addr))());
                        break;
                }
        }
    }
    return result;
}

int zunoAttachSysHandler(byte type, byte sub_type, void *handler) {
	HandlerFunc_t				*lp_b;
	HandlerFunc_t				*lp_e;
	uint16_t					code_offset;

	code_offset = (uint16_t)((uint32_t)(((byte*)handler) - ZUNO_CODE_START)) & 0xFFFF;
	lp_e = &g_zuno_odhw_cfg.h_sys_handler[MAX_AVAILIABLE_SYSHANDLERS];
	lp_b = lp_e - MAX_AVAILIABLE_SYSHANDLERS;
	while (lp_b < lp_e) {
		if (lp_b->main_type == type && lp_b->sub_type == sub_type && lp_b->code_offset == code_offset)
			return (0);
		lp_b++;
	}
	lp_b = lp_e - MAX_AVAILIABLE_SYSHANDLERS;
	while (lp_b < lp_e) {
		if (lp_b->code_offset == 0) {
			lp_b->main_type = type;
			lp_b->sub_type = sub_type;
			lp_b->code_offset = code_offset;
			return (0);
		}
		lp_b++;
	}
	return (-1);
}

int zunoDetachSysHandler(byte type, byte sub_type, void *handler) {
	HandlerFunc_t				*lp_b;
	HandlerFunc_t				*lp_e;
	uint16_t					code_offset;

	code_offset = (uint16_t)((uint32_t)(((byte*)handler) - ZUNO_CODE_START)) & 0xFFFF;
	lp_e = &g_zuno_odhw_cfg.h_sys_handler[MAX_AVAILIABLE_SYSHANDLERS];
	lp_b = lp_e - MAX_AVAILIABLE_SYSHANDLERS;
	while (lp_b < lp_e) {
		if (lp_b->main_type == type && lp_b->sub_type == sub_type && lp_b->code_offset == code_offset) {
			lp_b->code_offset = 0;
			return (0);
		}
		lp_b++;
	}
	return (-1);
}

int zunoDetachSysHandlerAllSubType(byte type, byte sub_type) {
	HandlerFunc_t				*lp_b;
	HandlerFunc_t				*lp_e;
	int							out;

	out = -1;
	lp_e = &g_zuno_odhw_cfg.h_sys_handler[MAX_AVAILIABLE_SYSHANDLERS];
	lp_b = lp_e - MAX_AVAILIABLE_SYSHANDLERS;
	while (lp_b < lp_e) {
		if (lp_b->main_type == type && lp_b->sub_type == sub_type) {
			lp_b->code_offset = 0;
			out = 0;
		}
		lp_b++;
	}
	return (out);
}

void zunoSetSleepTimeout(uint8_t index, uint32_t timeout){
    zunoSysCall(ZUNO_FUNC_SLEEP_CONTROL, 2, index, timeout);
}
void zunoSetWUPTimer(uint32_t timeout){
    zunoSysCall(ZUNO_FUNC_WUP_CONTROL, 1, timeout);
}

void zunoStartLearn(byte timeout, bool secured){
    zunoSysCall(ZUNO_FUNC_LEARN, 2, timeout, secured);
}
void * __zunoJTBL(int vec, void * data) {
    return zunoJumpTable(vec, data);
}

void delay(dword ms){
    void * ret = zunoSysCall(ZUNO_FUNC_DELAY_MS, 1, ms);
}

dword millis(){
    return (dword) zunoSysCall(ZUNO_FUNC_MILLIS, 0);
}
void digitalWrite(uint8_t pin, uint8_t mode) {
	uint8_t						real_port;
	uint8_t						real_pin;

	real_port = getRealPort(pin);
	real_pin = getRealPin(pin);
	if (mode == true)
		GPIO_PinOutSet(real_port, real_pin);
	else
		GPIO_PinOutClear(real_port, real_pin);
}

void pinMode(uint8_t pin, int mode){
	GPIO_PinModeSet(getRealPort(pin), getRealPin(pin), (GPIO_Mode_TypeDef)(mode & 0x0F), ((mode & 0x100) != 0) ? true : false);
}
int getRealPin(uint8_t pin)
{
    int real_pin = ZUNO_PIN_DEFS[pin].pin;
    return real_pin;
}


int getRealPort(uint8_t pin)
{
    int real_port = ZUNO_PIN_DEFS[pin].port;
    return real_port;
}

uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin) {
	uint8_t				i;

	i = 0;
	pin = (getRealPort(pin) << 4) | getRealPin(pin);
	while (i < count) {
		if (location[i] == pin)
			return (i);
		i++;
	}
	return (0);
}

int digitalRead(uint8_t pin) {
    int real_port = ZUNO_PIN_DEFS[pin].port;
    int real_pin = ZUNO_PIN_DEFS[pin].pin;
    /*uint32_t aliasAddr = ((uint32_t)&GPIO->P[real_port].DIN); //PER_BITSET_MEM_BASE + ((uint32_t)(&GPIO->P[real_port].DOUT) - PER_MEM_BASE);  
    //val = (val > 0);
    //   BITBAND_PER_BASE + (((uint32_t)addr - PER_MEM_BASE) * (uint32_t) 32) + (bit * (uint32_t) 4);
    aliasAddr -= PER_MEM_BASE;
    aliasAddr <<= 5;
    aliasAddr += BITBAND_PER_BASE;
    aliasAddr +=  (real_pin << 2);

    return (*(volatile uint32_t *)aliasAddr);*/
    return (GPIO->P[real_port].DIN & (1<<real_pin)) != 0;
}

int analogRead(uint8_t pin) {
    uint32_t sampleValue;
    if(!g_zuno_odhw_cfg.ADCInitialized){
        // Initialize ADC only the first time we need it
        zme_ADC_Enable();
        g_zuno_odhw_cfg.ADCInitialized = true;
    }
    ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;
    // Init for single conversion use, use 5V reference
    singleInit.reference  = adcRef5V;
    singleInit.posSel     = zme_ADC_PIN2Channel(pin);
    singleInit.resolution = adcRes12Bit;
    singleInit.acqTime    = adcAcqTime256;
    ADC_InitSingle(ADC0, &singleInit);
    ADC_Start(ADC0, adcStartSingle);
    while (ADC0->STATUS & ADC_STATUS_SINGLEACT);
    sampleValue = ADC_DataSingleGet(ADC0);
    // zme_ADC_Disable(); // Move to "BEFORESLEEP" hadler
    return sampleValue;
}

void delayMicroseconds(word tdelay){
    while(tdelay--){
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
   }
}


bool analogWrite(uint8_t pin, word value) {
	return (_analogWrite(pin, (value > 0xFF) ? 0xFF : value));
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
    zunoSysCall(ZUNO_FUNC_COMMIT_CONFIG, 0);
}

/*
bool 	 b_write = va_arg(lst, uint32_t) > 0;
			uint16_t addr  	 = va_arg(lst, uint32_t)&0x0ffff;
			uint16_t size  	 = va_arg(lst, uint32_t)&0x0ffff;
			uint8_t * p_data = va_arg(lst,uint8_t *);
			zme_EEPROM_io(g_zuno_state.file_system, addr, p_data, size, b_write);
*/
int zunoEEPROMWrite(word address, word size, byte * data) {
    return (int)zunoSysCall(ZUNO_FUNC_EEPROM_IO, 4, true, address, size, data);
}
int zunoEEPROMRead(word address, word size, byte * data) {
    return (int)zunoSysCall(ZUNO_FUNC_EEPROM_IO, 4, false, address, size, data);
}
int zunoEEPROMErase() {
    return (int)zunoSysCall(ZUNO_FUNC_EEPROM_ERASE, 1, 0xCAFE0ACE);
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

int main(){

    return 0;

}