#ifndef ZW_COMMAND_CLASS_SUPPORT
#define ZW_COMMAND_CLASS_SUPPORT

#define MANUFACTURER_SPECIFIC_LOGGER_REPORT (0x05 + 0x10)
#define MANUFACTURER_SPECIFIC_TEST_PACKAGE  (0x05 + 0x11)

#define MAX_ZW_PACKAGE 170
#define ZUNO_LIFELINE_GRP 1
#ifndef ZUNO_REPORTTIME_DIVIDER
#define ZUNO_REPORTTIME_DIVIDER  0x07
#endif
#ifndef ZUNO_MAX_REPORTCOUNT_PER_MOMENT 
#define ZUNO_MAX_REPORTCOUNT_PER_MOMENT 3
#endif
#define UNKNOWN_CHANNEL       0xFF 
#define LOWEST_LONG_RANGE_NODE_ID   (0x0100)
/* Application Status command class commands */
#define APPLICATION_STATUS_VERSION                                                       0x01
#define APPLICATION_BUSY                                                                 0x01
#define APPLICATION_REJECTED_REQUEST                                                     0x02

/* Values used for Application Busy command */
#define APPLICATION_BUSY_TRY_AGAIN_LATER                                                 0x00
#define APPLICATION_BUSY_TRY_AGAIN_IN_WAIT_TIME_SECONDS                                  0x01
#define APPLICATION_BUSY_REQUEST_QUEUED_EXECUTED_LATER                                   0x02

#define PLAIN_ASSOC_MAP 0x80

/************************************************************/
/* Application Rejected Request command class structs */    
/************************************************************/
typedef struct											ZwApplicationRejectedRequestFrame_s
{
	uint8_t												cmdClass;/* The command class */
	uint8_t												cmd;/* The command */
	uint8_t												status;/**/
}														ZwApplicationRejectedRequestFrame_t;

enum{
	ZME_FREQ_EU,
	ZME_FREQ_RU,
	ZME_FREQ_IN,
	ZME_FREQ_US,
	ZME_FREQ_ANZ,
	ZME_FREQ_HK,
	ZME_FREQ_CN,
	ZME_FREQ_JP,
	ZME_FREQ_KR,
	ZME_FREQ_IL,
	ZME_FREQ_MY,
	ZME_FREQ_LR_US=0x011
};
enum
{
	COMMAND_CLASS_UNKNOWN = 0x0,
	COMMAND_CLASS_BASIC = 0x20,
	COMMAND_CLASS_APPLICATION_STATUS = 0x22,
	COMMAND_CLASS_SWITCH_BINARY = 0x25,
	COMMAND_CLASS_SWITCH_MULTILEVEL = 0x26,
	COMMAND_CLASS_SCENE_ACTIVATION = 0x2B,
	COMMAND_CLASS_SENSOR_MULTILEVEL = 0x31,
	COMMAND_CLASS_METER = 0x32,
	COMMAND_CLASS_SWITCH_COLOR = 0x33,
	COMMAND_CLASS_THERMOSTAT_MODE = 0x40,
	COMMAND_CLASS_THERMOSTAT_OPERATING_STATE = 0x42,
	COMMAND_CLASS_THERMOSTAT_SETPOINT = 0x43,
	COMMAND_CLASS_THERMOSTAT_FAN_MODE = 0x44,
	COMMAND_CLASS_THERMOSTAT_FAN_STATE = 0x45,
	COMMAND_CLASS_SCHEDULE_ENTRY_LOCK = 0x4E,
	COMMAND_CLASS_TRANSPORT_SERVICE = 0x55,
	COMMAND_CLASS_ASSOCIATION_GRP_INFO = 0x59,
	COMMAND_CLASS_DEVICE_RESET_LOCALLY = 0x5A,
	COMMAND_CLASS_CENTRAL_SCENE = 0x5B,
	COMMAND_CLASS_ZWAVEPLUS_INFO = 0x5E,
	COMMAND_CLASS_MULTI_CHANNEL = 0x60,
	COMMAND_CLASS_DOOR_LOCK = 0x62,
	COMMAND_CLASS_WINDOW_COVERING = 0x6A,
	COMMAND_CLASS_SUPERVISION = 0x6C,
	COMMAND_CLASS_CONFIGURATION = 0x70,
	COMMAND_CLASS_NOTIFICATION = 0x71,
	COMMAND_CLASS_MANUFACTURER_SPECIFIC = 0x72,
	COMMAND_CLASS_POWERLEVEL = 0x73,
	COMMAND_CLASS_SOUND_SWITCH = 0x79,
	COMMAND_CLASS_FIRMWARE_UPDATE_MD=0x7A,
	COMMAND_CLASS_BATTERY = 0x80,
	COMMAND_CLASS_USER_CREDENTIAL = 0x83,
	COMMAND_CLASS_WAKE_UP = 0x84,
	COMMAND_CLASS_ASSOCIATION = 0x85,
	COMMAND_CLASS_VERSION = 0x86,
	COMMAND_CLASS_INDICATOR = 0x87,
	COMMAND_CLASS_TIME = 0x8A,
	COMMAND_CLASS_TIME_PARAMETERS = 0x8B,
	COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION = 0x8E,
	COMMAND_CLASS_SECURITY = 0x98,
	COMMAND_CLASS_SECURITY_2 = 0x9F,
	COMMAND_CLASS_AUTHENTICATION = 0xA1
};

