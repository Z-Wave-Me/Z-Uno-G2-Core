#ifndef ZUNO_DEFINITIONS
#define ZUNO_DEFINITIONS
#include "ZUNO_CoreDefs.h"
#include "time.h"

#ifndef ZUNO_PREPROC_PHASE
	#include "Custom_defs.h"
#endif

#define ZUNO_UNO				1//Для тип чего собираеться - зуно
#define ZUNO_RASBERI			2//Для тип чего собираеться - распбери
#define ZUNO_BOOTLOADER			3//Для тип чего собираеться - загрузчик

#ifndef ZUNO_ASSEMBLY_TYPE
	#define ZUNO_ASSEMBLY_TYPE		1//Текущий тип сборки
#endif

typedef enum
{
	ZunoErrorOk,//Good!!!
	ZunoErrorTredIo,
	ZunoErrorTimerAlredy,//the timer is already in use
	ZunoErrorUsartAlredy,//the usart is already in use
	ZunoErrorExtInt,//Failed to configure interrupt
	ZunoErrorAttachSysHandler,//Not enough space in the handler pool
	ZunoErrorBtnInvalidType,//Failed to change type
	ZunoErrorBtnChangeMode,//Failed to change button operation mode
	ZunoErrorInvalidValue,

	/* do not change */
	ZunoErrorDmaLimitChannel,//
	ZunoErrorDmaInvalidUniqId,//
	ZunoErrorDmaUniqIdAlready,//
	ZunoErrorDmaInvalidReconfig,//
	/*                                         */

	ZunoErrorSyncInvalidType,
	ZunoErrorSyncInvalidInit,
	ZunoErrorSyncDeInit,
	ZunoErrorNeo,//Failed NEO
	ZunoErrorInvalidPin,//Invalid pin
	ZunoErrorNotInit,
	ZunoErrorResourceAlready,//resource is already taken
	ZunoErrorDhtResultPrevisous,
	ZunoErrorDhtNoSync,
	ZunoErrorDhtWrongData,
	ZunoErrorDhtTimeout,
	ZunoErrorDhtCrc,
	ZunoErrorTrngNotDate,
	ZunoErrorTrngFaill,
	ZunoErrorSomfyNotDevice,
	ZunoErrorSomfyNack,
	ZunoErrorNotData,
	ZunoErrorOverflow,
	ZunoErrorFailed,
	ZunoErrorTimeout,
	ZunoErrorRepeat,
	ZunoErrorBusy,
	ZunoErrorNotMatchCrc,
	ZunoErrorModBusRtuIllegalFunction,
	ZunoErrorModBusRtuIllegalDataAdress,
	ZunoErrorModBusRtuIllegalDataValue,
	ZunoErrorModBusRtuSlaveDeviceFalture,
	ZunoErrorModBusRtuAcknowledge,
	ZunoErrorModBusRtuSlaveDeviceBusy,
	ZunoErrorModBusRtuOther,
	ZunoErrorModBusRtuMemoryParityError,
	ZunoErrorModBusRtuNoises,
	ZunoErrorModBusRtuGatewayPathUnavailable,
	ZunoErrorModBusRtuGatewayTargetDeviceFailedRespond,
	ZunoErrorMemory//Failed to allocate memory
} ZunoError_t;

#include "ZUNO_AutoDef.h"

#define MAX_CHANNEL_PARAMS                              4
#define ZUNO_MAX_MULTI_CHANNEL_NUMBER 					32
#define ZUNO_MAX_ASSOC_NUMBER 							32
#define ZUNO_NAX_CCS_FOR_CHANNEL                        2
#define ZUNO_MAX_CCTYPES                                8
#define ZUNO_CODE_START                                 0x30000L
#define USER_SPACE_FLASH_ADDR                           0x10000
#define ZUNO_CUSTOM_CODESPACE_SIZE                      (0xA000-0x100)
#define MAX_ZUNO_PWMS           						4
#define MAX_AVAILIABLE_SYSHANDLERS 						32
#define MAX_ZWTRANSPORT_ENCAP							8


#define MAX_SLEEP_DELAY 								60000
#define ZUNO_MAX_CONTROLLER_WUP_TIMEOUT 				30000
#define ZUNO_SLEEP_INITIAL_TIMEOUT 						100
#define ZUNO_SLEEP_INCLUSION_TIMEOUT 					5000
#define ZUNO_SLEEP_OTA_TIMEOUT 							20000
#define ZUNO_SLEEP_INTERVIEW_TIMEOUT 					5000
#define ZUNO_SLEEP_RX_TIMEOUT 							3000
#define ZUNO_SLEEP_TX_TIMEOUT							1000

#define INCLUSION_STATUS_SUCESS							0x00
#define INCLUSION_STATUS_IN_PROGRESS  					0x06
#define INCLUSION_STATUS_USER_ABORT                     0xFF
#define MAX_NODEID										232
#define BOOTLOADER_STORAGE_AREA_START					0x3a000


enum { 
	ZUNO_EEPROM_OK,
	ZUNO_EEPROM_NOTALIGNED,
	ZUNO_EEPROM_OUT_OF_MEM,
	ZUNO_EEPROM_LOCKED,
	ZUNO_EEPROM_TIMEOUT,
	ZUNO_EEPROM_UNKNOWN
};

enum {
    ZUNO_JUMPTBL_SETUP,
    ZUNO_JUMPTBL_LOOP,
    ZUNO_JUMPTBL_CMDHANDLER,
	ZUNO_JUMPTBL_SYSTIMER,
	ZUNO_JUMPTBL_SYSEVENT,
	ZUNO_JUMPTBL_IRQ,
	ZUNO_JUMPTBL_SLEEP,
	ZUNO_JUMPTBL_WUP
};

enum {
    CMU_CLOCK_SUBFUNC_GETFREQ,
    CMU_CLOCK_SUBFUNC_ENABLE
};

enum {
    ZUNO_UNKNOWN_CMD,
    ZUNO_COMMAND_PROCESSED,
    ZUNO_COMMAND_ANSWERED,
	ZUNO_COMMAND_UNPACKED,
	ZUNO_COMMAND_BLOCKED
};

enum{
    ZUNO_CFG_DENIED,
    ZUNO_CFG_THESAME,
    ZUNO_CFG_NEW
};
enum {
	ZUNO_MODE_ALWAYS_LISTENING_NUMBER,				//0
	ZUNO_MODE_WAKE_UP_NUMBER,						//1
	ZUNO_MODE_FLIRS_NUMBER,							//2
};

