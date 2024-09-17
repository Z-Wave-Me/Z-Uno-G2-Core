#ifndef ZUNO_DAC_H
#define ZUNO_DAC_H

#include "em_vdac.h"

#if defined(_SILICON_LABS_32B_SERIES_2)
typedef enum							ZunoDacClassRef_e
{
	ZunoDacClassRef1V25 = vdacRef1V25,
	ZunoDacClassRef2V5 = vdacRef2V5,
}										ZunoDacClassRef_t;

typedef struct							ZunoDacClassChannelProcess_s
{
	uint32_t							value;
	uint8_t								pin;
	uint8_t								channel;
	#if defined(_SILICON_LABS_32B_SERIES_2)
	uint8_t								real_pin;
	VDAC_ChPortSel_t					vdac_port;
	bool								alt;
	#endif
}										ZunoDacClassChannelProcess_t;

typedef struct							ZunoDacClassChannelSave_s
{
	uint32_t							value;
	uint8_t								pin;
}										ZunoDacClassChannelSave_t;

class ZunoDacClass {
	public:
		ZunoDacClass(void);
		inline bool								begin(void) {return(this->begin(ZunoDacClassRef2V5));};
		bool									begin(ZunoDacClassRef_t ref);
		bool									write(uint8_t pin, float v);
		bool									disable(uint8_t pin);

	private:
		inline bool								_test_already_channel(ZunoDacClassChannelProcess_t *process);
		inline bool								_test_free_channel(ZunoDacClassChannelProcess_t *process);
		inline bool								_write(ZunoDacClassChannelProcess_t *process);
		inline bool								_get_values(ZunoDacClassChannelProcess_t *process, uint8_t pin, float v);
		#if defined(_SILICON_LABS_32B_SERIES_2)
		inline bool								_get_values_series(ZunoDacClassChannelProcess_t *process, uint8_t pin);
		#endif
		inline void								_dac_init(ZunoDacClassRef_t ref);
		ZunoDacClassRef_t						_vRef;
		bool									_init;
		ZunoDacClassChannelSave_t				_save[0x2];
};

extern ZunoDacClass DAC;
#endif

#endif//ZUNO_DAC_H