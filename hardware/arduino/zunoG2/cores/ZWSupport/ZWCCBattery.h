#ifndef ZWCC_BATTERY
#define ZWCC_BATTERY
#include "Arduino.h"

#define BATTERY_GET                                                                      0x02
#define BATTERY_REPORT                                                                   0x03

/************************************************************/
/* Battery Report command class structs */                  
/************************************************************/
typedef struct								ZwBatteryReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									batteryLevel;/**/
}											ZwBatteryReportFrame_t;

void    zunoSendBatteryReport();
int     zuno_CCBattery(ZUNOCommandPacket_t * cmd);
void    zuno_CCBattery_OnSetup();
#endif // ZWCC_BATTERY