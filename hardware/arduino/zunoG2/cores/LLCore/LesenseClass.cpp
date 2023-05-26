#include "Arduino.h"
#include "stdio.h"
#include "stdarg.h"
#include "LesenseClass.h"
#include "zwaveme_libft.h"
#include "Sync.h"

void zmeADCInit();
ADC_PosSel_TypeDef zme_ADC_PIN2Channel(uint8_t pin);

#define ADC_MASK_CHANNEL			0x1F
#define ADC_SHIFT_PUSSEL			0x3

/* Constants */
const ZunoLesenseAdcnInit_t LesenseClass::_initLesenseAdc = LSENSE_ADC_INIT_DEFAULT;


/* Values */
 ZunoLesenseValues_t LesenseClass::_values = {
		.SyncLesenseClass = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterLesenseClass), 
		.list = 0x0,
		.LesenseScanSequence_fq = (1000 / 0x10),
		.count_lesense = 0x0,
		.LesenseClassKey = true
	};

/* Public Constructors */
LesenseClass::LesenseClass(void) {
}

/* Public Methods */
// ZunoError_t LesenseClass::addAcmpThres(uint8_t pin, bool (*function)(uint8_t, uint16_t), uint16_t acmpThres, LESENSE_ChCompMode_TypeDef compMode) {
// 	ACMP_Channel_TypeDef			possel;
// 	ZunoError_t						ret;

// 	if ((possel = (ACMP_Channel_TypeDef)zme_ADC_PIN2Channel(pin)) == (ACMP_Channel_TypeDef)adcPosSelAVDD)
// 		return (ZunoErrorInvalidPin);
// 	if (((possel & ADC_MASK_CHANNEL)) > ((sizeof(LESENSE->CH) / sizeof(LESENSE->CH[0x0])) - 0x1))
// 		return (ZunoErrorInvalidPin);
// 	if ((ret = zunoSyncLockWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey)) != ZunoErrorOk)
// 		return (ret);
// 	ret = this->_addAcmpThres(pin, function, acmpThres, compMode, possel);
// 	zunoSyncReleseWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey);
// 	return (ret);
// }

ZunoError_t LesenseClass::setScanSequence(size_t ups) {
	ZunoError_t						ret;

	if ((ret = zunoSyncLockWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey)) != ZunoErrorOk)
		return (ret);
	if (ups < 2000 || ups > 1000000)
		ret = ZunoErrorInvalidValue;
	else {
		this->_values.LesenseScanSequence_fq = LESENSE_ScanFreqSet(0x0, (1000000 / ups));
		ret = ZunoErrorOk;
	}
	zunoSyncReleseWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey);
	return (ret);
}

void LesenseClass::deleteAdc(uint8_t pin) {
	if (zunoSyncLockWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey) != ZunoErrorOk)
		return ;
	this->_deleteAdc(pin);
	zunoSyncReleseWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey);
}

ZunoError_t LesenseClass::addAdc(uint8_t pin, bool (*function)(uint8_t, uint16_t)) {
	ADC_PosSel_TypeDef				possel;
	ZunoError_t						ret;

	if ((possel = zme_ADC_PIN2Channel(pin)) == adcPosSelAVDD)
		return (ZunoErrorInvalidPin);
	if (((possel & ADC_MASK_CHANNEL)) > ((sizeof(LESENSE->CH) / sizeof(LESENSE->CH[0x0])) - 0x1))
		return (ZunoErrorInvalidPin);
	if ((ret = zunoSyncLockWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey)) != ZunoErrorOk)
		return (ret);
	ret = this->_addAdc(pin, possel, function);
	zunoSyncReleseWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey);
	return (ret);
}

ZunoError_t LesenseClass::adcThres(uint8_t pin, uint16_t cntThres, LESENSE_ChCompMode_TypeDef compMode) {
	ZunoError_t						ret;

	if ((ret = zunoSyncLockWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey)) != ZunoErrorOk)
		return (ret);
	ret = this->_adcThres(pin, cntThres, compMode);
	zunoSyncReleseWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey);
	return (ret);
}