enum 
{	
	ZUNO_WAKEUP_REASON_PIN         = 0,   /**< Reset triggered by reset pin */
    ZUNO_WAKEUP_REASON_WUP_EM4     = 1,   /**< Reset triggered by wake up by timer from deep sleep state  */
//Legacy: ZW_WAKEUP_SENSOR = 2,   /**< Wake up by a Wakeup Beam */
  	ZUNO_WAKEUP_REASON_WATCH_DOG    = 3,   /**< Reset triggered by watchdog */
  	ZUNO_WAKEUP_REASON_EXT_EM4      = 4,
	ZUNO_WAKEUP_REASON_POR          = 5,   /**< Reset triggered by external interrupt event in deep sleep state */
//Legacy: ZW_WAKEUP_USB_SUSPEND= 6  /**< Wake up by USB suspend */
    ZUNO_WAKEUP_REASON_SOFTRESET    = 7,   /**< Reset triggered by software */
//Legacy: ZW_WAKEUP_EMRG_WD_RESET= 8,  /**< Wake up by emergency watchdog reset */
    ZUNO_WAKEUP_REASON_BROWNOUT    = 9,   /**< Reset triggered by brownout circuit */
    ZUNO_WAKEUP_REASON_OTHER       = 0xFF /**< Reset triggered by none of the above */
};
#define ZUNO_ASSOC_NO_PARAMS 							0x00

enum
{
	CHANNEL_HANDLER_EMPTY,      // DEFAULT_VALUE
	CHANNEL_HANDLER_SINGLE_GETTER,
	CHANNEL_HANDLER_SINGLE_GETTERSETTER,
	CHANNEL_HANDLER_SINGLE_VALUEMAPPER,
	CHANNEL_HANDLER_MULTI_GETTER,
	CHANNEL_HANDLER_MULTI_GETTERSETTER,
	CHANNEL_HANDLER_MULTI_MAPPER,
	CHANNEL_HANDLER_SINGLE_GETTERSETTER_2P,
	CHANNEL_HANDLER_MULTI_GETTERSETTER_2P,
	CHANNEL_HANDLER_SINGLE_THERMOSTAT,
	CHANNEL_HANDLER_MULTI_THERMOSTAT
};

enum{
    SECURITY_KEY_S2_UNAUTHENTICATED_BIT=0x01,
    SECURITY_KEY_S2_AUTHENTICATED_BIT=0x02,
    SECURITY_KEY_S2_ACCESS_BIT=0x04,
    SECURITY_KEY_S0_BIT=0x80
};
enum {
	CHANNEL_TYPE_FLAGS_EMPTY=0,
	CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE=0x01,
	CHANNEL_TYPE_FLAGS_IN_USE = 0x80
};

enum {
	DEVICE_CONFIGURATION_FLAGS_SLEEP = 0x01,
	DEVICE_CONFIGURATION_FLAGS_FLIRS = 0x02,
	DEVICE_CONFIGURATION_FLAGS_SMARTSTART_DISABLE = 0x08
};
enum{
	HEADER_FLAGS_DBG = 0x10,
	HEADER_FLAGS_NOLEDS = 0x20,
	HEADER_FLAGS_NOSKETCH_OTA = 0x40,
	HEADER_FLAGS_NOSKETCH_USBLOAD = 0x80
	
};
#define DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP  0x03
enum{
	ZUNO_SYS_EVENT_START 	= 0x00,
	ZUNO_SYS_EVENT_GOSLEEP 	= 0x01,
	ZUNO_SYS_EVENT_SETDEFAULT = 0x11,
	ZUNO_SYS_EVENT_LEARNSTATUS = 0x12,
	ZUNO_SYS_EVENT_EEPROMRESET = 0x13,
	ZUNO_SYS_EVENT_LEARNSTARTED = 0x14,
	ZUNO_SYS_EVENT_FWAUTH     = 0x15,
	ZUNO_SYS_EVENT_OTA_STARTED = 0x16,
	ZUNO_SYS_EVENT_OTA_IMAGE_READY = 0x17,
	ZUNO_SYS_EVENT_OTA_FINISHED = 0x18,
	ZUNO_SYS_EVENT_QUEUE_OVERLOAD   	= 0xC0,
	ZUNO_SYS_EVENT_INVALID_TX_REQUEST = 0xD0,
	ZUNO_SYS_EVENT_INVALID_COMMAND = 0xD1

};
/*
ZUNO_JUMPTBL_SETUP,
    ZUNO_JUMPTBL_LOOP,
    ZUNO_JUMPTBL_CMDHANDLER,
	ZUNO_JUMPTBL_SYSTIMER,
	ZUNO_JUMPTBL_SYSEVENT,
	ZUNO_JUMPTBL_IRQ,
	ZUNO_JUMPTBL_SLEEP,
	ZUNO_JUMPTBL_WUP
*/
enum {
	ZUNO_HANDLER_SYSTIMER,
	ZUNO_HANDLER_SYSEVENT,
	ZUNO_HANDLER_IRQ,
	ZUNO_HANDLER_SLEEP,
	ZUNO_HANDLER_WUP,
	ZUNO_HANDLER_DEBUGPRINT, 
	ZUNO_HANDLER_ZW_CFG,
	ZUNO_HANDLER_ZW_BATTERY,
	ZUNO_HANDLER_REPORT,
	ZUNO_HANDLER_EXTINT,
	ZUNO_HANDLER_GPT,
	ZUNO_HANDLER_MAX_NUMBER
};
enum{
	ZUNO_DBGPRT_SYS,	
	ZUNO_DBGPRT_CUSTOM_ERR,
	ZUNO_DBGPRT_CUSTOM_WARN,
	ZUNO_DBGPRT_CUSTOM_INFO,
	ZUNO_DBGPRT_CUSTOM_DBG
};
enum{
	ZUNO_PACKETFLAGS_GROUP = 0x80,
	ZUNO_PACKETFLAGS_RESEVED = 0x01
};

#define LEARN_TIMEOUT_INF 	0
#define LEARN_TIMEOUT_STOP 	0xFF

#define ZWAVE_CHANNEL_MAPPED_BIT 0x80

/* Transmit frame option flags */
#define TRANSMIT_OPTION_ACK                     0x01    /* request acknowledge from destination node */
#define TRANSMIT_OPTION_LOW_POWER               0x02    /* transmit at low output power level (1/3 of normal RF range)*/
#define TRANSMIT_OPTION_MULTICAST_AS_BROADCAST  0x02    /* The multicast frame should be send as a broadcast */
#define TRANSMIT_OPTION_AUTO_ROUTE              0x04    /* request retransmission via repeater nodes */
/* do not use response route - Even if available */
#define TRANSMIT_OPTION_NO_ROUTE                0x10
/* Use explore frame if needed */
#define TRANSMIT_OPTION_EXPLORE                 0x20
#define ZWAVE_PLUS_TX_OPTIONS 					(TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE | TRANSMIT_OPTION_EXPLORE)

