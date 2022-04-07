#include "Arduino.h"
#include "ZWCCIndicator.h"

#define INDICATOR_LED_PIN					29


static uint16_t _dimming = 0x0;
uint64_t rtcc_micros(void);

__WEAK const ZunoIndicatorParameter_t *zunoIndicatorGetParameterArrayUser(void) {
	return (0x0);
}

__WEAK const ZunoIndicatorParameter_t *zunoIndicatorGetParameterArrayUserEnd(void) {
	return (0x0);
}

__WEAK ZunoIndicatorTimer_t *zunoIndicatorGetParameterArrayUserTimer(void) {
	return (0x0);
};

__WEAK void zunoIndicatorDigitalWrite(uint8_t pin, uint8_t value, uint8_t indicatorId) {
	digitalWrite(pin, value);
	(void)indicatorId;
}

__WEAK void zunoIndicatorPinMode(uint8_t pin, uint8_t value, uint8_t indicatorId) {
	pinMode(pin, value);
	(void)indicatorId;
}

static ZunoIndicatorTimer_t _indicator_parameter_timer;
static const ZunoIndicatorParameter_t _indicator_parameter =
{
	.description = 0x0,
	.support_prop_mask = INDICATOR_PROP_SUPPORT_MASK,
	.pin = INDICATOR_LED_PIN,
	.indicatorId = INDICATOR_ID_NODE_IDENTIFY
};

static const ZunoIndicatorParameter_t *_indicatorGetParameterArray(size_t indicatorId) {
	const ZunoIndicatorParameter_t							*parameter_array;
	const ZunoIndicatorParameter_t							*parameter_array_b;
	const ZunoIndicatorParameter_t							*parameter_array_e;
	size_t													tempos;

	if ((parameter_array = zunoIndicatorGetParameterArrayUser()) != 0x0) {
		parameter_array_e = zunoIndicatorGetParameterArrayUserEnd();
		parameter_array_b = parameter_array;
		if (indicatorId != INDICATOR_ID_NA) {
			while (parameter_array_b < parameter_array_e) {
				if (parameter_array_b->indicatorId == indicatorId)
					return (parameter_array_b);
				parameter_array_b++;
			}
		}
		else {
			indicatorId = (size_t)-1;
			while (parameter_array_b < parameter_array_e) {
				if ((tempos = parameter_array_b->indicatorId) < indicatorId) {
					indicatorId = tempos;
					parameter_array = parameter_array_b;
				}
				parameter_array_b++;
			}
			if (indicatorId > INDICATOR_ID_NODE_IDENTIFY)
				parameter_array = &_indicator_parameter;
			return (parameter_array);
		}
	}
	if (indicatorId == INDICATOR_ID_NA || indicatorId == INDICATOR_ID_NODE_IDENTIFY)
		return (&_indicator_parameter);
	return (0x0);
}

static ZunoIndicatorTimer_t *_indicatorGetParameterArrayTimer(size_t indicatorId) {
	const ZunoIndicatorParameter_t							*parameter_array;
	ZunoIndicatorTimer_t									*timer_array;

	if ((parameter_array = _indicatorGetParameterArray(indicatorId)) != 0x0 && parameter_array != &_indicator_parameter) {
		timer_array = zunoIndicatorGetParameterArrayUserTimer();
		return (&timer_array[parameter_array - zunoIndicatorGetParameterArrayUser()]);
	}
	if (indicatorId == INDICATOR_ID_NODE_IDENTIFY)
		return (&_indicator_parameter_timer);
	return (0x0);
}

