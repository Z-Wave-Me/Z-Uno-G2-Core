#include "ZUNO_SHIELD.h"

#define FIRST_0_10V_CHANNEL 1
#define LAST_0_10V_CHANNEL  4
#define FIRST_PWM_CHANNEL   5
#define LAST_PWM_CHANNEL    8
#define FIRST_VOLTAGE_CHANNEL   9
#define LAST_VOLTGAE_CHANNEL    12

#define VOLTAGE_HYSTERESIS 100
#define ALL_PWM_CHANNELS   0x0F

uint8_t     dimmer010V[4] = {25, 33, 50, 99};
uint8_t     dimmerPWM[4] = {25, 33, 50, 99};
uint16_t    sensorVoltage[4];
uint16_t    sensorVoltageReported[4];

ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(dimmer010V,NULL),
                    ZUNO_SWITCH_MULTILEVEL(dimmer010V,NULL),
                    ZUNO_SWITCH_MULTILEVEL(dimmer010V,NULL),
                    ZUNO_SWITCH_MULTILEVEL(dimmer010V,NULL),
                    ZUNO_SWITCH_MULTILEVEL(dimmerPWM,NULL),
                    ZUNO_SWITCH_MULTILEVEL(dimmerPWM,NULL),
                    ZUNO_SWITCH_MULTILEVEL(dimmerPWM,NULL),
                    ZUNO_SWITCH_MULTILEVEL(dimmerPWM,NULL),
                    ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_VOLTAGE, SENSOR_MULTILEVEL_SCALE_VOLT, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, 3, sensorVoltage),
                    ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_VOLTAGE, SENSOR_MULTILEVEL_SCALE_VOLT, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, 3, sensorVoltage),
                    ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_VOLTAGE, SENSOR_MULTILEVEL_SCALE_VOLT, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, 3, sensorVoltage),
                    ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_VOLTAGE, SENSOR_MULTILEVEL_SCALE_VOLT, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, 3, sensorVoltage));


ZUNOShield shield;
const ShieldADCJumper_t ADCJumpers[] = {SHIELD_ADC_JUMPER_I12V, SHIELD_ADC_JUMPER_I12V, SHIELD_ADC_JUMPER_I12V, SHIELD_ADC_JUMPER_I12V};
void setup(){
    //Serial.begin();
    //Serial0.begin();
    shield.initADCAll((ShieldADCJumper_t*)ADCJumpers);
    shield.init0_10V();
    shield.initPWM(ALL_PWM_CHANNELS);
}
void loop(){
    int i;
    for(i=FIRST_0_10V_CHANNEL;i<=LAST_0_10V_CHANNEL;i++){
        shield.write0_10V(i-FIRST_0_10V_CHANNEL+1, dimmer010V[i-FIRST_0_10V_CHANNEL]);
    }
    for(i=FIRST_PWM_CHANNEL;i<=LAST_PWM_CHANNEL;i++){
        shield.writePWMPercentage(i-FIRST_PWM_CHANNEL+1, dimmerPWM[i-FIRST_PWM_CHANNEL]);
    }
    for(i=FIRST_VOLTAGE_CHANNEL;i<=LAST_VOLTGAE_CHANNEL;i++){
        uint8_t j = i-FIRST_VOLTAGE_CHANNEL;
        sensorVoltage[j] = shield.readADCMillivolts(j+1);
        //Serial.printf("ADC:%d %d mV\n",j,sensorVoltage[j]);

        if(abs(sensorVoltage[j]-sensorVoltageReported[j]) > VOLTAGE_HYSTERESIS){
            sensorVoltageReported[j] = sensorVoltage[j];
            zunoSendReport(i);
        }
    }
}