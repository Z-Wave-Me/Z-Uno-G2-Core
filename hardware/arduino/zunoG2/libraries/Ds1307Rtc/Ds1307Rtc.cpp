#include "Ds1307Rtc.h"
#include "Status.h"

#define DS_1307_RTC_CLASS_CURRENT_CENTURY							2000

#define DS_1307_RTC_CLASS_CMD_DATE									0x0
#define DS_1307_RTC_CLASS_CMD_STORAGE								0x8

#define DS_1307_RTC_CLASS_HALT										0x80
#define DS_1307_RTC_CLASS_AM_PM										0x40
#define DS_1307_RTC_CLASS_PM										0x20
#define DS_1307_RTC_CLASS_AM_PM_MASK								0x1F
#define DS_1307_RTC_CLASS_SECOND_MASK								0x7F
#define DS_1307_RTC_CLASS_24_HOUR_MASK								0x3F

typedef struct							Ds1307RtcDate_s
{
	uint8_t								second;
	uint8_t								minute;
	uint8_t								hour;
	uint8_t								wday;
	uint8_t								day;
	uint8_t								month;
	uint8_t								year;
}										Ds1307RtcDate_t;

typedef struct							Ds1307RtcCmdSet_s
{
	uint8_t								command;
	Ds1307RtcDate_t						date;
}										Ds1307RtcCmdSet_t;

typedef struct							Ds1307RtcCmdStorageWrite_s
{
	uint8_t								command;
	uint8_t								data[DS_1307_RTC_CLASS_EEPROM_SIZE];
}										Ds1307RtcCmdStorageWrite_t;

/* Constants */


/* Public Constructors */
Ds1307RtcClass::Ds1307RtcClass(TwoWire *wire, uint8_t addr): _wire(wire), _addr(addr) {
}


/* Public Methods */
bool Ds1307RtcClass::write(uint8_t addr, const void *buffer, uint8_t len) {
	Ds1307RtcCmdStorageWrite_t					cmd_storage_write;

	if (len == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_DS_1307_RTC, STATUS_BAD_ARGUMENTS), false));
	if ((addr + len) > DS_1307_RTC_CLASS_EEPROM_SIZE)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_DS_1307_RTC, STATUS_BAD_ARGUMENTS), false));
	cmd_storage_write.command = DS_1307_RTC_CLASS_CMD_STORAGE + addr;
	memcpy(&cmd_storage_write.data[0x0], buffer, len);
	if (this->_wire->transfer(this->_addr, &cmd_storage_write, sizeof(cmd_storage_write.command) + len) != WIRE_ERORR_TRANSMISSION_SUCCESS)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool Ds1307RtcClass::read(uint8_t addr, void *buffer, uint8_t len) {
	uint8_t							command;
	uint8_t							*tmp;
	size_t							step;

	if (len == 0x0)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_DS_1307_RTC, STATUS_BAD_ARGUMENTS), false));
	if ((addr + len) > DS_1307_RTC_CLASS_EEPROM_SIZE)
		return (this->_last_status(STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_DS_1307_RTC, STATUS_BAD_ARGUMENTS), false));
	command = DS_1307_RTC_CLASS_CMD_STORAGE + addr;
	if (this->_wire->transfer(this->_addr, &command, sizeof(command)) != WIRE_ERORR_TRANSMISSION_SUCCESS)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	tmp = (uint8_t *)buffer;
	while (len != 0x0) {
		if (len > WIRE_BUFFER_LENGTH)
			step = WIRE_BUFFER_LENGTH;
		else
			step = len;
		len = len - step;
		if (this->_wire->requestFrom(this->_addr, step) != step)
			return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
		while (step-- != 0x0) {
			tmp[0x0] = this->_wire->read();
			tmp++;
		}
	}
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool Ds1307RtcClass::set(time_t time) {
	struct tm								timeinfo;

	gmtime_r(&time, &timeinfo);
	return (this->set(&timeinfo));
}

