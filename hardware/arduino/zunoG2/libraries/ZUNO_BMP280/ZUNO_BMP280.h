/*************************************************** 
  This is a library for the Bosch BMP280/BME280 Barometric Pressure + Temp sensor + Humidity sensor

  Designed specifically to work with the Bosch BMP280 or BME280 sensors 
  Writen by Z-Wave>ME team for Z-Uno project.
  Used code from:
  1) Written by Limor Fried/Ladyada for Adafruit Industries.  
  2) From Bosch datasheet
  Slightly adoptated for fix-point math ans Z-Uno stack behaviour.
 ****************************************************/

#ifndef ZME_BMP280_H
#define ZNE_BMP280_H

#include "Arduino.h"
#include "Wire.h"
#include "SPI.h"

/*!
 *  @brief  default I2C address
 */
#define BME280_ADDRESS (0x77)           // Primary I2C Address
                                        /*!
                                         *  @brief  alternate I2C address
                                         */
#define BME280_ADDRESS_ALTERNATE (0x76) // Alternate Address

/*!
 *  @brief Register addresses
 */
enum {
  BME280_REGISTER_DIG_T1 = 0x88,
  BME280_REGISTER_DIG_T2 = 0x8A,
  BME280_REGISTER_DIG_T3 = 0x8C,

  BME280_REGISTER_DIG_P1 = 0x8E,
  BME280_REGISTER_DIG_P2 = 0x90,
  BME280_REGISTER_DIG_P3 = 0x92,
  BME280_REGISTER_DIG_P4 = 0x94,
  BME280_REGISTER_DIG_P5 = 0x96,
  BME280_REGISTER_DIG_P6 = 0x98,
  BME280_REGISTER_DIG_P7 = 0x9A,
  BME280_REGISTER_DIG_P8 = 0x9C,
  BME280_REGISTER_DIG_P9 = 0x9E,

  BME280_REGISTER_DIG_H1 = 0xA1,
  BME280_REGISTER_DIG_H2 = 0xE1,
  BME280_REGISTER_DIG_H3 = 0xE3,
  BME280_REGISTER_DIG_H4 = 0xE4,
  BME280_REGISTER_DIG_H5 = 0xE5,
  BME280_REGISTER_DIG_H6 = 0xE7,

  BME280_REGISTER_CHIPID = 0xD0,
  BME280_REGISTER_VERSION = 0xD1,
  BME280_REGISTER_SOFTRESET = 0xE0,

  BME280_REGISTER_CAL26 = 0xE1, // R calibration stored in 0xE1-0xF0

  BME280_REGISTER_CONTROLHUMID = 0xF2,
  BME280_REGISTER_STATUS = 0XF3,
  BME280_REGISTER_CONTROL = 0xF4,
  BME280_REGISTER_CONFIG = 0xF5,
  BME280_REGISTER_PRESSUREDATA = 0xF7,
  BME280_REGISTER_TEMPDATA = 0xFA,
  BME280_REGISTER_HUMIDDATA = 0xFD
};

/**************************************************************************/
/*!
    @brief  calibration data
*/
/**************************************************************************/
typedef struct {
  uint16_t dig_T1; ///< temperature compensation value
  int16_t dig_T2;  ///< temperature compensation value
  int16_t dig_T3;  ///< temperature compensation value

  uint16_t dig_P1; ///< pressure compensation value
  int16_t dig_P2;  ///< pressure compensation value
  int16_t dig_P3;  ///< pressure compensation value
  int16_t dig_P4;  ///< pressure compensation value
  int16_t dig_P5;  ///< pressure compensation value
  int16_t dig_P6;  ///< pressure compensation value
  int16_t dig_P7;  ///< pressure compensation value
  int16_t dig_P8;  ///< pressure compensation value
  int16_t dig_P9;  ///< pressure compensation value

  uint8_t dig_H1; ///< humidity compensation value
  int16_t dig_H2; ///< humidity compensation value
  uint8_t dig_H3; ///< humidity compensation value
  int16_t dig_H4; ///< humidity compensation value
  int16_t dig_H5; ///< humidity compensation value
  int8_t dig_H6;  ///< humidity compensation value
} bme280_calib_data;
/*=========================================================================*/

#define BAD_BMP280_16BVALUE 0xFFFF
#define BAD_BMP280_32BVALUE 0xFFFFFFFF

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with BME280 IC
*/
/**************************************************************************/
class ZUNO_BMP280 {
	public:
		/** Oversampling rate for the sensor. */
		enum sensor_sampling {
			/** No over-sampling. */
			SAMPLING_NONE = 0x00,
			/** 1x over-sampling. */
			SAMPLING_X1 = 0x01,
			/** 2x over-sampling. */
			SAMPLING_X2 = 0x02,
			/** 4x over-sampling. */
			SAMPLING_X4 = 0x03,
			/** 8x over-sampling. */
			SAMPLING_X8 = 0x04,
			/** 16x over-sampling. */
			SAMPLING_X16 = 0x05
		};

