#include "Arduino.h"
#include "zuno_analog_read.h"

#define ANALOG_READ_RESOLUTION_UNKNOWN				0x0

#ifndef BATTERY_LOW
#define BATTERY_LOW 2500
#endif
#ifndef BATTERY_HIGH
#define BATTERY_HIGH 3000
#endif


#if !defined(WITH_CUSTOM_BATTERY_HANDLER)
static int _analogRead(uint8_t pin, uint8_t adc_resolution);
uint8_t defaultBatteryHandler(void) {
    dword res = _analogRead(BATTERY, 12);
    res *= 5000;
    res >>= 12;
    if(res >= BATTERY_HIGH)
        return 100; 
    res -= BATTERY_LOW;
    res *= 100;
    return res / (BATTERY_HIGH - BATTERY_LOW);
}
#endif

#if defined(ADC_COUNT) && (ADC_COUNT > 0)
#define ZUNO_ANALOG_READ_REFERENCE_STRUCT		ADC_Ref_TypeDef
static ADC_Res_TypeDef  __adc_resolution2Mode(uint8_t res){
    if(res > 8)
        return adcRes12Bit;
    if(res > 6)
        return adcRes8Bit;
    return 	adcRes6Bit;
}

static uint8_t  __adc_resolution2RealBits(uint8_t res){
    if(res > 8)
        return 12;
    if(res > 6)
        return 8;
    return 	6;
} 

ADC_PosSel_TypeDef zme_ADC_PIN2Channel(uint8_t pin) {
	ADC_PosSel_TypeDef				out;

	switch(pin) {
		case 21://PC6
			out = adcPosSelAPORT1XCH6;
			break ;
		case 22://PC7
			out = adcPosSelAPORT1YCH7;
			break ;
		case 0://PC8
			out = adcPosSelAPORT1XCH8;
			break ;
		case 1://PC9
			out = adcPosSelAPORT1YCH9;
			break ;
		case 23://PC10
			out = adcPosSelAPORT1XCH10;
			break ;
		case 25://PC11
			out = adcPosSelAPORT1YCH11;
			break ;
		case 2://PF2
			out = adcPosSelAPORT1XCH18;
			break ;
		case 7://PF4
			out = adcPosSelAPORT1XCH20;
			break ;
		case 8://PF5
			out = adcPosSelAPORT1YCH21;
			break ;
		case 3://PF6
			out = adcPosSelAPORT1XCH22;
			break ;
		case 4://PF7
			out = adcPosSelAPORT1YCH23;
			break ;
		case 5://PD9
			out = adcPosSelAPORT3YCH1;
			break ;
		case 6://PD10
			out = adcPosSelAPORT3XCH2;
			break ;
		case 9://PD11
			out = adcPosSelAPORT3YCH3;
			break ;
		case 10://PD12
			out = adcPosSelAPORT3XCH4;
			break ;
		case 24://PD13
			out = adcPosSelAPORT3YCH5;
			break ;
		case 11://PD14
			out = adcPosSelAPORT3XCH6;
			break ;
		case 12://PD15
			out = adcPosSelAPORT3YCH7;
			break ;
		case 13://PA0
			out = adcPosSelAPORT3XCH8;
			break ;
		case 14://PA1
			out = adcPosSelAPORT3YCH9;
			break ;
		case 15://PA2
			out = adcPosSelAPORT3XCH10;
			break ;
		case 16://PA3
			out = adcPosSelAPORT3YCH11;
			break ;
		case 17://PA4
			out = adcPosSelAPORT3XCH12;
			break ;
		default:
			out = adcPosSelAVDD;
			break ;
	}
	return (out);
}

void zmeADCInit(void) {
	ADC_Init_TypeDef				adcInit;
	static bool						ADCInitialized = false;

	if(!ADCInitialized){
		adcInit = ADC_INIT_DEFAULT;
		CMU_ClockEnable(cmuClock_HFPER, true);
		CMU_ClockEnable(cmuClock_ADC0, true);
		CMU->ADCCTRL = CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO;// Select AUXHFRCO for ADC ASYNC mode so that ADC can run on EM2
		CMU_AUXHFRCOBandSet(cmuAUXHFRCOFreq_4M0Hz);
		adcInit.timebase = ADC_TimebaseCalc(0);
		adcInit.prescale = ADC_PrescaleCalc(CMU_AUXHFRCOBandGet(), 0);
		adcInit.em2ClockConfig = adcEm2ClockOnDemand;
		ADC_Init(ADC0, &adcInit);
		ADCInitialized = true;
	}
}

