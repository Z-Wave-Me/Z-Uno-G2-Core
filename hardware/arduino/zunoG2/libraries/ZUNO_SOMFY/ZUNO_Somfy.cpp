#include <Arduino.h>
#include "ModBus.h"
#include "Sync.h"
#include "ZUNO_Somfy.h"


#define ZUNO_SOMFY_CMD_SET_NETWORK_CONFIG		(0x56)
#define ZUNO_SOMFY_CMD_SET_NODE_DISCOVERY		(0x50)

#define ZUNO_SOMFY_CMD_GET_MOTOR_POSITION		(0x0C)
#define ZUNO_SOMFY_CMD_POST_MOTOR_POSITION		(0x0D)
#define ZUNO_SOMFY_CMD_GET_NODE_ADDR			(0x40)

#define ZUNO_SOMFY_CMD_POST_NODE_ADDR			(0x60)

#define ZUNO_SOMFY_CMD_CTRL_STOP				(0x2)
#define ZUNO_SOMFY_CMD_CTRL_MOVETO				(0x3)

#define ZUNO_SOMFY_CMD_ACK						(0x7F)
#define ZUNO_SOMFY_CMD_NACK						(0x6F)

#define ZUNO_SOMFY_MASTER_TYPE					(0xF0)
#define ZUNO_SOMFY_ACK_TRUE						(0x80)
#define ZUNO_SOMFY_REPEAT						(0x3)
#define ZUNO_SOMFY_MAX_POSITION					(99)

#define ZUNO_SOMFY_BAUDRATE						(4800)
#define ZUNO_SOMFY_CONVERT(value)				((uint8_t)~(value))//Перед отправкай все кроме crc инвертируеться
#define ZUNO_SOMFY_TFREE_MS						(3)// Bus free timeout
#define ZUNO_SOMFY_TREQ_MS						(11)//Bus inactivity delay for a master before it can send a new request
#define ZUNO_SOMFY_TREP_MS						(256)// 5ms - 255ms Bus inactivity delay for a slave node before sending its reply (value is partially randomized between Min and Max)
#define ZUNO_SOMFY_MAX_LEN_CMD					(0x20)//Максимум отправляемых и получаемых данных в байтах
#define ZUNO_SOMFY_MASTER_SOURCE				(0x010000)

#define ZUNO_SOMFY_LEN_ASK(len, bAsk)			((uint8_t)((len & 0x1F) | ask))

typedef struct								SomfyCmdStart_s
{
	uint8_t									cmd;
	uint8_t									lenAsk;
	uint8_t									type;//Тип master всегда 0x0 кроме поиска slave тогда 0xF
	uint8_t									source[3];/* LSB  to MSB */
	uint8_t									dest[3];/* LSB  to MSB */
}											SomfyCmdStart_t;

typedef struct								SomfyCmdEnd_s
{
	uint8_t									crc[2];/* MSB  to LSB */
}											SomfyCmdEnd_t;

typedef struct								SomfyCmdSetNodeDiscovery_s
{
	SomfyCmdStart_t							start;
	uint8_t									data;//lock(0x01) or unlock(0x00) for find
	SomfyCmdEnd_t							end;
}											SomfyCmdSetNodeDiscovery_t;

typedef struct								SomfyCmdPostNodeAddr_s
{
	SomfyCmdStart_t							start;
	SomfyCmdEnd_t							end;
}											SomfyCmdPostNodeAddr_t;

typedef enum								SomfyCmdMovetoFunction_e
{
	SomfyCmdMovetoFunctionDown = 0x0,// 00h … DOWN limit Position is ignored
	SomfyCmdMovetoFunctionUp = 0x1,// 01h … UP limit Position is ignored
	SomfyCmdMovetoFunctionMoveToIp = 0x2,// 02h … Intermediate Position Position contains IP index (0 to 15)
	SomfyCmdMovetoFunctionMoveToRange = 0x4// 04h … Position in % of full travel range Position contains % value (0 to 100)
}											SomfyCmdMovetoFunction_t;

typedef struct								SomfyCmdMoveto_s
{
	SomfyCmdStart_t							start;
	SomfyCmdMovetoFunction_t				function;
	uint8_t									position[2];/* LSB  to MSB */
	uint8_t									reserved;
	SomfyCmdEnd_t							end;
}											SomfyCmdMoveto_t;

typedef struct								SomfyCmdStop_s
{
	SomfyCmdStart_t							start;
	uint8_t									reserved;
	SomfyCmdEnd_t							end;
}											SomfyCmdStop_t;

