#ifndef ZUNO_SOMFY_H
#define ZUNO_SOMFY_H

#include "Arduino.h"

#define ZUNO_SOMFY_RS480_GLYDEA					(0x6)
#define ZUNO_SOMFY_TYPE_RS480_GLYDEA			(1 << ZUNO_SOMFY_RS480_GLYDEA)

#define ZUNO_SOMFY_INVALID_VALUE				(0xFFFFFFFF)

typedef struct							ZunoSomfyList_s
{
	struct ZunoSomfyList_s				*next;
	uint8_t								dest[3];/* LSB  to MSB */
	uint8_t								type;
}										ZunoSomfyList_t;

class SomfyClass {
	public:
		SomfyClass(HardwareSerial *hardwareSerial = &Serial1);
		ZunoError_t							begin(size_t types, uint8_t rx, uint8_t tx, uint8_t dir_pin);
		ZunoError_t							begin(size_t types) { return (this->begin(types, RX1, TX1, 2)); };
		void								end(void);
		ZunoError_t							move(size_t id, size_t position);
		size_t								getPosition(size_t id);
		ZunoError_t							stop(size_t id);
		size_t								getCountDevice(void);

	private:
		inline void								_end(ZunoSomfyList_t *list);
		inline ZunoError_t						_begin(size_t types, uint8_t rx, uint8_t tx, uint8_t dir_pin);
		inline size_t							_getPosition(size_t id);
		inline ZunoError_t						_move(size_t id, size_t position);
		inline ZunoError_t						_stop(size_t id);
		inline size_t							_receive(void *dest);
		inline ZunoError_t						_send(void *buffer, size_t len, ZunoSomfyList_t *list);
		inline ZunoSomfyList_t					*_findList(size_t id);
		static ZunoSync_t						_syncSomfy;
		HardwareSerial							*_hardwareSerial;
		ZunoSomfyList_t							*_list;
		uint8_t									_dir_pin;
		uint8_t									_key;
};

#endif//ZUNO_SOMFY_H