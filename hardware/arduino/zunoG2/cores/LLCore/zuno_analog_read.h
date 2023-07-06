#ifndef ZUNO_ANALOG_READ_H
#define ZUNO_ANALOG_READ_H

#include "em_adc.h"
#include "em_iadc.h"

// MULTI_CHIP
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
void analogReference(ADC_Ref_TypeDef ref);
#endif
void analogReadResolution(uint8_t bits);
void analogWriteResolution(uint8_t bits);
int analogRead(uint8_t pin);

// MULTI_CHIP
#if defined(ADC_COUNT) && (ADC_COUNT > 0)
void analogAcqTime(ADC_AcqTime_TypeDef acqtime);
#endif

uint8_t defaultBatteryHandler(void);

#endif//ZUNO_ANALOG_READ_H