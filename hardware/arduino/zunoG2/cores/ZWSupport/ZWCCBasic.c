#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCBasic.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCWindowCovering.h"
#include "ZWCCDoorLock.h"

#if defined(WITH_CC_SWITCH_COLOR) && defined(WITH_CC_SWITCH_MULTILEVEL)
__WEAK void __zunoSetterSwitchColorBrightness(uint8_t channel, uint8_t newValue) {
	(void)channel;
	(void)newValue;
}

__WEAK uint8_t __zunoGetterSwitchColorBrightness(uint8_t channel) {
	return (0x0);
	(void)channel;
}
#endif

void __zuno_BasicUniversalSetter1P(byte zuno_ch, uint8_t value) {
    uint8_t type = ZUNO_CFG_CHANNEL(zuno_ch).type;

    switch (type) {
        #ifdef WITH_CC_WINDOW_COVERING
        case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
            __zunoWindowCoveringBasicSet(zuno_ch, value);
            break;
        #endif
        #if defined(WITH_CC_SWITCH_COLOR) && defined(WITH_CC_SWITCH_MULTILEVEL)
        case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
            __zunoSetterSwitchColorBrightness(zuno_ch, value);
            break;
        #endif
        default:
            zuno_universalSetter1P(zuno_ch, value);
            break ;
    }
}

uint8_t __zuno_BasicUniversalGetter1P(byte zuno_ch) {
	uint8_t								value;

	uint8_t type = ZUNO_CFG_CHANNEL(zuno_ch).type;
	switch (type) {
		#ifdef WITH_CC_WINDOW_COVERING
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
			value = __zunoWindowCoveringBasicGet(zuno_ch);
			break;
		#endif
		#if defined(WITH_CC_SWITCH_COLOR) && defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
			value = __zunoGetterSwitchColorBrightness(zuno_ch);
			break;
		#endif
		default:
			value = zuno_universalGetter1P(zuno_ch);
			break ;
	}
	return (value);
}

void __zuno_BasicUniversalTimerStop(uint8_t channel) {
	switch (ZUNO_CFG_CHANNEL(channel).type) {
		#if defined(WITH_CC_SWITCH_COLOR) && defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
		#endif
		#if defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
			__zuno_CCSwitchMultilevelTimerStop(channel);
			break ;
		#endif
		#if defined(WITH_CC_WINDOW_COVERING)
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
			__zuno_CCWindowCoveringTimerStop(channel);
			break ;
		#endif
		#if defined(WITH_CC_SWITCH_BINARY)
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			__zuno_CCSwitchBinaryTimerStop(channel);
			break ;
		#endif
		#if defined(WITH_CC_DOORLOCK)
		case ZUNO_DOORLOCK_CHANNEL_NUMBER:
			__zuno_CCDoorLockTimerStop(channel);
			break ;
		#endif
		#if defined(WITH_CC_SOUND_SWITCH)
		case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
			__zuno_CCSoundSwitchTimerStop(channel);
			break ;
		#endif
		default:
			zuno_CCTimerBasicFindStop(channel);
			break ;
	}
}

