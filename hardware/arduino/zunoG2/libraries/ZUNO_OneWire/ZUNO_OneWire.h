#ifndef ZUNO_ONEWIRE_LIB
#define ZUNO_ONEWIRE_LIB

#include "Arduino.h"

class OneWire {
    public:
    OneWire(byte bus_pin);

    byte reset(void);
    void write(byte v, byte power = 1);
    byte read();
    void select(byte * rom);
    void skip();
    void depower();
    void readROM(byte * rom);
    byte crc8(byte * addr, byte len);
    void reset_search();
    bool search(uint8_t * newAddr);

    private:
    inline void digitalWriteFast(uint8_t val);
    inline int digitalReadFast();
    inline void pinModeFast(uint8_t);

    int real_port;
    int real_pin;
    uint32_t aliasAddr_in;
    uint32_t aliasAddr_out;
    byte bus_pin;
    byte ows_id_bit_number;
    byte ows_last_zero, ows_rom_byte_number, ows_search_result;
    byte ows_id_bit, ows_cmp_id_bit;
    byte ows_rom_byte_mask, ows_search_direction;
    byte ows_ROM_NO[8];
    byte LastDiscrepancy;
    byte LastFamilyDiscrepancy;
    bool LastDeviceFlag;
    bool read_bit();
    void write_bit(bool bit);

};

#endif // ZUNO_ONEWIRE_LIB