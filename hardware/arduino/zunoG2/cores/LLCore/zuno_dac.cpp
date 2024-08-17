#include "Arduino.h"
#include "zuno_dac.h"
#include "zuno_gpio_bus_alloc.h"

#if defined(_SILICON_LABS_32B_SERIES_2)
static ZunoGpioBus_t _get_bus_type(uint8_t channel) {
	ZunoGpioBus_t									type;

	switch (channel) {
		case 0x0:
			type = ZunoGpioBusVdac0Ch0;
			break ;
		case 0x1:
			type = ZunoGpioBusVdac0Ch1;
			break ;
		default:
			type = ZunoGpioBusUnknown;
			break ;
	}
	return (type);
}
#endif

/* Public Constructors */
ZunoDacClass::ZunoDacClass(void): _vRef(ZunoDacClassRef1V25), _init(false){
	size_t						i;

	i = 0x0;
	while (i < (sizeof(this->_save) / sizeof(this->_save[0x0]))) {
		this->_save[i].pin = UNKNOWN_PIN;
		i++;
	}
}

/* Public Methods */
bool ZunoDacClass::begin(ZunoDacClassRef_t ref) {
	this->_vRef = ref;
	this->_dac_init(ref);
	this->_init = true;
	return (true);
}

bool ZunoDacClass::write(uint8_t pin, float v) {
	ZunoDacClassChannelProcess_t				process;

	if (this->_init == false)
		return (false);
	if (this->_get_values(&process, pin, v) == false)
		return (false);
	return (this->_write(&process));
}

bool ZunoDacClass::disable(uint8_t pin) {
	uint8_t												i;
	#if defined(_SILICON_LABS_32B_SERIES_2)
	ZunoGpioBus_t										type;
	#endif

	if (pin == UNKNOWN_PIN)
		return (false);
	while (i < (sizeof(this->_save) / sizeof(this->_save[0x0]))) {
		if (this->_save[i].pin == pin) {
			#if defined(_SILICON_LABS_32B_SERIES_2)
			if ((type = _get_bus_type(i)) == ZunoGpioBusUnknown)
				return (false);
			if (zme_gpio_bus_free(pin, type) == false)
				return (false);
			#endif
			this->_save[i].pin = UNKNOWN_PIN;
			VDAC_Enable(VDAC0, i, false);
			return (true);
		}
		i++;
	}
	return (false);
}

/* Private Methods */
bool ZunoDacClass::_test_free_channel(ZunoDacClassChannelProcess_t *process) {
	uint8_t												i;
	uint8_t												i_free;
	uint8_t												n;

	i = 0x0;
	i_free = 0x0;
	n = 0x0;
	while (n < (sizeof(this->_save) / sizeof(this->_save[0x0]))) {
		if (this->_save[n].pin == process[i].pin) {
			process[i].channel = n;
			break ;
		}
		n++;
	}
	if (n >= (sizeof(this->_save) / sizeof(this->_save[0x0]))) {
		while (i_free < (sizeof(this->_save) / sizeof(this->_save[0x0]))) {
			if (this->_save[i_free].pin == UNKNOWN_PIN) {
				process[i].channel = i_free;
				break ;
			}
			i_free++;
		}
		if (i_free >= (sizeof(this->_save) / sizeof(this->_save[0x0])))
			return (false);
	}
	return (true);
}

bool ZunoDacClass::_get_values(ZunoDacClassChannelProcess_t *process, uint8_t pin, float v) {
	uint32_t								in_value;
	uint32_t								ref_value;

	if (v < 0x0)
		return (false);
	in_value = v * 100;
	ref_value = 0x0;
	switch (this->_vRef) {
		case ZunoDacClassRef1V25:
			ref_value = 125;
			break ;
		case ZunoDacClassRef2V5:
			ref_value = 250;
			break ;
	}
	if (in_value > ref_value)
		return (false);
	process->value =((in_value * 4095) / ref_value);
	process->pin = pin;
	return (this->_get_values_series(process, pin));
}


#if defined(_SILICON_LABS_32B_SERIES_2)
bool ZunoDacClass::_write(ZunoDacClassChannelProcess_t *process) {
	uint8_t											i;
	VDAC_InitChannel_TypeDef						initChannel;
	ZunoGpioBus_t									type;

	if (this->_test_free_channel(process) == false)
		return (false);
	if (this->_save[process->channel].pin == UNKNOWN_PIN) {
		if ((type = _get_bus_type(process->channel)) == ZunoGpioBusUnknown)
			return (false);
		if (zme_gpio_bus_alloc(process->pin, type) == false)
			return (false);
		initChannel = VDAC_INITCHANNEL_DEFAULT;
		//initChannel.highCapLoadEnable = false;
		//initChannel.powerMode = vdacPowerModeLowPower;
		initChannel.auxOutEnable = true;
		initChannel.mainOutEnable = false;
		initChannel.port = process->vdac_port;
		initChannel.pin = process->real_pin;
		VDAC_InitChannel(VDAC0, &initChannel, process->channel);
		VDAC_Enable(VDAC0, process->channel, true);
		this->_save[process->channel].value = process->value;
		this->_save[process->channel].pin = process->pin;
	}
	else {
		if (this->_save[process->channel].value == process->value)
			return (true);
		this->_save[process->channel].value = process->value;
		VDAC_ChannelOutputSet(VDAC0, process->channel, process->value);
		return (true);
	}
	i = 0x0;
	while (i < (sizeof(this->_save) / sizeof(this->_save[0x0]))) {
		if (this->_save[i].pin != UNKNOWN_PIN) {
			VDAC_ChannelOutputSet(VDAC0, i, this->_save[i].value);
		}
		i++;
	}
	return (true);
}


bool ZunoDacClass::_get_values_series(ZunoDacClassChannelProcess_t *process, uint8_t pin) {
	uint8_t								real_port;
	VDAC_ChPortSel_t					vdac_port;

	process->real_pin = getRealPin(pin);
	real_port = getRealPort(pin);
	switch (real_port) {
		case gpioPortA:
			vdac_port = vdacChPortA;
			break ;
		case gpioPortB:
			vdac_port = vdacChPortB;
			break ;
		case gpioPortC:
			vdac_port = vdacChPortC;
			break ;
		case gpioPortD:
			vdac_port = vdacChPortD;
			break ;
		default:
			return (false);
			break ;
	}
	process->vdac_port = vdac_port;
	return (true);
}

void ZunoDacClass::_dac_init(ZunoDacClassRef_t ref) {
	VDAC_Init_TypeDef					init = VDAC_INIT_DEFAULT;

	// Use the HFRCOEM23 to clock the VDAC in order to operate in EM3 mode - VDAC to max frequency of 1 MHz
	CMU_ClockSelectSet(cmuClock_VDAC0, cmuSelect_HFRCOEM23);
	// Enable the HFRCOEM23 and VDAC clocks
	CMU_ClockEnable(cmuClock_HFRCOEM23, true);
	CMU_ClockEnable(cmuClock_VDAC0, true);
	// Calculate the VDAC clock prescaler value resulting in a 1 MHz VDAC clock
	init.prescaler = VDAC_PrescaleCalc(VDAC0, 1000000);
	// Clocking is requested on demand
	init.onDemandClk = false;
	init.reference = (VDAC_Ref_TypeDef)ref;
	// // Allocate the analog bus for VDAC0 inputs
	VDAC_Init(VDAC0, &init);
}
#endif

ZunoDacClass DAC = ZunoDacClass();