/**
* A response route is locked by the application
*/
#define RECEIVE_STATUS_ROUTED_BUSY 0x01
/**
* Received at low output power level, this must
* have the same value as TRANSMIT_OPTION_LOW_POWER
*/
#define RECEIVE_STATUS_LOW_POWER 0x02
/**
* Mask for masking out the received frametype bits
*/
#define RECEIVE_STATUS_TYPE_MASK 0x0C
/**
* Received frame is singlecast frame (rxOptions == xxxx00xx)
*/
#define RECEIVE_STATUS_TYPE_SINGLE 0x00
/**
* Received frame is broadcast frame (rxOptions == xxxx01xx)
*/
#define RECEIVE_STATUS_TYPE_BROAD 0x04
/**
* Received frame is multicast frame (rxOptions == xxxx10xx)
*/
#define RECEIVE_STATUS_TYPE_MULTI 0x08
/**
* Received frame is an explore frame (rxOptions == xxx1xxxx)
* Only TYPE_BROAD can be active at the same time as TYPE_EXPLORE
*/
#define RECEIVE_STATUS_TYPE_EXPLORE 0x10
/**
* Received frame is not send to me (rxOptions == x1xxxxxx)
* - useful only in promiscuous mode
*/
#define RECEIVE_STATUS_FOREIGN_FRAME 0x40

// ----------------------------------------------------------
// CHANNELS CONFIGURAION HELPERS/CONSTANTS 
// ----------------------------------------------------------

// Sensor Binary types
#define ZUNO_SENSOR_BINARY_TYPE_GENERAL_PURPOSE 		0x01
#define ZUNO_SENSOR_BINARY_TYPE_SMOKE 					0x02
#define ZUNO_SENSOR_BINARY_TYPE_CO 						0x03
#define ZUNO_SENSOR_BINARY_TYPE_CO2 					0x04
#define ZUNO_SENSOR_BINARY_TYPE_HEAT 					0x05
#define ZUNO_SENSOR_BINARY_TYPE_WATER 					0x06
#define ZUNO_SENSOR_BINARY_TYPE_FREEZE 					0x07
#define ZUNO_SENSOR_BINARY_TYPE_TAMPER 					0x08
#define ZUNO_SENSOR_BINARY_TYPE_AUX 					0x09
#define ZUNO_SENSOR_BINARY_TYPE_DOOR_WINDOW 			0x0a
#define ZUNO_SENSOR_BINARY_TYPE_TILT 					0x0b
#define ZUNO_SENSOR_BINARY_TYPE_MOTION 					0x0c
#define ZUNO_SENSOR_BINARY_TYPE_GLASSBREAK 				0x0d
#define ZUNO_SENSOR_BINARY_TYPE_HOME_HEALTH 			0x0e
#define ZUNO_SENSOR_BINARY_TYPE_SIREN	 				0x0f
#define ZUNO_SENSOR_BINARY_TYPE_WATER_VALVE 			0x10
#define ZUNO_SENSOR_BINARY_TYPE_WEATHER_ALARM 			0x11
#define ZUNO_SENSOR_BINARY_TYPE_IRRIGATION 				0x12
#define ZUNO_SENSOR_BINARY_TYPE_GAS_COMBUSTIBLE 		0x13
#define ZUNO_SENSOR_BINARY_TYPE_GAS_TOXIC 				0x14
/*
#define NOTIFICATION_SET_HOME_HEALTH_V7                                                  0x0D
#define NOTIFICATION_SET_SIREN_V7                                                        0x0E
#define NOTIFICATION_SET_WATER_VALVE_V7                                                  0x0F
#define NOTIFICATION_SET_WEATHER_ALARM_V7                                                0x10
#define NOTIFICATION_SET_IRRIGATION_V7                                                   0x11
#define NOTIFICATION_SET_GAS_ALARM_V7
*/

// Notifications
//Notification types
#define NOTIFICATION_TYPE_SMOKE_ALARM					0x01
#define NOTIFICATION_TYPE_CO_ALARM 						0x02
#define NOTIFICATION_TYPE_CO2_ALARM						0x03
#define NOTIFICATION_TYPE_HEAT_ALARM					0x04
#define NOTIFICATION_TYPE_WATER_ALARM 					0x05
#define NOTIFICATION_TYPE_ACCESS_CONTROL_ALARM			0x06
#define NOTIFICATION_TYPE_BURGLAR_ALARM					0x07
#define NOTIFICATION_TYPE_POWER_MANAGEMENT_ALARM		0x08
#define NOTIFICATION_TYPE_SYSTEM_ALARM 					0x09
#define NOTIFICATION_TYPE_EMERGENCY_ALARM				0x0a
#define NOTIFICATION_TYPE_CLOCK_ALARM					0x0b
#define NOTIFICATION_TYPE_APPLIANCE_ALARM				0x0c
#define NOTIFICATION_TYPE_HOME_HEALTH					0x0d
#define NOTIFICATION_TYPE_SIREN							0x0e
#define NOTIFICATION_TYPE_WATER_VALVE					0x0f
#define NOTIFICATION_TYPE_WEATHER_ALAR					0x10
#define NOTIFICATION_TYPE_IRRIGATION					0x11
#define NOTIFICATION_TYPE_GAS_ALARM						0x12

