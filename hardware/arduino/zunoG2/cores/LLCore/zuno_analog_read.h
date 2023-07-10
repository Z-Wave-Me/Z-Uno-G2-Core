#ifndef ZUNO_ANALOG_READ_H
#define ZUNO_ANALOG_READ_H

#include "em_adc.h"
#include "em_iadc.h"

#if defined(ADC_COUNT) && (ADC_COUNT > 0)
#define ZUNO_ANALOG_READ_DEFAULT_REFERENCE				adcRef5V
#define ZUNO_ANALOG_READ_DEFAULT_REFERENCE_VOLTAGE		5.0
void analogReference(ADC_Ref_TypeDef ref);
#endif

#if defined(IADC_COUNT) && (IADC_COUNT > 0)
#define ZUNO_ANALOG_READ_DEFAULT_REFERENCE				iadcCfgReferenceInt1V2
#define ZUNO_ANALOG_READ_DEFAULT_REFERENCE_VOLTAGE		1.21
void analogReference(IADC_CfgReference_t ref);
#endif

void analogReadResolution(uint8_t bits);
int analogRead(uint8_t pin);

uint8_t defaultBatteryHandler(void);

#endif//ZUNO_ANALOG_READ_H