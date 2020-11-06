// Arduino.h
#ifndef ZUNO_ARDUINOH
#define ZUNO_ARDUINOH

#define ZUNO_UNO				1
#define ZUNO_RASBERI			2
#define ZUNO_ASSEMBLY_TYPE		1
// #ifndef ZUNO_ASSEMBLY_TYPE
// 	#define ZUNO_ASSEMBLY_TYPE			ZUNO_UNO//default
// #endif

typedef enum
{
	ZunoErrorOk,//Good!!!
	ZunoErrorTimerAlredy,//the timer is already in use
	ZunoErrorUsartAlredy,//the usart is already in use
	ZunoErrorExtInt,//Failed to configure interrupt
	ZunoErrorAttachSysHandler,//Not enough space in the handler pool
	ZunoErrorBtnInvalidType,//Failed to change type
	ZunoErrorBtnChangeMode,//Failed to change button operation mode
	ZunoErrorInvalidValue,
	ZunoErrorDmaLimitChannel,//
	ZunoErrorSyncInvalidType,
	ZunoErrorNeo,//Failed NEO
	ZunoErrorInvalidPin,//Invalid pin
	ZunoErrorResourceAlready,//resource is already taken
	ZunoErrorMemory//Failed to allocate memory
} ZunoError_t;

#include "ZUNO_Definitions.h"
#include "ArduinoTypes.h"
#include "LLCore.h"
#include "ZUNO_StaticData.h"
#ifndef ZUNO_PREPROC_PHASE
#include <string.h>
#endif
#include "binary.h" // to make somebody which doesn't use hexadecimal values happy
#include "CrtxGPIO.h"
#include "ZWSupport.h"
#include "CrtxCmu.h"
#include "HardwareSerial.h"
// #include "Print.h"  // <- Здесь должен быть HardwareSerial


typedef enum {
  /** Input disabled. Pullup if DOUT is set. */
  GPIOMODE_DISABLED                  = _GPIO_P_MODEL_MODE0_DISABLED,
  /** Input enabled. Filter if DOUT is set */
  GPIOMODE_INPUT                     = _GPIO_P_MODEL_MODE0_INPUT,
  /** Input enabled. DOUT determines pull direction */
  GPIOMODE_INPUTPULL                 = _GPIO_P_MODEL_MODE0_INPUTPULL,
  /** Input enabled with filter. DOUT determines pull direction */
  GPIOMODE_INPUTPULLFILTER           = _GPIO_P_MODEL_MODE0_INPUTPULLFILTER,
  /** Push-pull output */
  GPIOMODE_OUTPUT_PUSHPULL           = _GPIO_P_MODEL_MODE0_PUSHPULL,
  /** Wired-or output */
  GPIOMODE_OUTPUT_WIREDOR              = _GPIO_P_MODEL_MODE0_WIREDOR,
  /** Wired-or output with pull-down */
  GPIOMODE_OUTPUT_WIREDORPD             = _GPIO_P_MODEL_MODE0_WIREDORPULLDOWN,
  /** Open-drain output */
  GPIOMODE_OUTPUT_OPENDRAIN             = _GPIO_P_MODEL_MODE0_WIREDAND,
  /** Open-drain output with filter */
  GPIOMODE_OUTPUT_OPENDRAINFLT          = _GPIO_P_MODEL_MODE0_WIREDANDFILTER,
  /** Open-drain output with pullup */
  GPIOMODE_OUTPUT_OPENDRAINPUP           = _GPIO_P_MODEL_MODE0_WIREDANDPULLUP,
  /** Open-drain output with filter and pullup */
  GPIOMODE_OUTPUT_OPENDRAINPUPFLT        = _GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER,
} GPIO_Mode_t;

enum{
    DISABLED = GPIOMODE_DISABLED,
    OUTPUT = GPIOMODE_OUTPUT_PUSHPULL,
    INPUT = GPIOMODE_INPUT,
    INPUT_PULLUP    = 0x100 | GPIOMODE_INPUTPULL,
    INPUT_PULLDOWN  = GPIOMODE_INPUTPULL,
	INPUT_PULLUP_FILTER = 0x100 | GPIOMODE_INPUTPULLFILTER,
	INPUT_PULLDOWN_FILTER = GPIOMODE_INPUTPULLFILTER,
    OUTPUT_UP = 0x100 | GPIOMODE_OUTPUT_PUSHPULL,
    OUTPUT_DOWN = GPIOMODE_OUTPUT_PUSHPULL,
    INPUT_UP = 0x100 | GPIOMODE_INPUT,
    INPUT_DOWN = GPIOMODE_INPUT
};

