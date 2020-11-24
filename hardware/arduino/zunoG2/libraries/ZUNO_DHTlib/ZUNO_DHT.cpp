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
		.timer = TIMER0,
		.lpLock = &gSyncTIMER0,
		.dmaSignal = zdmaPeripheralSignal_TIMER0_UFOF,
		.bus_clock = cmuClock_TIMER0
	},
	{
		.timer = TIMER1,
		.lpLock = &gSyncTIMER1,
		.dmaSignal = zdmaPeripheralSignal_TIMER1_UFOF,
		.bus_clock = cmuClock_TIMER1
	}
};

/* Public Constructors */
DHT::DHT(uint8_t pin, DHT_TYPE_SENSORS_t type): _lastreadtime(-1), _pin(pin), _type(type)
#if (ZUNO_ZERO_BSS != true)
	, _value({0}), _crc(0), _lpKey(0)
#endif
{
}

/* Public Methods */
ZunoError_t DHT::begin(void) {
	const ZunoDhtTypeConfig_t			*gconfigTable_b;
	const ZunoDhtTypeConfig_t			*gconfigTable_e;
	ZunoError_t							ret;

	gconfigTable_b = &gconfigTable[0];
	gconfigTable_e = &gconfigTable_b[(sizeof(gconfigTable) / sizeof(ZunoDhtTypeConfig_t))];
	while (gconfigTable_b < gconfigTable_e) {
		ret = zunoSyncOpen(gconfigTable_b->lpLock, SyncMasterDht, this->_init, (size_t)gconfigTable_b, &this->_lpKey);
		if (ret == ZunoErrorOk) {
			g_config = gconfigTable_b;
			break ;
		}
		else if (ret != ZunoErrorResourceAlready)
			return (ret);
		gconfigTable_b++;
	}
	pinMode(this->_pin, INPUT_PULLUP);
	zunoSyncReleseWrite(g_config->lpLock, SyncMasterDht, &this->_lpKey);
	return (ZunoErrorOk);
}

void DHT::end(void) {
	const ZunoDhtTypeConfig_t			*config;

	if ((config = g_config) == 0)
		return ;
	zunoSyncClose(config->lpLock, SyncMasterDht, this->_deInit, (size_t)config, &this->_lpKey);
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
	if ((ret = zunoSyncLockRead(config->lpLock, SyncMasterDht, &this->_lpKey)) != ZunoErrorOk)
		return (ret);
	ret = this->_readBody(config, bForce);
	zunoSyncReleseRead(config->lpLock, SyncMasterDht, &this->_lpKey);
	return (ret);
}

ZunoError_t DHT::_deInit(size_t param) {
	TIMER_Init_TypeDef					timerInit;
	TIMER_TypeDef						*timer;
	const ZunoDhtTypeConfig_t			*config;

	config = (const ZunoDhtTypeConfig_t *)param;
	TIMER_Reset(config->timer);
	g_config = 0;
	return (ZunoErrorOk);
}

static const TIMER_Init_TypeDef gInitTimer =
{
	.enable = false,						/* Enable timer when initialization completes. */           \
	.debugRun = false,						/* Stop counter during debug halt. */                       \
	.prescale = timerPrescale1,				/* No prescaling. */                                        \
	.clkSel = timerClkSelHFPerClk,			/* Select HFPER / HFPERB clock. */                          \
	.count2x = false,						/* Not 2x count mode. */                                    \
	.ati = false,							/* No ATI. */                                               \
	.fallAction = timerInputActionNone,		/* No action on falling input edge. */                      \
	.riseAction = timerInputActionNone,		/* No action on rising input edge. */                       \
	.mode = timerModeUp,					/* Up-counting. */                                          \
	.dmaClrAct = true,						/* Do not clear DMA requests when DMA channel is active. */ \
	.quadModeX4 = false,					/* Select X2 quadrature decode mode (if used). */           \
	.oneShot = false,						/* Disable one shot. */                                     \
	.sync = false							/* Not started/stopped/reloaded by other timers. */         \
};

ZunoError_t DHT::_init(size_t param) {
	TIMER_TypeDef						*timer;
	const ZunoDhtTypeConfig_t			*config;

	config = (const ZunoDhtTypeConfig_t *)param;
	CMU_ClockEnable(config->bus_clock, true);
	timer = config->timer;
	TIMER_TopSet(timer, CMU_ClockFreqGet(config->bus_clock) / 1000000 * 18);
	TIMER_Init(timer, &gInitTimer);
	return (ZunoErrorOk);
}

static uint32_t *_whileBit(uint32_t *b, uint32_t *e, uint32_t mask, size_t iMax, uint32_t *value) {
	size_t						i;
	uint32_t					tempos;
	uint32_t					*bTmp;

	i = 0;
	tempos = 0;
	while (b < e && i < iMax) {
		while (b < e && (b[0] & mask) == 0)
			b++;
		bTmp = b;
		while (b < e && (b[0] & mask) != 0)
			b++;
		tempos = tempos << 1;
		tempos |= (b - bTmp > 2) ? 1 : 0;
		i++;
	}
	value[0] = tempos;
	return (b);
}

inline ZunoError_t DHT::_readBody(const void *lpConfig, uint8_t bForce) {
	const ZunoDhtTypeConfig_t				*config;
	size_t									currenttime;
	size_t									pin;
	DHT_TYPE_SENSORS_t						type;
	ZunoError_t								ret;
	uint32_t								buffWriteDma[DHT_BUFFER_DMA_WRITE_LEN];
	uint32_t								*b;
	uint32_t								*e;
	DHT_TYPE_VALUE_t						value;
	uint32_t								crc;
	uint32_t								mask;
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
	b = _whileBit(b, e, mask, 32, &value.value);
	b = _whileBit(b, e, mask, 8, &crc);
	if (b == e || (uint8_t)(value.byte0 + value.byte1 + value.byte2 + value.byte3) != (uint8_t)crc)
		return (ZunoErrorDhtCrc);
	this->_value = value;
	this->_crc = crc;
	return (ZunoErrorOk);
}
