#include "Arduino.h"
#include "zuno_analog_read.h"

static bool _ADCInitialized = false;
static ADC_AcqTime_TypeDef _adc_acqtime = adcAcqTime256;
static ADC_Ref_TypeDef _adc_reference = adcRef5V;
static uint8_t _adc_resolution = 10;

#ifndef BATTERY_LOW
#define BATTERY_LOW 2500
#endif
#ifndef BATTERY_HIGH
#define BATTERY_HIGH 3000
#endif

#if !defined(WITH_CUSTOM_BATTERY_HANDLER)
uint8_t defaultBatteryHandler(void) {
    uint8_t old_res  = _adc_resolution;
    _adc_resolution = 12;
    dword res = analogRead(BATTERY);
    _adc_resolution = old_res;
    res *= 5000;
    res >>= 12;
    if(res >= BATTERY_HIGH)
        return 100; 
    res -= BATTERY_LOW;
    res *= 100;
    return res / (BATTERY_HIGH - BATTERY_LOW);
}
#endif

// MULTI_CHIP
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
static ADC_Res_TypeDef  __adc_resolution2Mode(uint8_t res){
    if(res > 8)
        return adcRes12Bit;
    if(res > 6)
        return adcRes8Bit;
    return 	adcRes6Bit;
}
#endif

static uint8_t  __adc_resolution2RealBits(uint8_t res){
    if(res > 8)
        return 12;
    if(res > 6)
        return 8;
    return 	6;
} 
static uint32_t __oversampleValue(uint32_t v, uint8_t src, uint8_t dst){
    if(src > dst)
        return v >> (src - dst);
    return v << (dst - src);
}

// MULTI_CHIP
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
void analogReference(ADC_Ref_TypeDef ref){
    _adc_reference = ref;
}
#endif

void analogReadResolution(uint8_t bits){
    _adc_resolution = bits;
}

// MULTI_CHIP
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
void analogAcqTime(ADC_AcqTime_TypeDef acqtime){
    _adc_acqtime = acqtime;
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
#endif

// MULTI_CHIP
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
void zmeADCInit() {
	ADC_Init_TypeDef				adcInit;

	if(!_ADCInitialized){
		adcInit = ADC_INIT_DEFAULT;
		CMU_ClockEnable(cmuClock_HFPER, true);
		CMU_ClockEnable(cmuClock_ADC0, true);
		CMU->ADCCTRL = CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO;// Select AUXHFRCO for ADC ASYNC mode so that ADC can run on EM2
		CMU_AUXHFRCOBandSet(cmuAUXHFRCOFreq_4M0Hz);
		adcInit.timebase = ADC_TimebaseCalc(0);
		adcInit.prescale = ADC_PrescaleCalc(CMU_AUXHFRCOBandGet(), 0);
		adcInit.em2ClockConfig = adcEm2ClockOnDemand;
		ADC_Init(ADC0, &adcInit);
		_ADCInitialized = true;
	}
}
#endif

// MULTI_CHIP
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
int analogRead(uint8_t pin) {
	uint32_t								sampleValue;
	ADC_InitSingle_TypeDef					singleInit;

	zmeADCInit();
	singleInit = ADC_INITSINGLE_DEFAULT;
	// Init for single conversion use, use 5V reference
	singleInit.reference  = _adc_reference;
	singleInit.posSel     = zme_ADC_PIN2Channel(pin);
	singleInit.resolution = __adc_resolution2Mode(_adc_resolution);
	singleInit.acqTime    = _adc_acqtime;
	ADC_InitSingle(ADC0, &singleInit);
	ADC_Start(ADC0, adcStartSingle);
	while (ADC0->STATUS & ADC_STATUS_SINGLEACT)
		;
	sampleValue = ADC_DataSingleGet(ADC0);
	ADC0->CMD = ADC_CMD_SINGLESTOP;
	return (__oversampleValue(sampleValue, __adc_resolution2RealBits(_adc_resolution), _adc_resolution));
}
#endif
