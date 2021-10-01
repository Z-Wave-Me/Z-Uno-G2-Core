#include "ZWCCWakeup.h"
#include "Debug.h"

extern uint8_t     g_outgoing_data[];

static uint8_t    g_wup_sended_notify = 0;
static uint8_t    g_wup_inclusion = 0;
extern uint8_t g_outgoing_report_data[];

typedef struct							ZunoWakeUpSave_s
{
	uint32_t							wakeUpIntervalStepSeconds: 0x18;
	uint32_t							nodeId: 0x8;
}										ZunoWakeUpSave_t;

void _zunoSleepOnWUPStart();
void _zunoSleepOnWUPStop();
bool _zunoIsWUPLocked();

static void __zunoSetupWUPTimeout() {
	ZunoWakeUpSave_t				save;

	zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&save);
	#ifdef LOGGING_DBG
	LOGGING_UART.print("Wakeup timer was set to:");
	LOGGING_UART.print(save.wakeUpIntervalStepSeconds);
	LOGGING_UART.print("seconds");
	#endif
	zunoSetWUPTimer(save.wakeUpIntervalStepSeconds);
}

void zuno_sendWUP_NotificationReport() {
	ZunoWakeUpSave_t				save;
	size_t							wake_nodeid;

	if(zunoNID() == 0)
		return;
	if(_zunoIsWUPLocked()){
		// We have already sent WakeUp notofication and controller haven't responded to it
		#ifdef LOGGING_DBG
		LOGGING_UART.println("WUP Locked!");
		#endif
		return;
	}
	zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&save);
	wake_nodeid = save.nodeId;
	if((wake_nodeid < 0x1) || (wake_nodeid > MAX_NODEID))
		wake_nodeid = 0x1;
	fillOutgoingRawPacket(&g_outgoing_report_packet, g_outgoing_report_data, 0, 0, wake_nodeid);
	g_outgoing_report_packet.src_zw_channel  = 0; 
	// !!! DBG
	#ifdef LOGGING_DBG
	LOGGING_UART.print("SENDING WUP NOTIFICATION! NodeID:");
	LOGGING_UART.println(wake_nodeid);
	#endif
	CMD_REPORT_CC = COMMAND_CLASS_WAKE_UP;
	CMD_REPORT_CMD = WAKE_UP_NOTIFICATION;
	CMD_REPORT_LEN = 2;
	zunoSendZWPackage(&g_outgoing_report_packet);
	_zunoSleepOnWUPStart();
}

void zunoSendWakeUpNotification(void);
void zuno_CCWakeup_OnSetup(){
	//pinMode(BUTTON_PIN, INPUT);
	uint8_t reason = zunoGetWakeReason();
	bool on_timer = (g_zuno_sys->persistent_timer_map & PERSISTENT_SYSTIMER) &&
		((reason == ZUNO_WAKEUP_REASON_WUT_EM4) ||
	     (reason == ZUNO_WAKEUP_REASON_WUT_EM2) );
	bool on_button = false;
	#ifdef LOGGING_DBG
	LOGGING_UART.print("GPIOEM4MASK:");
	LOGGING_UART.println(g_zuno_sys->gpio_em4flags, HEX);
	#endif
	#ifndef NO_BTN_WUP_NOTIFICATION
	on_button = ((g_zuno_sys->gpio_em4flags & zunoMapPin2EM4Bit(BUTTON_PIN)) && ((reason == ZUNO_WAKEUP_REASON_EXT_EM2) ||
	    (reason == ZUNO_WAKEUP_REASON_EXT_EM4)));
	#endif
	if (on_timer || on_button){
		#ifdef LOGGING_DBG
		LOGGING_UART.println("APPEND WAKEUP!");
		#endif
        zunoSendWakeUpNotification();
        return;
    }
	if((reason == ZUNO_WAKEUP_REASON_SOFTRESET) || (reason == ZUNO_WAKEUP_REASON_BROWNOUT) || (reason == ZUNO_WAKEUP_REASON_WATCH_DOG)){    
		__zunoSetupWUPTimeout();
	}
}
void zuno_CCWakeup_OnDefault(){
	ZunoWakeUpSave_t				save;

	// Serial0.println("WUP DEFAULT");
	save.wakeUpIntervalStepSeconds = WAKEUP_INTERVAL_DEFAULT;
	save.nodeId = 0x1;
	zunoEEPROMWrite(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&save);
	__zunoSetupWUPTimeout();
}