/*
#define NOTIFICATION_SET_HOME_HEALTH_V7                                                  0x0D
#define NOTIFICATION_SET_SIREN_V7                                                        0x0E
#define NOTIFICATION_SET_WATER_VALVE_V7                                                  0x0F
#define NOTIFICATION_SET_WEATHER_ALARM_V7                                                0x10
#define NOTIFICATION_SET_IRRIGATION_V7                                                   0x11
#define NOTIFICATION_SET_GAS_ALARM_V7                                                    0x12
*/
#define NOTIFICATION_ON_VALUE							0xff
#define NOTIFICATION_OFF_VALUE							0x00
//Notification events (UL=Unknown Location)
#define NOTIFICATION_UNKNOWN_EVENT						0xfe
//Smoke
#define NOTIFICATION_EVENT_SMOKE						0x01
#define NOTIFICATION_EVENT_SMOKE_UL						0x02
#define NOTIFICATION_EVENT_SMOKE_TEST					0x03
//CO
#define NOTIFICATION_EVENT_CO							0x01
#define NOTIFICATION_EVENT_CO_UL						0x02
#define NOTIFICATION_EVENT_CO_TEST						0x03
//CO2
#define NOTIFICATION_EVENT_CO2							0x01
#define NOTIFICATION_EVENT_CO2_UL						0x02
//HEAT
#define NOTIFICATION_EVENT_OVERHEAT						0x01
#define NOTIFICATION_EVENT_OVERHEAT_UL					0x02
#define NOTIFICATION_EVENT_TEMP_RISE					0x03
#define NOTIFICATION_EVENT_TEMP_RISE_UL					0x04
#define NOTIFICATION_EVENT_UNDERHEAT					0x05
#define NOTIFICATION_EVENT_UNDERHEAT_UL					0x06
//WATER
#define NOTIFICATION_EVENT_WATER_LEAK					0x01
#define NOTIFICATION_EVENT_WATER_LEAK_UL				0x02
#define NOTIFICATION_EVENT_WATER_LEVEL_DROP				0x03
#define NOTIFICATION_EVENT_WATER_LEVEL_DROP_UL			0x04
//ACCESS
#define NOTIFICATION_EVENT_MANUAL_LOCK					0x01
#define NOTIFICATION_EVENT_MANUAL_UNLOCK				0x02
#define NOTIFICATION_EVENT_MANUAL_NOT_FULLY_LOCKED		0x07
#define NOTIFICATION_EVENT_RF_LOCK						0x03
#define NOTIFICATION_EVENT_RF_UNLOCK					0x04
#define NOTIFICATION_EVENT_RF_NOT_FULLY_LOCKED			0x08
#define NOTIFICATION_EVENT_KEYPAD_LOCK					0x05
#define NOTIFICATION_EVENT_KEYPAD_UNLOCK				0x06
#define NOTIFICATION_EVENT_AUTO_LOCKED					0x09
#define NOTIFICATION_EVENT_AUTO_LOCK_NOT_FULLY_LOCKED	0x0a
#define NOTIFICATION_EVENT_LOCK_JAMMED					0x0b
#define NOTIFICATION_EVENT_ALL_USER_CODES_DELETED		0x0c
#define NOTIFICATION_EVENT_SINGLE_USER_CODE_DELETED		0x0d
#define NOTIFICATION_EVENT_NEW_USER_CODE_ADDED			0X0e
#define NOTIFICATION_EVENT_NEW_USER_CODE_NOT_ADDED		0x0f
#define NOTIFICATION_EVENT_KEYPAD_TEMPORARY_DISABLE		0x10
#define NOTIFICATION_EVENT_KEYPAD_BUSY					0x11
#define NOTIFICATION_EVENT_NEW_PROGRAM_CODE_ENTERED		0x12
#define NOTIFICATION_EVENT_MANUAL_CODE_EXCEEDS_LIMITS	0x13
#define NOTIFICATION_EVENT_RF_UNLOCK_INVALID_CODE		0x14
#define NOTIFICATION_EVENT_RF_LOCK_INVALID_CODE			0x15
#define NOTIFICATION_EVENT_WINDOW_DOOR_OPENED			0x16
#define NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED			0x17
//BURGLAR, HOME SECURITY
#define NOTIFICATION_EVENT_INTRUSION					0x01
#define NOTIFICATION_EVENT_INTRUSION_UL					0x02
#define NOTIFICATION_EVENT_TAMPER_REMOVED				0x03
#define NOTIFICATION_EVENT_TAMPER_INVALID_CODE			0x04
#define NOTIFICATION_EVENT_GLASS_BREAK					0x05
#define NOTIFICATION_EVENT_GLASS_BREAK_UL				0x06
#define NOTIFICATION_EVENT_MOTION_DETECTION				0x07
#define NOTIFICATION_EVENT_MOTION_DETECTION_UL			0x08
//POWER MANAGEMENT
#define NOTIFICATION_EVENT_POWER_APPLIED				0x01
#define NOTIFICATION_EVENT_AC_DISCONNECTED				0x02
#define NOTIFICATION_EVENT_AC_RECONNECTED				0x03
#define NOTIFICATION_EVENT_SURGE						0x04
#define NOTIFICATION_EVENT_VOLTAGE_DROP					0x05
#define NOTIFICATION_EVENT_OVER_CURRENT					0x06
#define NOTIFICATION_EVENT_OVER_VOLTAGE					0x07
#define NOTIFICATION_EVENT_OVER_LOAD					0x08
#define NOTIFICATION_EVENT_LOAD_ERROR					0x09
#define NOTIFICATION_EVENT_REPLACE_BAT_SOON				0x0a
#define NOTIFICATION_EVENT_REPLACE_BAT_NOW				0x0b
//SYSTEM
#define NOTIFICATION_EVENT_HW_FAIL						0x01
#define NOTIFICATION_EVENT_SW_FAIL						0x02
#define NOTIFICATION_EVENT_HW_FAIL_OEM					0x03
#define NOTIFICATION_EVENT_SW_FAIL_OEM					0x04
//EMERGENCY_ALARM
#define NOTIFICATION_EVENT_CONTACT_POLICE				0x01
#define NOTIFICATION_EVENT_CONTACT_FIREMEN				0x02
#define NOTIFICATION_EVENT_CONTACT_MEDIC				0x03
//CLOCK
#define NOTIFICATION_EVENT_WAKE_UP_ALERT				0x01
#define NOTIFICATION_EVENT_TIMER_ENDED					0x02
// GAS
#define NOTIFICATION_EVENT_GAS_COMBUSTIBLE				0x02
#define NOTIFICATION_EVENT_GAS_TOXIC					0x04

// Meter
#define ZUNO_METER_TYPE_ELECTRIC	                    0x01
#define ZUNO_METER_TYPE_GAS		                        0x02
#define ZUNO_METER_TYPE_WATER		                    0x03
#define ZUNO_METER_RESETABLE		                    0x80
#define ZUNO_METER_ELECTRIC_SCALE_KWH	                 0x00
#define ZUNO_METER_ELECTRIC_SCALE_KVAH		             0x01
#define ZUNO_METER_ELECTRIC_SCALE_WATTS		             0x02
#define ZUNO_METER_ELECTRIC_SCALE_PULSECOUNT		     0x03
#define ZUNO_METER_ELECTRIC_SCALE_VOLTS		     		 0x04
#define ZUNO_METER_ELECTRIC_SCALE_AMPS		     		 0x05
#define ZUNO_METER_ELECTRIC_SCALE_POWERFACTOR		     0x06
#define ZUNO_METER_ELECTRIC_SCALE_MST		  			 0x07
#define ZUNO_METER_GAS_SCALE_METERS3	                 0x00
#define ZUNO_METER_GAS_SCALE_FEET3		             	 0x01
#define ZUNO_METER_GAS_SCALE_PULSECOUNT		    		 0x03
#define ZUNO_METER_WATER_SCALE_METERS3	                 0x00
#define ZUNO_METER_WATER_SCALE_FEET3		             0x01
#define ZUNO_METER_WATER_SCALE_GALLONS		             0x02
#define ZUNO_METER_WATER_SCALE_PULSECOUNT		    	 0x03
#define ZUNO_METER_WATER_SCALE_MST		    	 		 0x07
#define METER_PRECISION_ZERO_DECIMALS 					 0x00
#define METER_PRECISION_ONE_DECIMAL 					 0x01
#define METER_PRECISION_TWO_DECIMALS 					 0x02
#define METER_PRECISION_THREE_DECIMALS 					 0x03
#define METER_RESET_ENABLE 								 0x01
#define METER_RESET_DISABLE 							 0x00
#define METER_SIZE_ONE_BYTE 							 0x01
#define METER_SIZE_TWO_BYTES 							 0x02
#define METER_SIZE_FOUR_BYTES 							 0x04
#define METER_PROPERTIES_COMBINER(SCALE,SIZE,PRECISION) \
			(((SIZE-1) & 0x03) << 6)| \
			((SCALE & 0x07)) | \
			((PRECISION & 0x07) << 3)

#define METER_EMPTY_RESETTER							