static void _analogReadPeripheryConfig(uint8_t pin, uint8_t adc_resolution, ADC_Ref_TypeDef reference) {
	ADC_InitSingle_TypeDef					singleInit;

	singleInit = ADC_INITSINGLE_DEFAULT;
	// Init for single conversion use, use 5V reference
	singleInit.reference  = reference;
	singleInit.posSel     = zme_ADC_PIN2Channel(pin);
	singleInit.resolution = __adc_resolution2Mode(adc_resolution);
	singleInit.acqTime    = adcAcqTime256;
	ADC_InitSingle(ADC0, &singleInit);
}

static uint32_t _analogReadPeriphery(void) {
	uint32_t								sampleValue;

	ADC_Start(ADC0, adcStartSingle);
	while (ADC0->STATUS & ADC_STATUS_SINGLEACT)
		;
	sampleValue = ADC_DataSingleGet(ADC0);
	ADC0->CMD = ADC_CMD_SINGLESTOP;
	return (sampleValue);
}
#endif

#if defined(IADC_COUNT) && (IADC_COUNT > 0)
#define ZUNO_ANALOG_READ_REFERENCE_STRUCT		IADC_CfgReference_t
static IADC_PosInput_t _getPosInput(uint8_t pin) {
	uint8_t							real_port;
	uint8_t							real_pin;
	IADC_PosInput_t					out;

	if (pin == BATTERY)
		return (iadcPosInputAvdd);
	real_port = getRealPort(pin);
	real_pin = getRealPin(pin);
	switch (real_port) {
			case gpioPortA:
				out = (IADC_PosInput_t)(iadcPosInputPortAPin0 + real_pin);
				break ;
			case gpioPortB:
				out = (IADC_PosInput_t)(iadcPosInputPortBPin0 + real_pin);
				break ;
			case gpioPortC:
				out = (IADC_PosInput_t)(iadcPosInputPortCPin0 + real_pin);
				break ;
			case gpioPortD:
				out = (IADC_PosInput_t)(iadcPosInputPortDPin0 + real_pin);
				break ;
		default:
			out = iadcPosInputAvdd;
			break ;
	}
	return (out);
}

static uint8_t  __adc_resolution2RealBits(uint8_t res) {
	if (res > 16)
		return (20);
	if (res > 12)
		return (16);
	return (12);
}

static IADC_Alignment_t __adc_alignment2RealBits(uint8_t res) {
	if (res > 16)
		return (iadcAlignRight20);
	if (res > 12)
		return (iadcAlignRight16);
	return (iadcAlignRight12);
}

static void __adc_resolution2Mode(uint8_t res, IADC_Config_t *configs) {
	IADC_CfgOsrHighSpeed_t								osrHighSpeed;
	IADC_DigitalAveraging_t								digAvg;

	switch (__adc_resolution2RealBits(res)) {
		case 20:
			osrHighSpeed = iadcCfgOsrHighSpeed32x;
			digAvg = iadcDigitalAverage16;
			break ;
		case 16://11 + log2(iadcCfgOsrHighSpeed8x*iadcDigitalAverage4) = 11 + 5
			osrHighSpeed = iadcCfgOsrHighSpeed8x;
			digAvg = iadcDigitalAverage4;
			break ;
		default:
			osrHighSpeed = iadcCfgOsrHighSpeed2x;
			digAvg = iadcDigitalAverage1;
			break ;
	}
	configs->osrHighSpeed = osrHighSpeed;
	configs->digAvg = digAvg;
}


void zmeADCInit(void) {
	static bool						ADCInitialized = false;

	if(!ADCInitialized){
		// Enable IADC clock
		CMU_ClockEnable(cmuClock_IADC0, true);
		// Configure IADC clock source for use while in EM2
		CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_FSRCO);
		// Allocate the analog bus for ADC0 inputs
		GPIO->ABUSALLOC |= (GPIO_ABUSALLOC_AEVEN0_ADC0 | GPIO_ABUSALLOC_AODD0_ADC0);
		GPIO->BBUSALLOC |= (GPIO_BBUSALLOC_BEVEN0_ADC0 | GPIO_BBUSALLOC_BODD0_ADC0);
		GPIO->CDBUSALLOC |= (GPIO_CDBUSALLOC_CDEVEN0_ADC0 | GPIO_CDBUSALLOC_CDODD0_ADC0);
		ADCInitialized = true;
	}
}