enum{
	SYSREPORT_MAP_BATTERY_BIT = 0x01,
	SYSREPORT_MAP_WAKEUP_BIT = 0x02
};
enum{
	SYSREQUEST_MAP_BATTERY_BIT = 0x01
};

typedef void zuno_configuration_changed(uint8_t, uint32_t);


typedef struct				ZUNOCommandHandlerOption_s
{
	node_id_t				src_node;
	bool					multi;
	bool					supervision;
	uint8_t					cmd_class;
}							ZUNOCommandHandlerOption_t;

#define ZUNO_COMMAND_HANDLER_OPTIONS(_src_node, _multi, _supervision, _cmd_class)				\
{																								\
	.src_node = _src_node,																		\
	.multi = _multi,																			\
	.supervision = _supervision,																\
	.cmd_class = _cmd_class,																	\
}																								\

#define ZUNO_COMMAND_HANDLER_OPTIONS_DEFAULT()									\
{																						\
	.src_node = 0x0,																	\
	.multi = false,																		\
	.supervision = false,																\
	.cmd_class = COMMAND_CLASS_UNKNOWN,													\
}																						\

typedef struct				ZUNOCommandReport_t
{
	ZUNOCommandHandlerOption_t option;
	bool					outside;
	bool					valid;
}							ZUNOCommandReport_s;

typedef struct				ZUNOCommandPacket_t
{
	ZUNOCommandCmd_t		packet;
	ZUNOCommandReport_s		report;
}							ZUNOCommandPacket_t;

typedef struct				ZUNOCommandPacketReport_s
{
	ZUNOCommandPacket_t		info;
	uint8_t					data[MAX_ZW_PACKAGE];
}							ZUNOCommandPacketReport_t;

uint8_t zuno_findChannelByZWChannelIndexChannel(byte zw_ch);
void zunoSetupBitMask(byte * arr, byte b, byte max_sz);
void fillOutgoingReportPacketUnsolicited(byte channel, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options);
void fillOutgoingReportPacketUnsolicitedLifeLine(ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options);
void fillOutgoingReportPacketAsync(ZUNOCommandPacketReport_t *frame, size_t ch);
bool fillOutgoingRawPacket(ZUNOCommandPacket_t * p, uint8_t * d, uint8_t ch, uint8_t flags, node_id_t dst);
void zunoSendReportSet(byte channel, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options, const void *add);
void ZWCCSetup();
void zunoRFLogger(ZUNOSysEvent_t * ev);

bool _zunoHasPendingReports();
void _zunoMarkChannelRequested(uint8_t ch);
void _zunoMarkChannelUpdated(uint8_t ch);
void _zunoMarkSystemClassRequested(uint8_t systembit);

#define ZW_CMD_CLASS          (cmd->cmd[0])
#define ZW_CMD                (cmd->cmd[1])
#define ZW_CMD_BPARAM(N)      (cmd->cmd[2+N])
// !!! FIX