// Meter TBL Monitor
#define ZUNO_METER_TBL_MONITOR_TYPE_ELECTRIC_SINGLE				0x01
#define ZUNO_METER_TBL_MONITOR_TYPE_GAS							0x02
#define ZUNO_METER_TBL_MONITOR_TYPE_WATER						0x03
#define ZUNO_METER_TBL_MONITOR_TYPE_ELECTRIC_TWIN				0x04
#define ZUNO_METER_TBL_MONITOR_TYPE_ELECTRIC_3P_SINGLE_DIRECT	0x05
#define ZUNO_METER_TBL_MONITOR_TYPE_ELECTRIC_3P_SINGLE_ECT		0x06
#define ZUNO_METER_TBL_MONITOR_TYPE_ELECTRIC_ONE_PHASE_DIRECT	0x07
#define ZUNO_METER_TBL_MONITOR_TYPE_HEATING						0x08
#define ZUNO_METER_TBL_MONITOR_TYPE_COOLING						0x09
#define ZUNO_METER_TBL_MONITOR_TYPE_HEATING_AND_COOLING			0x0A
#define ZUNO_METER_TBL_MONITOR_TYPE_ELECTRIC_SUB				0x0B

#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_KWH					0x0//kilowatt hours (kWh)
#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_KVARH					0x1//kiloVolt-Ampere reactive hours (kVARh)
#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_PERCENTAGE			0x2//Percentage (%)
#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_PULSE_COUNT			0x3//Pulse count (unitless)
#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_KVAR					0x4//kiloVolt-Ampere reactive (kVAR)
#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_VOLTAGE				0x5//Voltage (V)
#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_AMPERE				0x6//Amperes (A)
#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_KW					0x7//kilowatt (kW)
#define ZUNO_METER_TBL_MONITOR_SCALE_ELECTRIC_RATIO					0x8//Ratio (unitless)

#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_METER3				0x0//Cubic meter (m3)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_FEET3				0x1//Cubic feet (ft3)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_GALLON_US			0x2//US gallon
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_PULSE_COUNT			0x3//Pulse count (unitless)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_GALLON_IMP			0x4//IMP gallon
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_LITER				0x5//Liter (l)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_KPA					0x6//kiloPascal (kPa)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_CCF					0x7//Centum cubic feet (CCF)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_M3H					0x8//Cubic meter per hour (m3/h)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_LITTERH				0x9//Liter per hour (l/h)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_KWH					0xA//kilowatt hour (kWh)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_MWH					0xB//megawatt hour (MWh)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_KW					0xC//kilowatt (kW)
#define ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_HOUR					0xD//hour (h)

#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_METER3		0x0//Cubic meter (m3)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_TONNE		0x1//Tonne / Metric ton (t=1000kg)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_M3H		0x2//Cubic meter per hour (m3/h)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_LITTERH	0x3//Liter per hour (l/h)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_KW			0x4//kilowatt (kW)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_MW			0x5//megawatt (MW)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_KWH		0x6//kilowatt hour (kWh)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_MWH		0x7//megawatt hour (MWh)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_GJOULE		0x8//Giga Joule (GJ)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_GCALORIE	0x9//Giga Calorie (Gcal)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_CELCIUS	0xA//Degree Celcius (Co)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_FAHRENHEIT	0xB//Degree Fahrenheit (oF)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_HOUR		0xC//hour (h)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_TEMPERATURE	0xD//volume-based temperature (m3 x Co)
#define ZUNO_METER_TBL_MONITOR_SCALE_HEATING_AND_COOLING_KPA		0xE//kiloPascal (kPa)

#define ZUNO_METER_TBL_MONITOR_RATE_UNSPECIFIED					0x00
#define ZUNO_METER_TBL_MONITOR_RATE_IMPORT						0x01
#define ZUNO_METER_TBL_MONITOR_RATE_EXPORT						0x02

#define ZUNO_METER_TBL_MONITOR_PAY_CREDIT						0x01
#define ZUNO_METER_TBL_MONITOR_PAY_PREPAYMENT					0x02
#define ZUNO_METER_TBL_MONITOR_PAY_PREPAYMENT_DEBT_RECOVERY		0x03

#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_TOTAL_PRIMARY_ACTIVE_ENERGY					(1 << 00)//kWh                                    Energy delivered to the unit before transformation.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_TOTAL_PRIMARY_REACTIVE_ENERGY				(1 << 01)//kVARh                                  Energy delivered to the unit before transformation.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_TOTAL_SECONDARY_ACTIVE_ENERGY				(1 << 02)//kVARh                                  Consumed energy after transformation.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_TOTAL_SECONDARY_REACTIVE_ENERGY				(1 << 03)//kVARh                                  EConsumed energy after transformation.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_INSTANTANEOUS_PRIMARY_ACTIVE_ENERGY			(1 << 04)//kW                                     Current power consumption.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_INSTANTANEOUS_PRIMARY_REACTIVE_ENERGY		(1 << 05)//kvar                                   Current power consumption.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_PRIMARY_ACTIVE_MAXIMUM_DEMAND				(1 << 06)//kW                                     All time maximum active power demand.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_PRIMARY_REACTIVE_MAXIMUM_DEMAND				(1 << 07)//kVAR                                   All time maximum reactive power demand.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_CUMULATIVE_PRIMARY_ACTIVE_MAXIMUM_DEMAND	(1 << 08)//kW                                     Accumulated power over period.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_CUMULATIVE_REACTIVE_MAXIMUM_DEMAND			(1 << 09)//kVAR                                   Accumulated power over period.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_VOLTAGE_PHASE1								(1 << 10)//V                                      Voltage measured on phase 1.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_VOLTAGE_PHASE2								(1 << 11)//V                                      Voltage measured on phase 2.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_VOLTAGE_PHASE3								(1 << 12)//V                                      Voltage measured on phase 3.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_AMPERE_PHASE1								(1 << 13)//V                                      Amperes measured on phase 1.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_AMPERE_PHASE2								(1 << 14)//V                                      Amperes measured on phase 2.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_AMPERE_PHASE3								(1 << 15)//V                                      Amperes measured on phase 3.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_PULSE_INPUT									(1 << 16)//Pulse Count                            Pulse count on pulse input port of meter.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_CURRENT_TRANFORMATION_RATIO					(1 << 17)//ratio                                  Transformation ratio between primary and secondary energy.
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_POWER_FACTOR								(1 << 18)//%                                      Power factor contains the ratio of real power to total power expressed as a percentage (-100 to +100).

