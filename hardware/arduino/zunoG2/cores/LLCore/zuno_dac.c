#include "Arduino.h"
#include "em_vdac.h"
#include "zuno_dac.h"
#include "HardwareSerial.h"

#if defined(_SILICON_LABS_32B_SERIES_2)

#define ZUNO_DAC_REFERENCE						2.5f

static void _zuno_dac_init(void) {
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
	init.reference = vdacRef2V5;
	// // Allocate the analog bus for VDAC0 inputs
	GPIO->ABUSALLOC |= (GPIO_ABUSALLOC_AEVEN0_VDAC0CH0 | GPIO_ABUSALLOC_AODD0_VDAC0CH0) | (GPIO_ABUSALLOC_AEVEN1_VDAC0CH1 | GPIO_ABUSALLOC_AODD1_VDAC0CH1);
	GPIO->BBUSALLOC |= (GPIO_BBUSALLOC_BEVEN0_VDAC0CH0 | GPIO_BBUSALLOC_BODD0_VDAC0CH0) | (GPIO_BBUSALLOC_BEVEN1_VDAC0CH1 | GPIO_BBUSALLOC_BODD1_VDAC0CH1);
	GPIO->CDBUSALLOC |= (GPIO_CDBUSALLOC_CDEVEN0_VDAC0CH0 | GPIO_CDBUSALLOC_CDODD0_VDAC0CH0) | (GPIO_CDBUSALLOC_CDEVEN1_VDAC0CH1 | GPIO_CDBUSALLOC_CDODD1_VDAC0CH1);
	VDAC_Init(VDAC0, &init);
}

static void _zuno_dac_init_channel(uint8_t channel, VDAC_ChPortSel_t vdac_port, uint8_t real_pin) {
	VDAC_InitChannel_TypeDef			initChannel = VDAC_INITCHANNEL_DEFAULT;

	// Disable High Capacitance Load mode
	initChannel.highCapLoadEnable = false;
	// Use Low Power mode
	initChannel.powerMode = vdacPowerModeLowPower;
	initChannel.port = vdac_port;
	initChannel.pin = real_pin;
	initChannel.auxOutEnable = true;
	initChannel.mainOutEnable = false;
	VDAC_InitChannel(VDAC0, &initChannel, channel);
	VDAC_Enable(VDAC0, channel, true);

}

// Calculate the 12-bit output value
static uint32_t _getVdacValue(float vOut, float vRef)
{
	return (uint32_t)((vOut * 4095) / vRef);
}

static void _zuno_dac_init_channel_set(uint8_t channel, float v) {
	uint32_t							vdacValue;

	if (v <= 0x0) {
		VDAC_Enable(VDAC0, channel, true);
		return ;
	}
	vdacValue = _getVdacValue(v, ZUNO_DAC_REFERENCE);
	VDAC_ChannelOutputSet(VDAC0, channel, vdacValue);
}

static bool _zuno_dac_get_values(uint8_t pin, VDAC_ChPortSel_t *lp_vdac_port, uint8_t *lp_real_pin) {
	uint8_t								real_port;
	uint8_t								real_pin;
	VDAC_ChPortSel_t					vdac_port;

	real_port = getRealPort(pin);
	real_pin = getRealPin(pin);
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
	lp_vdac_port[0x0] = vdac_port;
	lp_real_pin[0x0] = real_pin;
	return (true);
}


bool zuno_dac(uint8_t pin_0, float v_0, uint8_t pin_1, float v_1) {
	static bool							b_init = false;
	VDAC_ChPortSel_t					vdac_port_0;
	uint8_t								real_pin_0;
	VDAC_ChPortSel_t					vdac_port_1;
	uint8_t								real_pin_1;

	if (v_0 > ZUNO_DAC_REFERENCE || v_1 > ZUNO_DAC_REFERENCE)
		return (false);
	if (_zuno_dac_get_values(pin_0, &vdac_port_0, &real_pin_0) == false)
		return (false);
	if (_zuno_dac_get_values(pin_1, &vdac_port_1, &real_pin_1) == false)
		return (false);
	if (b_init == false) {
		_zuno_dac_init();
		b_init = true;
	}
	_zuno_dac_init_channel(0x0, vdac_port_0, real_pin_0);
	_zuno_dac_init_channel(0x1, vdac_port_1, real_pin_1);
	_zuno_dac_init_channel_set(0x0, v_0);
	_zuno_dac_init_channel_set(0x1, v_1);
	return (true);
}

#endif



// #include "Arduino.h"
// #include "em_vdac.h"
// #include "zuno_dac.h"
// #include "HardwareSerial.h"

// #if defined(_SILICON_LABS_32B_SERIES_2)

// #define ZUNO_DAC_REFERENCE						2.5f

// // Calculate the 12-bit output value
// static uint32_t _getVdacValue(float vOut, float vRef)
// {
// 	return (uint32_t)((vOut * 4095) / vRef);
// }

