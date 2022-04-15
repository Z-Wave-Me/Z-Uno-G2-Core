// Arduino.h
#ifndef ZUNO_ARDUINOH
#define ZUNO_ARDUINOH

#include "new.h"

#include "ArduinoTypes.h"
#include "LLCore.h"
#include "ZUNO_Definitions.h"
#include "ZUNO_StaticData.h"
#ifndef ZUNO_PREPROC_PHASE
#include <string.h>
#endif
#include "binary.h" // to make somebody which doesn't use hexadecimal values happy
#include "em_device.h"
#include "em_gpio.h"
#include "em_adc.h"
#include "ZWSupport.h"
#include "HardwareSerial.h"
#include "LeUartClass.h"
#include "zwaveme_libft.h"
#include "Custom_decl.h" // 
#include <math.h>
#include "WCharacter.h"
#include "pgmspace.h"

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

// system data
extern ZUNOSetupSysState_t * g_zuno_sys;
#define zunoNID()               	(g_zuno_sys->node_id)
#define zunoSecurityStatus()    	(g_zuno_sys->highest_security_level)
#define zunoGrantedSecurityKeys()   (g_zuno_sys->granted_keys)
#define zunoInNetwork()         (g_zuno_sys->node_id != 0)
#define zunoIsDbgModeOn()       ((g_zuno_sys->flags & ZUNO_CFGFILE_FLAG_DBG) != 0)
#define zunoGetWakeReason()     (g_zuno_sys->wakeup_reason)
//#define zunoSendWakeUpNotification() zuno_sendWUP_Notification()

// Arduino specific macroses/function
long map(long x, long in_min, long in_max, long out_min, long out_max);
long random(long min, long max);
long random(long max);
void randomSeed(long seed);

#define UNKNOWN_PIN         0xFF

#define DEG_TO_RAD 			0.017453292519
#define RAD_TO_DEG 			57.29577951308
#define EULER 				2.718281828459

#define min(a,b) 				((a)<(b)?(a):(b))
#define max(a,b) 				((a)>(b)?(a):(b))
#define abs(x) 					((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     			((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) 			((deg)*DEG_TO_RAD)
#define degrees(rad) 			((rad)*RAD_TO_DEG)
#define sq(x) 					((x)*(x))
#define square(x) 				((x)*(x)) 
// Bit-wise operations
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define _BV(bit) (1 << (bit))


#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

/* Supervisor call */
void *zunoSysCall(uint8_t ct, uint8_t n, ...);
/* Some z-wave channels stuff*/
bool zunoIsChannelUpdated(uint8_t ch);
bool zunoIsChannelRequested(uint8_t ch);
bool zunoIsBatteryRequested();

/* sleep */
void zunoSetSleepTimeout(uint8_t index, uint32_t timeout);
void zunoMarkDeviceToSleep(uint8_t mode = SLEEP_MODE_EM4);
void zunoSendDeviceToSleep(uint8_t mode = SLEEP_MODE_EM4);
void zunoLockSleep(void);
bool zunoIsSleepLocked();
void zunoKickSleepTimeout(uint32_t ms);

/* Clock/Time */
time_t zunoGetTimeStamp(void);
bool zunoIsValidDate(void);
void zunoSetTimeStamp(time_t timeUnix);

#ifdef WITH_CC_WAKEUP
void zunoSendWakeUpNotification();
#endif
#ifdef WITH_CC_BATTERY
void zunoSendBatteryReport();
#endif
inline void zunoSetSleepingMode(byte mode) {
	g_zuno_sys->zwave_cfg->flags &= ~(DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP);
	mode &= DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP;
	g_zuno_sys->zwave_cfg->flags |= mode;
}
inline uint8_t zunoGetSleepingMode(void) {return (g_zuno_sys->zwave_cfg->flags & DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP);};
inline void zunoEnableSmartStart(bool en){
	if(en)
		g_zuno_sys->zwave_cfg->flags &= ~(DEVICE_CONFIGURATION_FLAGS_SMARTSTART_DISABLE);
	else
		g_zuno_sys->zwave_cfg->flags |= (DEVICE_CONFIGURATION_FLAGS_SMARTSTART_DISABLE);
}
inline void zunoSetProductID(uint16_t product_id){
	g_zuno_sys->zwave_cfg->product_id = product_id;
}


/* time */
void delay(dword ms);
dword millis(void);
dword micros(void);
void delayMicroseconds(word tdelay);
inline void yield() { delay(1); }


/* pin */
void pinMode(uint8_t pin, int mode);
uint8_t pin2HWPin(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t val);
uint8_t getPin(uint8_t port, uint8_t pin);
inline size_t getRealPort(uint8_t pin) {return(ZUNO_PIN_DEFS[pin].port);};
inline size_t getRealPin(uint8_t pin) {return(ZUNO_PIN_DEFS[pin].pin);};
uint32_t zunoMapPin2EM4Bit(uint8_t em4_pin);
uint32_t zunoMapPin2EM4Int(uint8_t em4_pin);
uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin);
size_t getLocationTimer0AndTimer1Chanell(uint8_t pin, uint8_t ch);
inline int digitalRead(uint8_t pin) {return (GPIO_PinInGet((GPIO_Port_TypeDef)getRealPort(pin), getRealPin(pin)));};