bool Ds1307RtcClass::set(struct tm *timeinfo) {
	Ds1307RtcCmdSet_t					set;

	set.command = DS_1307_RTC_CLASS_CMD_DATE;
	set.date.second = DS_1307_RTC_CLASS_HALT;// Stop the clock. The seconds will be written last
	set.date.minute = this->_dec2bcd(timeinfo->tm_min);//00 - 59
	set.date.hour = this->_dec2bcd(timeinfo->tm_hour);// 00 - 23
	set.date.wday = timeinfo->tm_wday + 0x1;// 1 - 7
	set.date.day = this->_dec2bcd(timeinfo->tm_mday);// 01 - 31
	set.date.month = this->_dec2bcd(timeinfo->tm_mon + 0x1);// 01 - 12
	set.date.year = this->_dec2bcd(timeinfo->tm_year % 100);// 00 - 99
	if (this->_wire->transfer(this->_addr, &set, sizeof(set)) != WIRE_ERORR_TRANSMISSION_SUCCESS)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	set.date.second = this->_dec2bcd(timeinfo->tm_sec);//00 - 59
	if (this->_wire->transfer(this->_addr, &set, 0x2) != WIRE_ERORR_TRANSMISSION_SUCCESS)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool Ds1307RtcClass::get(time_t *time) {
	struct tm								timeinfo;

	if (this->get(&timeinfo) == false)
		return (false);
	time[0x0] = mktime(&timeinfo);
	return (true);
}

bool Ds1307RtcClass::get(struct tm *timeinfo) {
	uint8_t							command;
	uint8_t							hour;

	command = DS_1307_RTC_CLASS_CMD_DATE;
	if (this->_wire->transfer(this->_addr, &command, sizeof(command)) != WIRE_ERORR_TRANSMISSION_SUCCESS)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	if (this->_wire->requestFrom(this->_addr, sizeof(Ds1307RtcDate_t)) != sizeof(Ds1307RtcDate_t))
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	timeinfo->tm_sec = this->_bcd2dec(this->_wire->read() & DS_1307_RTC_CLASS_SECOND_MASK);//00 - 59
	timeinfo->tm_min = this->_bcd2dec(this->_wire->read() );//00 - 59
	hour = this->_wire->read();
	if ((hour & DS_1307_RTC_CLASS_AM_PM) != 0x0)
		hour = this->_12hour_to_24hour(this->_bcd2dec(hour & DS_1307_RTC_CLASS_AM_PM_MASK), (hour & DS_1307_RTC_CLASS_PM));
	else
		hour = this->_bcd2dec(hour & DS_1307_RTC_CLASS_24_HOUR_MASK);
	timeinfo->tm_hour = hour;// 00 - 23
	timeinfo->tm_wday = this->_wire->read() - 0x1;//0 - 6
	timeinfo->tm_mday = this->_bcd2dec(this->_wire->read());// 01 - 31
	timeinfo->tm_mon = this->_bcd2dec(this->_wire->read()) - 0x1;//00 - 11
	timeinfo->tm_year = this->_bcd2dec(this->_wire->read()) + (DS_1307_RTC_CLASS_CURRENT_CENTURY - 1900);
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool Ds1307RtcClass::isRunning(void) {
	uint8_t							command;
	uint8_t							value;

	command = DS_1307_RTC_CLASS_CMD_DATE;
	if (this->_wire->transfer(this->_addr, &command, sizeof(command)) != WIRE_ERORR_TRANSMISSION_SUCCESS)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	// Just fetch the seconds register and check the top bit
	if (this->_wire->requestFrom(this->_addr, (uint8_t)0x1) != 0x1)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	value = this->_wire->read();
	if ((value & DS_1307_RTC_CLASS_HALT) != 0x0)
		return (this->_last_status(STATUS_SUCCESS, false));
	return (this->_last_status(STATUS_SUCCESS, true));
}

bool Ds1307RtcClass::begin(void) {
	size_t							scl;
	size_t							sda;

	if (this->_wire == &Wire) {
		scl = SCL;
		sda = SDA;
	}
	else {
		scl = SCL1;
		sda = SDA1;
	}
	return (this->begin(scl, sda));
}

bool Ds1307RtcClass::begin(uint8_t scl, uint8_t sda) {
	if (this->_wire->begin(0x0, scl, sda) != ZunoErrorOk)
		return (this->_last_status(STATUS_TMP_FOR_REPLACE, false));
	this->_wire->setClock(100000);
	return (this->_last_status(STATUS_SUCCESS, true));
}

/* Private Methods */
bool Ds1307RtcClass::_last_status(uint32_t status, bool ret) {
	SetLastStatus(status);
	return (ret);
}

uint8_t Ds1307RtcClass::_12hour_to_24hour(uint8_t hour, uint8_t bPM) {
	if (bPM == 0x0) {
		if (hour == 12)
			return (0);
		return (hour);
	}
	if (hour == 12)
		return (12);
	return (hour + 12);
}
