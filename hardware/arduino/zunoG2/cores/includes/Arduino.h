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
#include "ZWSupport.h"
#include "HardwareSerial.h"
#include "LeUartClass.h"
#include "zwaveme_libft.h"
#include "Custom_decl.h" // 
#include <math.h>
#include "WCharacter.h"
#include "pgmspace.h"
#include "SysHandlerMap.h"
#include "zuno_gpio.h"
#include "ZWCCMeter.h"

enum{
  ZUNO_SECUREPARAM_OFF = 0,
  ZUNO_SECUREPARAM_ON = 1,
  ZUNO_SECUREPARAM_UNDEFINED = 0xFF,
};

// system data
extern ZUNOSetupSysState_t * g_zuno_sys;
#define zunoNID()               	(g_zuno_sys->node_id)
#define zunoSecurityStatus()    	(g_zuno_sys->highest_security_level)
#define zunoGrantedSecurityKeys()   (g_zuno_sys->granted_keys)
#define zunoInNetwork()         (g_zuno_sys->node_id != 0)
#define zunoIsDbgModeOn()       ((g_zuno_sys->flags & ZUNO_CFGFILE_FLAG_DBG) != 0)
#define zunoGetWakeReason()     (g_zuno_sys->wakeup_reason)
#define zunoRSTRetention(N)     ( N < MAX_ZUNO_USER_RETENTION ? g_zuno_sys->usr_retention[N] : 0)
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

#ifdef WITH_CC_WAKEUP
void zunoSendWakeUpNotification();
#endif
#ifdef WITH_CC_BATTERY
void zunoSendBatteryReport();
#endif
inline void zunoSetSleepingMode(byte mode) {
  g_zuno_sys->zw_protocol_data->flags &= ~(DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP);
	mode &= DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP;
	g_zuno_sys->zw_protocol_data->flags |= mode;
}
inline uint8_t zunoGetSleepingMode(void) {
  return (g_zuno_sys->zw_protocol_data->flags & DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP);
};
inline void zunoEnableSmartStart(bool en){
  /*
	if(en)
		g_zuno_sys->zwave_cfg->flags &= ~(DEVICE_CONFIGURATION_FLAGS_SMARTSTART_DISABLE);
	else
		g_zuno_sys->zwave_cfg->flags |= (DEVICE_CONFIGURATION_FLAGS_SMARTSTART_DISABLE);
  */
 (void)en;
}
inline void zunoSetProductID(uint16_t product_id){
	g_zuno_sys->zw_protocol_data->product_id = product_id;
}


/* Clock/Time */
#include "zuno_time.h"

/* Analog read */
#include "zuno_analog_read.h"

/* EEPROM */
#define EEPROM_SKETH_ADDR								0x0
#define EEPROM_SKETH_SIZE								0xE00

#define EEPROM_NOTIFICATION_ADDR						((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->notification[0x0])
#define EEPROM_NOTIFICATION_SIZE						4
#define EEPROM_WAKEUP_ADDR								((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->wakeup[0x0])
#define EEPROM_WAKEUP_SIZE								4

#ifndef EEPROM_USER_CODE_ADDR
	#define EEPROM_USER_CODE_ADDR						EEPROM_SKETH_ADDR
#endif

#ifdef WITH_CC_BASIC
#define EEPROM_BASIC_SAVE_ADDR							((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->basic[0x0])
#define EEPROM_BASIC_SAVE_SIZE							(1 * ZUNO_MAX_MULTI_CHANNEL_NUMBER)
#endif
#if defined(WITH_CC_SWITCH_COLOR)
#define EEPROM_SWITCH_COLOR_SAVE_ADDR					((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->switch_color[0x0])
#define EEPROM_SWITCH_COLOR_SAVE_SIZE					(1 * ZUNO_MAX_MULTI_CHANNEL_NUMBER)
#endif
#if defined(WITH_CC_SOUND_SWITCH)
#define EEPROM_SWITCH_SOUND_SAVE_ADDR					((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->switch_sound[0x0])
#define EEPROM_SWITCH_SOUND_SAVE_SIZE					(3 * ZUNO_MAX_MULTI_CHANNEL_NUMBER)
#endif
#define EEPROM_USER_CHANNELS_EEPROM_ADDR				((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->zuno_zw_cfg)
#define EEPROM_USER_CHANNELS_EEPROM_SIZE				sizeof(g_zuno_zw_cfg)

// All last
#define EEPROM_CONFIGURATION_ADDR						((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->config_param)
#ifdef CONFIGPARAMETERS_MAX_COUNT
	#define EEPROM_CONFIGURATION_SIZE					(CONFIGPARAMETERS_MAX_COUNT * 0x4)
#else
	#define EEPROM_CONFIGURATION_SIZE					(0x20 * 0x4)
#endif

#define EEPROM_MAX_SIZE									0x1300