#define ZUNO_METER_TBL_MONITOR_DATASET_GAS_WATER_ACCUMULATED_VOLUME							(1 << 00)//m3                                     Total accumulated volume.
#define ZUNO_METER_TBL_MONITOR_DATASET_GAS_WATER_CURRENT_FLOW								(1 << 01)//l/h, m3/h                              Current flow value.
#define ZUNO_METER_TBL_MONITOR_DATASET_GAS_WATER_CURRENT_PRESSURE							(1 << 02)//kPa                                    Current pressure value.
#define ZUNO_METER_TBL_MONITOR_DATASET_GAS_WATER_PEAK_FLOW									(1 << 03)//l/h, m3/h                              Peak flow demand recorded.
#define ZUNO_METER_TBL_MONITOR_DATASET_GAS_WATER_HOUR_COUNTER								(1 << 04)//h                                      Hours in operation.
#define ZUNO_METER_TBL_MONITOR_DATASET_GAS_WATER_INPUT_A									(1 << 05)//m3/h, kW, m3, kWh, MWh, Pulse Count    Value of input port A on the meter.
#define ZUNO_METER_TBL_MONITOR_DATASET_GAS_WATER_INPUT_B									(1 << 06)//m3/h, kW, m3, kWh, MWh, Pulse Count    Value of input port B on the meter.

#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_HEAT_ENERGY						(1 << 00)//kWh, MWh, GJ, GCal                     Total accumulated energy used for heating.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_COOLING_ENERGY					(1 << 01)//kWh, MWh, GJ, GCal                     Total accumulated energy used for cooling.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_VOLUME_FORWARD					(1 << 02)//m3, ton                                Volume counter 1 – forward flow.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_VOLUME_RETURN					(1 << 03)//m3, ton                                Volume counter 2 – return flow.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_TEMPERATURE_FORWARD				(1 << 04)//Co, oF                                 Forward temperature.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_TEMPERATURE_RETURN				(1 << 05)//Co, oF                                 Return temperature.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_TEMPERATURE_SENSOR				(1 << 06)//Co, oF                                 Temperature sensor 3.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_ACTUAL_FLOW_VOLUME1				(1 << 07)//l/h, m3/h                              Current flow on volume 1.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_ACTUAL_FLOW_VOLUME2				(1 << 08)//l/h, m3/h                              Current flow on volume 2.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_ACTUAL_POWER						(1 << 09)//kW, MW                                 Current power.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_PEAK_FLOW						(1 << 10)//l/h, m3/h                              Peak flow recorded.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_PEAK_POWER						(1 << 11)//kW, MW                                 Peak power recorded.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_INPUT_A							(1 << 12)//m3/h, kW, m3, kWh, MWh, Pulse Count    Value of input port A on the meter.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_INPUT_B							(1 << 13)//m3/h, kW, m3, kWh, MWh, Pulse Count    Value of input port B on the meter.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_HOUR_COUNTER						(1 << 14)//h                                      Hour Counter.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_AVERAGE_TEMPERATURE_INLET		(1 << 15)//m3 x Co                                Volumed based average temperature for inlet pipe.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_AVERAGE_TEMPERATURE_OUTLET		(1 << 16)//m3 x Co                                Volumed based average temperature for outlet pipe.
#define ZUNO_METER_TBL_MONITOR_DATASET_HEATING_AND_COOLING_CURRENT_PRESSURE					(1 << 17)//kPa                                    Current pressure value.

#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_SUB_ACCUMULATED1							(1 << 00)//kWh
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_SUB_ACCUMULATED2							(1 << 01)//kVAh
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_SUB_INSTANT1								(1 << 02)//W
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_SUB_ACCUMULATED3							(1 << 03)//Pulse Count
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_SUB_INSTANT2								(1 << 04)//V
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_SUB_INSTANT3								(1 << 05)//A
#define ZUNO_METER_TBL_MONITOR_DATASET_ELECTRIC_SUB_POWER_FACTOR							(1 << 06)//%                                      Power factor contains the ratio of real power to total power.

#define ZUNO_METER_TBL_PRECISION_ZERO_DECIMALS					0x00
#define ZUNO_METER_TBL_PRECISION_ONE_DECIMAL					0x01
#define ZUNO_METER_TBL_PRECISION_TWO_DECIMALS					0x02
#define ZUNO_METER_TBL_PRECISION_THREE_DECIMALS					0x03

#define METER_TBL_REPORT_PROPERTIES1_METER_TYPE_MASK                                     0x3F
#define METER_TBL_REPORT_PROPERTIES1_RATE_TYPE_SHIFT                                     0x06
#define METER_TBL_REPORT_PROPERTIES2_PAY_METER_MASK                                      0x0F

typedef struct												ZunoMeterTblCapability_s
{
	uint32_t												datasetSupported;
	uint32_t												datasetHistorySupported;
	uint32_t												dataHistorySupported;
}															ZunoMeterTblCapability_t;

typedef struct												ZunoMeterTblHistoryValue_s
{
	uint32_t												value;
	uint8_t													precision;
	uint8_t													scale;
}															ZunoMeterTblHistoryValue_t;

// Sensor Multilevel types
#define ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE		                                   	0x01
#define ZUNO_SENSOR_MULTILEVEL_TYPE_GENERAL_PURPOSE_VALUE		                        0x02
#define ZUNO_SENSOR_MULTILEVEL_TYPE_LUMINANCE		                                    0x03
#define ZUNO_SENSOR_MULTILEVEL_TYPE_POWER		                                        0x04
#define ZUNO_SENSOR_MULTILEVEL_TYPE_RELATIVE_HUMIDITY		                            0x05
#define ZUNO_SENSOR_MULTILEVEL_TYPE_VELOCITY		                                    0x06
#define ZUNO_SENSOR_MULTILEVEL_TYPE_DIRECTION		                                    0x07
#define ZUNO_SENSOR_MULTILEVEL_TYPE_ATMOSPHERIC_PRESSURE		                        0x08
#define ZUNO_SENSOR_MULTILEVEL_TYPE_BAROMETRIC_PRESSURE		                           	0x09
#define ZUNO_SENSOR_MULTILEVEL_TYPE_SOLAR_RADIATION		                               	0x0A
#define ZUNO_SENSOR_MULTILEVEL_TYPE_DEW_POINT		                                    0x0B
#define ZUNO_SENSOR_MULTILEVEL_TYPE_RAIN_RATE		                                    0x0C
#define ZUNO_SENSOR_MULTILEVEL_TYPE_TIDE_LEVEL		                                    0x0D
#define ZUNO_SENSOR_MULTILEVEL_TYPE_WEIGHT		                                        0x0E
#define ZUNO_SENSOR_MULTILEVEL_TYPE_VOLTAGE		                                       	0x0F
#define ZUNO_SENSOR_MULTILEVEL_TYPE_CURRENT		                                       	0x10
#define ZUNO_SENSOR_MULTILEVEL_TYPE_CO2_LEVEL		                                    0x11
#define ZUNO_SENSOR_MULTILEVEL_TYPE_AIR_FLOW		                                    0x12
#define ZUNO_SENSOR_MULTILEVEL_TYPE_TANK_CAPACITY		                                0x13
#define ZUNO_SENSOR_MULTILEVEL_TYPE_DISTANCE		                                    0x14
#define ZUNO_SENSOR_MULTILEVEL_TYPE_ANGLE_POSITION		                                0x15
#define ZUNO_SENSOR_MULTILEVEL_TYPE_ROTATION                                            0x16
#define ZUNO_SENSOR_MULTILEVEL_TYPE_WATER_TEMPERATURE                                   0x17
#define ZUNO_SENSOR_MULTILEVEL_TYPE_SOIL_TEMPERATURE                                    0x18
#define ZUNO_SENSOR_MULTILEVEL_TYPE_SEISMIC_INTENSITY                                   0x19
#define ZUNO_SENSOR_MULTILEVEL_TYPE_SEISMIC_MAGNITUDE                                   0x1A
#define ZUNO_SENSOR_MULTILEVEL_TYPE_ULTRAVIOLET                                         0x1B
#define ZUNO_SENSOR_MULTILEVEL_TYPE_ELECTRICAL_RESISTIVITY                              0x1C
#define ZUNO_SENSOR_MULTILEVEL_TYPE_ELECTRICAL_CONDUCTIVITY                             0x1D
#define ZUNO_SENSOR_MULTILEVEL_TYPE_LOUDNESS                                            0x1E
#define ZUNO_SENSOR_MULTILEVEL_TYPE_MOISTURE                                            0x1F
#define ZUNO_SENSOR_MULTILEVEL_TYPE_FREQUENCY                                           0x20
#define ZUNO_SENSOR_MULTILEVEL_TYPE_TIME                                                0x21

