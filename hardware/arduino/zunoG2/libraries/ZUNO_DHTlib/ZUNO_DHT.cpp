#include "Arduino.h"
#include "CrtxTimer.h"
#include "CrtxCmu.h"
#include "ZDma.h"
#include "Sync.h"
#include "ZUNO_DHT.h"

#define DHT_MIN_INTERVAL						2000
#define DHT_UINIQID_DMA_WRITE					((size_t)&this->_lastreadtime)
#define DHT_BUFFER_DMA_WRITE_LEN				250

typedef struct							ZunoDhtTypeConfig_s
{
	TIMER_TypeDef						*timer;
	ZunoSync_t							*lpLock;
	ZDMA_PeripheralSignal_t				dmaSignal;
	CMU_Clock_TypeDef					bus_clock;
}										ZunoDhtTypeConfig_t;

static const ZunoDhtTypeConfig_t		*g_config = 0;

const ZunoDhtTypeConfig_t gconfigTable[3] = {
	{
		.timer = WTIMER0,
		.lpLock = &gSyncWTIMER0,
		.dmaSignal = zdmaPeripheralSignal_WTIMER0_UFOF,
		.bus_clock = cmuClock_WTIMER0
	},
	{
		.timer = TIMER1,
		.lpLock = &gSyncTIMER1,
		.dmaSignal = zdmaPeripheralSignal_TIMER1_UFOF,
		.bus_clock = cmuClock_TIMER1
	},
	{
		.timer = TIMER0,
		.lpLock = &gSyncTIMER0,
		.dmaSignal = zdmaPeripheralSignal_TIMER0_UFOF,
		.bus_clock = cmuClock_TIMER0
	}
};

/* Public Constructors */
DHT::DHT(uint8_t pin, DHT_TYPE_SENSORS_t type): _lastreadtime(-1), _value({0}), _crc(0), _pin(pin), _type(type) {
}

/* Public Methods */
ZunoError_t DHT::begin(void) {
	const ZunoDhtTypeConfig_t			*gconfigTable_b;
	const ZunoDhtTypeConfig_t			*gconfigTable_e;
	ZunoError_t							ret;

	gconfigTable_b = &gconfigTable[0];
	gconfigTable_e = &gconfigTable_b[(sizeof(gconfigTable) / sizeof(ZunoDhtTypeConfig_t))];
	while (gconfigTable_b < gconfigTable_e) {
		ret = zunoSyncOpen(gconfigTable_b->lpLock, SyncMasterDht, this->_init, (size_t)gconfigTable_b);
		if (ret == ZunoErrorOk) {
			g_config = gconfigTable_b;
			break ;
		}
		else if (ret != ZunoErrorResourceAlready)
			return (ret);
		gconfigTable_b++;
	}
	pinMode(this->_pin, INPUT_PULLUP);
	return (ZunoErrorOk);
}

void DHT::end(void) {
	const ZunoDhtTypeConfig_t			*config;

	if ((config = g_config) == 0)
		return ;
	zunoSyncClose(config->lpLock, SyncMasterDht, this->_deInit, (size_t)config);
}

int16_t DHT::readTemperatureC10(uint8_t bForce) {
	ZunoError_t								ret;
	DHT_TYPE_VALUE_t						value;
	int16_t									out;

	ret = this->_read(bForce);
	if (ret == ZunoErrorOk || ret == ZunoErrorDhtResultPrevisous) {
		value = this->_value;
		switch (this->_type) {
		case DHT11:
			return (value.byte2 * 10 + value.byte3);
			break ;
		default:
			out = ((value.byte2 & 0x7F) << 8) | value.byte3;
			if ((value.byte2 & 0x80) != 0)
				out = -out;
			return (out);
			break ;
		}
	}
	return (BAD_DHT_VALUE);
}

int16_t DHT::readHumidityH10(uint8_t bForce) {
	ZunoError_t								ret;
	DHT_TYPE_VALUE_t						value;

	ret = this->_read(bForce);
	if (ret == ZunoErrorOk || ret == ZunoErrorDhtResultPrevisous) {
		value = this->_value;
		switch (this->_type) {
		case DHT11:
			return (value.byte0 * 10 + value.byte1);
			break ;
		default:
			return ((value.byte0 << 8) | value.byte1);
			break ;
		}
	}
	return (BAD_DHT_VALUE);
}

float DHT::readTemperature(uint8_t bForce) {
	return (this->readTemperatureC10(bForce) / (float)10.0);
}

float DHT::readHumidity(uint8_t bForce) {
	return (this->readHumidityH10(bForce) / (float)10.0);
}