// bool zuno_dac(uint8_t pin, float v) {
// 	static uint8_t						pin_list[] = {UNKNOWN_PIN, UNKNOWN_PIN};
// 	static bool							b_init = false;
// 	VDAC_Init_TypeDef					init = VDAC_INIT_DEFAULT;
// 	VDAC_InitChannel_TypeDef			initChannel = VDAC_INITCHANNEL_DEFAULT;
// 	uint8_t								real_port;
// 	uint8_t								real_pin;
// 	VDAC_ChPortSel_t					vdac_port;
// 	uint32_t							vdacValue;
// 	uint8_t								channel;

// 	if (v > ZUNO_DAC_REFERENCE) {
// 		Serial0.print("zuno_dac fail\n");
// 		return (false);
// 	}
// 	if (v <= 0x0) {
// 		channel = 0x0;
// 		while (true) {
// 			if (channel >= (sizeof(pin_list) / sizeof(pin_list[0x0])))
// 				return (false);
// 			if (pin_list[channel] == pin) {
// 				pin_list[channel] = UNKNOWN_PIN;
// 				Serial0.print("zuno_dac disable\n");
// 				VDAC_Enable(VDAC0, channel, false);
// 				return (true);
// 			}
// 			channel++;
// 		}
// 	}
// 	real_port = getRealPort(pin);
// 	real_pin = getRealPin(pin);
// 	switch (real_port) {
// 		case gpioPortA:
// 			vdac_port = vdacChPortA;
// 			break ;
// 		case gpioPortB:
// 			vdac_port = vdacChPortB;
// 			break ;
// 		case gpioPortC:
// 			vdac_port = vdacChPortC;
// 			break ;
// 		case gpioPortD:
// 			vdac_port = vdacChPortD;
// 			break ;
// 		default:
// 			Serial0.print("zuno_dac fail\n");
// 			return (false);
// 			break ;
// 	}
// 	if (b_init == false) {
// 		// Use the HFRCOEM23 to clock the VDAC in order to operate in EM3 mode - VDAC to max frequency of 1 MHz
// 		CMU_ClockSelectSet(cmuClock_VDAC0, cmuSelect_HFRCOEM23);
// 		// Enable the HFRCOEM23 and VDAC clocks
// 		CMU_ClockEnable(cmuClock_HFRCOEM23, true);
// 		CMU_ClockEnable(cmuClock_VDAC0, true);
// 		// Calculate the VDAC clock prescaler value resulting in a 1 MHz VDAC clock
// 		init.prescaler = VDAC_PrescaleCalc(VDAC0, 1000000);
// 		// Clocking is requested on demand
// 		init.onDemandClk = false;
// 		init.reference = vdacRef2V5;
// 		// // Allocate the analog bus for VDAC0 inputs
// 		GPIO->ABUSALLOC |= (GPIO_ABUSALLOC_AEVEN0_VDAC0CH0 | GPIO_ABUSALLOC_AODD0_VDAC0CH0) | (GPIO_ABUSALLOC_AEVEN1_VDAC0CH1 | GPIO_ABUSALLOC_AODD1_VDAC0CH1);
// 		GPIO->BBUSALLOC |= (GPIO_BBUSALLOC_BEVEN0_VDAC0CH0 | GPIO_BBUSALLOC_BODD0_VDAC0CH0) | (GPIO_BBUSALLOC_BEVEN1_VDAC0CH1 | GPIO_BBUSALLOC_BODD1_VDAC0CH1);
// 		GPIO->CDBUSALLOC |= (GPIO_CDBUSALLOC_CDEVEN0_VDAC0CH0 | GPIO_CDBUSALLOC_CDODD0_VDAC0CH0) | (GPIO_CDBUSALLOC_CDEVEN1_VDAC0CH1 | GPIO_CDBUSALLOC_CDODD1_VDAC0CH1);
// 		VDAC_Init(VDAC0, &init);
// 		b_init = true;
// 		Serial0.print("zuno_dac init\n");
// 	}
// 	channel = 0x0;
// 	while (true) {
// 		if (channel >= (sizeof(pin_list) / sizeof(pin_list[0x0]))) {
// 			Serial0.print("zuno_dac faill\n");
// 			return (false);
// 		}
// 		if (pin_list[channel] == UNKNOWN_PIN)
// 			break ;
// 		channel++;
// 	}
// 	pin_list[channel] = pin;
// 	// Disable High Capacitance Load mode
// 	initChannel.highCapLoadEnable = false;
// 	// Use Low Power mode
// 	initChannel.powerMode = vdacPowerModeLowPower;
// 	initChannel.port = vdac_port;
// 	initChannel.pin = real_pin;
// 	initChannel.auxOutEnable = true;
// 	initChannel.mainOutEnable = false;
// 	VDAC_InitChannel(VDAC0, &initChannel, channel);
// 	vdacValue = _getVdacValue(v, ZUNO_DAC_REFERENCE);
// 	Serial0.print("zuno_dac vdacValue:");
// 	Serial0.println(vdacValue);
// 	// VDAC_ChannelOutputSet(VDAC0, channel, vdacValue);
// 	VDAC_Enable(VDAC0, channel, true);
// 	Serial0.print("zuno_dac init ch:");
// 	Serial0.println(channel);
// 	return (true);
// }

// #endif