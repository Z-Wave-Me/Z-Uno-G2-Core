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
#include "CrtxGPIO.h"
#include "ZWSupport.h"
#include "CrtxCmu.h"
#include "HardwareSerial.h"
#include "Libft.h"
// #include "Print.h"  // <- Здесь должен быть HardwareSerial

#include "Custom_decl.h" // 
// system data
extern ZUNOSetupSysState_t * g_zuno_sys;
#define zunoNID()               (g_zuno_sys->node_id)
#define zunoSecurityStatus()    (g_zuno_sys->avaliable_keys)
#define zunoInNetwork()         (g_zuno_sys->node_id != 0)
#define zunoGetWakeReason()     (g_zuno_sys->reset_reason)
//#define zunoSendWakeUpNotification() zuno_sendWUP_Notification()


/* Supervisor call */
void *zunoSysCall(uint8_t ct, uint8_t n, ...);
/* Some z-wave channels staff*/
bool zunoIsChannelUpdated(uint8_t ch);
bool zunoIsChannelRequested(uint8_t ch);
bool zunoIsBatteryRequested();

/* sleep */
void zunoSetSleepTimeout(uint8_t index, uint32_t timeout);
void zunoSendDeviceToSleep(void);
void zunoKickSleepTimeout(uint32_t ms);
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

/* time */
void delay(dword ms);
dword millis(void);
void delayMicroseconds(word tdelay);


/* pin */
void pinMode(uint8_t pin, int mode);
uint8_t pin2HWPin(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t val);
uint8_t getPin(uint8_t port, uint8_t pin);
inline size_t getRealPort(uint8_t pin) {return(ZUNO_PIN_DEFS[pin].port);};
inline size_t getRealPin(uint8_t pin) {return(ZUNO_PIN_DEFS[pin].pin);};
uint8_t getLocation(const uint8_t *location, size_t count, uint8_t pin);
size_t getLocationTimer0AndTimer1Chanell(uint8_t pin, uint8_t ch);
inline int digitalRead(uint8_t pin) {return (GPIO_PinInGet(getRealPort(pin), getRealPin(pin)));};
int  analogRead(uint8_t pin);


/* Handler */
ZunoError_t zunoAttachSysHandler(byte type, byte sub_type, void * handler);
ZunoError_t zunoDetachSysHandler(byte type, byte sub_type, void *handler);
ZunoError_t zunoDetachSysHandlerAllSubType(byte type, byte sub_type);
void * zunoSysHandlerCall(uint8_t type, uint8_t sub_type, ...);


/* EEPROM */
#define EEPROM_SKETH_ADDR								0x0
#define EEPROM_SKETH_SIZE								0x200
#define EEPROM_NOTIFICATION_ADDR						(EEPROM_SKETH_ADDR + EEPROM_SKETH_SIZE)
#define EEPROM_NOTIFICATION_SIZE						0x4
#define EEPROM_WAKEUP_ADDR								(EEPROM_NOTIFICATION_ADDR + EEPROM_NOTIFICATION_SIZE)
#define EEPROM_WAKEUP_SIZE								0x4
#define EEPROM_CONFIGURATION_ADDR						(EEPROM_WAKEUP_ADDR + EEPROM_WAKEUP_SIZE)
#define EEPROM_CONFIGURATION_SIZE						0x84

inline int zunoEEPROMWrite(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, true, address, size, data);};
inline int zunoEEPROMRead(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, false, address, size, data);};
inline int zunoEEPROMErase(void) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_ERASE, 1, 0xCAFE0ACE);};


/* Support */
void zunoSendZWPackage(ZUNOCommandPacket_t * pkg);
void zunoCommitCfg();
void zunoAppendChannelHandler(byte ch, byte value_size, byte type, void * handler);
inline void zunoSetZWChannel(byte ch, byte zw_channel) {ZUNO_CFG_CHANNEL(ch).zw_channel = zw_channel;};
byte zunoAddChannel(byte type, byte subtype, byte options);
void zunoSendReport(byte ch);


/* CFG */
#include "ZWCCConfiguration_define.h"

/* Associations */
void zunoAddAssociation(byte type, uint32_t params);
const char *zunoAssociationGroupName(uint8_t groupIndex);
void zunoSendToGroupSetValueCommand(uint8_t groupIndex, uint8_t value);
void zunoSendToGroupDimmingCommand(uint8_t groupIndex, uint8_t direction, uint8_t start_stop);
void zunoSendToGroupScene(uint8_t groupIndex, uint8_t scene);
void zunoSendToGroupDoorlockControl(uint8_t groupIndex, uint8_t open_close);

/* Unknown */
void WDOG_Feed();
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
bool zunoStartDeviceConfiguration();
inline void zunoSetS2Keys(byte keys) {g_zuno_sys->zwave_cfg->security_keys = keys;};
void zunoStartLearn(byte timeout, bool secured);
void _zme_memcpy(byte *dst, byte *src, byte count);
void zunoSetWUPTimer(uint32_t timeout);
/* Sleep & PowerDown mode */
void zuno_sendWUP_Notification();
ZunoError_t zunoEM4EnablePinWakeup(uint8_t em4_pin);

#include "GpioInterrupt.h"
#include "GeneralPurposeTimer.h"
#include "Tone.h"
#include "Threading.h"

#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
	#include "ReportHandler.h"
#endif

#endif // ZUNO_ARDUINOH