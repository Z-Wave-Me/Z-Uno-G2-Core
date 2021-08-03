#ifndef ZWCC_TIMER_PARAMETERS_H
#define ZWCC_TIMER_PARAMETERS_H

/* Time Parameters command class commands */
#define TIME_PARAMETERS_VERSION                                                          0x01
#define TIME_PARAMETERS_GET                                                              0x02
#define TIME_PARAMETERS_REPORT                                                           0x03
#define TIME_PARAMETERS_SET                                                              0x01

typedef struct									ZwTimerParametrs_s
{
	uint8_t										year1;/* MSB */
	uint8_t										year2;/* LSB */
	uint8_t										month;/**/
	uint8_t										day;/**/
	uint8_t										hourUtc;/**/
	uint8_t										minuteUtc;/**/
	uint8_t										secondUtc;/**/
}												ZwTimerParametrs_t;

/************************************************************/
/* Time Parameters Report command class structs */          
/************************************************************/
typedef struct									ZwTimerParametrsReportFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	ZwTimerParametrs_t							time;
}												ZwTimerParametrsReportFrame_t;

/************************************************************/
/* Time Parameters Set command class structs */             
/************************************************************/
typedef struct									ZwTimerParametrsSetFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	ZwTimerParametrs_t							time;
}												ZwTimerParametrsSetFrame_t;

int zuno_CCTimerParametrsHandler(ZUNOCommandPacket_t *cmd);
size_t zuno_CCTimerParametrsGet(const ZwTimerParametrs_t *packet, time_t *timeUnix);
void zuno_CCTimerParametrsSet(ZwTimerParametrs_t *packet, time_t time);

#endif// ZWCC_TIMER_PARAMETERS_H