enum {
	CTRL_GROUP_1 = 1,
	CTRL_GROUP_2,
	CTRL_GROUP_3,
	CTRL_GROUP_4,
	CTRL_GROUP_5
};

#ifndef DEFAULT_CONFIG_FLAGS
#define DEFAULT_CONFIG_FLAGS 0
#endif

#ifndef ZUNO_PIN_V
	#define ZUNO_PIN_V			3//default
#endif

#define ZEROX					3
#define INT0					17
#define INT1					18

#define ZUNO_SYSTIMER_PERIOD_MC			0xA

#if ZUNO_PIN_V == 1
	#define A0                  14
	#define A1                  15
	#define A2                  16
	#define A3                  17

	#define SCL                 24//by default PA1/RX - SCL
	#define SDA                 23//by default and PA0/TX - SDA
	#define SCL1                6//by default PA1/RX - SCL
	#define SDA1                7//by default and PA0/TX - SDA

	#define RX0					11
	#define TX0					7
	#define RX1					13
	#define TX1					12
	#define RX2					20
	#define TX2					10

	#define BATTERY             0xFF

	#define HIGH                1
	#define LOW                 0

	#define LED_BUILTIN         12
	
	#define ZUNO_PIN_LAST_INDEX	31
#elif ZUNO_PIN_V == 2
	#define PWM1				13
	#define PWM2                14
	#define PWM3                15
	#define PWM4                16

	#define A0                  3//PF6
	#define A1                  4//PF7
	#define A2                  5//PD9
	#define A3                  6//PD10

	#define SCL                 9//by default PD11 I2C0
	#define SDA                 10//by default PD12 I2C0
	#define SCL1                 2//by default PD11 I2C0
	#define SDA1                 24//by default PD12 I2C0

	#define RX0					25
	#define TX0					24
	#define RX1					8
	#define TX1					7
	#define RX2					26
	#define TX2					27

	#define SCK					0//by default USART1
	#define MISO				1//by default USART1 - RX
	#define MOSI				2//by default USART1 - TX
	#define SS					8//by default

	#define SCK2				16//by default PA5  USART2 
	#define MISO2				25//by default PF3 USART2 - RX
	#define MOSI2				7//by default PF4 USART2 - TX
	#define SS2					8//by default PF5

	#define BATTERY             0xFF

	#define HIGH                1
	#define LOW                 0

	#define LED_BUILTIN         13

	#define ZUNO_PIN_LAST_INDEX	25
#elif ZUNO_PIN_V == 3
	#define PWM1				13
	#define PWM2                14
	#define PWM3                15
	#define PWM4                16

	#define A0                  3
	#define A1                  4
	#define A2                  5
	#define A3                  6

	#define SCL                 9
	#define SDA                 10
	#define SCL1                2
	#define SDA1                24

	#define RX0					25
	#define TX0					24
	#define RX1					8
	#define TX1					7
	#define RX2					27
	#define TX2					26

	#define SCK					0//by default USART1
	#define MISO				1//by default USART1 - RX
	#define MOSI				2//by default USART1 - TX
	#define SS					8//by default
	#define SCK2				16//by default PA5  USART2 
	#define MISO2				25//by default PF3 USART2 - RX
	#define MOSI2				7//by default PF4 USART2 - TX
	#define SS2					8//by default PF5

	#define BATTERY             0xFF

	#define HIGH                1
	#define LOW                 0

	#define LED_BUILTIN         15

	#define ZUNO_PIN_LAST_INDEX	25
#elif ZUNO_PIN_V == 4
	#define PWM1				13
	#define PWM2                14
	#define PWM3                15
	#define PWM4                16

	#define A0                  3
	#define A1                  4
	#define A2                  5
	#define A3                  6

	#define SCL                 9
	#define SDA                 10
	#define SCL1                23
	#define SDA1                25

	#define RX0					25
	#define TX0					24
	#define RX1					8
	#define TX1					7
	#define RX2					27
	#define TX2					26

	#define SCK					0//by default USART1
	#define MISO				1//by default USART1 - RX
	#define MOSI				2//by default USART1 - TX
	#define SS					8//by default
	#define SCK2				16//by default PA5  USART2 
	#define MISO2				25//by default PF3 USART2 - RX
	#define MOSI2				7//by default PF4 USART2 - TX
	#define SS2					8//by default PF5

	#define BATTERY             0xFF

	#define HIGH                1
	#define LOW                 0

	#define LED_BUILTIN         13

	#define ZUNO_PIN_LAST_INDEX	25