typedef struct								SomfyCmdGetMotorPosition_s
{
	SomfyCmdStart_t							start;
	SomfyCmdEnd_t							end;
}											SomfyCmdGetMotorPosition_t;

typedef struct								SomfyCmdPostMotorPosition_s
{
	SomfyCmdStart_t							start;
	uint8_t									position_pulse[2];
	uint8_t									position_percentage;
	uint8_t									reserved[8];
	SomfyCmdEnd_t							end;
}											SomfyCmdPostMotorPosition_t;

/* Values */
ZunoSync_t SomfyClass::_syncSomfy = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterSomfy);

/* Public Constructors */
SomfyClass::SomfyClass(HardwareSerial *hardwareSerial): _hardwareSerial(hardwareSerial), _key(true) {
}

/* Public Methods */
ZunoError_t SomfyClass::begin(size_t types, uint8_t rx, uint8_t tx, uint8_t dir_pin) {
	ZunoError_t						ret;

	zunoSyncLockWrite(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	ret = this->_begin(types, rx, tx, dir_pin);
	zunoSyncReleseWrite(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	return (ret);
}

void SomfyClass::end(void) {
	zunoSyncLockWrite(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	this->_end(this->_list);
	zunoSyncReleseWrite(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
}

ZunoError_t SomfyClass::move(size_t id, size_t position) {
	ZunoError_t						ret;

	zunoSyncLockRead(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	ret = this->_move(id, position);
	zunoSyncReleseRead(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	return (ret);
}

ZunoError_t SomfyClass::stop(size_t id) {
	ZunoError_t						ret;

	zunoSyncLockRead(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	ret = this->_stop(id);
	zunoSyncReleseRead(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	return (ret);
}

size_t SomfyClass::getCountDevice(void) {
	size_t					count;
	ZunoSomfyList_t			*list;

	zunoSyncLockRead(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	count = 0;
	list = this->_list;
	while (list != 0) {
		list = list->next;
		count++;
	}
	zunoSyncReleseRead(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	return (count);
}

size_t SomfyClass::getPosition(size_t id) {
	size_t					position;

	zunoSyncLockRead(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	position = this->_getPosition(id);
	zunoSyncReleseRead(&this->_syncSomfy, SyncMasterSomfy, &this->_key);
	return (position);
}

/* Private Methods */
inline size_t SomfyClass::_getPosition(size_t id) {
	ZunoSomfyList_t					*list;
	SomfyCmdGetMotorPosition_t		get_motor_position;
	union
	{
		uint8_t						buffer[ZUNO_SOMFY_MAX_LEN_CMD];
		SomfyCmdPostMotorPosition_t	post_motor_position;
	};

	if ((list = this->_findList(id)) == 0)
		return (ZUNO_SOMFY_INVALID_VALUE);
	get_motor_position.start.cmd = ZUNO_SOMFY_CMD_GET_MOTOR_POSITION;
	get_motor_position.start.lenAsk = sizeof(get_motor_position);
	this->_send(&get_motor_position, sizeof(get_motor_position), list);
	if (this->_receive(&buffer[0]) != sizeof(post_motor_position) || post_motor_position.start.cmd != ZUNO_SOMFY_CMD_POST_MOTOR_POSITION)
		return (ZUNO_SOMFY_INVALID_VALUE);
	return (post_motor_position.position_percentage);
}

inline ZunoError_t SomfyClass::_stop(size_t id) {
	ZunoSomfyList_t					*list;
	SomfyCmdStop_t					ctrl_stop;

	if ((list = this->_findList(id)) == 0)
		return (ZunoErrorSomfyNotDevice);
	ctrl_stop.start.cmd = ZUNO_SOMFY_CMD_CTRL_STOP;
	ctrl_stop.start.lenAsk = ZUNO_SOMFY_ACK_TRUE | sizeof(ctrl_stop);
	return (this->_send(&ctrl_stop, sizeof(ctrl_stop), list));
}

inline ZunoError_t SomfyClass::_move(size_t id, size_t position) {
	ZunoSomfyList_t					*list;
	SomfyCmdMoveto_t				ctrl_moveto;

	if ((list = this->_findList(id)) == 0)
		return (ZunoErrorSomfyNotDevice);
	if (position > ZUNO_SOMFY_MAX_POSITION)
		position = ZUNO_SOMFY_MAX_POSITION;
	ctrl_moveto.start.cmd = ZUNO_SOMFY_CMD_CTRL_MOVETO;
	ctrl_moveto.start.lenAsk = ZUNO_SOMFY_ACK_TRUE | sizeof(ctrl_moveto);
	ctrl_moveto.function = SomfyCmdMovetoFunctionMoveToRange;
	memcpy(&ctrl_moveto.position[0], &position, sizeof(ctrl_moveto.position));
	return (this->_send(&ctrl_moveto, sizeof(ctrl_moveto), list));
}

inline void SomfyClass::_end(ZunoSomfyList_t *list) {
	ZunoSomfyList_t					*list_tmp;

	while (list != 0) {
		list_tmp = list;
		list = list->next;
		free(list_tmp);
	}
	this->_list = 0;
}

inline ZunoError_t SomfyClass::_begin(size_t types, uint8_t rx, uint8_t tx, uint8_t dir_pin) {
	static const uint8_t			setNetworkConfig_brodcast[] = {ZUNO_SOMFY_CONVERT(ZUNO_SOMFY_CMD_SET_NETWORK_CONFIG), ZUNO_SOMFY_CONVERT(0x12), ZUNO_SOMFY_CONVERT(0xF0), ZUNO_SOMFY_CONVERT(0x01), ZUNO_SOMFY_CONVERT(0x00), ZUNO_SOMFY_CONVERT(0x00), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0x00), ZUNO_SOMFY_CONVERT(0xFF), 0x05, 0xA0};
	static const uint8_t			set_node_discovery_unlock[] = {ZUNO_SOMFY_CONVERT(ZUNO_SOMFY_CMD_SET_NODE_DISCOVERY), ZUNO_SOMFY_CONVERT(0x0C), ZUNO_SOMFY_CONVERT(0xF0), ZUNO_SOMFY_CONVERT(0x01), ZUNO_SOMFY_CONVERT(0x00), ZUNO_SOMFY_CONVERT(0x00), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0x00), 0x05, 0xAC};
	static const uint8_t			get_node_addr[] = {ZUNO_SOMFY_CONVERT(ZUNO_SOMFY_CMD_GET_NODE_ADDR), ZUNO_SOMFY_CONVERT(0x0B),ZUNO_SOMFY_CONVERT(0xF0), ZUNO_SOMFY_CONVERT(0x01), ZUNO_SOMFY_CONVERT(0x00), ZUNO_SOMFY_CONVERT(0x00), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), ZUNO_SOMFY_CONVERT(0xFF), 0x04, 0xBE};
	size_t							i;
	size_t							type;
	ZunoError_t						ret;
	ZunoSomfyList_t					*list;
	ZunoSomfyList_t					*list_tmp;
	ZunoSomfyList_t					*list_last;
	HardwareSerial					*hardwareSerial;
	SomfyCmdSetNodeDiscovery_t		set_node_discovery;
	ZunoSomfyList_t					list_send;
	union
	{
		uint8_t						buffer[ZUNO_SOMFY_MAX_LEN_CMD];
		SomfyCmdPostNodeAddr_t		post_node_addr;
	};

	hardwareSerial = this->_hardwareSerial;
	if ((ret = hardwareSerial->begin(ZUNO_SOMFY_BAUDRATE, rx, tx)) != ZunoErrorOk)
		return (ret);
	hardwareSerial->changeParity(usartOddParity);
	this->_end(this->_list);
	this->_dir_pin = dir_pin;
	pinMode(dir_pin, OUTPUT_UP);//Поднимаем и всегда RS485 держим на отправку данных
	hardwareSerial->write(&setNetworkConfig_brodcast[0], sizeof(setNetworkConfig_brodcast));//Что то конфигуриуем
	delay(ZUNO_SOMFY_TREQ_MS);
	hardwareSerial->write(&set_node_discovery_unlock[0], sizeof(set_node_discovery_unlock));//Разлачиваем все slave - что бы отдавали свой адресс во время поиска
	delay(ZUNO_SOMFY_TREQ_MS);
	i = 0;
	list = 0;
	while (i < ZUNO_SOMFY_REPEAT) {
		hardwareSerial->write(&get_node_addr[0], sizeof(get_node_addr));
		if (this->_receive(&buffer[0]) != sizeof(post_node_addr) || post_node_addr.start.cmd != ZUNO_SOMFY_CMD_POST_NODE_ADDR) {
			i++;
			continue ;
		}
		set_node_discovery.start.cmd = ZUNO_SOMFY_CMD_SET_NODE_DISCOVERY;
		set_node_discovery.start.lenAsk = ZUNO_SOMFY_ACK_TRUE | sizeof(set_node_discovery);//ask не будем получать - команда та - ждем тайминги - всегда долджна срабатывать
		set_node_discovery.data = 0x1;
		type = post_node_addr.start.type >> 4;
		list_send.type = type;
		memcpy(&list_send.dest[0], &post_node_addr.start.source[0], sizeof(list_send.dest));
		if ((ret = this->_send(&set_node_discovery, sizeof(set_node_discovery), &list_send)) != ZunoErrorOk) {//убираем тем самым из поиска
			this->_end(list);
			return (ret);
		}
		i = 0;
		if ((types & (1 << type)) == 0)
			continue ;
		if ((list_tmp = (ZunoSomfyList_t*)malloc(sizeof(ZunoSomfyList_t))) == 0) {
			this->_end(list);
			return (ZunoErrorMemory);
		}
		list_tmp->next = 0;
		list_tmp->type = type;
		memcpy(&list_tmp->dest[0], &post_node_addr.start.source[0], sizeof(list_tmp->dest));
		if (list == 0)
			list = list_tmp;
		else
			list_last->next = list_tmp;
		list_last = list_tmp;
	}
	if ((this->_list = list) == 0)
		return (ZunoErrorSomfyNotDevice);
	return (ZunoErrorOk);
}


inline ZunoSomfyList_t *SomfyClass::_findList(size_t id) {
	ZunoSomfyList_t			*list;
	size_t					i;

	list = this->_list;
	i = 0;
	while (list != 0) {
		if (id == i)
			break ;
		list = list->next;
		i++;
	}
	return (list);
}

inline size_t SomfyClass::_receive(void *dest) {
	HardwareSerial					*hardwareSerial;
	uint8_t							*b;
	uint8_t							*e;
	size_t							i;
	size_t							crc;
	size_t							data;

	delay(ZUNO_SOMFY_TFREE_MS);//Столько ждлем прежде чем переходим еа получение данных - что бы не далекий RS485 успел все данные отправить
	digitalWrite(this->_dir_pin, LOW);
	delay(ZUNO_SOMFY_TREP_MS);
	digitalWrite(this->_dir_pin, HIGH);
	hardwareSerial = this->_hardwareSerial;
	b = (uint8_t *)dest;
	i = 0;
	while (hardwareSerial->available()) {
		if (i > ZUNO_SOMFY_MAX_LEN_CMD)
			return (0);//overflow
		b[i++] = hardwareSerial->read();
	}
	if (i < 2)//crc - 2
		return (0);
	e = b + (i - 2);
	crc = 0;
	while (b < e) {
		data = b[0];
		crc = crc + data;
		b++[0] = ZUNO_SOMFY_CONVERT(data);
	}
	crc = __builtin_bswap16(crc);
	if (memcmp(&crc, b, 2) != 0)
		return (0);
	return (i);
}

inline ZunoError_t SomfyClass::_send(void *buffer, size_t len, ZunoSomfyList_t *list) {
	uint8_t							*b;
	uint8_t							*e;
	size_t							crc;
	size_t							data;
	size_t							lenAsk;
	size_t							i;
	uint8_t							buffer_receive[ZUNO_SOMFY_MAX_LEN_CMD];
	size_t							source;

	((SomfyCmdStart_t *)buffer)->type = ZUNO_SOMFY_MASTER_TYPE | list->type;
	memcpy(&((SomfyCmdStart_t *)buffer)->dest[0], &list->dest[0], sizeof(((SomfyCmdStart_t *)buffer)->source));
	source = ZUNO_SOMFY_MASTER_SOURCE;
	memcpy(&((SomfyCmdStart_t *)buffer)->source[0], &source, sizeof(((SomfyCmdStart_t *)buffer)->source));
	b = (uint8_t *)buffer;
	e = b + (len - 2);
	crc = 0;
	lenAsk = ((SomfyCmdStart_t *)buffer)->lenAsk;
	while (b < e) {
		data = ZUNO_SOMFY_CONVERT(b[0]);
		crc = crc + data;
		b++[0] = data;
	}
	crc = __builtin_bswap16(crc);
	memcpy(b, &crc, 2);
	i = 0;
	while (i < ZUNO_SOMFY_REPEAT) {
		delay(ZUNO_SOMFY_TREQ_MS);
		this->_hardwareSerial->write((uint8_t *)buffer, len);
		if ((lenAsk & ZUNO_SOMFY_ACK_TRUE) != 0) {
			if ((data = this->_receive(&buffer_receive[0])) != 0 && ((SomfyCmdStart_t *)&buffer_receive[0])->cmd == ZUNO_SOMFY_CMD_ACK)
				return (ZunoErrorOk);
		}
		else
			return (ZunoErrorOk);
		i++;
	}
	return (ZunoErrorSomfyNack);
}
