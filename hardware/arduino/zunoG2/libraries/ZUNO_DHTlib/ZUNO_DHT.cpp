#include "Arduino.h"
#include "Sync.h"
#include "ZUNO_DHT.h"
#include "zwaveme_libft.h"
#include "LdmaClass.h"
#include "em_device.h"
#include "em_timer.h"

#define DHT_CHANNEL								0

#define DHT_MIN_INTERVAL						2000
#define DHT_BUFFER_DMA_WRITE_LEN				(56 * 2)
#define DHT_TOP_FREQ							(200)

#define DHT_START_IMPULSE_MAX                  95
#define DHT_START_IMPULSE_MIN                  75

#define DHT_MARK_IMPULSE_MAX               	   70
#define DHT_MARK_IMPULSE_MIN               	   45
#define DHT_LOGIC_IMPULSE_POS_MAX              78
#define DHT_LOGIC_IMPULSE_POS_MIN              60
#define DHT_LOGIC_IMPULSE_NEG_MAX              32
#define DHT_LOGIC_IMPULSE_NEG_MIN              22
#define DHT_TIMER_MINIMUM_PACKAGE_LEN          ((1+32+8) << 1)

typedef struct							ZunoDhtTypeConfig_s
{
	TIMER_TypeDef						*timer;
	ZunoSync_t							*lpLock;
	LDMA_PeripheralSignal_t					dmaSignal;
	CMU_Clock_TypeDef					bus_clock;
}										ZunoDhtTypeConfig_t;

typedef struct							ZunoDhtTypeInit_s
{
	const ZunoDhtTypeConfig_t			*config;
}										ZunoDhtTypeInit_t;

static const ZunoDhtTypeConfig_t		*g_config = 0;

ZunoDhtList_t *DHT::_list = NULL;
uint8_t DHT::_freq = 0x0;

const ZunoDhtTypeConfig_t gconfigTable[] = {
	{
		.timer = TIMER0,
		.lpLock = &gSyncTIMER0,
		.dmaSignal =  ldmaPeripheralSignal_TIMER0_CC0,
		.bus_clock = cmuClock_TIMER0
	},
	{
		.timer = TIMER1,
		.lpLock = &gSyncTIMER1,
		.dmaSignal =  ldmaPeripheralSignal_TIMER1_CC0,
		.bus_clock = cmuClock_TIMER1
	}
};

/* Public Constructors */
DHT::DHT(uint8_t pin, DHT_TYPE_SENSORS_t type): _lastreadtime((size_t)(0 - DHT_MIN_INTERVAL)), _pin(pin), _type(type), _lpKey(false), _result(ZunoErrorDhtCrc)
{
}

/* Public Methods */
ZunoError_t DHT::begin(void) {
	const ZunoDhtTypeConfig_t			*gconfigTable_b;
	const ZunoDhtTypeConfig_t			*gconfigTable_e;
	ZunoError_t							ret;
	ZunoDhtTypeInit_t					init;

	if (this->_findList() != NULL)
		return (ZunoErrorOk);
	gconfigTable_b = &gconfigTable[0];
	gconfigTable_e = &gconfigTable_b[(sizeof(gconfigTable) / sizeof(ZunoDhtTypeConfig_t))];
	while (gconfigTable_b < gconfigTable_e) {
		init.config = gconfigTable_b;
		ret = zunoSyncOpen(gconfigTable_b->lpLock, SyncMasterDht, this->_init, (size_t)&init, &this->_lpKey);
		if (ret == ZunoErrorOk) {
			if (this->_addList() == false)
				ret = ZunoErrorMemory;
			break ;
		}
		else if (ret != ZunoErrorResourceAlready)
			return (ret);
		gconfigTable_b++;
	}
	zunoSyncReleseWrite(g_config->lpLock, SyncMasterDht, &this->_lpKey);
	return (ZunoErrorOk);
}

void DHT::end(void) {
	const ZunoDhtTypeConfig_t			*config;
	ZunoDhtList_t						*list;

	if ((config = g_config) == 0)
		return ;
	if ((list = this->_findList()) == NULL)
		return ;
	this->_cutList(list);
	if (DHT::_list != NULL)
		return ;
	zunoSyncClose(config->lpLock, SyncMasterDht, this->_deInit, (size_t)config, &this->_lpKey);
}

int16_t DHT::readTemperatureC10(uint8_t bForce) {
	ZunoError_t								ret;
	DHT_TYPE_VALUE_t						value;
	int16_t									out;

	ret = this->_read(bForce);
	value = this->_value;
	if (ret == ZunoErrorOk || ret == ZunoErrorDhtResultPrevisous) {
		switch (this->_type) {
			case DHT11:
				out = value.byte2 * 10 + value.byte3;
				break ;
			case DHT12:
				out = value.byte2 * 10 + (value.byte3 & 0x7F);
				if ((value.byte3 & 0x80) != 0)
					out = -out;
				break ;
			case DHT22:
			case DHT21:
				out = ((value.byte2 & 0x7F) << 8) | value.byte3;
				if ((value.byte2 & 0x80) != 0)
					out = -out;
				break ;
			default:
				out = BAD_DHT_VALUE;
				break ;
		}
	}
	else
		out = BAD_DHT_VALUE;
	return (out);
}