#define ZUNO_SENSOR_MULTILEVEL_TYPE_FORMALDEHYDE_CH2O_LEVEL                             0x24
#define ZUNO_SENSOR_MULTILEVEL_TYPE_RADON_CONCENTRATION                                 0x25
#define ZUNO_SENSOR_MULTILEVEL_TYPE_METHANE_DENSITY_CH4                                 0x26
#define ZUNO_SENSOR_MULTILEVEL_TYPE_VOLATILE_ORGANIC_COMPOUND                           0x27
#define ZUNO_SENSOR_MULTILEVEL_TYPE_CARBON_MONOXIDE_CO                           		0x28

#define ZUNO_SENSOR_MULTILEVEL_TYPE_WATER_FLOW                           				0x37

//Sensor Multilevel scales,sizes,precisions
#define SENSOR_MULTILEVEL_PRECISION_ZERO_DECIMALS 									0x00
#define SENSOR_MULTILEVEL_PRECISION_ONE_DECIMAL 									0x01
#define SENSOR_MULTILEVEL_PRECISION_TWO_DECIMALS 									0x02
#define SENSOR_MULTILEVEL_SIZE_ONE_BYTE 											0x01
#define SENSOR_MULTILEVEL_SIZE_TWO_BYTES 											0x02
#define SENSOR_MULTILEVEL_SIZE_FOUR_BYTES 											0x04

// Air temperature
#define SENSOR_MULTILEVEL_SCALE_CELSIUS 											0x00 
//General purpose
#define SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE									0x00 
#define SENSOR_MULTILEVEL_SCALE_DIMENSIONLESS_VALUE									0x01 

//Luminance
#define SENSOR_MULTILEVEL_SCALE_LUX													0x01
//Power
#define SENSOR_MULTILEVEL_SCALE_WATT												0x00
#define SENSOR_MULTILEVEL_SCALE_BTU_PER_HOUR										0x01
//Humidity
#define SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE									0x00 
//Moisture
#define SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE									0x00
//Velocity
#define SENSOR_MULTILEVEL_SCALE_METERS_PER_SECOND	 								0x00
//Athmospheric pressure
#define SENSOR_MULTILEVEL_SCALE_KILO_PASCAL 										0x00
//Barometric pressure
#define SENSOR_MULTILEVEL_SCALE_KILOPASCAL										0x00
//Solar radiation
#define SENSOR_MULTILEVEL_SCALE_WAVELENGTH_PER_SQUARE_METER								0x00
//Dew point
#define SENSOR_MULTILEVEL_SCALE_CELSIUS											0x00
//Rain rate
#define SENSOR_MULTILEVEL_SCALE_MILLIMETERS_PER_HOUR									0x00
//Tide level
#define SENSOR_MULTILEVEL_SCALE_METER											0x00
//Weight
#define SENSOR_MULTILEVEL_SCALE_KILOGRAM										0x00
//Voltage
#define SENSOR_MULTILEVEL_SCALE_VOLT											0x00
//Current
#define SENSOR_MULTILEVEL_SCALE_AMPERE											0x00
//CO2 level
#define SENSOR_MULTILEVEL_SCALE_PARTS_PER_MILLION										0x00
//Air flow
#define SENSOR_MULTILEVEL_SCALE_CUBIC_METER_PER_HOUR									0x00
//Tank capacity
#define SENSOR_MULTILEVEL_SCALE_LITER											0x00
//Distance
#define SENSOR_MULTILEVEL_SCALE_METER											0x00
//Angle position
#define SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE								0x00
//Rotation
#define SENSOR_MULTILEVEL_SCALE_REVOLUTION_PER_MINUTE  							0x00
//Water temperature
#define SENSOR_MULTILEVEL_SCALE_CELSIUS											0x00
//Soil temperature
#define SENSOR_MULTILEVEL_SCALE_CELSIUS											0x00
//Seismic intensity 
#define SENSOR_MULTILEVEL_SCALE_MERCALLI										0x00
//Seismic magnitude 
#define SENSOR_MULTILEVEL_SCALE_LOCAL											0x00
//Ultraviolet
#define SENSOR_MULTILEVEL_SCALE_ULTRAVIOLET_INDEX								0x00
//Electrical conductivity 
#define SENSOR_MULTILEVEL_SCALE_SIEMENS_PER_METER								0x00
//Electrical resistivity 
#define SENSOR_MULTILEVEL_SCALE_OHM_METER										0x00
//Loudness
#define SENSOR_MULTILEVEL_SCALE_DECIBELS										0x00
//Frequency
#define SENSOR_MULTILEVEL_SCALE_HERTZ											0x00
//Time
#define SENSOR_MULTILEVEL_SCALE_SECOND											0x00
//Target temperature
#define SENSOR_MULTILEVEL_SCALE_CELSIUS											0x00
#define SENSOR_MULTILEVEL_SCALE_LITERS_PER_HOUR									0x00

//Sensor Multilevel Properties
#define SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK                                      0x07
#define SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT                                    0x03
#define SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK                                     0x18
#define SENSOR_MULTILEVEL_PROPERTIES_PRECISION_SHIFT                                0x05
#define SENSOR_MULTILEVEL_PROPERTIES_PRECISION_MASK                                 0xE0
#define SENSOR_MULTILEVEL_PROPERTIES_COMBINER(SCALE,SIZE,PRECISION) \
			(SIZE & SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK) | \
			((SCALE << SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT) & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) | \
			((PRECISION << SENSOR_MULTILEVEL_PROPERTIES_PRECISION_SHIFT) & SENSOR_MULTILEVEL_PROPERTIES_PRECISION_MASK)
#define MACRO_CAST_POINTER_TO_VOID(FUNCTION) 										FUNCTION //((VOID_FUNC_POINTER_VOID) FUNCTION)


