#ifndef __EEPROM_LIB__
#define __EEPROM_LIB__

#include "Arduino.h"

#define ONEBYTE 1

class EEPROMClass
{
    public:

        EEPROMClass(){};
	
		int put(uint32_t address, void *value, uint16_t val_size);
	    int get(uint32_t address, void *value, uint16_t val_size);
		byte read(uint32_t address);
		void update(uint32_t address, byte value);
		void write(uint32_t address, byte value);
		int erase(void);
	
	private:
		byte temp_byte;
};

extern EEPROMClass EEPROM;

#endif