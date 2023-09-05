#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCBasic.h"
#include "ZWCCSwitchMultilevel.h"

#ifdef WITH_CC_BASIC
size_t zuno_CCThermostatModeTobasic(size_t channel, size_t value);
int zuno_CCSoundSwitchBasicSet(size_t channel, size_t toneIdentifier);
static int _basic_set(byte channel, const ZwBasicSetFrame_t *paket) {
	size_t							value;
	size_t							type;

	type = ZUNO_CFG_CHANNEL(channel).type;
	value = paket->value;
	#if defined(WITH_CC_SOUND_SWITCH)
	switch (type) {
		#if defined(WITH_CC_SOUND_SWITCH)
		case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
			return (zuno_CCSoundSwitchBasicSet(channel, value));
			break ;
		#endif
		default:
			break ;
	}
	#endif
	zuno_CCTimerBasicFindStop(channel);
	switch (type) {
		#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
		case ZUNO_THERMOSTAT_CHANNEL_NUMBER:
			value = zuno_CCThermostatModeTobasic(channel, value);
			break;
		#endif
		#ifdef WITH_CC_SWITCH_BINARY
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			if (value > 0x63 && value < 0xFF)
				return (ZUNO_COMMAND_BLOCKED_FAILL);
			value = value ? 0xFF : 0x00;// Map the value right way
			break;
		#endif
		#ifdef WITH_CC_WINDOW_COVERING
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
		#endif
		#ifdef WITH_CC_SWITCH_COLOR
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
		#endif
		#ifdef WITH_CC_SWITCH_MULTILEVEL
		case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
			if (value > 0x63 && value < 0xFF)
				return (ZUNO_COMMAND_BLOCKED_FAILL);
			if (value == 0xFF) {
				size_t							tempos;
				if ((tempos = zunoBasicSaveGet(channel)) != 0)
					value = tempos;
				else
				value = 0x63;
			}
			else if (value != 0x0)
				zunoBasicSaveSet(channel, &value);
			break;
		#endif
		default:
			break;
	}
	ZWCC_BASIC_SETTER_1P(channel, value);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSoundSwitchBasicGet(size_t channel, ZwBasicReportV2Frame_t *report);

static int _basic_get(byte channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwBasicReportV2Frame_t					*report;
	ZunoTimerBasic_t						*lp;
	size_t									currentValue;
	size_t									targetValue;
	size_t									duration;
	size_t									type;

	report = (ZwBasicReportV2Frame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_BASIC; set in - fillOutgoingPacket
	// report->cmd = BASIC_REPORT; set in - fillOutgoingPacket
	frame_report->packet.len = sizeof(ZwBasicReportV2Frame_t);
	type = ZUNO_CFG_CHANNEL(channel).type;
	#if defined(WITH_CC_SOUND_SWITCH)
	switch (type) {
		#if defined(WITH_CC_SOUND_SWITCH)
		case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
			return (zuno_CCSoundSwitchBasicGet(channel, report));
			break ;
		#endif
		default:
			break ;
	}
	#endif
	currentValue = ZWCC_BASIC_GETTER_1P(channel);
	switch (type) {
		#if defined(WITH_CC_SWITCH_BINARY) || defined(WITH_CC_DOORLOCK) || defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
		#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
		case ZUNO_THERMOSTAT_CHANNEL_NUMBER:
		#endif
		#if defined(WITH_CC_SWITCH_BINARY)
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
		#endif
		#if defined(WITH_CC_DOORLOCK)
		case ZUNO_DOORLOCK_CHANNEL_NUMBER:
		#endif
			currentValue = currentValue ? 0xFF : 0x00;
			break;
		#endif
		default:
			break;
	}
	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0 && lp->channel != 0x0 && (lp->bMode & ZUNO_TIMER_SWITCH_NO_BASIC) == 0x0) {
		duration = zuno_CCTimerTable8(lp->ticksEnd - lp->ticks);
		targetValue = lp->targetValue;
	}
	else {
		targetValue = currentValue;
		duration = 0x0;
	}
	report->currentValue = currentValue;
	report->targetValue = targetValue;
	report->duration = duration;
	zunoExitCritical();
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCBasicHandler(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int										rs;

	switch(ZW_CMD){
		case BASIC_GET:
			rs = _basic_get(channel, frame_report);
			break ;
		case BASIC_SET:
			rs = _basic_set(channel, (const ZwBasicSetFrame_t *)cmd->cmd);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return rs;
}
// !!!!
// #define EEPROM_BASIC_SAVE_SIZE 32
// #define EEPROM_BASIC_SAVE_ADDR 0x100

void zunoBasicSaveInit(void) {
	uint8_t					buffer_basic[EEPROM_BASIC_SAVE_SIZE];

	memset(&buffer_basic[0x0], 0x0, sizeof(buffer_basic));
	zunoEEPROMWrite(EEPROM_BASIC_SAVE_ADDR, sizeof(buffer_basic), &buffer_basic[0x0]);
}

void zunoBasicSaveSet(uint8_t channel, void *value) {
	zunoEEPROMWrite(EEPROM_BASIC_SAVE_ADDR + channel, 0x1, (uint8_t *)value);
}

uint8_t zunoBasicSaveGet(uint8_t channel) {
	uint8_t								value;

	zunoEEPROMRead(EEPROM_BASIC_SAVE_ADDR + channel, 0x1, &value);
	return (value);
}
#endif