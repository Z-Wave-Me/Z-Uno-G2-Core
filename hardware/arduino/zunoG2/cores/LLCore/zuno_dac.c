#include "Arduino.h"
#include "em_vdac.h"
#include "zuno_dac.h"

#if defined(_SILICON_LABS_32B_SERIES_2)

#define ZUNO_DAC_CHANNEL_NUM					0
#define ZUNO_DAC_REFERENCE						2.5f

// Calculate the 12-bit output value
static uint32_t _getVdacValue(float vOut, float vRef)
{
	return (uint32_t)((vOut * 4095) / vRef);
}

bool zuno_dac(uint8_t pin, float v) {
	static bool							b_init = false;
	VDAC_Init_TypeDef					init = VDAC_INIT_DEFAULT;
	VDAC_InitChannel_TypeDef			initChannel = VDAC_INITCHANNEL_DEFAULT;
	uint8_t								real_port;
	uint8_t								real_pin;
	VDAC_ChPortSel_t					vdac_port;
	uint32_t							vdacValue;

	if (v > ZUNO_DAC_REFERENCE)
		return (false);
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
	if (b_init == false) {
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
		GPIO->ABUSALLOC |= (GPIO_ABUSALLOC_AEVEN0_VDAC0CH0 | GPIO_ABUSALLOC_AODD0_VDAC0CH0);
		GPIO->BBUSALLOC |= (GPIO_BBUSALLOC_BEVEN0_VDAC0CH0 | GPIO_BBUSALLOC_BODD0_VDAC0CH0);
		GPIO->CDBUSALLOC |= (GPIO_CDBUSALLOC_CDEVEN0_VDAC0CH0 | GPIO_CDBUSALLOC_CDODD0_VDAC0CH0);
		VDAC_Init(VDAC0, &init);
		b_init = true;
	}
	vdacValue = _getVdacValue(v, ZUNO_DAC_REFERENCE);
	if (vdacValue == 0x0 || v < 0x0) {
		VDAC_Enable(VDAC0, ZUNO_DAC_CHANNEL_NUM, false);
		return (true);
	}
	// Disable High Capacitance Load mode
	initChannel.highCapLoadEnable = false;
	// Use Low Power mode
	initChannel.powerMode = vdacPowerModeLowPower;
	initChannel.port = vdac_port;
	initChannel.pin = real_pin;
	initChannel.auxOutEnable = true;
	initChannel.mainOutEnable = false;
	VDAC_InitChannel(VDAC0, &initChannel, ZUNO_DAC_CHANNEL_NUM);
	VDAC_Enable(VDAC0, ZUNO_DAC_CHANNEL_NUM, true);
	VDAC_ChannelOutputSet(VDAC0, ZUNO_DAC_CHANNEL_NUM, vdacValue);
	return (true);
}

#endif