#ifndef TONE_H
#define TONE_H

void tone(uint8_t pin, uint16_t freq);
void toneDelayed(uint8_t pin, uint16_t freq, uint16_t duration);
void noTone(uint8_t pin);

uint8_t _analogWrite(uint8_t pin, uint8_t value);

#endif //TONE_H