/* Private Methods */
inline ZunoError_t DHT::_read(uint8_t bForce) {
	ZunoError_t								ret;
	const ZunoDhtTypeConfig_t				*config;

	if ((config = g_config) == 0)
		return (ZunoErrorNotInit);
	if ((ret = zunoSyncLockRead(config->lpLock, SyncMasterDht)) != ZunoErrorOk)
		return (ret);
	ret = this->_readBody(config, bForce);
	zunoSyncReleseRead(config->lpLock, SyncMasterDht);
	return (ret);
}

void DHT::_deInit(size_t param) {
	TIMER_Init_TypeDef					timerInit;
	TIMER_TypeDef						*timer;
	const ZunoDhtTypeConfig_t			*config;

	config = (const ZunoDhtTypeConfig_t *)param;
	TIMER_Reset(config->timer);
	g_config = 0;
}

ZunoError_t DHT::_init(size_t param) {
	TIMER_Init_TypeDef					timerInit;
	TIMER_TypeDef						*timer;
	const ZunoDhtTypeConfig_t			*config;

	config = (const ZunoDhtTypeConfig_t *)param;
	CMU_ClockEnable(config->bus_clock, true);
	timerInit = TIMER_INIT_DEFAULT;
	timerInit.dmaClrAct = true;
	timerInit.enable = false;
	timer = config->timer;
	TIMER_TopSet(timer, CMU_ClockFreqGet(config->bus_clock) / 1000000 * 18);
	TIMER_Init(timer, &timerInit);
	return (ZunoErrorOk);
}

inline ZunoError_t DHT::_readBody(const void *lpConfig, uint8_t bForce) {
	const ZunoDhtTypeConfig_t				*config;
	size_t									currenttime;
	size_t									pin;
	DHT_TYPE_SENSORS_t						type;
	ZunoError_t								ret;
	uint32_t								buffWriteDma[DHT_BUFFER_DMA_WRITE_LEN];
	uint32_t								*b;
	uint32_t								*bTmp;
	uint32_t								*e;
	DHT_TYPE_VALUE_t						value;
	uint32_t								crc;
	uint32_t								mask;
	size_t									i;
	TIMER_TypeDef							*timer;

	config = (ZunoDhtTypeConfig_t *)lpConfig;
	currenttime = millis();
	if (bForce == false && ((currenttime - this->_lastreadtime) < DHT_MIN_INTERVAL))// Чтобы не опрашивать сенсор слишком часто
		return (ZunoErrorDhtResultPrevisous);
	pin = this->_pin;
	if ((ret = ZDMA.toPeripheralMemory(DHT_UINIQID_DMA_WRITE, config->dmaSignal, &buffWriteDma[0], (void *)&GPIO->P[getRealPort(pin)].DIN, DHT_BUFFER_DMA_WRITE_LEN, zdmaData32)) != ZunoErrorOk)
		return (ret);
	buffWriteDma[DHT_BUFFER_DMA_WRITE_LEN - 1] = 0;
	this->_lastreadtime = currenttime;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW); // Send start signal
	type = this->_type;
	switch (type) {
		case DHT11:// Датчик долго думает
			currenttime = 20;
			break ;
		default:// Гораздо быстрее откликается
			currenttime = 2;
			break ;
	}
	delay(currenttime);
	noInterrupts();
	pinMode(pin, INPUT_PULLUP);
	timer = config->timer;
	TIMER_Enable(timer, true);
	interrupts();
	delay(8);
	TIMER_Enable(timer, false);
	mask = 1 << getRealPin(pin);
	b = &buffWriteDma[0];
	e = &b[DHT_BUFFER_DMA_WRITE_LEN];
	if ((buffWriteDma[DHT_BUFFER_DMA_WRITE_LEN - 1] & mask) == 0)
		return (ZunoErrorDhtNoSync);
	while (b < e && (b[0] & mask) == 0)
		b++;
	while (b < e && (b[0] & mask) != 0)
		b++;
	while (b < e && (b[0] & mask) == 0)
		b++;
	while (b < e && (b[0] & mask) != 0)
		b++;
	value.value = 0;
	i = 0;
	while (b < e && i < 32) {
		while (b < e && (b[0] & mask) == 0)
			b++;
		bTmp = b;
		while (b < e && (b[0] & mask) != 0)
			b++;
		value.value = value.value << 1;
		value.value |= (b - bTmp > 2) ? 1 : 0;
		i++;
	}
	crc = 0;
	i = 0;
	while (b < e && i < 8) {
		while (b < e && (b[0] & mask) == 0)
			b++;
		bTmp = b;
		while (b < e && (b[0] & mask) != 0)
			b++;
		crc = crc << 1;
		crc |= (b - bTmp > 2) ? 1 : 0;
		i++;
	}
	if (b == e || (uint8_t)(value.byte0 + value.byte1 + value.byte2 + value.byte3) != (uint8_t)crc)
		return (ZunoErrorDhtCrc);
	this->_value = value;
	this->_crc = crc;
	return (ZunoErrorOk);
}
