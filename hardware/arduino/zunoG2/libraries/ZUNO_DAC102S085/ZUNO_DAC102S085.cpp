#include "ZUNO_DAC102S085.h"
DAC102S085::DAC102S085(uint8_t cs_pin){
    _cs_pin = cs_pin;
    _spi_interface = &SPI;
    
}
DAC102S085::DAC102S085(SPIClass * spi_interface, uint8_t cs_pin){
    _cs_pin = cs_pin;
    _spi_interface = spi_interface;
} 
void DAC102S085::begin(){
    // Configure CS pin to output
    pinMode(_cs_pin, OUTPUT);
    digitalWrite(_cs_pin, HIGH); // Set idle value
    // SPI interface initialisation
    _spi_interface->begin();
}
void DAC102S085::end(){
    _spi_interface->end();
}
void DAC102S085::writeRaw(uint16_t raw_value){
    _spi_interface->beginTransaction();
    digitalWrite(_cs_pin, LOW);
    // MSB first
    _spi_interface->transfer((uint8_t)(raw_value >> 8));
    _spi_interface->transfer((uint8_t)(raw_value & 0xFF));
    _spi_interface->endTransaction();
    digitalWrite(_cs_pin, HIGH);
}
void DAC102S085::writeValue(DACChannel_t channel, uint16_t value){
    uint16_t raw = 0x1000;
    if(channel == DAC_CHANNEL_B){
        raw = 0x5000;
    } 
    // 10 bits only
    value &= 0x3F;
    value <<= 2; // first 2 bits are empty
    raw |= value;
    writeRaw(raw);
}
void DAC102S085::powerDown(DACPowerMode_t pm){
    uint16_t raw = pm;
    raw <<= 12;
    writeRaw(raw);
}