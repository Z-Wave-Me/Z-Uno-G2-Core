#include "EEPROM.h"

int EEPROMClass::put(uint32_t address, void *value, uint16_t val_size)
{
    return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, true, address, val_size, value);
}

int EEPROMClass::get(uint32_t address, void *value, uint16_t val_size)
{
    return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, false, address, val_size, value);
}

byte EEPROMClass::read(uint32_t address)
{
    this->get(address, &this->temp_byte, ONEBYTE);
    return temp_byte;
}

void EEPROMClass::update(uint32_t address, byte value)
{
    this->get(address, &this->temp_byte, ONEBYTE);
    if (value != temp_byte)
    {
        temp_byte = value;
        this->put(address, &this->temp_byte, ONEBYTE);
    }
}

void EEPROMClass::write(uint32_t address, byte value)
{
    this->temp_byte = value;
    this->put(address, &this->temp_byte, ONEBYTE);
}

int EEPROMClass::erase(void)
{
    return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_ERASE, 1, 0xCAFE0ACE);
}

EEPROMClass EEPROM;