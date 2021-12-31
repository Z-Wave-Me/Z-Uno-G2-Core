#ifndef ARDUINO_PROGMEM_H
#define ARDUINO_PROGMEM_H
// Backward compatibility with AVR
#define pgm_read_byte(addr) ((uint8_t*)addr)[0]
#define PROGMEM
#endif // ARDUINO_PROGMEM_H