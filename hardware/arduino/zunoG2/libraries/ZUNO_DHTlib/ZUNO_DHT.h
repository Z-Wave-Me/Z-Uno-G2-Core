
#ifndef ZUNO_DHT_H
#define ZUNO_DHT_H

#define DHT_RESULT_OK				ZunoErrorOk
#define DHT_RESULT_PREVIOUS			ZunoErrorDhtResultPrevisous
#define DHT_RESULT_ERROR_NOSYNC		ZunoErrorDhtNoSync
#define DHT_RESULT_ERROR_TIMEOUT	ZunoErrorDhtTimeout
#define DHT_RESULT_ERROR_CRC		ZunoErrorDhtCrc

#define BAD_DHT_VALUE				0xFFFF

typedef enum			DHT_TYPE_SENSORS_e
{
	DHT11,
	DHT21,
	DHT22,
	AM2301 = DHT21
}						DHT_TYPE_SENSORS_t;

typedef union			DHT_TYPE_VALUE_u
{
	uint32_t			value;
	struct
	{
		uint8_t			byte3;
		uint8_t			byte2;
		uint8_t			byte1;
		uint8_t			byte0;
	};
}						DHT_TYPE_VALUE_t;

class DHT {
	public:
		DHT(uint8_t pin, DHT_TYPE_SENSORS_t type = DHT22);
		ZunoError_t								begin(void);
		void									end(void);
		inline ZunoError_t						read(void) {return (this->_read(false));};
		inline ZunoError_t						read(uint8_t bForce) {return (this->_read(bForce));};
		int16_t									readTemperatureC10(uint8_t bForce);// returns temperature in 10 th of Celsius
		int16_t									readHumidityH10(uint8_t bForce);// returns humidity in 10 th of percent
		float									readTemperature(uint8_t bForce);// Returns temperature as float in Celsius
		float									readHumidity(uint8_t bForce);// Returns humidity as float in pecents
		inline int16_t							readTemperatureC10(void) {return (this->readTemperatureC10(false));};
		inline int16_t							readHumidityH10(void) {return (this->readHumidityH10(false));};
		inline float							readTemperature(void) {return (this->readTemperature(false));};
		inline float							readHumidity(void) {return (this->readHumidity(false));};
		inline void								getRawData(uint8_t *ptr) {
			DHT_TYPE_VALUE_t						value;

			value = this->_value;
			ptr[0] = value.byte0;
			ptr[1] = value.byte1;
			ptr[2] = value.byte2;
			ptr[3] = value.byte3;
			ptr[4] = this->_crc;
		};
	private:
		static ZunoError_t						_init(size_t param);
		static void								_deInit(size_t param);
		ZunoError_t								_read(uint8_t bForce);
		inline ZunoError_t						_readBody(const void *lpConfig, uint8_t bForce);
		size_t									_lastreadtime;
		DHT_TYPE_VALUE_t						_value;
		uint8_t									_crc;
		uint8_t									_pin;
		DHT_TYPE_SENSORS_t						_type;
};

#endif//ZUNO_DHT_H