static void _analogReadPeripheryConfig(uint8_t pin, uint8_t adc_resolution, IADC_CfgReference_t reference) {
	IADC_Init_t								init = IADC_INIT_DEFAULT;
	IADC_AllConfigs_t						initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
	IADC_InitSingle_t						initSingle = IADC_INITSINGLE_DEFAULT;
	IADC_SingleInput_t						initSingleInput = IADC_SINGLEINPUT_DEFAULT;

	// Reset IADC to reset configuration in case it has been modified
	IADC_reset(IADC0);
	// Modify init structs and initialize
	init.warmup = iadcWarmupNormal;
	// Configuration 0 is used by both scan and single conversions by default
	// Use internal bandgap (supply voltage in mV) as reference
	initAllConfigs.configs[0].reference = reference;
	initAllConfigs.configs[0].vRef = IADC_getReferenceVoltage(reference);
	initAllConfigs.configs[0].analogGain = iadcCfgAnalogGain1x;

	__adc_resolution2Mode(adc_resolution, &initAllConfigs.configs[0x0]);

	// Initialize IADC
	// Note oversampling and digital averaging will affect the offset correction
	// This is taken care of in the IADC_init() function in the emlib
	IADC_init(IADC0, &init, &initAllConfigs);

	initSingle.start = false;
	initSingle.alignment = __adc_alignment2RealBits(adc_resolution);
	initSingleInput.posInput = _getPosInput(pin);
	IADC_initSingle(IADC0, &initSingle, &initSingleInput);
}

static uint32_t _analogReadPeriphery(void) {
	uint32_t								sampleValue;

	// Errata IADC_E305: Check SINGLEFIFOSTAT to make sure that SINGLEFIFO is getting emptied in case
	// where STATUS register is incorrect.
	while (((IADC0->STATUS & IADC_STATUS_SINGLEFIFODV) != 0UL) || (IADC0->SINGLEFIFOSTAT > 0)) {
		(void) IADC_pullSingleFifoData(IADC0);
	}
	IADC_command(IADC0, iadcCmdStartSingle);
	while((IADC0->STATUS & IADC_STATUS_CONVERTING) != 0x0)
		__NOP();
	while((IADC0->STATUS & IADC_STATUS_SINGLEFIFODV) == 0x0)
		__NOP();
	sampleValue = IADC_pullSingleFifoResult(IADC0).data;
	return (sampleValue);
}
#endif

static uint32_t __oversampleValue(uint32_t v, uint8_t src, uint8_t dst) {
    if(src > dst)
        return v >> (src - dst);
    return v << (dst - src);
}

static ZunoSync_t _sync = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterAnalogRead);
static volatile uint8_t _key = true;

static uint8_t _adc_resolution = 10;

#if defined(ADC_COUNT) && (ADC_COUNT > 0)
static ADC_Ref_TypeDef _adc_reference = adcRef5V;
#endif

#if defined(IADC_COUNT) && (IADC_COUNT > 0)
static IADC_CfgReference_t _adc_reference = iadcCfgReferenceInt1V2;
#endif

#define ANALOG_READ_ENTER()					zunoSyncLockWrite(&_sync, SyncMasterAnalogRead, &_key)
#define ANALOG_READ_EXIT()					zunoSyncReleseWrite(&_sync, SyncMasterAnalogRead, &_key)

static int _analogRead(uint8_t pin, uint8_t adc_resolution) {
	static uint8_t								pin_old = UNKNOWN_PIN;
	static uint8_t								adc_resolution_old = ANALOG_READ_RESOLUTION_UNKNOWN;
	static ZUNO_ANALOG_READ_REFERENCE_STRUCT	reference_old = ZUNO_ANALOG_READ_DEFAULT_REFERENCE;
	uint32_t									sampleValue;
	bool										update;
	int											out;
	ZUNO_ANALOG_READ_REFERENCE_STRUCT			reference;

	if (ANALOG_READ_ENTER() != ZunoErrorOk)
		return (0x0);
	zmeADCInit();
	if (adc_resolution == ANALOG_READ_RESOLUTION_UNKNOWN)
		adc_resolution = _adc_resolution;
	update = false;
	if (pin_old != pin) {
		pinMode(pin, INPUT);
		pin_old = pin;
		update = true;
	}
	if (adc_resolution_old != adc_resolution) {
		adc_resolution_old = adc_resolution;
		update = true;
	}
	reference = _adc_reference;
	if (reference_old != reference) {
		reference_old = reference;
		update = true;
	}
	if (update == true)
		_analogReadPeripheryConfig(pin, adc_resolution, reference);
	sampleValue = _analogReadPeriphery();
	#if defined(IADC_COUNT) && (IADC_COUNT > 0)
	if (pin == BATTERY)
		sampleValue = sampleValue * 0x4;
	#endif
	out = __oversampleValue(sampleValue, __adc_resolution2RealBits(adc_resolution), adc_resolution);
	ANALOG_READ_EXIT();
	return (out);
}


void analogReference(ZUNO_ANALOG_READ_REFERENCE_STRUCT ref) {
	if (ANALOG_READ_ENTER() != ZunoErrorOk)
		return ;
	_adc_reference = ref;
	ANALOG_READ_EXIT();
}


void analogReadResolution(uint8_t bits) {
	if (ANALOG_READ_ENTER() != ZunoErrorOk)
		return ;
	_adc_resolution = bits;
	ANALOG_READ_EXIT();
}

int analogRead(uint8_t pin) {
	return (_analogRead(pin, ANALOG_READ_RESOLUTION_UNKNOWN));
}