int16_t DHT::readHumidityH10(uint8_t bForce) {
	ZunoError_t								ret;
	DHT_TYPE_VALUE_t						value;
	int16_t									out;

	ret = this->_read(bForce);
	value = this->_value;
	if (ret == ZunoErrorOk || ret == ZunoErrorDhtResultPrevisous) {
		switch (this->_type) {
			case DHT11:
			case DHT12:
				out = (value.byte0 * 10 + value.byte1);
				break ;
			case DHT21:
			case DHT22:
				out = ((value.byte0 << 8) | value.byte1);
				break ;
			default:
				out = BAD_DHT_VALUE;
				break ;
		}
	}
	else
		out = BAD_DHT_VALUE;
	return (out);
}

/*!
 *  @brief  Read temperature
 *  @param  S
 *          Scale. Boolean value:
 *					- true = Fahrenheit
 *					- false = Celcius
 *  @param  force
 *          true if in force mode
 *	@return Temperature value in selected scale
 */
float DHT::readTemperature(bool S, bool bforce) {
	int16_t				value;
	float				f;

	value = this->readTemperatureC10(bforce);
	if ((uint16_t)value == BAD_DHT_VALUE)
		return (0 / (float)0);
	f = value / (float)10.0;
	if (S == false)
		return (f);
	return (this->convertCtoF(f));
}

float DHT::readHumidity(uint8_t bForce) {
	int16_t				value;

	value = this->readHumidityH10(bForce);
	if ((uint16_t)value == BAD_DHT_VALUE)
		return (0 / (float)0);
	return (value / (float)10.0);
}

/* Private Methods */
ZunoDhtList_t *DHT::_findList(void) {
	ZunoDhtList_t	*list;

	list = this->_list;
	while (list != NULL) {
		if (list->dht == this)
			break ;
		list = list->next;
	}
	return (list);
}