ZunoError_t LesenseClass::adcResolution(ADC_Res_TypeDef resolution) {
	ADC_InitScan_TypeDef			initScan;
	ZunoError_t						ret;

	if ((ret = zunoSyncLockWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey)) != ZunoErrorOk)
		return (ret);
	this->_adcInit();
	initScan = ADC_INITSCAN_DEFAULT;
	initScan.reference = (ADC_Ref_TypeDef)((ADC0->SCANCTRL & _ADC_SCANCTRL_REF_MASK) >> _ADC_SCANCTRL_REF_SHIFT);
	initScan.resolution = resolution;
	initScan.acqTime = (ADC_AcqTime_TypeDef)((ADC0->SCANCTRL & _ADC_SCANCTRL_AT_MASK) >> _ADC_SCANCTRL_AT_SHIFT);
	initScan.fifoOverwrite = true;// FIFO overflow overwrites old data
	ADC_InitScan(ADC0, &initScan);
	zunoSyncReleseWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey);
	return (ZunoErrorOk);
}
ZunoError_t LesenseClass::adcReference(ADC_Ref_TypeDef reference) {
	ADC_InitScan_TypeDef			initScan;
	ZunoError_t						ret;

	if ((ret = zunoSyncLockWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey)) != ZunoErrorOk)
		return (ret);
	this->_adcInit();
	initScan = ADC_INITSCAN_DEFAULT;
	initScan.reference = reference;
	initScan.resolution = (ADC_Res_TypeDef)((ADC0->SCANCTRL & _ADC_SCANCTRL_RES_MASK) >> _ADC_SCANCTRL_RES_SHIFT);
	initScan.acqTime = (ADC_AcqTime_TypeDef)((ADC0->SCANCTRL & _ADC_SCANCTRL_AT_MASK) >> _ADC_SCANCTRL_AT_SHIFT);
	initScan.fifoOverwrite = true;// FIFO overflow overwrites old data
	ADC_InitScan(ADC0, &initScan);
	zunoSyncReleseWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey);
	return (ZunoErrorOk);
}

ZunoError_t LesenseClass::adcAcqTime(ADC_AcqTime_TypeDef acqtime) {
	ADC_InitScan_TypeDef			initScan;
	ZunoError_t						ret;

	if ((ret = zunoSyncLockWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey)) != ZunoErrorOk)
		return (ret);
	this->_adcInit();
	initScan = ADC_INITSCAN_DEFAULT;
	initScan.reference = (ADC_Ref_TypeDef)((ADC0->SCANCTRL & _ADC_SCANCTRL_REF_MASK) >> _ADC_SCANCTRL_REF_SHIFT);
	initScan.resolution = (ADC_Res_TypeDef)((ADC0->SCANCTRL & _ADC_SCANCTRL_RES_MASK) >> _ADC_SCANCTRL_RES_SHIFT);
	initScan.acqTime = acqtime;
	initScan.fifoOverwrite = true;// FIFO overflow overwrites old data
	ADC_InitScan(ADC0, &initScan);
	zunoSyncReleseWrite(&LesenseClass::_values.SyncLesenseClass, SyncMasterLesenseClass, &LesenseClass::_values.LesenseClassKey);
	return (ZunoErrorOk);
}


/* Private Methods */
// ZunoError_t LesenseClass::_addAcmpThres(uint8_t pin, bool (*function)(uint8_t, uint16_t), uint16_t acmpThres, LESENSE_ChCompMode_TypeDef compMode, ACMP_Channel_TypeDef possel) {
// 	ZunoLesenseHeader_t				*list;
// 	ZunoError_t						ret;
// 	uint32_t						perctrl;
// 	ACMP_TypeDef					*acmp;
// 	CMU_Clock_TypeDef				clock;
// 	ACMP_CapsenseInit_TypeDef		capsenseInit;
// 	LESENSE_ChDesc_TypeDef			initLesenseCh;
// 	size_t							channel;

