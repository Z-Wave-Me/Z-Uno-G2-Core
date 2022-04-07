#ifndef LESENSE_CLASS_UART_H
#define LESENSE_CLASS_UART_H

#include "em_lesense.h"
#include "em_acmp.h"

typedef enum
{
	LesenseTypeAdc,
	LesenseTypeAcmp
} ZunoLesenseType_t;


typedef struct							ZunoLesenseAdcnInit_s
{
	uint16_t							fghgf;
}										ZunoLesenseAdcnInit_t;

#define LSENSE_ADC_INIT_DEFAULT\
	{\
		0\
	}


typedef struct							ZunoLesenseHeader_s
{
	struct ZunoLesenseHeader_s			*next;
	bool 								(*function)(uint8_t, uint16_t);
	uint16_t							value;
	uint8_t								pin;
	uint8_t								channel;
	ZunoLesenseType_t					type;
}										ZunoLesenseHeader_t;

typedef struct							ZunoLesenseValues_s
{
	ZunoSync_t							SyncLesenseClass;
	ZunoLesenseHeader_t					*list;
	uint16_t							LesenseScanSequence_fq;
	uint8_t								count_lesense;
	uint8_t								LesenseClassKey;
}										ZunoLesenseValues_t;

typedef struct							ZunoLesenseAdc_s
{
	ZunoLesenseHeader_t					header;//first always must be
}										ZunoLesenseAdc_t;

class LesenseClass {
	public:
		LesenseClass(void);
		// ZunoError_t								addAcmpThres(uint8_t pin, bool (*function)(uint8_t, uint16_t), uint16_t acmpThres, LESENSE_ChCompMode_TypeDef compMode);
		inline size_t							getScanSequence(void) {return ((1000000 / this->_values.LesenseScanSequence_fq));};
		ZunoError_t								setScanSequence(size_t ups);
		ZunoError_t								addAdc(uint8_t pin, bool (*function)(uint8_t, uint16_t));
		void									deleteAdc(uint8_t pin);
		ZunoError_t								adcResolution(ADC_Res_TypeDef resolution);
		ZunoError_t								adcReference(ADC_Ref_TypeDef reference);
		ZunoError_t								adcAcqTime(ADC_AcqTime_TypeDef acqtime);
		ZunoError_t								adcThres(uint8_t pin, uint16_t cntThres, LESENSE_ChCompMode_TypeDef compMode);

	private:
		// inline ZunoError_t						_addAcmpThres(uint8_t pin, bool (*function)(uint8_t, uint16_t), uint16_t acmpThres, LESENSE_ChCompMode_TypeDef compMode, ACMP_Channel_TypeDef possel);
		inline ZunoError_t						_addAdc(uint8_t pin, ADC_PosSel_TypeDef possel, bool (*function)(uint8_t, uint16_t));
		inline void								_deleteAdc(uint8_t pin);
		inline void								_adcInit(void);
		inline ZunoError_t						_adcThres(uint8_t pin, uint16_t cntThres, LESENSE_ChCompMode_TypeDef compMode);
		static void								_LESENSE_IRQHandler(uint32_t flags);
		inline ZunoError_t						_lesenseInit(void);
		inline void								_lesenseDeInit(void);
		inline ZunoLesenseHeader_t				*_findList(uint8_t pin);
		static ZunoLesenseHeader_t				*_findListChannel(uint8_t channel);
		inline void								_addList(ZunoLesenseHeader_t *list);
		inline void								_cutList(ZunoLesenseHeader_t *list);
		static const ZunoLesenseAdcnInit_t		_initLesenseAdc;
		static ZunoLesenseValues_t				_values;

};

extern LesenseClass Lesense;


#endif // LESENSE_CLASS_UART_H