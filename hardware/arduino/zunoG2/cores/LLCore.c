#include "Arduino.h"
#include "LLCore.h"
#include "ZGecko.h"
#include "CrtxGPIO.h"
#include "CrtxADC.h"
#include "CrtxTimer.h"
#include "Stub.h"


void * __zunoJTBL(int vec, void * data) __attribute__((section(".sketch_jmptbl")));
ZUNOCodeHeader_t g_zuno_codeheader __attribute__((section(".sketch_struct"))) =  {{'Z','M','E','Z','U','N','O','C'}, ZUNO_CORE_VERSION_MAJOR, ZUNO_CORE_VERSION_MINOR, 0x0000, 0x0000, 0x00};

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

#if defined ZUNO_PIN_V1
// "NIKBOARD" map
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
    {0, 0},  //  23 - A0 (RX)
    {0, 1},  //  24 - A1 (TX)
    {0, 2},  //  25 - A2 (ADC0)
    {0, 3},  //  26 - A3 
    {0, 4},  //  27 - A4
    {0, 5},  //  28 - A5
    {1, 11}, //  29 - B11 
    {1, 12}, //  30 - B12
    {1, 13}, //  31 - B13
    
};
#elif defined ZUNO_PIN_V2
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
	{3, 13},//26 - PD13 - USB Serial
	{5, 2}//27 - PF2 - USB Serial
};
#elif defined ZUNO_PIN_V3
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
	{0, 0},//13 - PA0 - ARDURINO LED - blue and PWM1
	{0, 1},//14 - PA1 - PWM2
	{0, 2},//15 - PA2 - PWM3 
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
	{5, 2},//26 - PF2 - USB Serial
	{5, 3}//27 - PF3 - USB Serial
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
    // Global values initialization
    uint32_t * cd = &__etext;
    for(uint32_t * p=&__data_start__; p<&__data_end__; p++, cd++){
        *p = *cd;
    }
    for(uint32_t * p=&__bss_start__; p<&__bss_end__; p++){
        *p = 0;
    }
    // Constructors....
    size_t count, i;
    count = __preinit_array_end - __preinit_array_start;
    for (i = 0; i < count; i++)
        __preinit_array_start[i]();
    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++)
        __init_array_start[i]();
    // Initialize Hardware default CFG
    memset(&g_zuno_odhw_cfg,0,sizeof(ZUNOOnDemandHW_t));
    g_zuno_odhw_cfg.pwm_freq_scaller = 100UL;//0xFFFF;


}
#ifdef WITH_AUTOSETUP
// this is managing using "preproc" util
void zuno_static_autosetup();
#endif