bool DHT::_addList(void) {
	ZunoDhtList_t		*list_next;
	ZunoDhtList_t		*list_tmp;
	ZunoDhtList_t		*list;

	if ((list = (ZunoDhtList_t *)malloc(sizeof(list[0x0]))) == NULL)
		return (false);
	list->next = NULL;
	list->dht = this;
	if ((list_next = this->_list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->_list = list;
	return (true);
}

void DHT::_cutList(ZunoDhtList_t *list) {
	ZunoDhtList_t		*list_prev;
	ZunoDhtList_t		*list_tmp;

	list_prev = this->_list;
	if (list == list_prev)
		this->_list = list->next;
	else {
		while ((list_tmp = list_prev->next) != list)
			list_prev = list_tmp;
		list_prev->next = list->next;
	}
}

inline ZunoError_t DHT::_read(uint8_t bForce) {
	ZunoError_t								ret;
	const ZunoDhtTypeConfig_t				*config;

	if ((config = g_config) == 0)
		return (ZunoErrorNotInit);
	if ((ret = zunoSyncLockRead(config->lpLock, SyncMasterDht, &this->_lpKey)) != ZunoErrorOk)
		return (ret);
	ret = this->_readBody(config, bForce);
	#ifdef DHT_LIB_DEBUG
	Serial.print("DHT STATUS:");
	Serial.println(ret);
	#endif
	this->_result = ret;
	zunoSyncReleseRead(config->lpLock, SyncMasterDht, &this->_lpKey);
	return (ret);
}

ZunoError_t DHT::_deInit(size_t param) {
	const ZunoDhtTypeConfig_t			*config;

	config = (const ZunoDhtTypeConfig_t *)param;
	TIMER_Reset(config->timer);
	g_config = 0;
	return (ZunoErrorOk);
}

ZunoError_t DHT::_init(size_t param) {
	TIMER_TypeDef						*timer;
	const ZunoDhtTypeConfig_t			*config;
	TIMER_Init_TypeDef					init;
	ZunoDhtTypeInit_t					*initDht;
	TIMER_InitCC_TypeDef				initCC;
	size_t								freq;

	initDht = (ZunoDhtTypeInit_t *)param;
	config = initDht->config;
	g_config = config;
	CMU_ClockEnable(config->bus_clock, true);
	timer = config->timer;
	init = TIMER_INIT_DEFAULT;
	init.enable = false;
	init.dmaClrAct = true;
	init.riseAction = timerInputActionReloadStart;
	init.fallAction = timerInputActionReloadStart;
	TIMER_Init(timer, &init);
	initCC = TIMER_INITCC_DEFAULT;
	initCC.edge = timerEdgeBoth;
	initCC.mode = timerCCModeCapture;
	initCC.filter = true;
	TIMER_InitCC(timer, DHT_CHANNEL, &initCC);
	freq = CMU_ClockFreqGet(config->bus_clock) / 1000000;
	TIMER_TopSet(timer, freq * DHT_TOP_FREQ);
	DHT::_freq = freq;
	return (ZunoErrorOk);
}


bool DHT::_find_startmarker(uint16_t * &b, uint8_t max_size){
	while(true) {
		uint16_t t1 = *b/_freq;
		uint16_t t2 = *(b+1)/_freq;
		uint16_t t3 = *(b+2)/_freq;
		if((DHT_START_IMPULSE_MIN <= t1)  && ( t1 <= DHT_START_IMPULSE_MAX) &&
		(DHT_START_IMPULSE_MIN <= t2)  && ( t2 <= DHT_START_IMPULSE_MAX) &&
		(t3 >= 47) && ( t3 <= 65)){
			b += 2;
			return true;
		}
		b++;
		max_size--;
		if (max_size < DHT_TIMER_MINIMUM_PACKAGE_LEN)
			return (false); // The package is too short
	}
	return false;
}
bool  DHT::_extract_value(uint16_t * &b, uint32_t &value, uint8_t bits){
	value = 0;
	while(bits--){
		uint16_t m = *b/_freq;
		b++;
		uint16_t l = *b/_freq;
		b++;
		value <<= 1;
		if(l > m)
			value |= 1;
	}
	return true;
}
		

inline ZunoError_t DHT::_readBody(const void *lpConfig, uint8_t bForce) {
	const ZunoDhtTypeConfig_t				*config;
	size_t									currenttime;
	ZunoError_t								ret;
	uint16_t								buffWriteDma[DHT_BUFFER_DMA_WRITE_LEN];
	uint16_t								*b;
	DHT_TYPE_VALUE_t						value;
	uint32_t								crc;
	TIMER_TypeDef							*timer;
	ssize_t									channel;
	LdmaClassTransferSingle_t				array;

	if (this->_findList() == NULL)
		return (ZunoErrorNotInit);
	config = (ZunoDhtTypeConfig_t *)lpConfig;
	config->timer->ROUTELOC0 = getLocationTimer0AndTimer1Chanell(this->_pin, DHT_CHANNEL);
	currenttime = millis();
	if (bForce == false && ((currenttime - this->_lastreadtime) < DHT_MIN_INTERVAL)) {// Чтобы не опрашивать сенсор слишком часто
		if ((ret = this->_result) == ZunoErrorOk || ret == ZunoErrorDhtResultPrevisous)
			return (ZunoErrorDhtResultPrevisous);
		return (ret);
	}
	timer = config->timer;
	if ((channel = LdmaClass::transferSingle((void *)&timer->CC[DHT_CHANNEL].CCV, &buffWriteDma[0], DHT_BUFFER_DMA_WRITE_LEN, config->dmaSignal, ldmaCtrlSizeHalf, ldmaCtrlSrcIncNone, ldmaCtrlDstIncOne, &array)) < 0x0)
		return (ZunoErrorDmaLimitChannel);
	_lastreadtime = currenttime;
	pinMode(this->_pin, OUTPUT_DOWN);// Send start signal
	switch (_type) {
		case DHT21:
		case DHT22:// Гораздо быстрее откликается 
			currenttime = 2;
			break ;
		default:// Датчик долго думает
			currenttime = 20;
			break ;
	}
	delay(currenttime);
	noInterrupts();
	timer->ROUTEPEN = (1UL << DHT_CHANNEL);//enabled CC
	pinMode(this->_pin, INPUT_PULLUP);
	TIMER_Enable(timer, true);
	interrupts();
	delay(6);
	timer->ROUTEPEN = _TIMER_ROUTEPEN_RESETVALUE;//disabled CC
	TIMER_Enable(timer, false);
	LdmaClass::transferStop(channel);
	b = &buffWriteDma[0];//Let's pass the noise
	#ifdef DHT_LIB_DEBUG
	int i;
	Serial.print("DHT TIMER BUFF:{ ");
	for(i=0;i<DHT_BUFFER_DMA_WRITE_LEN;i++){
		Serial.print(buffWriteDma[i]/_freq);
		Serial.print(" ");
	}
	Serial.println("}");
	#endif
	if(!_find_startmarker(b, DHT_BUFFER_DMA_WRITE_LEN)){
		#ifdef DHT_LIB_DEBUG
		Serial.println("NOSYNC1");
		#endif
		return (ZunoErrorDhtNoSync);
	}
	#ifdef DHT_LIB_DEBUG
	Serial.print("Start value:");
	Serial.println(*b/_freq);
	#endif
	if(!_extract_value(b, value.value, 32)){
		#ifdef DHT_LIB_DEBUG
		Serial.println("WRONG VALUE DATA");
		#endif
		return (ZunoErrorDhtWrongData);
	}
	if(!_extract_value(b, crc, 8)){
		#ifdef DHT_LIB_DEBUG
		Serial.println("WRONG CRC DATA");
		#endif
		return (ZunoErrorDhtWrongData);
	}
	if ((uint8_t)(value.byte0 + value.byte1 + value.byte2 + value.byte3) != (uint8_t)crc)
		return (ZunoErrorDhtCrc);
	this->_value = value;
	this->_crc = crc;
	return (ZunoErrorOk);
}
