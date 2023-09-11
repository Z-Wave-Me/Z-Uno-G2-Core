#include "Wire.h"
#include "ZUNO_SCD4x.h"
uint16_t Address = 0x62;
uint8_t cnt = 0;
int16_t lastTemp = 0;
int16_t curTemp;
uint16_t curHum, curCO2;
uint16_t lastHum = 0;
uint16_t lastCO2 = 10;
enum{
    PARAM_TEMP_OFFSET=64,
    PARAM_TEMP_HYST,
    PARAM_HUMIDITY_HYST,
    PARAM_CO2_HYST,
    PARAM_REPORTING_INT,
    PARAM_AMB_PRESSURE,
    PARAM_SENS_ALT,
    PARAM_FACTORY_RESET
};

ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE); //Z-Uno Sleaping mode
ZUNO_SETUP_CHANNELS(
  ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_CO2_LEVEL, SENSOR_MULTILEVEL_SCALE_PARTS_PER_MILLION, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, SENSOR_MULTILEVEL_PRECISION_ZERO_DECIMALS, curCO2),                                  
  ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE, SENSOR_MULTILEVEL_SCALE_CELSIUS, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, SENSOR_MULTILEVEL_PRECISION_ONE_DECIMAL, curTemp),  
  ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_RELATIVE_HUMIDITY, SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, SENSOR_MULTILEVEL_PRECISION_ONE_DECIMAL,curHum)
);
 ZUNO_SETUP_CONFIGPARAMETERS(
         ZUNO_CONFIG_PARAMETER_INFO("Temperature offset (step 1/10°C)", "Define temperature offset in 1/10 grad, it can depend on various factors such as the SCD4x measurement mode, self-heating of close components", 0, 200, 45),
         ZUNO_CONFIG_PARAMETER_INFO("Temperature hysteresis (step 1/10°C)", "Defines hysteresis of temperature for additional sending value in 1/10 grad", 1, 20, 5),
         ZUNO_CONFIG_PARAMETER_INFO("Humidity hysteresis", "Defines hysteresis of humidity for additional sending value", 1, 20, 5),
         ZUNO_CONFIG_PARAMETER_INFO("CO2 hysteresis", "Defines hysteresis of CO2 value for additional sending value", 0, 1000, 0),
         ZUNO_CONFIG_PARAMETER_INFO("Reporting interval (sec)", "Defines the default reporting interval (possible step: 5sec)", 20, 3600, 40),
         ZUNO_CONFIG_PARAMETER_INFO("Ambient pressure (Pa)", "Note that setting an ambient pressure using 'Set Ambient Pressure' overrides any pressure compensation based on a previously set sensor altitude. Use of this command is highly recommended for applications *experiencing significant ambient pressure changes* to ensure sensor accuracy", 0, 150000, 0),
         ZUNO_CONFIG_PARAMETER_INFO("Sensor altitude (m)", "Typically, the sensor altitude is set once after device installation", 0, 5000, 0),
         ZUNO_CONFIG_PARAMETER_INFO("Factory reset", "Set to '1' for factory reset and then Z-Uno is restarting", 0, 1, 0)
 );

ZUNO_SCD4x SCD4x;
void setup() {
  float cfgParam1;
  Wire.begin();  
  Serial.begin(115200);
  delay(1000);
  SCD4x.stopPeriodicMeasurement();           // for reading/setting sensor parameters - see doc
  if(zunoInNetwork()) {
    zunoSaveCFGParam(PARAM_FACTORY_RESET,0);   // Reset the value to default
    // Get configuration parameters and set sensor values (must be done before read measurement!)
    cfgParam1 = zunoLoadCFGParam(PARAM_TEMP_OFFSET)/10.0;
    bool result = SCD4x.setTemperatureOffset(cfgParam1);
    cfgParam1 = zunoLoadCFGParam(PARAM_AMB_PRESSURE);
    result &=  SCD4x.setAmbientPressure(cfgParam1);
    cfgParam1 = zunoLoadCFGParam(PARAM_SENS_ALT);
    result &= result && SCD4x.setSensorAltitude(cfgParam1);
    if (!result) {
      Serial.print("error while setting parameters! Error number: (");
      Serial.print(SCD4x.getLastError());
      Serial.println(" )");
    }
  } else {
    Serial.println("Z-UNO IS NOT IN NETWORK INCLUDED - NO Z-WAVE FEATURES AVAILABLE!");
  }
  printSensorSettings();
  SCD4x.startPeriodicMeasurement();
}

