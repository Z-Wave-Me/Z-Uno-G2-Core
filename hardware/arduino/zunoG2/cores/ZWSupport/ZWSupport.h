#ifndef ZW_COMMAND_CLASS_SUPPORT
#define ZW_COMMAND_CLASS_SUPPORT
#define MAX_ZW_PACKAGE 56
#define ZUNO_LIFELINE_GRP 1

// DBG
/*#define LOGGING_DBG                 1
#define WITH_CC_SWITCH_BINARY       1
#define WITH_CC_SWITCH_MULTILEVEL   1
#define WITH_CC_MULTICHANNEL        1*/

//#define LOGGING_DBG 0

#ifdef LOGGING_DBG
#ifndef LOGGING_UART 
#define LOGGING_UART Serial0
#endif
#endif
// 
enum
{
	COMMAND_CLASS_BASIC = 0x20,
	COMMAND_CLASS_SWITCH_BINARY = 0x25,
	COMMAND_CLASS_SWITCH_MULTILEVEL = 0x26,
	COMMAND_CLASS_SENSOR_MULTILEVEL = 0x31,
	COMMAND_CLASS_METER = 0x32,
	COMMAND_CLASS_SWITCH_COLOR = 0x33,
	COMMAND_CLASS_THERMOSTAT_MODE = 0x40,
	COMMAND_CLASS_THERMOSTAT_SETPOINT = 0x43,
	COMMAND_CLASS_MULTICHANNEL = 0x60,
	COMMAND_CLASS_DOOR_LOCK = 0x62,
	COMMAND_CLASS_CONFIGURATION = 0x70,
	COMMAND_CLASS_NOTIFICATION = 0x71,
	COMMAND_CLASS_BATTERY = 0x80,
};


// SINGLE_GETTER
typedef uint8_t zuno_singlegetter1ub_t(void);
typedef uint16_t zuno_singlegetter2ub_t(void);
typedef uint32_t zuno_singlegetter4ub_t(void);
typedef int8_t  zuno_singlegetter1b_t(void);
typedef int16_t zuno_singlegetter2b_t(void);
typedef int32_t zuno_singlegetter4b_t(void);
// MULTI_GETTER
typedef uint8_t zuno_multigetter1ub_t(uint8_t);
typedef uint16_t zuno_multigetter2ub_t(uint8_t);
typedef uint32_t zuno_multigetter4ub_t(uint8_t);
typedef int8_t  zuno_multigetter1b_t(uint8_t);
typedef int16_t zuno_multigetter2b_t(uint8_t);
typedef int32_t zuno_multigetter4b_t(uint8_t);
// SINGLE_SETTER
typedef void zuno_singlesetter1ub_t(uint8_t);
typedef void zuno_singlesetter2ub_t(uint16_t);
typedef void zuno_singlesetter4ub_t(uint32_t);
typedef void zuno_singlesetter1b_t(int8_t);
typedef void zuno_singlesetter2b_t(int16_t);
typedef void zuno_singlesetter4b_t(int32_t);
// MULTI_SETTER
typedef void zuno_multisetter1ub_t(uint8_t, uint8_t);
typedef void zuno_multisetter2ub_t(uint8_t, uint16_t);
typedef void zuno_multisetter4ub_t(uint8_t, uint32_t);
typedef void zuno_multisetter1b_t(uint8_t, int8_t);
typedef void zuno_multisetter2b_t(uint8_t, int16_t);
typedef void zuno_multisetter4b_t(uint8_t, int32_t);