#define ZUNO_CFG_CHANNEL_COUNT  (g_zuno_zw_cfg.num_channels)
#define ZUNO_CFG_CHANNEL(N)     (g_zuno_zw_cfg.channels[N])
//#define ZUNO_CFG_TYPE_COUNT     0//(g_zuno_sys->zwave_cfg->num_channel_types)
//#define ZUNO_CFG_TYPE(N)        0//g_zuno_sys->zwave_cfg->channel_types[N]
//#define ZUNO_CFG_TYPES          NULL//g_zuno_sys->zwave_cfg->channel_types
//#define ZUNO_CFG_BASECCS(N)     g_zuno_sys->zwave_cfg->custom_base_ccs[N]
//#define ZUNO_CFG_BASE_CCS_NUM   0//g_zuno_sys->zwave_cfg->num_custom_base_ccs
#define ZUNO_CFG_ASSOCIATION_COUNT		(g_zuno_zw_cfg.num_associations)
#define ZUNO_CFG_ASSOCIATION(N)			(g_zuno_zw_cfg.associations[N])


#define APPLICATION_NODEINFO_NOT_LISTENING            0x00
#define APPLICATION_NODEINFO_LISTENING                0x01
#define APPLICATION_FREQ_LISTENING_MODE_1000ms        0x10
#define APPLICATION_FREQ_LISTENING_MODE_250ms         0x20

/* Device class Av Control Point */
#define GENERIC_TYPE_AV_CONTROL_POINT                                                    0x03 /*AV Control Point*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_DOORBELL                                                           0x12
#define SPECIFIC_TYPE_SATELLITE_RECEIVER                                                 0x04 /*Satellite Receiver*/
#define SPECIFIC_TYPE_SATELLITE_RECEIVER_V2                                              0x11 /*Satellite Receiver V2*/
#define SPECIFIC_TYPE_SOUND_SWITCH                                                       0x01

/* Device class Display */
#define GENERIC_TYPE_DISPLAY                                                             0x04
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_SIMPLE_DISPLAY                                                     0x01 /*Display (simple) Device Type*/

/* Device class Entry Control */
#define GENERIC_TYPE_ENTRY_CONTROL                                                       0x40 /*Entry Control*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_DOOR_LOCK                                                          0x01 /*Door Lock*/
#define SPECIFIC_TYPE_ADVANCED_DOOR_LOCK                                                 0x02 /*Advanced Door Lock*/
#define SPECIFIC_TYPE_SECURE_KEYPAD_DOOR_LOCK                                            0x03 /*Door Lock (keypad –lever) Device Type*/
#define SPECIFIC_TYPE_SECURE_KEYPAD_DOOR_LOCK_DEADBOLT                                   0x04 /*Door Lock (keypad – deadbolt) Device Type*/
#define SPECIFIC_TYPE_SECURE_DOOR                                                        0x05 /*Barrier Operator Specific Device Class*/
#define SPECIFIC_TYPE_SECURE_GATE                                                        0x06 /*Barrier Operator Specific Device Class*/
#define SPECIFIC_TYPE_SECURE_BARRIER_ADDON                                               0x07 /*Barrier Operator Specific Device Class*/
#define SPECIFIC_TYPE_SECURE_BARRIER_OPEN_ONLY                                           0x08 /*Barrier Operator Specific Device Class*/
#define SPECIFIC_TYPE_SECURE_BARRIER_CLOSE_ONLY                                          0x09 /*Barrier Operator Specific Device Class*/
#define SPECIFIC_TYPE_SECURE_LOCKBOX                                                     0x0A /*SDS12724*/

/* Device class Generic Controller */
#define GENERIC_TYPE_GENERIC_CONTROLLER                                                  0x01 /*Remote Controller*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_PORTABLE_REMOTE_CONTROLLER                                         0x01 /*Remote Control (Multi Purpose) Device Type*/
#define SPECIFIC_TYPE_PORTABLE_SCENE_CONTROLLER                                          0x02 /*Portable Scene Controller*/
#define SPECIFIC_TYPE_PORTABLE_INSTALLER_TOOL                                            0x03
#define SPECIFIC_TYPE_REMOTE_CONTROL_AV                                                  0x04 /*Remote Control (AV) Device Type*/
#define SPECIFIC_TYPE_REMOTE_CONTROL_SIMPLE                                              0x06 /*Remote Control (Simple) Device Type*/

/* Device class Meter */
#define GENERIC_TYPE_METER                                                               0x31 /*Meter*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_SIMPLE_METER                                                       0x01 /*Sub Energy Meter Device Type*/
#define SPECIFIC_TYPE_ADV_ENERGY_CONTROL                                                 0x02 /*Whole Home Energy Meter (Advanced) Device Type*/
#define SPECIFIC_TYPE_WHOLE_HOME_METER_SIMPLE                                            0x03 /*Whole Home Meter (Simple) Device Type*/