// 	list = this->_findList(pin);
// 	if (list != 0x0)
// 		return (ZunoErrorOk);
// 	perctrl = LESENSE->PERCTRL;
// 	if ((perctrl & _LESENSE_PERCTRL_ACMP0MODE_MASK) == LESENSE_PERCTRL_ACMP0MODE_DISABLE) {
// 		acmp = ACMP0;
// 		clock = cmuClock_ACMP0;
// 		perctrl = LESENSE_PERCTRL_ACMP0MODE_MUXTHRES;
// 	}
// 	else if ((perctrl & _LESENSE_PERCTRL_ACMP1MODE_MASK) == LESENSE_PERCTRL_ACMP1MODE_DISABLE) {
// 		acmp = ACMP1;
// 		clock = cmuClock_ACMP1;
// 		perctrl = LESENSE_PERCTRL_ACMP1MODE_MUXTHRES;
// 	}
// 	else
// 		return (ZunoErrorInvalidPin);
// 	if ((list = (ZunoLesenseHeader_t *)malloc(sizeof(ZunoLesenseAdc_t))) == 0)
// 		return (ZunoErrorMemory);
// 	if ((ret = this->_lesenseInit()) != ZunoErrorOk) {
// 		free(list);
// 		return (ret);
// 	}
// 	list->pin = pin;
// 	list->next = 0x0;
// 	list->function = ((bool (*)(uint8_t, uint16_t))function);
// 	list->type = LesenseTypeAcmp;
// 	LESENSE_ScanStop();
// 	CMU_ClockEnable(cmuClock_HFPER, true);
// 	CMU_ClockEnable(clock, true);
// 	capsenseInit = ACMP_CAPSENSE_INIT_DEFAULT;
// 	ACMP_CapsenseInit(acmp, &capsenseInit);
// 	ACMP_CapsenseChannelSet(acmp, possel);
// 	while (!(acmp->STATUS & ACMP_STATUS_ACMPACT))// Wait until ACMP warms up
// 		;
// 	channel = (possel & ADC_MASK_CHANNEL);
// 	list->channel = channel;
// 	initLesenseCh = LESENSE_CH_CONF_DEFAULT;
// 	initLesenseCh.enaScanCh = true;  // Enable scan channel
// 	initLesenseCh.enaInt = true;
// 	initLesenseCh.storeCntRes = false;
// 	initLesenseCh.sampleMode = lesenseSampleModeACMP;
// 	initLesenseCh.intMode = lesenseSetIntLevel;
// 	initLesenseCh.compMode = compMode;
// 	initLesenseCh.evalMode = lesenseEvalModeThreshold;
// 	initLesenseCh.acmpThres = acmpThres;
// 	initLesenseCh.exTime = 0x0;
// 	initLesenseCh.measDelay = 0x0;
// 	initLesenseCh.sampleDelay = 0x0;
// 	LESENSE_ChannelConfig(&initLesenseCh, channel);
// 	LESENSE->CH[channel].EVAL = LESENSE->CH[channel].EVAL | LESENSE_CH_EVAL_STRSAMPLE_DATASRC;
// 	this->_addList(list);
// 	// LESENSE->PERCTRL = LESENSE->PERCTRL | perctrl;
// 	LESENSE_ScanStart();
// 	return (ZunoErrorOk);
// }

void LesenseClass::_deleteAdc(uint8_t pin) {
	ZunoLesenseHeader_t				*list;
	ADC_PosSel_TypeDef				possel;
	size_t							channel;

	list = this->_findList(pin);
	if (list == 0x0 || list->type != LesenseTypeAdc)
		return ;
	possel = zme_ADC_PIN2Channel(pin);
	LESENSE_ScanStop();
	ADC0->CMD = ADC_CMD_SCANSTOP;/* Make sure scan sequence is not in progress. */
	channel = (possel & ADC_MASK_CHANNEL);
	ADC0->SCANINPUTSEL = ADC0->SCANINPUTSEL & (~(_ADC_SCANINPUTSEL_INPUT0TO7SEL_MASK << ((channel / 0x8) * 0x8)));
	ADC0->SCANMASK = ADC0->SCANMASK ^ (0x1 << channel);
	BUS_RegBitWrite(&LESENSE->IEN, channel, false);/* Enable/disable interrupts on channel */
	BUS_RegBitWrite(&LESENSE->CHEN, channel, false);/* Enable/disable scan channel chIdx. */
	LESENSE_ScanStart();
	this->_lesenseDeInit();
	this->_cutList(list);
	free(list);
}