static int _up_interval_capabilities_report(void) {
	ZwZwaveWakeUpIntervalCapabilitiesReportFrame_t		*report;

	report = (ZwZwaveWakeUpIntervalCapabilitiesReportFrame_t *)&CMD_REPLY_CC;
	// report->v3.cmdClass = COMMAND_CLASS_WAKE_UP; //set in - fillOutgoingPacket
	// report->v3.cmd = WAKE_UP_INTERVAL_CAPABILITIES_REPORT; //set in - fillOutgoingPacket
	report->v3.minimumWakeUpIntervalSeconds1 = (WAKEUP_INTERVAL_MIN >> 16) & 0xFF;
	report->v3.minimumWakeUpIntervalSeconds2 = (WAKEUP_INTERVAL_MIN >> 8) & 0xFF;
	report->v3.minimumWakeUpIntervalSeconds3 = (WAKEUP_INTERVAL_MIN & 0xFF);
	report->v3.maximumWakeUpIntervalSeconds1 = (WAKEUP_INTERVAL_MAX >> 16) & 0xFF;
	report->v3.maximumWakeUpIntervalSeconds2 = (WAKEUP_INTERVAL_MAX >> 8) & 0xFF;
	report->v3.maximumWakeUpIntervalSeconds3 = (WAKEUP_INTERVAL_MAX & 0xFF);
	report->v3.defaultWakeUpIntervalSeconds1 = (WAKEUP_INTERVAL_DEFAULT >> 16) & 0xFF;
	report->v3.defaultWakeUpIntervalSeconds2 = (WAKEUP_INTERVAL_DEFAULT >> 8) & 0xFF;
	report->v3.defaultWakeUpIntervalSeconds3 = (WAKEUP_INTERVAL_DEFAULT & 0xFF);
	report->v3.wakeUpIntervalStepSeconds1 = (WAKEUP_INTERVAL_STEP >> 16) & 0xFF;
	report->v3.wakeUpIntervalStepSeconds2 = (WAKEUP_INTERVAL_STEP >> 8) & 0xFF;
	report->v3.wakeUpIntervalStepSeconds3 = (WAKEUP_INTERVAL_STEP & 0xFF);
	report->v3.properties1 = 0x0;
	CMD_REPLY_LEN = sizeof(report->v3);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _up_interval_get(void) {
	ZwZwaveWakeUpIntervalReportFrame_t		*report;
	ZunoWakeUpSave_t						save;
	uint32_t								wakeup_data;

	zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (uint8_t *)&save);
	report = (ZwZwaveWakeUpIntervalReportFrame_t *)&CMD_REPLY_CC;
	// report->v3.cmdClass = COMMAND_CLASS_WAKE_UP; //set in - fillOutgoingPacket
	// report->v3.cmd = WAKE_UP_INTERVAL_REPORT; //set in - fillOutgoingPacket
	wakeup_data = save.wakeUpIntervalStepSeconds;
	report->v3.seconds1 = (wakeup_data >> 16) & 0xFF;
	report->v3.seconds2 = (wakeup_data >> 8) & 0xFF;
	report->v3.seconds3 = (wakeup_data & 0xFF);
	report->v3.nodeid = save.nodeId;
	CMD_REPLY_LEN = sizeof(report->v3);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _up_interval_set(const ZwZwaveWakeUpIntervalSetFrame_t *cmd) {
	ZunoWakeUpSave_t						save;

	save.wakeUpIntervalStepSeconds = (cmd->v3.seconds1 << 0x10) | (cmd->v3.seconds2 << 0x8) | (cmd->v3.seconds3);
	save.nodeId = cmd->v3.nodeid;
	zunoEEPROMWrite(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (byte*)&save);
	zunoSetWUPTimer(save.wakeUpIntervalStepSeconds);
	memset(&save, 0x0, EEPROM_WAKEUP_SIZE);
	zunoEEPROMRead(EEPROM_WAKEUP_ADDR, EEPROM_WAKEUP_SIZE, (uint8_t *)&save);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCWakeupHandler(ZUNOCommandPacket_t * cmd) {
	int								rs;

	switch(ZW_CMD) {
		case WAKE_UP_INTERVAL_CAPABILITIES_GET:
			rs = _up_interval_capabilities_report();
			break ;
		case WAKE_UP_INTERVAL_GET:
			rs = _up_interval_get();
			break ;
		case WAKE_UP_INTERVAL_SET:
			rs = _up_interval_set((const ZwZwaveWakeUpIntervalSetFrame_t *)cmd->cmd);
			break ;
		case WAKE_UP_NO_MORE_INFORMATION:
			g_wup_sended_notify = false;
			if(g_wup_inclusion){
				g_wup_inclusion = false;
				#ifdef LOGGING_DBG
				LOGGING_UART.print("Inclusion timer stop");
				#endif
			}
			__zunoSetupWUPTimeout();
			_zunoSleepOnWUPStop();
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return rs;
}