void loop() {
  delay(5000);  // minimum - see doc
  SCD4x.readMeasurement();
  if(zunoInNetwork())    // Check if Z-Uno is included in Network
  {
    cnt++;
    if(zunoLoadCFGParam(PARAM_REPORTING_INT) <= cnt * 5) cnt = 0;   // define reporting interval
  
    // bool result = Serial.println(SCD4x.getDataReadyStatus()) ;  // optional use to be sure about it, integrated crc check will detect wrong values
    if(SCD4x.getLastError() == COMMUNICATION_ERROR_OK) {
      curCO2=SCD4x.getCO2();
      if(abs(lastCO2 - curCO2) >= zunoLoadCFGParam(PARAM_CO2_HYST) || cnt == 0) {
        zunoSendReport(1);
        lastCO2 = curCO2;
      }
      Serial.print("CO2: "); Serial.println(curCO2);
      curTemp=10*SCD4x.getTemperature();
      if(abs(lastTemp - curTemp) >= 10 * zunoLoadCFGParam(PARAM_TEMP_HYST) || cnt == 0)
      {
        zunoSendReport(2);
        lastTemp = curTemp;
      }
      Serial.print("Temp: "); Serial.println(curTemp/10.0);
      curHum=10*SCD4x.getHumidity();
      if(abs(lastHum - curHum) >= 10 * zunoLoadCFGParam(PARAM_HUMIDITY_HYST) || cnt == 0)
      {
        zunoSendReport(3);
        lastHum = curHum;
      }
      Serial.print("Hum: "); Serial.println(curHum/10.0);
      if (zunoLoadCFGParam(PARAM_FACTORY_RESET) == 1) {
        Serial.println("FACTORY RESET (inactive - see comment!");
        //SCD4x.perfomFactoryReset();                // REMOVE COMMENT IF YOU WANT TO ENABLE FEATURE !
        zunoReboot();
      }
    }
    else {
      Serial.print("communication error: "); Serial.println(SCD4x.getLastError());
    }
  } else {
      // WITHOUT Z-WAVE NETWORK SIMPLE REQUEST  without error handling
      Serial.println("-- NO Z-WAVE network! --");
      Serial.print("CO2:  ");Serial.println(SCD4x.getCO2());
      Serial.print("Temp: ");Serial.println(SCD4x.getTemperature());
      Serial.print("Hum:  ");Serial.println(SCD4x.getHumidity());
  }
}
void printSensorSettings() {
  bool result=SCD4x.getSensorData();
  char sn[20];
  SCD4x.copySerialNumber(sn);
  Serial.print("Sensor S/N: ");Serial.println(sn);
  Serial.print("Temp.-Offset:");Serial.println(SCD4x.getTempOffsetValue());
  Serial.print("Sensor Altitude: ");Serial.println(SCD4x.getSensorAltValue());
  Serial.print("Sensor AutomaticSelfCalibration: ");Serial.println(SCD4x.getASCValue());
  if(zunoInNetwork()) {
    Serial.print("Sensor Ambient Pressure: ");Serial.println(zunoLoadCFGParam(PARAM_AMB_PRESSURE));
    Serial.print("Sensor Factory Reset after reboot: ");Serial.println(zunoLoadCFGParam(PARAM_FACTORY_RESET));
  }
  if (!result) 
    Serial.println("error while getting sensor parameters!");
}