void __zuno_BasicUniversalDimingStop(uint8_t channel) {
	switch (ZUNO_CFG_CHANNEL(channel).type) {
		#if defined(WITH_CC_WINDOW_COVERING)
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
			__zuno_CCWindowCoveringDimingStop(channel);
			break ;
		#endif
		default:
			break ;
	}
}
uint8_t __zuno_CCThermostatModeTobasicGet(size_t channel);
void __zuno_BasicUniversalGetCurrentValueDurationTargetValue(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	size_t									type;
	size_t									currentValue;
	size_t									targetValue;
	size_t									duration;
	ZunoTimerBasic_t						*lp;

	type = ZUNO_CFG_CHANNEL(channel).type;
	switch (type) {
		#if defined(WITH_CC_SWITCH_COLOR) && defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
		#endif
		#if defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
			__zuno_CCSwitchMultilevelGetValues(channel, current_value, duration_table_8, target_value);
			break ;
		#endif
		#if defined(WITH_CC_WINDOW_COVERING)
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
			__zuno_CCWindowCoveringGetValues(channel, current_value, duration_table_8, target_value);
			break ;
		#endif
		#if defined(WITH_CC_SWITCH_BINARY)
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			__zuno_CCSwitchBinaryGetValues(channel, current_value, duration_table_8, target_value);
			break ;
		#endif
		#if defined(WITH_CC_DOORLOCK)
		case ZUNO_DOORLOCK_CHANNEL_NUMBER:
			__zuno_CCDoorLockGetValues(channel, current_value, duration_table_8, target_value);
			break ;
		#endif
		#if defined(WITH_CC_SOUND_SWITCH)
		case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
			__zuno_CCSoundSwitchGetValues(channel, current_value, duration_table_8, target_value);
			break ;
		#endif
		default:
			switch (type) {
				#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
				case ZUNO_THERMOSTAT_CHANNEL_NUMBER:
					currentValue = __zuno_CCThermostatModeTobasicGet(channel);
					break;
				#endif
				default:
					currentValue = __zuno_BasicUniversalGetter1P(channel);
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
			zunoExitCritical();
			current_value[0x0] = currentValue;
			target_value[0x0] = targetValue;
			duration_table_8[0x0] = duration;
			break ;
	}
}

#ifdef WITH_CC_BASIC
uint8_t __zuno_CCThermostatModeTobasicSet(uint8_t channel, uint8_t value);
int zuno_CCSoundSwitchBasicSet(size_t channel, size_t toneIdentifier, const ZUNOCommandHandlerOption_t *options);
static int _basic_set(byte channel, const ZwBasicSetFrame_t *paket, const ZUNOCommandHandlerOption_t *options) {
	size_t							value;
	size_t							type;

	type = ZUNO_CFG_CHANNEL(channel).type;
	value = paket->value;
	switch (type) {
		#if defined(WITH_CC_SOUND_SWITCH)
		case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
			return (zuno_CCSoundSwitchBasicSet(channel, value, options));
			break ;
		#endif
	}
	__zuno_BasicUniversalTimerStop(channel);
	switch (type) {
		#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
		case ZUNO_THERMOSTAT_CHANNEL_NUMBER:
			value = __zuno_CCThermostatModeTobasicSet(channel, value);
			break;
		#endif
		#ifdef WITH_CC_SWITCH_BINARY
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			if (value > 0x63 && value < 0xFF)
				return (ZUNO_COMMAND_BLOCKED_FAIL);
			value = value ? 0xFF : 0x00;// Map the value right way
			break;
		#endif
		#if defined(WITH_CC_WINDOW_COVERING) && defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
		#endif
		#if defined(WITH_CC_SWITCH_COLOR) && defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
		#endif
		#if defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
			if (value > 0x63 && value < 0xFF)
				return (ZUNO_COMMAND_BLOCKED_FAIL);
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
	__zuno_BasicUniversalSetter1P(channel, value);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
	(void)options;
}

static int _basic_get(byte channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwBasicReportV2Frame_t					*report;

	report = (ZwBasicReportV2Frame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_BASIC; set in - fillOutgoingPacket
	// report->cmd = BASIC_REPORT; set in - fillOutgoingPacket
	frame_report->info.packet.len = sizeof(ZwBasicReportV2Frame_t);
	__zuno_BasicUniversalGetCurrentValueDurationTargetValue(channel, &report->currentValue, &report->duration, &report->targetValue);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCBasicHandler(byte channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options) {
	int										rs;

	switch(ZW_CMD){
		case BASIC_GET:
			rs = _basic_get(channel, frame_report);
			break ;
		case BASIC_SET:
			rs = _basic_set(channel, (const ZwBasicSetFrame_t *)cmd->cmd, options);
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