// SINGLE_GETTER 2P
typedef uint8_t zuno_singlegetter1ub_2p_t(uint32_t);
typedef uint16_t zuno_singlegetter2ub_2p_t(uint32_t);
typedef uint32_t zuno_singlegetter4ub_2p_t(uint32_t);
// MULTI_GETTER 2P
typedef uint8_t zuno_multigetter1ub_2p_t(uint8_t, uint32_t);
typedef uint16_t zuno_multigetter2ub_2p_t(uint8_t, uint32_t);
typedef uint32_t zuno_multigetter4ub_2p_t(uint8_t, uint32_t);
// SINGLE_SETTER 2P
typedef void zuno_singlesetter1ub_2p_t(uint32_t, uint8_t);
typedef void zuno_singlesetter2ub_2p_t(uint32_t, uint16_t);
typedef void zuno_singlesetter4ub_2p_t(uint32_t, uint32_t);
// MULTI_SETTER 2P
typedef void zuno_multisetter1ub_2p_t(uint8_t, uint32_t, uint8_t);
typedef void zuno_multisetter2ub_2p_t(uint8_t, uint32_t, uint16_t);
typedef void zuno_multisetter4ub_2p_t(uint8_t, uint32_t, uint32_t);

typedef void zuno_configuration_changed(uint8_t, uint32_t);

// Common CC subroutines and data
extern ZUNOCommandPacket_t g_outgoing_packet;
void zuno_universalSetter1P(byte zuno_ch, int32_t value);
void zuno_universalSetter2P(byte zuno_ch, uint32_t value, uint32_t value_add);
int32_t zuno_universalGetter1P(byte zuno_ch);
uint32_t zuno_universalGetter2P(byte zuno_ch, uint32_t value);
ZUNOChannel_t * zuno_findChannelByZWChannel(byte zw_ch);
void zunoSetupBitMask(byte * arr, byte b, byte max_sz);
byte zuno_findChannelType(byte type, ZUNOChannelCCS_t* types, byte count);
byte getMaxChannelTypes();
void fillOutgoingPacket(ZUNOCommandPacket_t * cmd);
void fillOutgoingReportPacket(uint8_t ch);

#define CMD_REPLY_LEN g_outgoing_packet.len 
#define CMD_REPLY_CMD g_outgoing_packet.cmd[1]
#define CMD_REPLY_DATA(N) g_outgoing_packet.cmd[N+2]
#define CMD_REPLY_CC  g_outgoing_packet.cmd[0]

#define ZW_CMD_CLASS          (cmd->cmd[0])
#define ZW_CMD                (cmd->cmd[1])
#define ZW_CMD_BPARAM(N)      (cmd->cmd[2+N])

#define ZUNO_CFG_CHANNEL_COUNT  (g_zuno_sys->zwave_cfg->num_channels)
#define ZUNO_CFG_CHANNEL(N)     g_zuno_sys->zwave_cfg->channels[N]
#define ZUNO_CFG_TYPE_COUNT     (g_zuno_sys->zwave_cfg->num_channel_types)
#define ZUNO_CFG_TYPE(N)        g_zuno_sys->zwave_cfg->channel_types[N]
#define ZUNO_CFG_TYPES          g_zuno_sys->zwave_cfg->channel_types

/* Device class Av Control Point */
#define GENERIC_TYPE_AV_CONTROL_POINT                                                    0x03 /*AV Control Point*/
#define SPECIFIC_TYPE_NOT_USED                                                           0x00 /*Specific Device Class Not Used*/
#define SPECIFIC_TYPE_DOORBELL                                                           0x12
#define SPECIFIC_TYPE_SATELLITE_RECEIVER                                                 0x04 /*Satellite Receiver*/
#define SPECIFIC_TYPE_SATELLITE_RECEIVER_V2                                              0x11 /*Satellite Receiver V2*/

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
																		   
#define ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH                                0x0700   //On/Off Power Switch  Device Type
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_PLUGIN	                     0x0701	  //Relay device, implemented as a plugin device
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_WALL_OUTLET	                 0x0702	  //Relay device, implemented as a wall outlet
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_CEILING_OUTLET	             0x0703	  //Relay device, implemented as a ceiling outlet
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_WALL_LAMP	                 0x0704	  //Relay device, implemented as a wall mounted lamp
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_HIGH	             0x0705	  //Relay device, implemented as a ceiling outlet
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_LOW	             0x0706	  //Relay device, implemented as a ceiling outlet
																		   