typedef struct									ZwEepromSkethConfigParam_s
{
	uint8_t										config_param[EEPROM_CONFIGURATION_SIZE];
} __attribute__((aligned(0x100),packed))		ZwEepromSkethConfigParam_t;

typedef struct									ZwEepromSketh_s
{
	uint8_t										sketh[EEPROM_SKETH_SIZE];
	uint8_t										notification[EEPROM_NOTIFICATION_SIZE];
	uint8_t										wakeup[EEPROM_WAKEUP_SIZE];
	#if defined(WITH_CC_BASIC)
	uint8_t										basic[EEPROM_BASIC_SAVE_SIZE];
	#endif
	#if defined(WITH_CC_SWITCH_COLOR)
	uint8_t										switch_color[EEPROM_SWITCH_COLOR_SAVE_SIZE];
	#endif
	#if defined(WITH_CC_SOUND_SWITCH)
	uint8_t										switch_sound[EEPROM_SWITCH_SOUND_SAVE_SIZE];
	#endif
	ZUNOZWConfiguation_t						zuno_zw_cfg;
	ZwEepromSkethConfigParam_t					config_param;
}												ZwEepromSketh_t;


inline int zunoEEPROMWrite(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, true, address, size, data);};
inline int zunoEEPROMRead(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, false, address, size, data);};
inline int zunoEEPROMErase(void) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_ERASE, 1, 0xCAFE0ACE);};


/* Z-Wave protocol support */
void zunoSendZWPackage(ZUNOCommandPacket_t * pkg);
void zunoCommitCfg();
#include "zuno_channel_handlers.h"
inline void zunoSetZWChannel(byte ch, byte zw_channel) {
  ZUNO_CFG_CHANNEL(ch).zw_channel = zw_channel;
};
byte zunoAddChannel(byte type, byte subtype, uint32_t options);
bool zunoAddBaseCCS(byte ccs, byte version);
void zunoSendReport(byte ch);
void zunoResetLocally();
void zunoSendNIF();
bool zunoStartDeviceConfiguration();
inline void zunoSetS2Keys(byte keys) {
  g_zuno_sys->zw_protocol_data->req_s2_keys = keys;
};
void zunoStartLearn(byte timeout, bool secured);
bool zunoPTIConfigUART(uint8_t tx_pin, uint32_t baud);
void zunoSendTestPackage(uint8_t * data, uint8_t len, uint8_t dst_node_id);
void zunoStartRadioTest(RadioTestType_t mode, ZWaveRegion_t region, uint32_t timeout, uint8_t power, uint8_t channel);
// Backward compatibility macro
#define ZUNO_START_CONFIG() 						zunoStartDeviceConfiguration()
#define ZUNO_ADD_CHANNEL(TYPE, SUBTYPE, OPTIONS)  	zunoAddChannel(TYPE, SUBTYPE, OPTIONS)
#define ZUNO_ADD_ASSOCIATION(TYPE, OPTIONS)			zunoAddAssociation(TYPE, OPTIONS)
#define ZUNO_COMMIT_CONFIG() 						zunoCommitCfg()



/* CFG */
#include "ZWCCConfiguration_define.h"

/* Associations */
void zunoAddAssociation(byte type, uint8_t channel);
const char *zunoAssociationGroupName(uint8_t groupIndex);
void zunoSendToGroupSetValueCommand(uint8_t groupIndex, uint8_t value);
void zunoSendToGroupDimmingCommand(uint8_t groupIndex, uint8_t direction, uint8_t start_stop);
void zunoSendToGroupScene(uint8_t groupIndex, uint8_t scene);
void zunoSendToGroupDoorlockControlTiming(uint8_t groupIndex, uint8_t open_close, uint16_t seconds);
inline void zunoSendToGroupDoorlockControl(uint8_t groupIndex, uint8_t open_close) {return (zunoSendToGroupDoorlockControlTiming(groupIndex, open_close, 0x0));};

/* Misc */
void WDOG_Feed();
void zunoUpdateSysConfig(bool deffered=true, bool force=false);
void zunoReboot(bool force=true);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout=20000);
void _zme_memcpy(byte *dst, byte *src, byte count);
uint8_t zmeMapDict(uint8_t * dict, uint8_t size, uint8_t key, bool back);


/* Sleep & PowerDown mode */
void zuno_sendWUP_Notification();
ZunoError_t zunoEM4EnablePinWakeup(uint8_t em4_pin);
void zunoSetWUPTimer(uint32_t timeout);
void zunoSetCustomWUPTimer(uint32_t timeout);


#include "GpioInterrupt.h"
#include "GeneralPurposeTimer.h"
#include "Tone.h"
#include "Threading.h"
#include "ReportHandler.h"

extern ZUNOCodeHeader_t g_zuno_codeheader;
#endif // ZUNO_ARDUINOH