ZunoError_t LesenseClass::_addAdc(uint8_t pin, ADC_PosSel_TypeDef possel, bool (*function)(uint8_t, uint16_t)) {
	ZunoLesenseHeader_t				*list;
	ZunoError_t						ret;
	size_t							newSel;
	size_t							shift;
	size_t							inpusel;

	this->_adcInit();
	list = this->_findList(pin);
	if (list != 0x0)
		return (ZunoErrorOk);
	shift = (((possel & ADC_MASK_CHANNEL) / 0x8) * 0x8);
	newSel = (possel >> ADC_SHIFT_PUSSEL) << shift;
	inpusel = ADC0->SCANINPUTSEL & (_ADC_SCANINPUTSEL_INPUT0TO7SEL_MASK << shift);
	if (inpusel != newSel && inpusel != 0x0)
		return (ZunoErrorInvalidPin);
	if ((list = (ZunoLesenseHeader_t *)malloc(sizeof(ZunoLesenseAdc_t))) == 0)
		return (ZunoErrorMemory);
	if ((ret = this->_lesenseInit()) != ZunoErrorOk) {
		free(list);
		return (ret);
	}
	list->pin = pin;
	list->channel = ((sizeof(LESENSE->CH) / sizeof(LESENSE->CH[0x0])));
	list->next = 0x0;
	list->function = function;
	list->type = LesenseTypeAdc;
	this->_addList(list);
	LESENSE_ScanStop();
	ADC0->CMD = ADC_CMD_SCANSTOP;/* Make sure scan sequence is not in progress. */
	ADC0->SCANINPUTSEL = ADC0->SCANINPUTSEL | newSel;
	ADC0->SCANMASK = ADC0->SCANMASK | (0x1 << (possel & ADC_MASK_CHANNEL));
	LESENSE_ScanStart();
	return (ZunoErrorOk);
}

ZunoError_t LesenseClass::_adcThres(uint8_t pin, uint16_t cntThres, LESENSE_ChCompMode_TypeDef compMode) {
	ZunoLesenseHeader_t				*list;
	LESENSE_ChDesc_TypeDef			initLesenseCh;
	size_t							channel;

	list = this->_findList(pin);
	if (list == 0x0 || list->type != LesenseTypeAdc)
		return (ZunoErrorInvalidPin);
	initLesenseCh = LESENSE_CH_CONF_DEFAULT;
	initLesenseCh.enaScanCh = true;  // Enable scan channel
	initLesenseCh.enaInt = true;
	initLesenseCh.storeCntRes = false;
	initLesenseCh.sampleMode = lesenseSampleModeADC;
	initLesenseCh.intMode = lesenseSetIntLevel;
	initLesenseCh.compMode = compMode;
	initLesenseCh.evalMode = lesenseEvalModeThreshold;
	initLesenseCh.cntThres = cntThres;
	LESENSE_ScanStop();
	channel = (zme_ADC_PIN2Channel(pin) & ADC_MASK_CHANNEL);
	LESENSE_ChannelConfig(&initLesenseCh, channel);
	LESENSE->CH[channel].EVAL = LESENSE->CH[channel].EVAL | LESENSE_CH_EVAL_STRSAMPLE_DATASRC;
	list->channel = channel;
	LESENSE_ScanStart();
	return (ZunoErrorOk);
}

void LesenseClass::_adcInit(void) {
	ADC_InitScan_TypeDef			initScan;

	if ((ADC0->SCANCTRLX & ADC_SCANCTRLX_FIFOOFACT_OVERWRITE) != 0x0)
		return ;
	zmeADCInit();
	initScan = ADC_INITSCAN_DEFAULT;
	initScan.scanInputConfig.scanInputSel = 0x0;
	initScan.reference = adcRef5V;
	initScan.resolution = adcRes12Bit;
	initScan.acqTime = adcAcqTime256;
	initScan.fifoOverwrite = true;// FIFO overflow overwrites old data
	ADC_InitScan(ADC0, &initScan);
}