// Thermostats

#define THERMOSTAT_FLAGS_OFF					0x01
#define THERMOSTAT_FLAGS_HEAT					0x02
#define THERMOSTAT_FLAGS_COOL					0x04
#define THERMOSTAT_FLAGS_FURNACE				0x08
#define THERMOSTAT_FLAGS_DRY					0x10
#define THERMOSTAT_FLAGS_MOIST					0x20
#define THERMOSTAT_FLAGS_AUTO_CHANGEOVER		0x40
#define THERMOSTAT_FLAGS_AUTO					THERMOSTAT_FLAGS_AUTO_CHANGEOVER
#define THERMOSTAT_FLAGS_FULL_POWER				0x80


#define THERMOSTAT_MODE_OFF				0x00
#define THERMOSTAT_MODE_HEAT			0x01
#define THERMOSTAT_MODE_COOL			0x02
#define THERMOSTAT_MODE_FURNACE			0x07
#define THERMOSTAT_MODE_DRY				0x08
#define THERMOSTAT_MODE_MOIST			0x09
#define THERMOSTAT_MODE_AUTO_CHANGEOVER	0x0A
#define THERMOSTAT_MODE_AUTO			THERMOSTAT_MODE_AUTO_CHANGEOVER
#define THERMOSTAT_MODE_FULL_POWER		0x0F



#define THERMOSTAT_UNITS_CELSIUS		0
#define THERMOSTAT_UNITS_FAHRENHEIT		0x80
#define THERMOSTAT_RANGE_NEG			0x20
#define THERMOSTAT_RANGE_POS			0x40
#define THERMOSTAT_LIMITS_MASK			0x1F
#define THERMOSTAT_PROPERTIES_COMBINER(UNITS, POS_NEG, LIMITS)						(UNITS | POS_NEG | (LIMITS & THERMOSTAT_LIMITS_MASK))
// Switch color
#define SWITCH_COLOR_FLAGS_WARM_WHITE	0x01
#define SWITCH_COLOR_FLAGS_COLD_WHITE 	0x02
#define SWITCH_COLOR_FLAGS_RED 			0x04
#define SWITCH_COLOR_FLAGS_GREEN 		0x08
#define SWITCH_COLOR_FLAGS_BLUE 		0x10
#define SWITCH_COLOR_FLAGS_AMBER 		0x20
#define SWITCH_COLOR_FLAGS_CYAN 		0x40
#define SWITCH_COLOR_FLAGS_PURPLE 		0x80

#define SWITCH_COLOR_COMPONENT_WARM_WHITE  0x00
#define SWITCH_COLOR_COMPONENT_COLD_WHITE  0x01
#define SWITCH_COLOR_COMPONENT_RED         0x02
#define SWITCH_COLOR_COMPONENT_GREEN       0x03
#define SWITCH_COLOR_COMPONENT_BLUE        0x04
#define SWITCH_COLOR_COMPONENT_AMBER       0x05
#define SWITCH_COLOR_COMPONENT_CYAN        0x06
#define SWITCH_COLOR_COMPONENT_PURPLE      0x07

#define ZUNO_SLEEPING_MODE_ALWAYS_AWAKE 			    ZUNO_MODE_ALWAYS_LISTENING_NUMBER
#define ZUNO_SLEEPING_MODE_SLEEPING			 		    ZUNO_MODE_WAKE_UP_NUMBER
#define ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE 		    ZUNO_MODE_FLIRS_NUMBER
#define SKETCH_FLAG_S2_UNAUTHENTICATED_BIT				SECURITY_KEY_S2_UNAUTHENTICATED_BIT
#define SKETCH_FLAG_S2_AUTHENTICATED_BIT 				SECURITY_KEY_S2_AUTHENTICATED_BIT
#define SKETCH_FLAG_S2_ACCESS_BIT						SECURITY_KEY_S2_ACCESS_BIT
#define SKETCH_FLAG_S0_BIT          				    SECURITY_KEY_S0_BIT


#define ZUNO_AWAKETIMEOUT_SLEEPNOW                      0              
#define ZUNO_AWAKETIMEOUT_FOREVER                       0xFFFFFFFF
#define ZUNO_SLEEPLOCK_SYSTEM                           0
#define ZUNO_SLEEPLOCK_CUSTOM                           1

enum {
	CTRL_GROUP_1 = 1,
	CTRL_GROUP_2,
	CTRL_GROUP_3,
	CTRL_GROUP_4,
	CTRL_GROUP_5,
	CTRL_GROUP_6,
	CTRL_GROUP_7,
	CTRL_GROUP_8,
	CTRL_GROUP_9,
	CTRL_GROUP_10,
	CTRL_GROUP_11,
	CTRL_GROUP_12,
	CTRL_GROUP_13,
	CTRL_GROUP_14,
	CTRL_GROUP_15,
	CTRL_GROUP_16,
	CTRL_GROUP_17,
	CTRL_GROUP_18,
	CTRL_GROUP_19,
	CTRL_GROUP_20,
	CTRL_GROUP_21,
	CTRL_GROUP_22,
	CTRL_GROUP_23,
	CTRL_GROUP_24,
	CTRL_GROUP_25,
	CTRL_GROUP_26,
	CTRL_GROUP_27,
	CTRL_GROUP_28,
	CTRL_GROUP_29,
	CTRL_GROUP_30,
	CTRL_GROUP_31,
	CTRL_GROUP_32
};

#ifndef DEFAULT_CONFIG_FLAGS
#define DEFAULT_CONFIG_FLAGS 0
#endif

#ifndef ZUNO_PIN_V
	#define ZUNO_PIN_V			4//default
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
	#define SCK2				3
	#define MISO2				4
	#define MOSI2				7
	#define SS2					8

	#define BATTERY             0xFF

	#define HIGH                1
	#define LOW                 0

	#define LED_BUILTIN         15

	#define ZUNO_PIN_LAST_INDEX	27
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
	#define SCK2				3
	#define MISO2				4
	#define MOSI2				7
	#define SS2					8

	#define BATTERY             0xFF

	#define HIGH                1
	#define LOW                 0

	#define LED_BUILTIN         13

	#define ZUNO_PIN_LAST_INDEX	27
#elif ZUNO_PIN_V == 6
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
	#define SCK2				3
	#define MISO2				4
	#define MOSI2				7
	#define SS2					8

	#define BATTERY             0xFF

	#define HIGH                1
	#define LOW                 0

	#define LED_BUILTIN         13

	#define ZUNO_PIN_LAST_INDEX	27
#elif ZUNO_PIN_V == 1000
	#define RX0					11
	#define TX0					7
	#define RX1					13
	#define TX1					12
	#define RX2					20
	#define TX2					10

	#define HIGH                1
	#define LOW                 0
	#define BATTERY             0xFF
	#define ZUNO_PIN_LAST_INDEX	5
#else
	#error ZUNO_PIN_V
#endif


#endif // ZUNO_DEFINITIONS