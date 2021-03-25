#ifndef ZWCC_TIMER_PARAMETERS_H
#define ZWCC_TIMER_PARAMETERS_H

/* Time Parameters command class commands */
#define TIME_PARAMETERS_VERSION                                                          0x01
#define TIME_PARAMETERS_GET                                                              0x02
#define TIME_PARAMETERS_REPORT                                                           0x03
#define TIME_PARAMETERS_SET                                                              0x01

/************************************************************/
/* Time Parameters Report command class structs */          
/************************************************************/
typedef struct									ZwTimerParametrsReportFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										year1;/* MSB */
	uint8_t										year2;/* LSB */
	uint8_t										month;/**/
	uint8_t										day;/**/
	uint8_t										hourUtc;/**/
	uint8_t										minuteUtc;/**/
	uint8_t										secondUtc;/**/
}												ZwTimerParametrsReportFrame_t;

/************************************************************/
/* Time Parameters Set command class structs */             
/************************************************************/
typedef struct									ZwTimerParametrsSetFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										year1;/* MSB */
	uint8_t										year2;/* LSB */
	uint8_t										month;/**/
	uint8_t										day;/**/
	uint8_t										hourUtc;/**/
	uint8_t										minuteUtc;/**/
	uint8_t										secondUtc;/**/
}												ZwTimerParametrsSetFrame_t;

int zuno_CCTimerParametrs(ZUNOCommandPacket_t *cmd);

#endif// ZWCC_TIMER_PARAMETERS_H