/* CO2 sensor SCD4x library for Z-Uno G2
 *  v. 1.0 07.09.2023  by Michael Pruefer
 *  based on Sensirion sensor documentation
 *  see https://sensirion.com/media/documents/E0F04247/631EF271/CD_DS_SCD40_SCD41_Datasheet_D1.pdf
 *
 */
//ZUNO_SCD4x.h

#ifndef ZUNO_SCD4x_h
#define ZUNO_SCD4x_h

#include "Arduino.h"

#define SCD4x_ADDR  	0x62	// I2C Address

#define SCD4x_CMD_STPM  0x21b1		// cmd start_periodic_measurement
#define SCD4x_CMD_REAM  0xec05		// cmd read_measurement
#define SCD4x_CMD_SPPM  0x3f86		// cmd stop_periodic_measurement
#define SCD4x_CMD_STOF  0x241d		// cmd set_temperature_offset
#define SCD4x_CMD_GTOF  0x2318		// cmd get_temperature_offset
#define SCD4x_CMD_SSAL  0x2427		// cmd set_sensor_altitude
#define SCD4x_CMD_GSAL  0x2322		// cmd get_sensor_altitude
#define SCD4x_CMD_SAPR  0xe000		// cmd set_ambient_pressure
#define SCD4x_CMD_PCAL  0x362f		// cmd perform_forced_recalibration
#define SCD4x_CMD_SACA  0x2416		// cmd set_automatic_self_calibration_enabled
#define SCD4x_CMD_GACA  0x2313		// cmd get_automatic_self_calibration_enabled
#define SCD4x_CMD_SLPM  0x21ac		// cmd start_low_power_periodic_measurement
#define SCD4x_CMD_GDRA  0xe4b8		// cmd get_data_ready_status
#define SCD4x_CMD_PERS  0x3615		// cmd persist_settings
#define SCD4x_CMD_GSER  0x3682		// cmd get_serial_number
#define SCD4x_CMD_PSTE  0x3639		// cmd perform_self_test
#define SCD4x_CMD_PFRS  0x3632		// cmd perfom_factory_reset
#define SCD4x_CMD_PRIN  0x3646		// cmd reinit
//SCD41
#define SCD4x_CMD_MSSH  0x219d		// cmd measure_single_shot
#define SCD4x_CMD_MSS1  0x2196		// cmd measure_single_shot_rht_only
#define SCD4x_CMD_PWDN  0x36e0		// cmd power_down
#define SCD4x_CMD_WKUP  0x36f6		// cmd wake_up

#define COMMUNICATION_ERROR_OK  0
#define COMMUNICATION_ERROR_I2C 1
#define COMMUNICATION_ERROR_CRC 2
#define MAX_SN_LENGTH           18

class ZUNO_SCD4x
{
  public:
	ZUNO_SCD4x();
	bool startPeriodicMeasurement(void);
	bool stopPeriodicMeasurement(void);
	void readMeasurement(byte*,int);    // read data
	void readMeasurement(void);    // read data
  bool getDataReadyStatus(void);
  bool setTemperatureOffset(float tempOffset);
  bool getTemperatureOffset(void);
  bool setSensorAltitude(uint16_t sensorAlt);
  bool getSensorAltitude(void);
  bool setAmbientPressure(uint32_t ambPressure);
  bool setAutomaticSelfCalibrationEnabled(uint16_t ASCEnabled);
  bool getAutomaticSelfCalibrationEnabled(void);
  bool performFocedRecalibraion(uint16_t targetCO2ppm);
  bool startLowPowerPeriodicMeasurement(void);
  bool PersistSettings(void);
  bool getSerialNumber(void);
  bool perfomFactoryReset(void);
  bool reinit(void);
  bool measureSingleShot(void);
  bool measureSingleShotRHTOnly(void);
  bool powerDown(void);
  bool wakeUp(void);
  bool getSensorData(void);           // read all sensor properties

  // Sensor values extractors
  uint16_t getCO2() const { return _CO2;};
  float    getTemperature() const { return _Temp; };
  float    getHumidity() const { return _Hum; };
  void     copySerialNumber(char * str) const { strncpy(str, _serialNumber, MAX_SN_LENGTH); };
  uint8_t  getLastError() const { return _comError; };
  uint16_t getSensorAltValue() const {return _sensorAlt; };
  float    getTempOffsetValue() const {return _TempOffset; };
  uint16_t getASCValue() const {return _sensorASC; };
  
  private:
  // sensor properties
  uint16_t _CO2;
	float _Temp;
	float _Hum;
  float _TempOffset;
  uint8_t _comError;               // 1- I2C error, 2- CRC error
  uint16_t _sensorASC;
  uint16_t _sensorAlt;
  float _CO2Correction;
  char  _serialNumber[MAX_SN_LENGTH];
  // methods
  bool sendCmd(uint16_t cmdCode, uint16_t delayMs);
  bool sendCmd(uint16_t cmdCode, uint16_t parameter, uint16_t delayMs);
  uint16_t readDbyte(uint16_t registerAddress, uint16_t delayMs = 1);
  uint8_t calcCRC8(uint8_t data[], uint8_t len);
  bool _extract2BytesValue(uint16_t & result);
  
};
#endif // ZUNO_SCD4x_h
