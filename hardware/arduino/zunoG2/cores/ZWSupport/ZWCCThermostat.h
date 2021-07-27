#ifndef ZWCC_SWITCH_THERMOSTAT_H
#define ZWCC_SWITCH_THERMOSTAT_H

#include "Arduino.h"

/* Switch Thermostat command class commands */
#define COMMAND_CLASS_THERMOSTAT_FAN_MODE                                                0x44
#define COMMAND_CLASS_THERMOSTAT_FAN_STATE                                               0x45
#define COMMAND_CLASS_THERMOSTAT_HEATING                                                 0x38
#define COMMAND_CLASS_THERMOSTAT_OPERATING_STATE                                         0x42
#define COMMAND_CLASS_THERMOSTAT_SETBACK                                                 0x47

/* Thermostat Fan Mode command class commands */
#define THERMOSTAT_FAN_MODE_VERSION                                                      0x01
#define THERMOSTAT_FAN_MODE_GET                                                          0x02
#define THERMOSTAT_FAN_MODE_REPORT                                                       0x03
#define THERMOSTAT_FAN_MODE_SET                                                          0x01
#define THERMOSTAT_FAN_MODE_SUPPORTED_GET                                                0x04
#define THERMOSTAT_FAN_MODE_SUPPORTED_REPORT                                             0x05

/* Thermostat Heating command class commands */
#define THERMOSTAT_HEATING_VERSION                                                       0x01
#define THERMOSTAT_HEATING_STATUS_REPORT                                                 0x0D
#define THERMOSTAT_HEATING_MODE_GET                                                      0x02
#define THERMOSTAT_HEATING_MODE_REPORT                                                   0x03
#define THERMOSTAT_HEATING_MODE_SET                                                      0x01
#define THERMOSTAT_HEATING_RELAY_STATUS_GET                                              0x09
#define THERMOSTAT_HEATING_RELAY_STATUS_REPORT                                           0x0A
#define THERMOSTAT_HEATING_SETPOINT_GET                                                  0x05
#define THERMOSTAT_HEATING_SETPOINT_REPORT                                               0x06
#define THERMOSTAT_HEATING_SETPOINT_SET                                                  0x04
#define THERMOSTAT_HEATING_STATUS_GET                                                    0x0C
#define THERMOSTAT_HEATING_STATUS_SET                                                    0x0B
#define THERMOSTAT_HEATING_TIMED_OFF_SET                                                 0x11

/* Thermostat Mode command class commands */
#define THERMOSTAT_MODE_VERSION                                                          0x03
#define THERMOSTAT_MODE_GET                                                              0x02
#define THERMOSTAT_MODE_REPORT                                                           0x03
#define THERMOSTAT_MODE_SET                                                              0x01
#define THERMOSTAT_MODE_SUPPORTED_GET                                                    0x04
#define THERMOSTAT_MODE_SUPPORTED_REPORT                                                 0x05

/* Thermostat Operating State command class commands */
#define THERMOSTAT_OPERATING_STATE_VERSION                                               0x01
#define THERMOSTAT_OPERATING_STATE_GET                                                   0x02
#define THERMOSTAT_OPERATING_STATE_REPORT                                                0x03

/* Thermostat Setback command class commands */
#define THERMOSTAT_SETBACK_VERSION                                                       0x01
#define THERMOSTAT_SETBACK_GET                                                           0x02
#define THERMOSTAT_SETBACK_REPORT                                                        0x03
#define THERMOSTAT_SETBACK_SET                                                           0x01

/* Thermostat Setpoint command class commands */
#define THERMOSTAT_SETPOINT_VERSION                                                      0x01
#define THERMOSTAT_SETPOINT_GET                                                          0x02
#define THERMOSTAT_SETPOINT_REPORT                                                       0x03
#define THERMOSTAT_SETPOINT_SET                                                          0x01
#define THERMOSTAT_SETPOINT_SUPPORTED_GET                                                0x04
#define THERMOSTAT_SETPOINT_SUPPORTED_REPORT                                             0x05
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET                                             0x09
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT                                          0x0A

int zuno_CCThermostatModeHandler(uint8_t channel, ZUNOCommandPacket_t *cmd);
int zuno_CCThermostatReport(byte channel);
int zuno_CCThermostatSetPointHandler(uint8_t channel, ZUNOCommandPacket_t *cmd);
#endif // ZWCC_SWITCH_THERMOSTAT_H