void * zunoJumpTable(int vec, void * data) {
    switch(vec){
        case ZUNO_JUMPTBL_SETUP:
            LLInit();
            g_zuno_sys = (ZUNOSetupSysState_t*)data;
            delay(2000);// ! DBG - что бы информацию выводила отладочную окуратно без разброса - в Realese - убрать
            #ifdef WITH_AUTOSETUP
            zuno_static_autosetup();
            #endif
            setup();
            break;
        case ZUNO_JUMPTBL_LOOP:
            loop();
            delay(20); // to avoid starvation
            break;
        case ZUNO_JUMPTBL_CMDHANDLER:
            return (void*)zuno_CommandHandler((ZUNOCommandPacket_t *) data);
        case ZUNO_JUMPTBL_SYSEVENT:
            for(int i=0;i<getSysHandlerCount(ZUNO_HANDLER_SYSEVENT);i++)
                ((zuno_user_sysevent_handler *)(getSysHandlerPtr(ZUNO_HANDLER_SYSEVENT, i)))((ZUNOSysEvent_t*)data);
            break;
        case ZUNO_JUMPTBL_SYSTIMER:
            zuno_CCTimer((uint32_t)data);
            for(int i=0;i<getSysHandlerCount(ZUNO_HANDLER_SYSTIMER);i++)
                ((zuno_user_systimer_handler *)(getSysHandlerPtr(ZUNO_HANDLER_SYSTIMER, i)))((uint32_t)data);
            break;
        default:
            break; // UNKNOWN VECTOR
    }
    return (void*)0;
}
int zunoAttachSysHandler(byte type, void * handler){
    if(type >= ZUNO_HANDLER_MAX_NUMBER)
        return -2;
    if(g_zuno_odhw_cfg.h_sys_handler_len[type] >= MAX_HANDLER_LIST)
        return -1;
    g_zuno_odhw_cfg.h_sys_handler[type][g_zuno_odhw_cfg.h_sys_handler_len[type]] = handler;
    g_zuno_odhw_cfg.h_sys_handler_len[type]++;
    return g_zuno_odhw_cfg.h_sys_handler_len[type];
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
void digitalWrite(uint8_t pin, uint8_t val){

    int real_port = ZUNO_PIN_DEFS[pin].port;
    int real_pin = ZUNO_PIN_DEFS[pin].pin;
    /*if(val)
        GPIO->P[real_port].DOUT |= (1<< real_pin);
    else
        GPIO->P[real_port].DOUT &= ~(1<< real_pin);*/
    uint32_t aliasAddr = ((uint32_t)&GPIO->P[real_port].DOUT); //PER_BITSET_MEM_BASE + ((uint32_t)(&GPIO->P[real_port].DOUT) - PER_MEM_BASE);  
    //val = (val > 0);
    //   BITBAND_PER_BASE + (((uint32_t)addr - PER_MEM_BASE) * (uint32_t) 32) + (bit * (uint32_t) 4);
    aliasAddr -= PER_MEM_BASE;
    aliasAddr <<= 5;
    aliasAddr += BITBAND_PER_BASE;
    aliasAddr +=  (real_pin << 2);

    *(volatile uint32_t *)aliasAddr = (uint32_t)val;
}

void pinMode(uint8_t pin, int mode){
    int real_port = ZUNO_PIN_DEFS[pin].port;
    int real_pin = ZUNO_PIN_DEFS[pin].pin;
    int real_mode = mode & 0xFF;
    bool on_off    = ((mode & 0x100)  != 0);

    if( real_mode != DISABLED ){
        digitalWrite(pin, on_off);
    }
    if(real_pin < 8){
      GPIO->P[real_port].MODEL = (GPIO->P[real_port].MODEL & ~(0xFu << (real_pin << 2)))
                          | (real_mode << (real_pin << 2 ));
    } else {
      GPIO->P[real_port].MODEH = (GPIO->P[real_port].MODEH & ~(0xFu << ((real_pin - 8) << 2)))
                          | (mode << ((real_pin - 8) << 2));
    }
    if( real_mode == DISABLED ){
        digitalWrite(pin, on_off);
    }

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
byte aux_findPWMChannel(byte pin){
    int i;
    for(i=0;i<MAX_ZUNO_PWMS;i++){
        if(g_zuno_odhw_cfg.pwm_pins[i] == pin)
            return i;
    }
    return INVALID_PIN_INDEX;
}

void delayMicroseconds(word tdelay){
    while(tdelay--){
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
        asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
   }
}

static inline dword map_pwmloc2ch(int loc, int ch){
    loc = (loc + 32-ch) & 0x1F;
    ch <<= 3;
    return loc << ch;
}
bool analogWrite(uint8_t pin, word value){
    
    if(!g_zuno_odhw_cfg.PWMInitialized){
        memset(g_zuno_odhw_cfg.pwm_pins, INVALID_PIN_INDEX, sizeof(g_zuno_odhw_cfg.pwm_pins));
        CMU_ClockEnable(cmuClock_TIMER1, true);
        TIMER_TopSet(TIMER1, g_zuno_odhw_cfg.pwm_freq_scaller);
        // Set the PWM duty cycle to zero for all channels!
        TIMER_CompareBufSet(TIMER1, 0, 0);
        TIMER_CompareBufSet(TIMER1, 1, 0);
        TIMER_CompareBufSet(TIMER1, 2, 0);
        TIMER_CompareBufSet(TIMER1, 3, 0);
        // Create a timerInit object, based on the API default
        TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
        TIMER_Init(TIMER1, &timerInit);
        g_zuno_odhw_cfg.PWMInitialized = true;
        // const uint8_t g_loc_pa0_pf7_all[]

    }
    byte ch =  aux_findPWMChannel(pin);
    if(value == 0){
        // switch off the led if it was enabled already
        if(ch == INVALID_PIN_INDEX)
            return false; // We don't have this pin is occupied by the PWM - go out
        g_zuno_odhw_cfg.pwm_pins[ch] = INVALID_PIN_INDEX;
        // disable CC
        TIMER1->ROUTEPEN &= ~(1UL<<ch);
        // Switch off this pin anyway
        digitalWrite(pin, 0);  
        return true;
    } 
    if(ch == INVALID_PIN_INDEX){    
        ch = aux_findPWMChannel(INVALID_PIN_INDEX);
        if(ch == INVALID_PIN_INDEX)
            return false;
        TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
        timerCCInit.mode      = timerCCModePWM;
        timerCCInit.cmoa      = timerOutputActionToggle;
        timerCCInit.outInvert = 0;
        TIMER_InitCC(TIMER1, ch, &timerCCInit);
        g_zuno_odhw_cfg.pwm_pins[ch] = pin; // We occupied this channel with the needed pin
        uint32_t pwm_loc = getLocation(g_loc_pa0_pf7_all, g_loc_pa0_pf7_all_size, pin);
        pwm_loc =  map_pwmloc2ch(pwm_loc, ch);
        TIMER1->ROUTELOC0 &=  ~(0x1FUL<<(ch<<3));
        TIMER1->ROUTELOC0 |=  pwm_loc;
        TIMER1->ROUTEPEN |= (1UL<<ch);
        // enable the output
        digitalWrite(pin, 0);

    } 
    TIMER_CompareBufSet(TIMER1, ch, value);
    
    return true;
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