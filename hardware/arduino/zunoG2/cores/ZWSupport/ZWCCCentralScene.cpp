#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCCentralScene.h"

__WEAK const ZunoCentralSceneParameterArray_t *zunoCentralSceneGetParameterArrayUser(void) {
	static ZunoCentralSceneParameterTimer_t _central_scene_parameter_timer[0x1];
	static const ZunoCentralSceneParameterArray_t _central_scene_parameter_array =
	{
		.timer = &_central_scene_parameter_timer[0x0],
		.mask = CENTRAL_SCENE_KEY_ALL_MASK, 
		.count = ((sizeof(_central_scene_parameter_timer) / sizeof(_central_scene_parameter_timer[0x0])))
	};
	return (&_central_scene_parameter_array);
}

static uint8_t _lock_count = 0x0;
static uint8_t _slow_mode = true;

uint64_t rtcc_micros(void);

static int _central_scene_supported_report(void) {
	const ZunoCentralSceneParameterArray_t						*parametr_array;
	ZwCentralSceneSupportedReportFrame_t						*report;
	uint32_t													support_prop_mask;
	size_t														len;

	report = (ZwCentralSceneSupportedReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE; set in - fillOutgoingPacket
	// report->cmd = CENTRAL_SCENE_SUPPORTED_REPORT_V3; set in - fillOutgoingPacket
	parametr_array = zunoCentralSceneGetParameterArrayUser();
	support_prop_mask = parametr_array->mask;
	len = ((((sizeof(support_prop_mask) * 0x8) - __builtin_clz(support_prop_mask)) >> 0x3) + 0x1);
	report->supportedScenes = parametr_array->count;
	report->properties1 = CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_SLOW_REFRESH_SUPPORT_BIT_MASK_V3 | CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_IDENTICAL_BIT_MASK_V3 |((len << CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASK_BYTES_SHIFT_V3) & CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASK_BYTES_MASK_V3);
	memcpy(&report->supportedKeyAttributesForScene[0x0], (uint8_t *)&support_prop_mask, len);
	CMD_REPLY_LEN = sizeof(report[0x0]) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _central_scene_configuration_report(void) {
	ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME				*report;
	size_t														properties1;

	report = (ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE; set in - fillOutgoingPacket
	// report->cmd = CENTRAL_SCENE_CONFIGURATION_REPORT_V3; set in - fillOutgoingPacket
	if (_slow_mode == true)
		properties1 = CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3;
	else
		properties1 = 0x0;
	report->properties1 = properties1;
	CMD_REPLY_LEN = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _central_scene_configuration_set(const ZW_CENTRAL_SCENE_CONFIGURATION_SET_V3_FRAME *frame) {
	size_t														properties1;
	size_t														slow_mode;

	properties1 = frame->properties1;
	if ((properties1 & CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3) != 0x0)
		slow_mode = true;
	else
		slow_mode = false;
	_slow_mode  = slow_mode;
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCCentralSceneHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case CENTRAL_SCENE_CONFIGURATION_SET_V3:
			rs = _central_scene_configuration_set((const ZW_CENTRAL_SCENE_CONFIGURATION_SET_V3_FRAME *)&cmd->cmd[0x0]);
			break ;
		case CENTRAL_SCENE_CONFIGURATION_GET_V3:
			rs = _central_scene_configuration_report();
			break ;
		case CENTRAL_SCENE_SUPPORTED_GET_V3:
			rs = _central_scene_supported_report();
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

static void _lock(ZunoCentralSceneParameterTimer_t *timer, uint64_t ms) {
	
	uint64_t								ms_old;

	ms_old = timer->ms;
	if (ms == 0x0) {
		if (ms_old != 0x0) {
			if (--_lock_count == 0x0)
				g_sleep_data.latch--;
		}
	}
	else {
		if (ms_old == 0x0) {
			if (_lock_count++ == 0x0)
				g_sleep_data.latch++;
		}
	}
	timer->ms = ms;
}

void zuno_CCCentralSceneTimer(void) {
	const ZunoCentralSceneParameterArray_t						*parametr_array;
	uint64_t													ms;
	uint64_t													ms_old;
	ZunoCentralSceneParameterTimer_t							*timer_b;
	ZunoCentralSceneParameterTimer_t							*timer_e;

	if (_lock_count == 0x0)
		return ;
	parametr_array = zunoCentralSceneGetParameterArrayUser();
	timer_b = &parametr_array->timer[0x0];
	timer_e = &parametr_array->timer[parametr_array->count];
	ms = (rtcc_micros() / 1000);
	zunoEnterCritical();
	while (timer_b < timer_e) {
		ms_old = timer_b->ms;
		if (ms_old != 0 && ms_old <= ms)
			zuno_CCCentralSceneReport(timer_b - &parametr_array->timer[0x0] + 0x1, CENTRAL_SCENE_KEY_HELD_DOWN);
		timer_b++;
	}
	zunoExitCritical();
}

void zuno_CCCentralSceneReport(uint8_t sceneNumber, uint8_t event) {
	static uint8_t												sequenceNumber = 0x0;
	const ZunoCentralSceneParameterArray_t						*parametr_array;
	ZW_CENTRAL_SCENE_NOTIFICATION_V3_FRAME						*report;
	size_t														properties1;
	uint64_t													ms;

	parametr_array = zunoCentralSceneGetParameterArrayUser();
	if ((parametr_array->mask & (0x1 << event)) == 0x0)
		return ;
	if (sceneNumber > parametr_array->count || sceneNumber == 0x0)
		return ;
	switch (event) {
		case CENTRAL_SCENE_KEY_PRESSED_1:
		case CENTRAL_SCENE_KEY_PRESSED_2:
		case CENTRAL_SCENE_KEY_PRESSED_3:
		case CENTRAL_SCENE_KEY_PRESSED_4:
		case CENTRAL_SCENE_KEY_PRESSED_5:
		case CENTRAL_SCENE_KEY_RELEASED:
			zunoEnterCritical();
			_lock(&parametr_array->timer[sceneNumber- 0x1], 0x0);
			zunoExitCritical();
			break ;
		case CENTRAL_SCENE_KEY_HELD_DOWN:
			if (_slow_mode == true)
				ms = CENTRAL_SCENE_UPDATE_MS_SLOW;
			else
				ms = CENTRAL_SCENE_UPDATE_MS_FAST;
			ms = ms + (rtcc_micros() / 1000);
			zunoEnterCritical();
			_lock(&parametr_array->timer[sceneNumber- 0x1], ms);
			zunoExitCritical();
			break ;
		default:
			return ;
			break ;
	}
	fillOutgoingReportPacket(0x0);
	report = (ZW_CENTRAL_SCENE_NOTIFICATION_V3_FRAME *)&CMD_REPORT_CC;
	report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE;
	report->cmd = CENTRAL_SCENE_NOTIFICATION;
	report->sequenceNumber = sequenceNumber++;
	if (_slow_mode == true)
		properties1 = CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3;
	else
		properties1 = 0x0;
	report->properties1 = properties1 | event;
	report->sceneNumber = sceneNumber;
	CMD_REPORT_LEN = sizeof(report[0x0]);
	zunoSendZWPackage(&g_outgoing_report_packet);
}