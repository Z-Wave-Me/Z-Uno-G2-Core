#include "Arduino.h"
#include "SPI.h"

typedef enum{
    DAC_CHANNEL_A = 0,
    DAC_CHANNEL_B = 1
}DACChannel_t; 
typedef enum{
    DAC_POWERMODE_HIZ = 0x03,
    DAC_POWERMODE_2k5GND = 0x07,
    DAC_POWERMODE_100kGND= 0x0B,
    DAC_POWERMODE_DEEPHIZ = 0x0F
}DACPowerMode_t; 

class DAC102S085{

    public:
        DAC102S085(uint8_t cs_pin);
        DAC102S085(SPIClass * spi_interface, uint8_t cs_pin);
        void begin();
        void end();
        void writeRaw(uint16_t raw_value);
        void writeValue(DACChannel_t channel, uint16_t value);
        void powerDown(DACPowerMode_t pm);
    private:
        SPIClass * _spi_interface;
        uint8_t    _cs_pin;
        
};