#define ICON_TYPE_GENERIC_POWER_STRIP                                        0x0800   //Power Strip  Device Type
#define ICON_TYPE_SPECIFIC_POWER_STRIP_INDIVIDUAL_OUTLET	                 0x08FF	  //Individual outlet of a power strip for showing outlets in exploded view
																		   
#define ICON_TYPE_GENERIC_REMOTE_CONTROL_AV                                  0x0900   //Remote Control AV  Device Type
																		   
#define ICON_TYPE_GENERIC_REMOTE_CONTROL_MULTI_PURPOSE                       0x0A00   //Remote Control Multi Purpose Device Type
																		   
#define ICON_TYPE_GENERIC_REMOTE_CONTROL_SIMPLE                              0x0B00   //Remote Control Simple Device Type
#define ICON_TYPE_SPECIFIC_REMOTE_CONTROL_SIMPLE_KEYFOB                      0x0B01   //Remote Control Simple Device Type (Key fob)
																		   
#define ICON_TYPE_GENERIC_SENSOR_NOTIFICATION                                0x0C00   //Sensor Notification Device Type
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SMOKE_ALARM                   0x0C01   //Sensor Notification Device Type (Notification type Smoke Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO_ALARM                      0x0C02   //Sensor Notification Device Type (Notification type CO Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO2_ALARM                     0x0C03   //Sensor Notification Device Type (Notification type CO2 Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HEAT_ALARM                    0x0C04   //Sensor Notification Device Type (Notification type Heat Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_ALARM                   0x0C05   //Sensor Notification Device Type (Notification type Water Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_ACCESS_CONTROL                0x0C06   //Sensor Notification Device Type (Notification type Access Control)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_SECURITY                 0x0C07   //Sensor Notification Device Type (Notification type Home Security)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_POWER_MANAGEMENT              0x0C08   //Sensor Notification Device Type (Notification type Power Management)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SYSTEM                        0x0C09   //Sensor Notification Device Type (Notification type System)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_EMERGENCY_ALARM               0x0C0A   //Sensor Notification Device Type (Notification type Emergency Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CLOCK                         0x0C0B   //Sensor Notification Device Type (Notification type Clock)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_APPLIANCE                     0x0C0C
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_HEALTH                   0x0C0D
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SIREN                         0x0C0E
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_VALVE                   0x0C0F
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WEATHER_ALARM                 0x0C10
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_IRRIGATION                    0x0C11
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_GAS_ALARM                     0x0C12
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_MULTIDEVICE                   0x0CFF   //Sensor Notification Device Type (Bundled Notification functions)
																		   