static const ZunoIndicatorParameter_t *_indicatorGetParameterArrayNext(size_t indicatorId) {
	const ZunoIndicatorParameter_t							*parameter_array;
	const ZunoIndicatorParameter_t							*parameter_array_b;
	const ZunoIndicatorParameter_t							*parameter_array_e;
	size_t													tempos;
	size_t													indicatorId_next;

	if ((parameter_array = zunoIndicatorGetParameterArrayUser()) != 0x0) {
		parameter_array_e = zunoIndicatorGetParameterArrayUserEnd();
		parameter_array_b = parameter_array;
		indicatorId_next = (size_t)-1;
		while (parameter_array_b < parameter_array_e) {
			if ((tempos = parameter_array_b->indicatorId) > indicatorId && indicatorId_next > tempos) {
				indicatorId_next = tempos;
				parameter_array = parameter_array_b;
			}
			parameter_array_b++;
		}
		if (indicatorId_next != (size_t)-1 && (indicatorId >= INDICATOR_ID_NODE_IDENTIFY || indicatorId_next <= INDICATOR_ID_NODE_IDENTIFY))
			return (parameter_array);
	}
	if (indicatorId < INDICATOR_ID_NODE_IDENTIFY)
		return (&_indicator_parameter);
	return (0x0);
}