/* Device class Meter Pulse */
#define GENERIC_TYPE_METER_PULSE                                                         0x30 /*Pulse Meter*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/

/* Device class Non Interoperable */
#define GENERIC_TYPE_NON_INTEROPERABLE                                                   0xFF /*Non interoperable*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/

/* Device class Repeater Slave */
#define GENERIC_TYPE_REPEATER_SLAVE                                                      0x0F /*Repeater Slave*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_REPEATER_SLAVE                                                     0x01 /*Basic Repeater Slave*/

/* Device class Security Panel */
#define GENERIC_TYPE_SECURITY_PANEL                                                      0x17
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_ZONED_SECURITY_PANEL                                               0x01

/* Device class Semi Interoperable */
#define GENERIC_TYPE_SEMI_INTEROPERABLE                                                  0x50 /*Semi Interoperable*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_ENERGY_PRODUCTION                                                  0x01 /*Energy Production*/

/* Device class Sensor Alarm */
#define GENERIC_TYPE_SENSOR_ALARM                                                        0xA1
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_ADV_ZENSOR_NET_ALARM_SENSOR                                        0x05
#define SPECIFIC_TYPE_ADV_ZENSOR_NET_SMOKE_SENSOR                                        0x0A
#define SPECIFIC_TYPE_BASIC_ROUTING_ALARM_SENSOR                                         0x01
#define SPECIFIC_TYPE_BASIC_ROUTING_SMOKE_SENSOR                                         0x06
#define SPECIFIC_TYPE_BASIC_ZENSOR_NET_ALARM_SENSOR                                      0x03
#define SPECIFIC_TYPE_BASIC_ZENSOR_NET_SMOKE_SENSOR                                      0x08
#define SPECIFIC_TYPE_ROUTING_ALARM_SENSOR                                               0x02
#define SPECIFIC_TYPE_ROUTING_SMOKE_SENSOR                                               0x07
#define SPECIFIC_TYPE_ZENSOR_NET_ALARM_SENSOR                                            0x04
#define SPECIFIC_TYPE_ZENSOR_NET_SMOKE_SENSOR                                            0x09
#define SPECIFIC_TYPE_ALARM_SENSOR                                                       0x0B /*Sensor (Alarm) Device Type*/

/* Device class Sensor Binary */
#define GENERIC_TYPE_SENSOR_BINARY                                                       0x20 /*Binary Sensor*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_ROUTING_SENSOR_BINARY                                              0x01 /*Routing Binary Sensor*/

/* Device class Sensor Multilevel */
#define GENERIC_TYPE_SENSOR_MULTILEVEL                                                   0x21 /*Multilevel Sensor*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_ROUTING_SENSOR_MULTILEVEL                                          0x01 /*Sensor (Multilevel) Device Type*/
#define SPECIFIC_TYPE_CHIMNEY_FAN                                                        0x02

/* Device class Static Controller */
#define GENERIC_TYPE_STATIC_CONTROLLER                                                   0x02 /*Static Controller*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_PC_CONTROLLER                                                      0x01 /*Central Controller Device Type*/
#define SPECIFIC_TYPE_SCENE_CONTROLLER                                                   0x02 /*Scene Controller*/
#define SPECIFIC_TYPE_STATIC_INSTALLER_TOOL                                              0x03
#define SPECIFIC_TYPE_SET_TOP_BOX                                                        0x04 /*Set Top Box Device Type*/
#define SPECIFIC_TYPE_SUB_SYSTEM_CONTROLLER                                              0x05 /*Sub System Controller Device Type*/
#define SPECIFIC_TYPE_TV                                                                 0x06 /*TV Device Type*/
#define SPECIFIC_TYPE_GATEWAY                                                            0x07 /*Gateway Device Type*/

/* Device class Switch Binary */
#define GENERIC_TYPE_SWITCH_BINARY                                                       0x10 /*Binary Switch*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_POWER_SWITCH_BINARY                                                0x01 /*On/Off Power Switch Device Type*/
#define SPECIFIC_TYPE_SCENE_SWITCH_BINARY                                                0x03 /*Binary Scene Switch*/
#define SPECIFIC_TYPE_POWER_STRIP                                                        0x04 /*Power Strip Device Type*/
#define SPECIFIC_TYPE_SIREN                                                              0x05 /*Siren Device Type*/
#define SPECIFIC_TYPE_VALVE_OPEN_CLOSE                                                   0x06 /*Valve (open/close) Device Type*/
#define SPECIFIC_TYPE_COLOR_TUNABLE_BINARY                                               0x02