#elif ZUNO_PIN_V == 1000
	#define HIGH                1
	#define LOW                 0
	#define BATTERY             0xFF
#else
	#error ZUNO_PIN_V
#endif

//Supervisor call
void *zunoSysCall(uint8_t ct, uint8_t n, ...);

// system data
extern ZUNOSetupSysState_t * g_zuno_sys;
#define zunoNID()               (g_zuno_sys->node_id)
#define zunoInNetwork()         (g_zuno_sys->node_id != 0)
#define zunoGetWakeReason()     (g_zuno_sys->reset_reason)
//disable interrupts macros
#define noInterrupts() __asm volatile("cpsid i"::: "memory")
//inable interrupts macros
#define interrupts() __asm volatile("cpsie i"::: "memory")
#define zunoSendDeviceToSleep() zunoSetSleepTimeout(ZUNO_SLEEPLOCK_CUSTOM, ZUNO_AWAKETIMEOUT_SLEEPNOW);

// prototypes
void delay(dword ms);
dword millis();
void pinMode(uint8_t pin, int mode);
void digitalWrite(uint8_t pin, uint8_t val);
uint8_t getPin(uint8_t port, uint8_t pin);
int getRealPort(uint8_t);
int getRealPin(uint8_t);
uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin);
uint8_t getLocationTimer0AndTimer1Chanell(uint8_t pin, uint8_t ch);
int  digitalRead(uint8_t pin);
int  analogRead(uint8_t pin);
bool analogWrite(uint8_t pin, word value);
void WDOG_Feed();
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
void delayMicroseconds(word tdelay);
uint8_t pin2HWPin(uint8_t pin);
void zunoSendZWPackage(ZUNOCommandPacket_t * pkg);
void zunoCommitCfg();
void zunoAppendChannelHandler(byte ch, byte value_size, byte type, void * handler);
ZunoError_t zunoAttachSysHandler(byte type, byte sub_type, void * handler);
ZunoError_t zunoDetachSysHandler(byte type, byte sub_type, void *handler);
ZunoError_t zunoDetachSysHandlerAllSubType(byte type, byte sub_type);
void * zunoSysHandlerCall(uint8_t type, uint8_t sub_type, ...);
void zunoSetZWChannel(byte ch, byte zw_channel);
byte zunoAddChannel(byte type, byte subtype, byte options);
void zunoAddAssociation(byte type, uint32_t params);
void zunoSetAssociationGroupName(uint8_t groupIndex, char *group_name);
bool zunoStartDeviceConfiguration();
void zunoSetS2Keys(byte keys);
void zunoSetSleepingMode(byte mode);
uint8_t zunoGetSleepingMode(void);
void zunoStartLearn(byte timeout, bool secured);
void zunoSendReport(byte ch);
int zunoEEPROMWrite(word address, word size, byte * data);
int zunoEEPROMRead(word address, word size, byte * data);
int zunoEEPROMErase();
void _zme_memcpy(byte *dst, byte *src, byte count);
uint32_t zunoLoadCFGParam(uint8_t param);
void zunoSaveCFGParam(uint8_t param, uint32_t value);

void zunoSetSleepTimeout(uint8_t index, uint32_t timeout);
void zunoSetWUPTimer(uint32_t timeout);
void zunoSendBatteryReport();

// Associations
void zunoSendToGroupSetValueCommand(uint8_t groupIndex, uint8_t value);
void zunoSendToGroupDimmingCommand(uint8_t groupIndex, uint8_t direction, uint8_t start_stop);
void zunoSendToGroupScene(uint8_t groupIndex, uint8_t scene);
void zunoSendToGroupDoorlockControl(uint8_t groupIndex, uint8_t open_close);

//
#include "stdlib.h"
void *malloc(size_t size);
void free(void *ptr);

#include "GpioInterrupt.h"
#include "GeneralPurposeTimer.h"

#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
	#include "ReportHandler.h"
#endif

#endif // ZUNO_ARDUINOH