static int _indicator_supported_report(const ZW_INDICATOR_SUPPORTED_GET_V4_FRAME *frame) {
	const ZunoIndicatorParameter_t							*parameter_array;
	ZwIndicatorSupportedReportFrame_t						*report;
	size_t													indicatorId;
	size_t													len;
	uint32_t												support_prop_mask;

	report = (ZwIndicatorSupportedReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_INDICATOR; set in - fillOutgoingPacket
	// report->cmd = INDICATOR_SUPPORTED_REPORT_V4; set in - fillOutgoingPacket
	if ((parameter_array = _indicatorGetParameterArray(frame->indicatorId)) == 0x0) {
		report->indicatorId = INDICATOR_ID_NA;
		report->nextIndicatorId = INDICATOR_ID_NA;
		report->properties1 = 0x0;
		len =  sizeof(report[0x0]);
	}
	else {
		indicatorId = parameter_array->indicatorId;
		report->indicatorId = indicatorId;
		support_prop_mask = parameter_array->support_prop_mask;
		len = ((((sizeof(support_prop_mask) * 0x8) - __builtin_clz(support_prop_mask)) >> 0x3) + 0x1);
		report->properties1 = len;
		memcpy(&report->propertySupportedBitMask[0x0], (uint8_t *)&support_prop_mask, len);
		len = sizeof(report[0x0]) + len;
		if ((parameter_array = _indicatorGetParameterArrayNext(indicatorId)) == 0x0)
			indicatorId = INDICATOR_ID_NA;
		else
			indicatorId = parameter_array->indicatorId;
		report->nextIndicatorId = indicatorId;
	}
	CMD_REPLY_LEN = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _indicator_description_report(const ZW_INDICATOR_DESCRIPTION_GET_V4_FRAME *frame) {
	const ZunoIndicatorParameter_t							*parameter_array;
	ZwIndicatorDescriptionReportFrame_t						*report;
	size_t													indicatorId;
	size_t													len;
	const char												*description;

	report = (ZwIndicatorDescriptionReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_INDICATOR; set in - fillOutgoingPacket
	// report->cmd = INDICATOR_DESCRIPTION_REPORT_V4; set in - fillOutgoingPacket
	indicatorId = frame->indicatorId;
	report->indicatorId = indicatorId;
	if (indicatorId < 0x80 || indicatorId > 0x9F || (parameter_array = _indicatorGetParameterArray(indicatorId)) == 0x0) {
		report->descriptionLength = 0x0;
		len =  sizeof(report[0x0]);
	}
	else {
		if ((description = parameter_array->description) == 0x0)
			description = "Manufacturer Defined";
		len = strlen(description);
		if (len > (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(report[0x0])))
			len = (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(report[0x0]));
		report->descriptionLength = len;
		memcpy(&report->description[0x0], description, len);
		len = sizeof(report[0x0]) + len;
	}
	CMD_REPLY_LEN = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _indicator_report(const ZwIndicatorGetFrame_t *frame, size_t len) {
	ZwIndicatorReportFrame_t						*report;
	ZunoIndicatorTimer_t							*timer_array;
	size_t											value;
	size_t											indicatorId;

	report = (ZwIndicatorReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_INDICATOR; set in - fillOutgoingPacket
	// report->cmd = INDICATOR_REPORT_V4; set in - fillOutgoingPacket
	if (len == sizeof(frame->v1)) {
		timer_array = _indicatorGetParameterArrayTimer(INDICATOR_ID_NODE_IDENTIFY);
		switch (timer_array->type_prop) {
			case INDICATOR_PROP_TYPE_TIMEOUT:
				if (timer_array->ms != 0x0)
					value = 0xFF;
				else
					value = 0x0;
				break ;
			case INDICATOR_PROP_TYPE_TOGGLING:
				if (timer_array->ms != 0x0 && timer_array->prop.toggling.state == INDICATOR_TOGGLING_STATE_ON)
					value = 0xFF;
				else
					value = 0x0;
				break ;
			case INDICATOR_PROP_TYPE_BINARY:
			default:
				value = timer_array->prop.binary.value;
				break ;
		}
		report->v1.value = value;
		CMD_REPLY_LEN = sizeof(report->v1);
		return (ZUNO_COMMAND_ANSWERED);
	}
	report->v4.indicator0Value = 0x0;
	indicatorId = frame->v4.indicatorId;
	if ((timer_array = _indicatorGetParameterArrayTimer(indicatorId)) == 0x0) {
		len = 0x1;
		report->v4.variantgroup[0x0].indicatorId = INDICATOR_ID_NA;
		report->v4.variantgroup[0x0].propertyId = 0x0;
		report->v4.variantgroup[0x0].value = 0x0;
	}
	else {
		switch (timer_array->type_prop) {
			case INDICATOR_PROP_TYPE_TIMEOUT:
				len = 0x3;
				report->v4.variantgroup[0x0].indicatorId = indicatorId;
				report->v4.variantgroup[0x0].propertyId = INDICATOR_PROP_TIMEOUT_HOURS;
				report->v4.variantgroup[0x0].value = timer_array->prop.timeout.hours;
				report->v4.variantgroup[0x1].indicatorId = indicatorId;
				report->v4.variantgroup[0x1].propertyId = INDICATOR_PROP_TIMEOUT_MINUTES;
				report->v4.variantgroup[0x1].value = timer_array->prop.timeout.minutes;
				report->v4.variantgroup[0x2].indicatorId = indicatorId;
				report->v4.variantgroup[0x2].propertyId = INDICATOR_PROP_TIMEOUT_SECONDS;
				report->v4.variantgroup[0x2].value = timer_array->prop.timeout.seconds;
				break ;
			case INDICATOR_PROP_TYPE_TOGGLING:
				len = 0x3;
				report->v4.variantgroup[0x0].indicatorId = indicatorId;
				report->v4.variantgroup[0x0].propertyId = INDICATOR_PROP_TOGGLING_ON_OFF_PERIOD;
				report->v4.variantgroup[0x0].value = timer_array->prop.toggling.on_off_period;
				report->v4.variantgroup[0x1].indicatorId = indicatorId;
				report->v4.variantgroup[0x1].propertyId = INDICATOR_PROP_TOGGLING_ON_OFF_CYCLES;
				report->v4.variantgroup[0x1].value = timer_array->prop.toggling.on_off_cycles;
				report->v4.variantgroup[0x2].indicatorId = indicatorId;
				report->v4.variantgroup[0x2].propertyId = INDICATOR_PROP_TOGGLING_ON_TIME;
				report->v4.variantgroup[0x2].value = timer_array->prop.toggling.on_time;
				break ;
			case INDICATOR_PROP_TYPE_BINARY:
			default:
				len = 0x1;
				report->v4.variantgroup[0x0].indicatorId = indicatorId;
				report->v4.variantgroup[0x0].propertyId = INDICATOR_PROP_BINARY;
				report->v4.variantgroup[0x0].value = timer_array->prop.binary.value;
				break ;
		}

	}
	report->v4.properties1 = len;
	CMD_REPLY_LEN = (sizeof(report->v4) + (len * sizeof(report->v4.variantgroup[0x0])));
	return (ZUNO_COMMAND_ANSWERED);
}

static ZunoIndicatorTimer_t *_indicator_set_get_timer(const ZunoIndicatorParameter_t *parameter_array) {
	ZunoIndicatorTimer_t									*timer_array;

	if ( parameter_array != &_indicator_parameter) {
		timer_array = zunoIndicatorGetParameterArrayUserTimer();
		return (&timer_array[parameter_array - zunoIndicatorGetParameterArrayUser()]);
	}
	return (&_indicator_parameter_timer);
}

static void _lock_sleep(ZunoIndicatorTimer_t *timer_array, size_t new_sleep_lock) {
	static uint16_t							count = 0x0;
	size_t									old_sleep_lock;

	old_sleep_lock = timer_array->sleep_lock;
	timer_array->sleep_lock = new_sleep_lock;
	if (new_sleep_lock == true) {
		if (old_sleep_lock == false)
			count++;
		g_sleep_data.indicator_latch = true;
	}
	else {
		if (old_sleep_lock == true)
			count--;
		if (count == 0x0)
			g_sleep_data.indicator_latch = false;
	}
}

static void _set_ms(ZunoIndicatorTimer_t *timer_array, uint64_t ms) {
	uint64_t								ms_old;

	ms_old = timer_array->ms;
	if (ms == 0x0) {
		if (ms_old != 0x0)
			_dimming--;
	}
	else {
		if (ms_old == 0x0)
			_dimming++;
	}
	timer_array->ms = ms;
}

static void _timer_update_toggling(const ZunoIndicatorParameter_t *parameter_array, ZunoIndicatorTimer_t *timer_array, uint64_t ms_current) {
	size_t									value;
	size_t									state;
	size_t									on_off_cycles;

	if ((on_off_cycles = timer_array->prop.toggling.loop) == 0x0) {
		memset(&timer_array->prop.toggling, 0x0, sizeof(timer_array->prop.toggling));
		_set_ms(timer_array, 0x0);
		_lock_sleep(timer_array, false);
		zunoExitCritical();
		return ;
	}
	switch (timer_array->prop.toggling.state) {
		case INDICATOR_TOGGLING_STATE_ON:
			value = HIGH;
			state = INDICATOR_TOGGLING_STATE_OFF;
			ms_current = ms_current + timer_array->prop.toggling.on_time_ms;
			break ;
		case INDICATOR_TOGGLING_STATE_OFF:
		default:
			value = LOW;
			state = INDICATOR_TOGGLING_STATE_ON;
			ms_current = ms_current + timer_array->prop.toggling.off_time_ms;
			if (on_off_cycles != 0xFF)
				timer_array->prop.toggling.loop--;
			break;
	}
	timer_array->prop.toggling.state = state;
	_set_ms(timer_array, ms_current);
	zunoExitCritical();
	zunoIndicatorDigitalWrite(parameter_array->pin, value, parameter_array->indicatorId);
}

static void _timer_update(const ZunoIndicatorParameter_t *parameter_array, ZunoIndicatorTimer_t *timer_array, uint64_t ms_current) {
	uint64_t											ms;

	zunoEnterCritical();
	if ((ms = timer_array->ms) == 0x0 || ms > ms_current)
		return (zunoExitCritical());
	switch (timer_array->type_prop) {
		case INDICATOR_PROP_TYPE_TOGGLING:
			_timer_update_toggling(parameter_array, timer_array, ms_current);
			break ;
		default:
			zunoExitCritical();
			break ;
	}
}

void zuno_CCIndicatorTimer(void) {
	const ZunoIndicatorParameter_t						*parameter_array_b;
	const ZunoIndicatorParameter_t						*parameter_array_e;
	ZunoIndicatorTimer_t								*timer_array;
	uint64_t											ms;
	uint64_t											ms_current;

	if (_dimming == 0x0)
		return ;
	ms_current = rtcc_micros() / 1000;
	if ((ms = _indicator_parameter_timer.ms) != 0x0 && ms <= ms_current)
		_timer_update(&_indicator_parameter, &_indicator_parameter_timer, ms_current);
	if ((parameter_array_b = zunoIndicatorGetParameterArrayUser()) == 0x0)
		return ;
	parameter_array_e = zunoIndicatorGetParameterArrayUserEnd();
	timer_array = zunoIndicatorGetParameterArrayUserTimer();
	while (parameter_array_b < parameter_array_e) {
		if ((ms = timer_array->ms ) != 0x0 && ms <= ms_current)
			_timer_update(parameter_array_b, timer_array, ms_current);
		parameter_array_b++;
		timer_array++;
	}
}

static void _indicator_set_timeout(const ZunoIndicatorParameter_t *parameter_array, ZunoIndicatorTimerProp_t *prop) {
	// ZunoIndicatorTimer_t					*timer_array;
	// // size_t									

	// zunoEnterCritical();
	// timer_array->type_prop = INDICATOR_PROP_TYPE_TOGGLING;
	// _set_ms(timer_array, (rtcc_micros() / 1000));
	// zunoExitCritical();
	(void)parameter_array;
	(void)prop;
}

static void _indicator_set_toggling(const ZunoIndicatorParameter_t *parameter_array, ZunoIndicatorTimerProp_t *prop) {
	size_t									on_off_period;
	size_t									on_off_cycles;
	size_t									on_time;
	ZunoIndicatorTimer_t					*timer_array;
	size_t									on_time_ms;
	size_t									off_time_ms;
	size_t									on_off_period_length_ms;

	timer_array = _indicator_set_get_timer(parameter_array);
	zunoEnterCritical();
	timer_array->type_prop = INDICATOR_PROP_TYPE_TOGGLING;
	on_off_cycles = prop->toggling.on_off_cycles;
	on_off_period = prop->toggling.on_off_period;
	if (on_off_cycles == 0x0 || on_off_period <= 0x1) {
		memset(&timer_array->prop.toggling, 0x0, sizeof(timer_array->prop.toggling));
		_set_ms(timer_array, 0x0);
		_lock_sleep(timer_array, false);
		zunoExitCritical();
		zunoIndicatorDigitalWrite(parameter_array->pin, LOW, parameter_array->indicatorId);
	}
	on_time = prop->toggling.on_time;
	timer_array->prop.toggling.on_off_period = on_off_period;
	timer_array->prop.toggling.on_off_cycles = on_off_cycles;
	timer_array->prop.toggling.loop = on_off_cycles;
	timer_array->prop.toggling.on_time = on_time;
	timer_array->prop.toggling.state = INDICATOR_TOGGLING_STATE_ON;
	on_off_period_length_ms = on_off_period * 100;
	if (on_time >= on_off_period || on_time == 0x0)
		on_time_ms = on_off_period_length_ms / 0x2;
	else
		on_time_ms = on_time * 100;
	off_time_ms = on_off_period_length_ms - on_time_ms;
	timer_array->prop.toggling.on_time_ms = on_time_ms;
	timer_array->prop.toggling.off_time_ms = off_time_ms;
	_set_ms(timer_array, (rtcc_micros() / 1000));
	_lock_sleep(timer_array, true);
	zunoExitCritical();
}

static size_t _indicator_set_binary(const ZunoIndicatorParameter_t *parameter_array, ZunoIndicatorTimerProp_t *prop) {
	ZunoIndicatorTimer_t							*timer_array;
	size_t											value;
	size_t											sleep_lock;

	value = prop->binary.value;
	if (value < 0x64 || value == 0xFF) {
		timer_array = _indicator_set_get_timer(parameter_array);
		zunoEnterCritical();
		timer_array->type_prop = INDICATOR_PROP_TYPE_BINARY;
		timer_array->prop.binary.value = value;
		if (value != 0x0) {
			sleep_lock = true;
			value = HIGH;
		}
		else {
			_set_ms(timer_array, 0x0);
			sleep_lock = false;
			value = LOW;
		}
		_lock_sleep(timer_array, sleep_lock);
		zunoExitCritical();
		zunoIndicatorDigitalWrite(parameter_array->pin, value, parameter_array->indicatorId);
		return (true);
	}
	return (false);
}

static int _indicator_set_v1(size_t value) {
	ZunoIndicatorTimerProp_t						prop;

	prop.binary.value = value;
	return (_indicator_set_binary(_indicatorGetParameterArray(INDICATOR_ID_NODE_IDENTIFY), &prop));
}

static void _indicator_set_clear(size_t indicatorId, VG_INDICATOR_SET_V4_VG *variantgroup, VG_INDICATOR_SET_V4_VG *variantgroup_e) {
	while (variantgroup < variantgroup_e) {
		if (indicatorId == variantgroup->indicatorId)
			variantgroup->indicatorId = INDICATOR_ID_NA;
		variantgroup++;
	}
}

static void _indicator_set_clear_mask(size_t indicatorId, VG_INDICATOR_SET_V4_VG *variantgroup, VG_INDICATOR_SET_V4_VG *variantgroup_e, uint32_t prop_mask) {
	while (variantgroup < variantgroup_e) {
		if (indicatorId == variantgroup->indicatorId) {
			if ((prop_mask & (0x1 << variantgroup->propertyId)) != 0x0)
				variantgroup->indicatorId = INDICATOR_ID_NA;
		}
		variantgroup++;
	}
}

static uint32_t _indicator_set_find_mask(size_t indicatorId, VG_INDICATOR_SET_V4_VG *variantgroup, VG_INDICATOR_SET_V4_VG *variantgroup_e, uint32_t prop_mask) {
	size_t									propertyId;

	while (variantgroup < variantgroup_e) {
		if (indicatorId == variantgroup->indicatorId) {
			propertyId = (0x1 << variantgroup->propertyId);
			if ((prop_mask & propertyId) != 0x0)
				prop_mask = prop_mask ^ propertyId;
		}
		variantgroup++;
	}
	return (prop_mask);
}


static int _indicator_set_v4(size_t indicatorId, uint32_t prop_mask, VG_INDICATOR_SET_V4_VG *variantgroup, VG_INDICATOR_SET_V4_VG *variantgroup_e, const ZunoIndicatorParameter_t *parameter_array, int result) {
	ZunoIndicatorTimerProp_t						prop;
	size_t											propertyId;
	size_t											value;
	uint32_t										prop_mask_new;
	VG_INDICATOR_SET_V4_VG							*variantgroup_save;

	memset(&prop, 0x0, sizeof(prop));
	prop_mask_new = 0x0;
	variantgroup_save = variantgroup;
	while (variantgroup < variantgroup_e) {
		if (indicatorId == variantgroup->indicatorId) {
			propertyId = variantgroup->propertyId;
			if ((prop_mask & (0x1 << propertyId)) != 0x0) {
				variantgroup->indicatorId = INDICATOR_ID_NA;
				value = variantgroup->value;
				switch (variantgroup->propertyId) {
					case INDICATOR_PROP_BINARY:
						prop.binary.value = value;
						break ;
					case INDICATOR_PROP_TOGGLING_ON_OFF_PERIOD:
						prop.toggling.on_off_period = value;
						prop_mask_new = prop_mask_new | (0x1 << INDICATOR_PROP_TOGGLING_ON_OFF_PERIOD);
						break ;
					case INDICATOR_PROP_TOGGLING_ON_OFF_CYCLES:
						prop.toggling.on_off_cycles = value;
						prop_mask_new = prop_mask_new | (0x1 << INDICATOR_PROP_TOGGLING_ON_OFF_CYCLES);
						break ;
					case INDICATOR_PROP_TOGGLING_ON_TIME:
						prop.toggling.on_time = value;
						break ;
					case INDICATOR_PROP_TIMEOUT_HOURS:
						prop.timeout.hours = value;
						break ;
					case INDICATOR_PROP_TIMEOUT_MINUTES:
						prop.timeout.minutes = value;
						break ;
					case INDICATOR_PROP_TIMEOUT_SECONDS:
						prop.timeout.seconds = value;
						break ;
				}
			}
		}
		variantgroup++;
	}
	switch (prop_mask) {
		case (INDICATOR_PROP_BINARY_MASK):
			if (_indicator_set_binary(parameter_array, &prop) == false)
				result = ZUNO_COMMAND_BLOCKED_FAILL;
			else
				_indicator_set_clear(indicatorId, variantgroup_save, variantgroup_e);
			break ;
		case (INDICATOR_PROP_TOGGLING_MASK):
			if (prop_mask_new != ((0x1 << INDICATOR_PROP_TOGGLING_ON_OFF_PERIOD) | (0x1 << INDICATOR_PROP_TOGGLING_ON_OFF_CYCLES))) {
				result = ZUNO_COMMAND_BLOCKED_FAILL;
				break ;
			}
			_indicator_set_toggling(parameter_array, &prop);
			_indicator_set_clear(indicatorId, variantgroup_save, variantgroup_e);
			break ;
		case (INDICATOR_PROP_TIMEOUT_MASK):
				if (_indicator_set_find_mask(indicatorId, variantgroup_save, variantgroup_e, ((0x1 << INDICATOR_PROP_TOGGLING_ON_OFF_PERIOD) | (0x1 << INDICATOR_PROP_TOGGLING_ON_OFF_CYCLES))) != 0x0) {
					_indicator_set_timeout(parameter_array, &prop);
					_indicator_set_clear(indicatorId, variantgroup_save, variantgroup_e);
				}
				else
					_indicator_set_clear_mask(indicatorId, variantgroup_save, variantgroup_e, (INDICATOR_PROP_TIMEOUT_MASK));
			break ;
	}
	return (result);
}

static int _indicator_set_find_na(VG_INDICATOR_SET_V4_VG *variantgroup_b, VG_INDICATOR_SET_V4_VG *variantgroup_e) {
	while (variantgroup_b < variantgroup_e) {
		if (variantgroup_b->indicatorId == INDICATOR_ID_NA)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		variantgroup_b++;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static int _indicator_set(const ZwIndicatorSetFrame_t *frame, size_t len) {
	size_t											indicatorId;
	const ZunoIndicatorParameter_t					*parameter_array;
	VG_INDICATOR_SET_V4_VG							*variantgroup;
	VG_INDICATOR_SET_V4_VG							*variantgroup_e;
	VG_INDICATOR_SET_V4_VG							vg[((ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(frame->v4)) / sizeof(variantgroup[0x0]))];
	int												result;
	size_t											propertyId;

	if (len == sizeof(frame->v1))
		return (_indicator_set_v1(frame->v1.value));
	len = frame->v4.properties1 & INDICATOR_SET_PROPERTIES1_INDICATOR_OBJECT_COUNT_MASK_V4;
	if (len == 0x0)
		return (_indicator_set_v1(frame->v4.indicator0Value));
	if (len > ((ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(frame->v4)) / sizeof(variantgroup[0x0])))
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	memcpy(&vg[0x0], &frame->v4.variantgroup[0x0], len * sizeof(variantgroup[0x0]));
	variantgroup = &vg[0x0];
	variantgroup_e = &vg[len];
	result = _indicator_set_find_na(variantgroup, variantgroup_e);
	while (variantgroup < variantgroup_e) {
		if ((indicatorId = variantgroup->indicatorId) != INDICATOR_ID_NA) {
			if ((parameter_array = _indicatorGetParameterArray(indicatorId)) != 0x0) {
				propertyId = variantgroup->propertyId;
				if ((parameter_array->support_prop_mask & (0x1 << propertyId)) != 0x0) {
					switch (propertyId) {
						case INDICATOR_PROP_BINARY:
							result = _indicator_set_v4(indicatorId, (INDICATOR_PROP_BINARY_MASK), variantgroup, variantgroup_e, parameter_array, result);
							break ;
						case INDICATOR_PROP_TIMEOUT_HOURS:
						case INDICATOR_PROP_TIMEOUT_MINUTES:
						case INDICATOR_PROP_TIMEOUT_SECONDS:
							result = _indicator_set_v4(indicatorId, (INDICATOR_PROP_TIMEOUT_MASK), variantgroup, variantgroup_e, parameter_array, result);
							break ;
						case INDICATOR_PROP_TOGGLING_ON_OFF_PERIOD:
						case INDICATOR_PROP_TOGGLING_ON_OFF_CYCLES:
						case INDICATOR_PROP_TOGGLING_ON_TIME:
							result = _indicator_set_v4(indicatorId, (INDICATOR_PROP_TOGGLING_MASK), variantgroup, variantgroup_e, parameter_array, result);
							break ;
						default:
							result = ZUNO_COMMAND_BLOCKED_FAILL;
							break ;
					}
				}
				else
					result = ZUNO_COMMAND_BLOCKED_FAILL;
			}
			else
				result = ZUNO_COMMAND_BLOCKED_FAILL;
		}
		variantgroup++;
	}
	return (result);
}

void zunoIndicatorInit() {
	static uint8_t											init = false;
	const ZunoIndicatorParameter_t							*parameter_array_b;
	const ZunoIndicatorParameter_t							*parameter_array_e;
	size_t													indicatorId;
	size_t													tempos;

	if (init == true)
		return ;
	init = true;
	parameter_array_b = zunoIndicatorGetParameterArrayUser();
	parameter_array_e = zunoIndicatorGetParameterArrayUserEnd();
	tempos = 0x0;
	while (parameter_array_b < parameter_array_e) {
		indicatorId = parameter_array_b->indicatorId;
		if (indicatorId == INDICATOR_ID_NODE_IDENTIFY)
			tempos++;
		zunoIndicatorPinMode(parameter_array_b->pin, OUTPUT_DOWN, indicatorId);
		parameter_array_b++;
	}
	if (tempos == 0x0)
		zunoIndicatorPinMode(_indicator_parameter.pin, OUTPUT_DOWN, _indicator_parameter.indicatorId);
}

int zuno_CCIndicatorHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	zunoIndicatorInit();
	switch(ZW_CMD) {
		case INDICATOR_SET_V4:
			rs = _indicator_set((const ZwIndicatorSetFrame_t *)&cmd->cmd[0x0], cmd->len);
			break ;
		case INDICATOR_GET_V4:
			rs = _indicator_report((const ZwIndicatorGetFrame_t *)&cmd->cmd[0x0], cmd->len);
			break ;
		case INDICATOR_DESCRIPTION_GET_V4:
			rs = _indicator_description_report((const ZW_INDICATOR_DESCRIPTION_GET_V4_FRAME *)&cmd->cmd[0x0]);
			break ;
		case INDICATOR_SUPPORTED_GET_V4:
			rs = _indicator_supported_report((const ZW_INDICATOR_SUPPORTED_GET_V4_FRAME *)&cmd->cmd[0x0]);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}