/* Device class Switch Multilevel */
#define GENERIC_TYPE_SWITCH_MULTILEVEL                                                   0x11 /*Multilevel Switch*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_CLASS_A_MOTOR_CONTROL                                              0x05 /*Window Covering No Position/Endpoint Device Type*/
#define SPECIFIC_TYPE_CLASS_B_MOTOR_CONTROL                                              0x06 /*Window Covering Endpoint Aware Device Type*/
#define SPECIFIC_TYPE_CLASS_C_MOTOR_CONTROL                                              0x07 /*Window Covering Position/Endpoint Aware Device Type*/
#define SPECIFIC_TYPE_MOTOR_MULTIPOSITION                                                0x03 /*Multiposition Motor*/
#define SPECIFIC_TYPE_POWER_SWITCH_MULTILEVEL                                            0x01 /*Light Dimmer Switch Device Type*/
#define SPECIFIC_TYPE_SCENE_SWITCH_MULTILEVEL                                            0x04 /*Multilevel Scene Switch*/
#define SPECIFIC_TYPE_FAN_SWITCH                                                         0x08 /*Fan Switch Device Type*/
#define SPECIFIC_TYPE_COLOR_TUNABLE_MULTILEVEL                                           0x02

/* Device class Switch Remote */
#define GENERIC_TYPE_SWITCH_REMOTE                                                       0x12 /*Remote Switch*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_SWITCH_REMOTE_BINARY                                               0x01 /*Binary Remote Switch*/
#define SPECIFIC_TYPE_SWITCH_REMOTE_MULTILEVEL                                           0x02 /*Multilevel Remote Switch*/
#define SPECIFIC_TYPE_SWITCH_REMOTE_TOGGLE_BINARY                                        0x03 /*Binary Toggle Remote Switch*/
#define SPECIFIC_TYPE_SWITCH_REMOTE_TOGGLE_MULTILEVEL                                    0x04 /*Multilevel Toggle Remote Switch*/

/* Device class Switch Toggle */
#define GENERIC_TYPE_SWITCH_TOGGLE                                                       0x13 /*Toggle Switch*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_SWITCH_TOGGLE_BINARY                                               0x01 /*Binary Toggle Switch*/
#define SPECIFIC_TYPE_SWITCH_TOGGLE_MULTILEVEL                                           0x02 /*Multilevel Toggle Switch*/

/* Device class Thermostat */
#define GENERIC_TYPE_THERMOSTAT                                                          0x08 /*Thermostat*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_SETBACK_SCHEDULE_THERMOSTAT                                        0x03 /*Setback Schedule Thermostat*/
#define SPECIFIC_TYPE_SETBACK_THERMOSTAT                                                 0x05 /*Thermostat (Setback) Device Type*/
#define SPECIFIC_TYPE_SETPOINT_THERMOSTAT                                                0x04
#define SPECIFIC_TYPE_THERMOSTAT_GENERAL                                                 0x02 /*Thermostat General*/
#define SPECIFIC_TYPE_THERMOSTAT_GENERAL_V2                                              0x06 /*Thermostat (HVAC) Device Type*/
#define SPECIFIC_TYPE_THERMOSTAT_HEATING                                                 0x01 /*Thermostat Heating*/

/* Device class Ventilation */
#define GENERIC_TYPE_VENTILATION                                                         0x16
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_RESIDENTIAL_HRV                                                    0x01

/* Device class Window Covering */
#define GENERIC_TYPE_WINDOW_COVERING                                                     0x09 /*Window Covering*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_SIMPLE_WINDOW_COVERING                                             0x01 /*Simple Window Covering Control*/

/* Device class Zip Node */
#define GENERIC_TYPE_ZIP_NODE                                                            0x15
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_ZIP_ADV_NODE                                                       0x02
#define SPECIFIC_TYPE_ZIP_TUN_NODE                                                       0x01

/* Device class Wall Controller */
#define GENERIC_TYPE_WALL_CONTROLLER                                                     0x18
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_BASIC_WALL_CONTROLLER                                              0x01 /*Wall Controller Device Type*/