void analogReference(ADC_Ref_TypeDef ref);
void analogReadResolution(uint8_t bits);
void analogWriteResolution(uint8_t bits);
int  analogRead(uint8_t pin);
void analogAcqTime(ADC_AcqTime_TypeDef acqtime);


/* Handler */
ZunoError_t zunoAttachSysHandler(byte type, byte sub_type, void * handler);
ZunoError_t zunoDetachSysHandler(byte type, byte sub_type, void *handler);
ZunoError_t zunoDetachSysHandlerAllSubType(byte type, byte sub_type);
void * zunoSysHandlerCall(uint8_t type, uint8_t sub_type, ...);


/* EEPROM */
#define EEPROM_SKETH_ADDR								0x0
#define EEPROM_SKETH_SIZE								0xE00
#define EEPROM_NOTIFICATION_ADDR						(EEPROM_SKETH_ADDR + EEPROM_SKETH_SIZE)
#define EEPROM_NOTIFICATION_SIZE						0x4
#define EEPROM_WAKEUP_ADDR								(EEPROM_NOTIFICATION_ADDR + EEPROM_NOTIFICATION_SIZE)
#define EEPROM_WAKEUP_SIZE								0x4
#define EEPROM_CONFIGURATION_ADDR						(EEPROM_WAKEUP_ADDR + EEPROM_WAKEUP_SIZE)
#define EEPROM_CONFIGURATION_SIZE						0x84
#ifndef EEPROM_USER_CODE_ADDR
	#define EEPROM_USER_CODE_ADDR						EEPROM_SKETH_ADDR
#endif

inline int zunoEEPROMWrite(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, true, address, size, data);};
inline int zunoEEPROMRead(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, false, address, size, data);};
inline int zunoEEPROMErase(void) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_ERASE, 1, 0xCAFE0ACE);};


/* Z-Wave protocol support */
void zunoSendZWPackage(ZUNOCommandPacket_t * pkg);
void zunoCommitCfg();
void zunoAppendChannelHandler(byte ch, byte value_size, byte type, void * handler);
inline void zunoSetZWChannel(byte ch, byte zw_channel) {ZUNO_CFG_CHANNEL(ch).zw_channel = zw_channel;};
byte zunoAddChannel(byte type, byte subtype, byte options);
bool zunoAddBaseCCS(byte ccs, byte version);
void zunoSendReport(byte ch);
void zunoResetLocally();
void zunoSendNIF();
bool zunoStartDeviceConfiguration();
inline void zunoSetS2Keys(byte keys) {g_zuno_sys->zwave_cfg->security_keys = keys;};
void zunoStartLearn(byte timeout, bool secured);
bool zunoPTIConfigUART(uint8_t tx_pin, uint32_t baud);
// Backward compatibility macro
#define ZUNO_START_CONFIG() 						zunoStartDeviceConfiguration()
#define ZUNO_ADD_CHANNEL(TYPE, SUBTYPE, OPTIONS)  	zunoAddChannel(TYPE, SUBTYPE, OPTIONS)
#define ZUNO_ADD_ASSOCIATION(TYPE, OPTIONS)			zunoAddAssociation(TYPE, OPTIONS)
#define ZUNO_COMMIT_CONFIG() 						zunoCommitCfg()



/* CFG */
#include "ZWCCConfiguration_define.h"

/* Associations */
void zunoAddAssociation(byte type, uint32_t params);
const char *zunoAssociationGroupName(uint8_t groupIndex);
void zunoSendToGroupSetValueCommand(uint8_t groupIndex, uint8_t value);
void zunoSendToGroupDimmingCommand(uint8_t groupIndex, uint8_t direction, uint8_t start_stop);
void zunoSendToGroupScene(uint8_t groupIndex, uint8_t scene);
void zunoSendToGroupDoorlockControl(uint8_t groupIndex, uint8_t open_close);

/* Misc */
void WDOG_Feed();
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout=20000);
void _zme_memcpy(byte *dst, byte *src, byte count);


/* Sleep & PowerDown mode */
void zuno_sendWUP_Notification();
ZunoError_t zunoEM4EnablePinWakeup(uint8_t em4_pin);
void zunoSetWUPTimer(uint32_t timeout);
void zunoSetCustomWUPTimer(uint32_t timeout);

#include "GpioInterrupt.h"
#include "GeneralPurposeTimer.h"
#include "Tone.h"
#include "Threading.h"

#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
	#include "ReportHandler.h"
#endif

#endif // ZUNO_ARDUINOH