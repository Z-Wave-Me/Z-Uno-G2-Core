#ifndef TONE_H
#define TONE_H

#define PWM_FREQ_DEFAULT                480
#define PWM_FREQ_MIN                    2
#define PWM_FREQ_MAX                    8000000

ZunoError_t tone(uint8_t pin, uint16_t freq, uint32_t duration = 0x0);
void noTone(uint8_t pin);

bool analogWrite(uint8_t pin, word value);
void analogWriteFrequency(uint32_t freq);
void analogWriteResolution(uint8_t bits);
#endif //TONE_H