void LesenseClass::_LESENSE_IRQHandler(uint32_t flags) {
	uint32_t						tempos;
	uint32_t						bufdata;
	size_t							channel;
	ZunoLesenseHeader_t				*list;

	flags = flags & 0xFFFF;
	tempos = flags;
	LESENSE->IEN = LESENSE->IEN ^ flags;/* Enable/disable interrupts on channel */
	LESENSE->CHEN = LESENSE->CHEN ^ flags;/* Enable/disable scan channel chIdx. */
	while ((LESENSE_StatusGet() & LESENSE_STATUS_BUFDATAV) != 0x0) {
		bufdata = LESENSE_ScanResultDataGet();
		if ((list = LesenseClass::_findListChannel((bufdata & _LESENSE_BUFDATA_BUFDATASRC_MASK) >> _LESENSE_BUFDATA_BUFDATASRC_SHIFT)) != 0x0)
			list->value = bufdata & _LESENSE_BUFDATA_BUFDATA_MASK;
	}
	channel = 0x0;
	while (tempos != 0x0) {
		if ((tempos & 0x1) != 0x0)
			if ((list = LesenseClass::_findListChannel(channel)) == 0x0 || list->function(list->pin, list->value) == false)
				flags = flags ^ (0x1 << channel);
		tempos = tempos >> 0x1;
		channel++;
	}
	LESENSE->IEN = LESENSE->IEN | flags;/* Enable/disable interrupts on channel */
	LESENSE->CHEN = LESENSE->CHEN | flags;/* Enable/disable scan channel chIdx. */
}

ZunoError_t LesenseClass::_lesenseInit(void) {
	LESENSE_Init_TypeDef		initLesense;

	if (this->_values.count_lesense == 0x0)
	{
		if (zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_LESENCE, (void *)LesenseClass::_LESENSE_IRQHandler) != true)
			return (ZunoErrorAttachSysHandler);
		CMU_ClockEnable(cmuClock_HFLE, true);
		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
		CMU_ClockEnable(cmuClock_LESENSE, true);
		initLesense = LESENSE_INIT_DEFAULT;
		initLesense.coreCtrl.storeScanRes = true;
		initLesense.coreCtrl.debugRun = false;
		initLesense.coreCtrl.bufOverWr = true;
		LESENSE_Init(&initLesense, true);//Initialize LESENSE interface
		LESENSE_ScanFreqSet(0x0, this->_values.LesenseScanSequence_fq);
		NVIC_ClearPendingIRQ(LESENSE_IRQn);
		NVIC_EnableIRQ(LESENSE_IRQn);
		this->_values.count_lesense++;
	}
	return (ZunoErrorOk);
}

void LesenseClass::_lesenseDeInit(void) {

	if (--this->_values.count_lesense != 0x0)
		return
	NVIC_DisableIRQ(LESENSE_IRQn);
	LESENSE_Reset();
	zunoDetachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_LESENCE, (void *)LesenseClass::_LESENSE_IRQHandler);
}

void LesenseClass::_addList(ZunoLesenseHeader_t *list) {
	ZunoLesenseHeader_t		*list_next;
	ZunoLesenseHeader_t		*list_tmp;

	if ((list_next = this->_values.list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->_values.list = list;
}

void LesenseClass::_cutList(ZunoLesenseHeader_t *list) {
	ZunoLesenseHeader_t		*list_prev;
	ZunoLesenseHeader_t		*list_tmp;

	list_prev = this->_values.list;
	if (list == list_prev)
		this->_values.list = list->next;
	else {
		while ((list_tmp = list_prev->next) != list)
			list_prev = list_tmp;
		list_prev->next = list->next;
	}
}

ZunoLesenseHeader_t *LesenseClass::_findList(uint8_t pin) {
	ZunoLesenseHeader_t	*list;

	list = this->_values.list;
	while (list != 0) {
		if (list->pin == pin)
			break ;
		list = list->next;
	}
	return (list);
}

ZunoLesenseHeader_t *LesenseClass::_findListChannel(uint8_t channel) {
	ZunoLesenseHeader_t	*list;

	list = LesenseClass::_values.list;
	while (list != 0) {
		if (list->channel == channel)
			break ;
		list = list->next;
	}
	return (list);
}


/* Preinstantiate Objects */
LesenseClass Lesense;