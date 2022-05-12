#ifndef DS_1307_RTC_h
#define DS_1307_RTC_h

#include "Arduino.h"
#include "Wire.h"
#include "time.h"

#define DS_1307_RTC_CLASS_EEPROM_SIZE							56

class Ds1307RtcClass {
	public:
		Ds1307RtcClass(TwoWire *wire=&Wire, uint8_t addr=0x68);
		bool												begin(void);
		bool												begin(uint8_t scl, uint8_t sda);
		bool												get(struct tm *timeinfo);
		bool												get(time_t *time);
		bool												set(time_t time);
		bool												set(struct tm *timeinfo);
		bool												write(uint8_t addr, const void *buffer, uint8_t len);
		bool												read(uint8_t addr, void *buffer, uint8_t len);
		bool												isRunning(void);

	private:
		inline bool											_last_status(uint32_t status, bool ret);
		inline uint8_t										_12hour_to_24hour(uint8_t hour, uint8_t bPM);
		inline uint8_t										_dec2bcd(uint8_t num) {return ((num/10 * 16) + (num % 10));};
		inline uint8_t										_bcd2dec(uint8_t num) {return ((num/16 * 10) + (num % 16));};
		TwoWire									*_wire;
		uint8_t									_addr;
	// 	bool exists;
};

#endif//DS_1307_RTC_h