		/** Operating mode for the sensor. */
		enum sensor_mode {
			/** Sleep mode. */
			MODE_SLEEP = 0x00,
			/** Forced mode. */
			MODE_FORCED = 0x01,
			/** Normal mode. */
			MODE_NORMAL = 0x03,
		};

		/** Filtering level for sensor data. */
		enum sensor_filter {
			/** No filtering. */
			FILTER_OFF = 0x00,
			/** 2x filtering. */
			FILTER_X2 = 0x01,
			/** 4x filtering. */
			FILTER_X4 = 0x02,
			/** 8x filtering. */
			FILTER_X8 = 0x03,
			/** 16x filtering. */
			FILTER_X16 = 0x04
		};

		/** Standby duration in ms */
		enum standby_duration {
			/** 0.5 ms standby. */
			STANDBY_MS_0_5 = 0x00,
			/** 62.5 ms standby. */
			STANDBY_MS_63 = 0x01,
			/** 125 ms standby. */
			STANDBY_MS_125 = 0x02,
			/** 250 ms standby. */
			STANDBY_MS_250 = 0x03,
			/** 500 ms standby. */
			STANDBY_MS_500 = 0x04,
			/** 1000 ms standby. */
			STANDBY_MS_1000 = 0x05,
			/** 2000 ms standby. BMP280 only*/
			STANDBY_MS_2000 = 0x06,
			/** 4000 ms standby. BMP280 only*/
			STANDBY_MS_4000 = 0x07,
			/** 10 ms standby. BME280 only*/
			STANDBY_MS_10 = 0x06,
			/** 20 ms standby. BME280 only*/
			STANDBY_MS_20 = 0x07
		};

#define CHIPID_BMP280_1					0x56
#define CHIPID_BMP280_2					0x57
#define CHIPID_BMP280_3					0x58
#define CHIPID_BME280					0x60

  bool begin(uint8_t addr = BME280_ADDRESS, TwoWire *theWire = &Wire, uint8_t scl = SCL, uint8_t sda = SDA);
  bool begin(SPIClass *spi, uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss);

  void setSampling(sensor_mode mode = MODE_NORMAL,
                   sensor_sampling tempSampling = SAMPLING_X16,
                   sensor_sampling pressSampling = SAMPLING_X16,
                   sensor_sampling humSampling = SAMPLING_X16,
                   sensor_filter filter = FILTER_OFF,
                   standby_duration duration = STANDBY_MS_1000);

  bool takeForcedMeasurement(void);

  int16_t readTemperatureC100(void);
  float readTemperature(void);

  int32_t readPressureHgMM10(void);
  float readPressureHgMM(void);
  int32_t readPressurePa(void);
  float readPressure(void);

  int16_t readHumidityH10(void);
  float readHumidity(void);

  float readAltitude(float seaLevel);
  float seaLevelForAltitude(float altitude, float pressure);
  uint32_t sensorID(void);

  float getTemperatureCompensation(void);
  void setTemperatureCompensation(float);

protected:
	inline bool init();
	inline void readCoefficients(void);
	inline bool isReadingCalibration(void);

	inline void write8(byte reg, byte value);
	inline uint8_t read8(byte reg);
	inline uint16_t read16(byte reg);
	inline uint32_t read24(byte reg);
	inline int16_t readS16(byte reg);
	inline uint16_t read16_LE(byte reg); // little endian
	inline int16_t readS16_LE(byte reg); // little endian


	inline int32_t _readHumidity(void);
	inline int32_t _readPressurePa(void);
	inline void					_read(uint8_t *in, size_t in_count, uint8_t *out, size_t out_count);
	union
	{
		TwoWire						*_wire;
		SPIClass					*_spi;
	};
	uint8_t						_wire_addr;
	uint8_t						_sensorID; //!< ID of the BME Sensor

  int32_t t_fine; //!< temperature with high resolution, stored as an attribute
                  //!< as this is used for temperature compensation reading
                  //!< humidity and pressure

  int32_t t_fine_adjust = 0; //!< add to compensate temp readings and in turn
                             //!< to pressure and humidity readings

  bme280_calib_data _bme280_calib; //!< here calibration data is stored

	/**************************************************************************/
	/*!
		@brief  ctrl_meas register
	*/
	/**************************************************************************/
	struct ctrl_meas {
		// temperature oversampling
		// 000 = skipped
		// 001 = x1
		// 010 = x2
		// 011 = x4
		// 100 = x8
		// 101 and above = x16
		unsigned int osrs_t : 3; ///< temperature oversampling

		// pressure oversampling
		// 000 = skipped
		// 001 = x1
		// 010 = x2
		// 011 = x4
		// 100 = x8
		// 101 and above = x16
		unsigned int osrs_p : 3; ///< pressure oversampling

		// device mode
		// 00       = sleep
		// 01 or 10 = forced
		// 11       = normal
		unsigned int mode : 2; ///< device mode

		/// @return combined ctrl register
		unsigned int get() { return (osrs_t << 5) | (osrs_p << 2) | mode; }
	};
	ctrl_meas _measReg; //!< measurement register object

};

#endif