#define ICON_TYPE_GENERIC_SENSOR_MULTILEVEL                                  0x0D00   //Sensor Multilevel Device Type
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_TEMPERATURE                 0x0D01   //Sensor Multilevel Device Type (Sensor type Air Temperature)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_GENERAL_PURPOSE_VALUE           0x0D02   //Sensor Multilevel Device Type (Sensor type General Purpose Value)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LUMINANCE                       0x0D03   //Sensor Multilevel Device Type (Sensor type Luminance)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_POWER                           0x0D04   //Sensor Multilevel Device Type (Sensor type Power)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_HUMIDITY                        0x0D05   //Sensor Multilevel Device Type (Sensor type Humidity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VELOCITY                        0x0D06   //Sensor Multilevel Device Type (Sensor type Velocity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DIRECTION                       0x0D07   //Sensor Multilevel Device Type (Sensor type Direction)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ATMOSPHERIC_PRESSURE            0x0D08   //Sensor Multilevel Device Type (Sensor type Atmospheric Pressure)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BAROMETRIC_PRESSURE             0x0D09   //Sensor Multilevel Device Type (Sensor type Barometric Pressure)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOLOR_RADIATION                 0x0D0A   //Sensor Multilevel Device Type (Sensor type Solar Radiation)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DEW_POINT                       0x0D0B   //Sensor Multilevel Device Type (Sensor type Dew Point)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RAIN_RATE                       0x0D0C   //Sensor Multilevel Device Type (Sensor type Rain Rate)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIDE_LEVEL                      0x0D0D   //Sensor Multilevel Device Type (Sensor type Tide Level)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WEIGHT                          0x0D0E   //Sensor Multilevel Device Type (Sensor type Weight)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VOLTAGE                         0x0D0F   //Sensor Multilevel Device Type (Sensor type Voltage)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CURRENT                         0x0D10   //Sensor Multilevel Device Type (Sensor type Current)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CO2_LEVEL                       0x0D11   //Sensor Multilevel Device Type (Sensor type CO2 Level)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_FLOW                        0x0D12   //Sensor Multilevel Device Type (Sensor type Air Flow)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TANK_CAPACITY                   0x0D13   //Sensor Multilevel Device Type (Sensor type Tank Capacity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DISTANCE                        0x0D14   //Sensor Multilevel Device Type (Sensor type Distance)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ANGLE_POSITION                  0x0D15   //Sensor Multilevel Device Type (Sensor type Angle Position)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ROTATION                        0x0D16   //Sensor Multilevel Device Type (Sensor type Rotation)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_TEMPERATURE               0x0D17   //Sensor Multilevel Device Type (Sensor type Water Temperature)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOIL_TEMPERATURE                0x0D18   //Sensor Multilevel Device Type (Sensor type Soil Temperature)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_INTENSITY               0x0D19   //Sensor Multilevel Device Type (Sensor type Seismic Intensity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_MAGNITUDE               0x0D1A   //Sensor Multilevel Device Type (Sensor type Seismic Magnitude)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ULTRAVIOLET                     0x0D1B   //Sensor Multilevel Device Type (Sensor type Ultraviolet)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_RESISTIVITY          0x0D1C   //Sensor Multilevel Device Type (Sensor type Electrical Resistivity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_CONDUCTIVITY         0x0D1D   //Sensor Multilevel Device Type (Sensor type Electrical Conductivity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LOUDNESS                        0x0D1E   //Sensor Multilevel Device Type (Sensor type Loudness)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MOISTURE                        0x0D1F   //Sensor Multilevel Device Type (Sensor type Moisture)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_FREQUENCY                       0x0D20   //Sensor Multilevel Device Type (Sensor type Frequency)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIME                            0x0D21   //Sensor Multilevel Device Type (Sensor type Time )
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TARGET_TEMPERATURE              0x0D22   //Sensor Multilevel Device Type (Sensor type Target Temperature)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MULTIDEVICE                     0x0DFF   //Sensor Multilevel Device Type (Bundled Sensor functions)
																		   
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
																		   
#define ICON_TYPE_GENERIC_WINDOW_COVERING_NO_POSITION_ENDPOINT               0x1800   //Window Covering No Position/Endpoint  Device Type
																		   
#define ICON_TYPE_GENERIC_WINDOW_COVERING_ENDPOINT_AWARE                     0x1900   //Window Covering Endpoint Aware Device Type
																		   
#define ICON_TYPE_GENERIC_WINDOW_COVERING_POSITION_ENDPOINT_AWARE            0x1A00   //Window Covering Position/Endpoint Aware Device Type

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


typedef struct ZUnoDevTypeDef_s{
	byte gen_type;
	byte spec_type;
	word icon;
	word app_icon; 
}ZUnoDevTypeDef_t;

extern  const ZUNOChannelCCS_t ZUNO_CC_TYPES[];
extern  const ZUnoDevTypeDef_t ZUNO_DEV_TYPES[];
#define MAX(A, B) (A>B ? A : B)
#endif // ZW_COMMAND_CLASS_SUPPORT