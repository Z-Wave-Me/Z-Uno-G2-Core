#include "ZUNO_SHIELD.h"

#define DAC1_0_10V_CS 22
#define DAC2_0_10V_CS 21

#define ADC_MAIN_RES 10000
#define ADC_5V_RES   10000
#define ADC_12V_RES  36000
#define ADC_VREF     5000

ZUNOShield::ZUNOShield(ShieldPowerMode_t pm){
    _power_mode = pm;
    _pwm_map = 0;
    memset(_adc_jumpers, 0, sizeof(_adc_jumpers));
    _dacs[0] = NULL;
    _dacs[1] = NULL;
}
void ZUNOShield::initADCChannel(uint8_t channel, ShieldADCJumper_t type){
    const uint8_t adc_pins[] = {A0, A1, A2, A3};
    channel--;
    if(channel > 3)
        return;
    _adc_jumpers[channel] = type;
    pinMode(adc_pins[channel], INPUT);
}
void ZUNOShield::initADCAll(ShieldADCJumper_t * types){
    for(int i=1;i<=4;i++)
        initADCChannel(i, types[i]);
}
uint16_t ZUNOShield::readADCMillivolts(uint8_t channel){
    const uint8_t adc_pins[] = {A0, A1, A2, A3};
    channel--;
    if(channel > 3)
        return 0;
    analogReadResolution(16);
    uint32_t tmp = analogRead(adc_pins[channel]);
    tmp *= ADC_VREF;
    switch(_adc_jumpers[channel]){
        case SHIELD_ADC_JUMPER_IO3V:
            return tmp;
        case SHIELD_ADC_JUMPER_I5V:
            tmp *= (ADC_5V_RES + ADC_MAIN_RES);
            tmp /= ADC_MAIN_RES;
            return tmp;
        case SHIELD_ADC_JUMPER_I12V:
            tmp *= (ADC_12V_RES + ADC_MAIN_RES);
            tmp /= ADC_MAIN_RES;
            return tmp;
        
    }
    return tmp;
}
float    ZUNOShield::readADCVoltage(uint8_t channel){
    return readADCMillivolts(channel) / 1000.0f;
}
void     ZUNOShield::init0_10V(uint16_t ref_millivolts, SPIClass * spi_interface){
    if(_power_mode == SHIELD_POWER_3V_BATTERY)
        return; // We have no reference voltage for 0_10V
    _ref_voltage =  ref_millivolts;
    _dacs[0] = new DAC102S085(spi_interface, DAC1_0_10V_CS);
    _dacs[1] = new DAC102S085(spi_interface, DAC2_0_10V_CS);
    _dacs[0]->begin();
    _dacs[1]->begin();
     
}
void     ZUNOShield::deinit_0_10V(){
    if(_dacs[0] == NULL)
        return;
    _dacs[0]->end();
    _dacs[1]->end();
    delete _dacs[0];
    delete _dacs[1];
}
void     ZUNOShield::init0_10V(uint16_t ref_millivolts){
    init0_10V(ref_millivolts, &SPI);
}
void     ZUNOShield::initPWM(uint8_t mask){
    const uint8_t pwm_pins[] = {PWM1, PWM2, PWM3, PWM4};
    for(uint8_t i=0;i<4;i++){
        if(mask & (1<<i)){
            pinMode(pwm_pins[i], OUTPUT);
            analogWrite(pwm_pins[i], 0);
        }
    }
    _pwm_map = mask;
}
void    ZUNOShield::writePWMPercentage(uint8_t channel, uint8_t percents){
    const uint8_t pwm_pins[] = {PWM1, PWM2, PWM3, PWM4};
    channel--; // We use zero based index, but user starts from 1
    if(channel > 3)
        return;
    if((_pwm_map & (1 << channel)) == 0)
        return; // It wasn't configured
    if(percents > 99)
        percents = 99;
    analogWriteResolution(16);
    uint32_t val = (65535UL * percents) / 99; 
    analogWrite(pwm_pins[channel], val);
}
bool    ZUNOShield::write0_10V(uint8_t channel, uint8_t percentage){
    if(percentage > 99)
        percentage = 99;
    uint32_t tmp = (percentage * _ref_voltage) / 99;
    return write0_10V(channel, (uint16_t)(tmp));
}
bool    ZUNOShield::write0_10V(uint8_t channel, uint16_t millivolts){
    if(_dacs[0] == NULL)
        return false;
    if(_dacs[1] == NULL)
        return false;
    channel--;
    if(channel > 3)
        return false;
    if(millivolts > _ref_voltage)
        millivolts = _ref_voltage;
    uint32_t dac_value = (1023 * millivolts) / _ref_voltage;
    Serial.print("DAC value:");
    Serial.println(dac_value);
    switch(channel){
        case 0:
            _dacs[0]->writeValue(DAC_CHANNEL_A, dac_value);
            break;
        case 1:
            _dacs[0]->writeValue(DAC_CHANNEL_B, dac_value);
            break;
        case 2:
            _dacs[1]->writeValue(DAC_CHANNEL_A, dac_value);
            break;
        case 3:
            _dacs[1]->writeValue(DAC_CHANNEL_B, dac_value);
            break;
    }
    return true;
}
bool    ZUNOShield::write0_10V(uint8_t channel, float volts){
    uint32_t tmp = int(volts * 1000);
    return write0_10V(channel, (uint16_t)(tmp));
}