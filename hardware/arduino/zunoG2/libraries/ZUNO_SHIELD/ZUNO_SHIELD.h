#include "Arduino.h"
#include "ZUNO_DAC102S085.h"
typedef enum {
    SHIELD_POWER_12V,
    SHIELD_POWER_24V,
    SHIELD_POWER_3V_BATTERY
} ShieldPowerMode_t;

#define SHIELD_BASE_VREF 15700
typedef enum {
    SHIELD_ADC_JUMPER_IO3V,
    SHIELD_ADC_JUMPER_I5V,
    SHIELD_ADC_JUMPER_I12V
} ShieldADCJumper_t;
class ZUNOShield{
    public:
        ZUNOShield(ShieldPowerMode_t pm = SHIELD_POWER_12V);
        void initADCChannel(uint8_t channel, ShieldADCJumper_t type);
        void initADCAll(ShieldADCJumper_t * types);
        uint16_t readADCMillivolts(uint8_t channel);
        float    readADCVoltage(uint8_t channel);
        void     init0_10V(uint16_t ref_millivolts, SPIClass * spi_interface);
        void     init0_10V(uint16_t ref_millivolts = SHIELD_BASE_VREF);
        void     upfdate0_10VRef(uint16_t ref_millivolts){_ref_voltage = ref_millivolts;};
        void     setUpperVoltage(uint16_t ref_millivolts) {_ref_upper = ref_millivolts; };
        void     deinit_0_10V();
        void     initPWM(uint8_t mask);
        void     writePWMPercentage(uint8_t channel, uint8_t percents);
        bool     write0_10V(uint8_t channel, uint8_t percentage);
        bool     write0_10V(uint8_t channel, uint16_t millivolts);
        bool     write0_10V(uint8_t channel, float volts);
    private:
        ShieldPowerMode_t _power_mode;
        uint8_t           _pwm_map;
        ShieldADCJumper_t _adc_jumpers[4];
        DAC102S085     *  _dacs[2];
        uint16_t          _ref_voltage;
        uint16_t          _ref_upper;
        

        


};