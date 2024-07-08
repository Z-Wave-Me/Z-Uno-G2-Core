#ifndef ZWCC_BATTERY
#define ZWCC_BATTERY

#include "Arduino.h"
#include "ZWSupport.h"


/* Battery command class commands */
#define BATTERY_VERSION                                                                  0x03
#define BATTERY_GET                                                                      0x02
#define BATTERY_REPORT                                                                   0x03
#define BATTERY_HEALTH_GET                                                               0x04
#define BATTERY_HEALTH_REPORT                                                            0x05
/* Values used for Battery Report command */
#define BATTERY_REPORT_PROPERTIES1_REPLACE_RECHARGE_MASK                                 0x03
#define BATTERY_REPORT_PROPERTIES1_LOW_FLUID_BIT_MASK                                    0x04
#define BATTERY_REPORT_PROPERTIES1_OVERHEATING_BIT_MASK                                  0x08
#define BATTERY_REPORT_PROPERTIES1_BACKUP_BATTERY_BIT_MASK                               0x10
#define BATTERY_REPORT_PROPERTIES1_RECHARGEABLE_BIT_MASK                                 0x20
#define BATTERY_REPORT_PROPERTIES1_CHARGING_STATUS_MASK                                  0xC0
#define BATTERY_REPORT_PROPERTIES1_CHARGING_STATUS_SHIFT                                 0x06
#define BATTERY_REPORT_CHARGING_STATUS_DISCHARGING                                       0x00
#define BATTERY_REPORT_CHARGING_STATUS_CHARGING                                          0x01
#define BATTERY_REPORT_CHARGING_STATUS_MAINTAINING                                       0x02
#define BATTERY_REPORT_PROPERTIES2_DISCONNECTED_BIT_MASK                                 0x01
#define BATTERY_REPORT_PROPERTIES2_LOW_TEMPERATURE_STATUS_BIT_MASK                       0x02
#define BATTERY_REPORT_PROPERTIES2_RESERVED1_MASK                                        0xFC
#define BATTERY_REPORT_PROPERTIES2_RESERVED1_SHIFT                                       0x02
/* Values used for Battery Health Report command */
#define BATTERY_HEALTH_REPORT_PROPERTIES1_SIZE_MASK                                      0x07
#define BATTERY_HEALTH_REPORT_PROPERTIES1_SCALE_MASK                                     0x18
#define BATTERY_HEALTH_REPORT_PROPERTIES1_SCALE_SHIFT                                    0x03
#define BATTERY_HEALTH_REPORT_PROPERTIES1_PRECISION_MASK                                 0xE0
#define BATTERY_HEALTH_REPORT_PROPERTIES1_PRECISION_SHIFT                                0x05


/************************************************************/
/* Battery Report command class structs */                  
/************************************************************/
typedef struct								ZwBatteryReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									batteryLevel;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
}											ZwBatteryReportFrame_t;

typedef enum								ZunoBatteryChargingStatus_e
{
	ZunoBatteryChargingStatusDischarging = 0x0,
	ZunoBatteryChargingStatusCharging,
	ZunoBatteryChargingStatusMaintaining,
}											ZunoBatteryChargingStatus_t;

typedef struct								ZunoBattery_s
{
	ZunoBatteryChargingStatus_t				charging_status;
	bool									replaced_recharged_soon;
	bool									replaced_recharged_now;
	bool									temperature_low;
}											ZunoBattery_t;

bool zunoSendBatteryReportHandler();
void    zunoSendBatteryReport();
int     zuno_CCBattery(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);
void    zuno_CCBattery_OnSetup();
#endif // ZWCC_BATTERY