/* Device class Network Extender */
#define GENERIC_TYPE_NETWORK_EXTENDER                                                    0x05 /*Network Extender Generic Device Class*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_SECURE_EXTENDER                                                    0x01 /*Specific Device Secure Extender*/

/* Device class Appliance */
#define GENERIC_TYPE_APPLIANCE                                                           0x06
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_GENERAL_APPLIANCE                                                  0x01
#define SPECIFIC_TYPE_KITCHEN_APPLIANCE                                                  0x02
#define SPECIFIC_TYPE_LAUNDRY_APPLIANCE                                                  0x03

/* Device class Sensor Notification */
#define GENERIC_TYPE_SENSOR_NOTIFICATION                                                 0x07
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class not used*/
#define SPECIFIC_TYPE_NOTIFICATION_SENSOR                                                0x01

#define ICON_TYPE_UNASSIGNED                                                 0x0000   //MUST NOT be used by any product
																		   
#define ICON_TYPE_GENERIC_CENTRAL_CONTROLLER                                 0x0100   //Central Controller Device Type
																		   
#define ICON_TYPE_GENERIC_DISPLAY_SIMPLE                                     0x0200   //Display Simple Device Type
																		   
#define ICON_TYPE_GENERIC_DOOR_LOCK_KEYPAD                                   0x0300   //Door Lock Keypad  Device Type
																		   
#define ICON_TYPE_GENERIC_FAN_SWITCH                                         0x0400   //Fan Switch  Device Type
																		   
#define ICON_TYPE_GENERIC_GATEWAY                                            0x0500   //Gateway  Device Type

#define ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH                                0x0600   //Light Dimmer Switch  Device Type
#define ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_PLUGIN                        0x0601	  //Light Dimmer, implemented as a plugin device 
#define ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_OUTLET	                 0x0602	  //Light Dimmer, implemented as a wall outlet
#define ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_CEILING_OUTLET	             0x0603	  //Light Dimmer, implemented as a ceiling outlet
#define ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_WALL_LAMP     	             0x0604	  //Relay device, implemented as a wall mounted lamp
#define ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_HIGH	             0x0605	  //Relay device, implemented as a ceiling outlet
#define ICON_TYPE_SPECIFIC_LIGHT_DIMMER_SWITCH_LAMP_POST_LOW	             0x0606	  //Relay device, implemented as a ceiling outlet
																		   																		   
#define ICON_TYPE_GENERIC_POWER_STRIP                                        0x0800   //Power Strip  Device Type
#define ICON_TYPE_SPECIFIC_POWER_STRIP_INDIVIDUAL_OUTLET	                 0x08FF	  //Individual outlet of a power strip for showing outlets in exploded view
																		   
#define ICON_TYPE_GENERIC_REMOTE_CONTROL_AV                                  0x0900   //Remote Control AV  Device Type
																		   
#define ICON_TYPE_GENERIC_REMOTE_CONTROL_MULTI_PURPOSE                       0x0A00   //Remote Control Multi Purpose Device Type
																		   
#define ICON_TYPE_GENERIC_REMOTE_CONTROL_SIMPLE                              0x0B00   //Remote Control Simple Device Type
#define ICON_TYPE_SPECIFIC_REMOTE_CONTROL_SIMPLE_KEYFOB                      0x0B01   //Remote Control Simple Device Type (Key fob)
																		   

#define ICON_TYPE_GENERIC_SENSOR_MULTILEVEL                                  0x0D00   //Sensor Multilevel Device Type

#define ICON_TYPE_GENERIC_SET_TOP_BOX                                        0x0E00   //Set Top Box Device Type
																		   
#define ICON_TYPE_GENERIC_SIREN                                              0x0F00   //Siren Device Type
																		   
#define ICON_TYPE_GENERIC_SUB_ENERGY_METER                                   0x1000   //Sub Energy Meter Device Type
																		   
#define ICON_TYPE_GENERIC_SUB_SYSTEM_CONTROLLER                              0x1100   //Sub System Controller Device Type
																		   
#define ICON_TYPE_GENERIC_THERMOSTAT                                         0x1200   //Thermostat Device Type
#define ICON_TYPE_SPECIFIC_THERMOSTAT_LINE_VOLTAGE                           0x1201   //Thermostat Line Voltage Device Type
#define ICON_TYPE_SPECIFIC_THERMOSTAT_SETBACK                                0x1202   //Thermostat Setback Device Type
																		   
