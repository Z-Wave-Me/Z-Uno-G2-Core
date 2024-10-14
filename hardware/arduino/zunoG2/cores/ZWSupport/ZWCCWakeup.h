#ifndef ZWCC_WAKEUP
#define ZWCC_WAKEUP
#include "Arduino.h"
#include "ZWSupport.h"

#define WAKE_UP_VERSION                                                               0x03

#define WAKE_UP_INTERVAL_CAPABILITIES_GET                                             0x09
#define WAKE_UP_INTERVAL_CAPABILITIES_REPORT                                          0x0A
#define WAKE_UP_INTERVAL_GET                                                          0x05
#define WAKE_UP_INTERVAL_REPORT                                                       0x06
#define WAKE_UP_INTERVAL_SET                                                          0x04
#define WAKE_UP_NOTIFICATION                                                          0x07
#define WAKE_UP_NO_MORE_INFORMATION                                                   0x08

#ifndef WAKEUP_INTERVAL_MIN 
#define WAKEUP_INTERVAL_MIN                                                           60
#endif 
#ifndef WAKEUP_INTERVAL_MAX 
#define WAKEUP_INTERVAL_MAX                                                           3942000 // 3 years
#endif 
#ifndef WAKEUP_INTERVAL_DEFAULT 
#define WAKEUP_INTERVAL_DEFAULT                                                       3600 // Once in a hour
#endif 
#ifndef WAKEUP_INTERVAL_STEP 
#define WAKEUP_INTERVAL_STEP                                                          1 // One second
#endif 
#define WAKEUP_SLEEP_TIMEOUT                                                          3000
#define WAKEUP_MAXIMUM_CONTROLLER_TIMEOUT                                             15000 
#define WAKEUP_MAXIMUM_LEARN_TIMEOUT                                                  30000 

/************************************************************/
/* Wake Up Interval Capabilities Report V2 command class structs */
/************************************************************/
typedef struct _ZW_WAKE_UP_INTERVAL_CAPABILITIES_REPORT_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   minimumWakeUpIntervalSeconds1;/* MSB */
    uint8_t   minimumWakeUpIntervalSeconds2;
    uint8_t   minimumWakeUpIntervalSeconds3;/* LSB */
    uint8_t   maximumWakeUpIntervalSeconds1;/* MSB */
    uint8_t   maximumWakeUpIntervalSeconds2;
    uint8_t   maximumWakeUpIntervalSeconds3;/* LSB */
    uint8_t   defaultWakeUpIntervalSeconds1;/* MSB */
    uint8_t   defaultWakeUpIntervalSeconds2;
    uint8_t   defaultWakeUpIntervalSeconds3;/* LSB */
    uint8_t   wakeUpIntervalStepSeconds1;   /* MSB */
    uint8_t   wakeUpIntervalStepSeconds2;   
    uint8_t   wakeUpIntervalStepSeconds3;   /* LSB */
} ZW_WAKE_UP_INTERVAL_CAPABILITIES_REPORT_V2_FRAME;


/************************************************************/
/* Wake Up Interval Capabilities Report V3 command class structs */
/************************************************************/
typedef struct _ZW_WAKE_UP_INTERVAL_CAPABILITIES_REPORT_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   minimumWakeUpIntervalSeconds1;/* MSB */
    uint8_t   minimumWakeUpIntervalSeconds2;
    uint8_t   minimumWakeUpIntervalSeconds3;/* LSB */
    uint8_t   maximumWakeUpIntervalSeconds1;/* MSB */
    uint8_t   maximumWakeUpIntervalSeconds2;
    uint8_t   maximumWakeUpIntervalSeconds3;/* LSB */
    uint8_t   defaultWakeUpIntervalSeconds1;/* MSB */
    uint8_t   defaultWakeUpIntervalSeconds2;
    uint8_t   defaultWakeUpIntervalSeconds3;/* LSB */
    uint8_t   wakeUpIntervalStepSeconds1;   /* MSB */
    uint8_t   wakeUpIntervalStepSeconds2;   
    uint8_t   wakeUpIntervalStepSeconds3;   /* LSB */
    uint8_t   properties1;                  /* masked byte */
} ZW_WAKE_UP_INTERVAL_CAPABILITIES_REPORT_V3_FRAME;

typedef union								ZwZwaveWakeUpIntervalCapabilitiesReportFrame_u {//For more convenient support, several versions of commands
	ZW_WAKE_UP_INTERVAL_CAPABILITIES_REPORT_V2_FRAME			v2;
	ZW_WAKE_UP_INTERVAL_CAPABILITIES_REPORT_V3_FRAME			v3;
}											ZwZwaveWakeUpIntervalCapabilitiesReportFrame_t;

/************************************************************/
/* Wake Up Interval Report V3 command class structs */      
/************************************************************/
typedef struct _ZW_WAKE_UP_INTERVAL_REPORT_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   seconds1;                     /* MSB */
    uint8_t   seconds2;                     
    uint8_t   seconds3;                     /* LSB */
    uint8_t   nodeid;                       /**/
} ZW_WAKE_UP_INTERVAL_REPORT_V3_FRAME;

typedef union								ZwZwaveWakeUpIntervalReportFrame_u {//For more convenient support, several versions of commands
	ZW_WAKE_UP_INTERVAL_REPORT_V3_FRAME			v3;
}											ZwZwaveWakeUpIntervalReportFrame_t;


/************************************************************/
/* Wake Up Interval Set V3 command class structs */         
/************************************************************/
typedef struct _ZW_WAKE_UP_INTERVAL_SET_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   seconds1;                     /* MSB */
    uint8_t   seconds2;                     
    uint8_t   seconds3;                     /* LSB */
    uint8_t   nodeid;                       /**/
} ZW_WAKE_UP_INTERVAL_SET_V3_FRAME;

typedef union								ZwZwaveWakeUpIntervalSetFrame_u {//For more convenient support, several versions of commands
	ZW_WAKE_UP_INTERVAL_SET_V3_FRAME			v3;
}											ZwZwaveWakeUpIntervalSetFrame_t;

void zuno_sendWUP_Notification();
void zuno_CCWakeup_OnSetup();
void zuno_CCWakeup_OnDefault();
bool zuno_CCWakeup_BeforeSleep();
int zuno_CCWakeupHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);
void zuno_CCWakeup_OnAnyRx();
void zuno_sendWUP_NotificationReport();


#endif // ZWCC_WAKEUP