#include <Arduino.h>
#include "ZUNO_ModBus.h"
#include "Sync.h"
#include "ZUNO_Neptun.h"

#define NEPTUN_SENSORSS_WIRELESS_MAX_COUNT	50


typedef struct								NeptunGetDest_s
{
	uint8_t									adress;//slave
	uint8_t									fn;//Function code
	uint8_t									len;
	uint8_t									data[2];/* MSB  to LSB */
	uint8_t									crc16_modbus[2];/* MSB  to LSB */
}											NeptunGetDest_t;

/* Values */
ZunoSync_t NeptunClass::_syncNeptun = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterNeptun);

/* Public Constructors */
NeptunClass::NeptunClass(HardwareSerial *hardwareSerial, uint16_t timeout): ModBusRtuClass(hardwareSerial, timeout), _key(true), _adress(240) {

}

/* Public Methods */
ZunoError_t NeptunClass::begin(NeptunBaudrate_t baudrate, uint8_t rx, uint8_t tx, uint8_t dir_pin) {
	ZunoError_t						ret;

	zunoSyncLockWrite(&NeptunClass::_syncNeptun, SyncMasterNeptun, &this->_key);
	ret = ModBusRtuClass::begin(this->convertInBaudrate(baudrate), rx, tx, dir_pin);
	zunoSyncReleseWrite(&NeptunClass::_syncNeptun, SyncMasterNeptun, &this->_key);
	return (ret);
}

void NeptunClass::end(void) {
	zunoSyncLockWrite(&NeptunClass::_syncNeptun, SyncMasterNeptun, &this->_key);
	ModBusRtuClass::end();
	zunoSyncReleseWrite(&NeptunClass::_syncNeptun, SyncMasterNeptun, &this->_key);
}

NeptunSensorsWirelessStatus_t NeptunClass::devGetSensorsWirelessStatus(size_t id) {
	NeptunSensorsWirelessStatus_t			out;

	if (id == 0 || id > NEPTUN_SENSORSS_WIRELESS_MAX_COUNT) {
		out.status = ZunoErrorInvalidValue;
		return (out);
	}
	out.raw = this->_read(0x38 + id).raw;
	return (out);
}

NeptunSensorsWirelessConfig_t NeptunClass::devGetSensorsWirelessConfig(size_t id) {
	NeptunSensorsWirelessConfig_t			out;

	if (id == 0 || id > NEPTUN_SENSORSS_WIRELESS_MAX_COUNT) {
		out.status = ZunoErrorInvalidValue;
		return (out);
	}
	out.raw = this->_read(0x6 + id).raw;
	return (out);
}

ZunoError_t NeptunClass::devSetSensorsWirelessConfig(size_t id, NeptunSensorsGroop_t value) {
	if (id == 0 || id > NEPTUN_SENSORSS_WIRELESS_MAX_COUNT)
		return (ZunoErrorInvalidValue);
	return (this->_write(0x6 + id, value));
}

ZunoError_t NeptunClass::devGetMeter(NeptunConfigMeterId_t id, NeptunConfigMeterSlot_t slot, uint32_t *value) {
	NeptunGetOut_t					out;
	uint32_t						tempos;

	out = this->_read(0x6C + (id + slot) * 2);
	if (out.status == ZunoErrorOk) {
		tempos = out.value;
		out = this->_read(0x6B + (id + slot) * 2);
		tempos = tempos | (out.value << 0x10);
		value[0] = tempos;
	}
	return (out.status);
}

ZunoError_t NeptunClass::devSetMeter(NeptunConfigMeterId_t id, NeptunConfigMeterSlot_t slot, uint32_t value) {
	ZunoError_t						ret;

	ret = this->_write(0x6C + (id + slot) * 2, value);
	if (ret == ZunoErrorOk)
		ret = this->_write(0x6B + (id + slot) * 2, value >> 0x10);
	return (ret);
}

/* Private Methods */
ZunoError_t NeptunClass::_write(uint16_t reg, uint16_t value) {
	ZunoError_t							status;

	zunoSyncLockWrite(&NeptunClass::_syncNeptun, SyncMasterNeptun, &this->_key);
	status = ModBusRtuClass::writeSR(this->_adress, reg, value);
	zunoSyncReleseWrite(&NeptunClass::_syncNeptun, SyncMasterNeptun, &this->_key);
	return (status);
}

NeptunGetOut_t NeptunClass::_read(size_t reg) {
	NeptunGetDest_t					dest;
	NeptunGetOut_t					out;

	zunoSyncLockWrite(&NeptunClass::_syncNeptun, SyncMasterNeptun, &this->_key);
	if ((out.status = ModBusRtuClass::readHR(this->_adress, reg, 1, &dest)) == ZunoErrorOk) {
		out.value = dest.data[1] | (dest.data[0] << 8);
	}
	zunoSyncReleseWrite(&NeptunClass::_syncNeptun, SyncMasterNeptun, &this->_key);
	return (out);
}