#define ICON_TYPE_GENERIC_THERMOSTAT_SETBACK_OBSOLETED                       0x1300   //Thermostat Setback [Obsoleted] Device Type
																		   
#define ICON_TYPE_GENERIC_TV                                                 0x1400   //TV Device Type
																		   
#define ICON_TYPE_GENERIC_VALVE_OPEN_CLOSE                                   0x1500   //Valve Open/Close Device Type
																		   
#define ICON_TYPE_GENERIC_WALL_CONTROLLER                                    0x1600   //Wall Controller Device Type
																		   
#define ICON_TYPE_GENERIC_WHOLE_HOME_METER_SIMPLE                            0x1700   //Whole Home Meter Simple Device Type
																		   
#define ICON_TYPE_GENERIC_REPEATER                                           0x1B00   //Repeater Device Type 

#define ICON_TYPE_GENERIC_DIMMER_WALL_SWITCH	                             0x1C00	  //Wall Switch
#define ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_ONE_BUTTON	                 0x1C01	  //Wall Switch, 1 button
#define ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_TWO_BUTTONS	                 0x1C02	  //Wall Switch, 2 buttons
#define ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_THREE_BUTTONS	                 0x1C03	  //Wall Switch, 3 buttons
#define ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_FOUR_BUTTONS	                 0x1C04	  //Wall Switch, 4 buttons
#define ICON_TYPE_SPECIFIC_DIMMER_WALL_SWITCH_ONE_ROTARY	                 0x1CF1	  //Wall Switch, 1 rotary knob

#define ICON_TYPE_GENERIC_ON_OFF_WALL_SWITCH	                             0x1D00	  //Wall Switch
#define ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_ONE_BUTTON	                 0x1D01	  //Wall Switch, 1 button
#define ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_TWO_BUTTONS	                 0x1D02	  //Wall Switch, 2 buttons
#define ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_THREE_BUTTONS	                 0x1D03	  //Wall Switch, 3 buttons
#define ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_FOUR_BUTTONS	                 0x1D04	  //Wall Switch, 4 buttons
#define ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_DOOR_BELL                      0x1DE1   //Door Bell (button)
#define ICON_TYPE_SPECIFIC_ON_OFF_WALL_SWITCH_ONE_ROTARY	                 0x1DF1	  //Wall Switch, 1 rotary knob

#define ICON_TYPE_GENERIC_BARRIER                                            0x1E00   //Barrier

#define ICON_TYPE_GENERIC_IRRIGATION                                         0x1F00   //Irrigation

#define ICON_TYPE_GENERIC_ENTRY_CONTROL                                      0x2000   //Entry Control
#define ICON_TYPE_SPECIFIC_ENTRY_CONTROL_KEYPAD_0_9                          0x2001   //Entry Control Keypad 0-9
#define ICON_TYPE_SPECIFIC_ENTRY_CONTROL_RFID_TAG_READER_NO_BUTTON           0x2002   //Entry Control RFID tag reader, no button

#ifndef NEXT_ML_REPORTDELAY 
#define NEXT_ML_REPORTDELAY 3000UL
#endif

#define QUEUE_CHANNEL_SYNC 0x00
#define QUEUE_CHANNEL_CONTROL 0x01
#define QUEUE_CHANNEL_LLREPORT 0x02

extern ZUNOZWConfiguation_t g_zuno_zw_cfg;
uint32_t _zunoSetterValue2Cortex(uint8_t * packet, uint8_t sz);
uint8_t *zuno_AddCommonClassMinimal(uint8_t *b);
uint8_t *zuno_AddCommonClass(uint8_t *b);
int _zunoTransposeSecurityLevel(uint8_t sec);
uint8_t dynamicCCVersion(uint8_t cc);
#define MAX(A, B) (A>B ? A : B)
uint8_t zunoZMEFrequency2Region(uint8_t freqi);
uint8_t zunoRegion2ZMEFrequency(uint8_t freqi);

void zunoSendZWPacket(ZUNOCommandPacket_t * pkg);
void zunoSendZWPacketAdd(ZUNOCommandPacketReport_t *frame);

typedef struct _ZwAssociationGroupCommand_s
{
	uint8_t cmdClass;
	uint8_t cmd;
} _ZwAssociationGroupCommand_t;

void zunoSendReport(byte ch);

#endif // ZW_COMMAND_CLASS_SUPPORT