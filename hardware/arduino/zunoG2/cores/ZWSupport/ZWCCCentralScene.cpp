#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCCentralScene.h"

__WEAK const ZunoCentralSceneParameterArray_t *zunoCentralSceneGetParameterArrayUser(size_t channel) {
	return (0x0);
	(void)channel;
}

static uint64_t _mask_channel = 0x0;
uint64_t rtcc_micros(void);

static const ZunoCentralSceneParameterArray_t *_central_scene_GetParameterArray(size_t channel) {
	static ZunoCentralSceneParameterTimer_t _central_scene_parameter_timer[0x1];
	static const ZunoCentralSceneParameterArray_t _central_scene_parameter_array =
	{
		.timer = &_central_scene_parameter_timer[0x0],
		.mask = CENTRAL_SCENE_KEY_ALL_MASK, 
		.count = ((sizeof(_central_scene_parameter_timer) / sizeof(_central_scene_parameter_timer[0x0])))
	};
	const ZunoCentralSceneParameterArray_t							*out;

	if ((out = zunoCentralSceneGetParameterArrayUser(channel + 0x1)) != 0x0)
		return (out);
	return (&_central_scene_parameter_array);
}

static int _central_scene_supported_report(size_t channel) {
	const ZunoCentralSceneParameterArray_t						*parametr_array;
	ZwCentralSceneSupportedReportFrame_t						*report;
	uint32_t													support_prop_mask;
	size_t														len;

	report = (ZwCentralSceneSupportedReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE; set in - fillOutgoingPacket
	// report->cmd = CENTRAL_SCENE_SUPPORTED_REPORT_V3; set in - fillOutgoingPacket
	parametr_array = _central_scene_GetParameterArray(channel);
	support_prop_mask = parametr_array->mask;
	len = ((((sizeof(support_prop_mask) * 0x8) - __builtin_clz(support_prop_mask)) >> 0x3) + 0x1);
	report->supportedScenes = parametr_array->count;
	report->properties1 = CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_SLOW_REFRESH_SUPPORT_BIT_MASK_V3 | CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_IDENTICAL_BIT_MASK_V3 |((len << CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASK_BYTES_SHIFT_V3) & CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASK_BYTES_MASK_V3);
	memcpy(&report->supportedKeyAttributesForScene[0x0], (uint8_t *)&support_prop_mask, len);
	CMD_REPLY_LEN = sizeof(report[0x0]) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _central_scene_configuration_report(size_t channel) {
	ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME				*report;
	size_t														properties1;

	report = (ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE; set in - fillOutgoingPacket
	// report->cmd = CENTRAL_SCENE_CONFIGURATION_REPORT_V3; set in - fillOutgoingPacket
	if (CENTRAL_SCENE_FAST_REFRESH(channel) == false)
		properties1 = CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3;
	else
		properties1 = 0x0;
	report->properties1 = properties1;
	CMD_REPLY_LEN = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _central_scene_configuration_set(size_t channel, const ZW_CENTRAL_SCENE_CONFIGURATION_SET_V3_FRAME *frame) {
	size_t														properties1;

	properties1 = frame->properties1;
	if ((properties1 & CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3) == 0x0)
		CENTRAL_SCENE_FAST_REFRESH(channel) = true;
	else
		CENTRAL_SCENE_FAST_REFRESH(channel) = false;
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCCentralSceneHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case CENTRAL_SCENE_CONFIGURATION_SET_V3:
			rs = _central_scene_configuration_set(channel, (const ZW_CENTRAL_SCENE_CONFIGURATION_SET_V3_FRAME *)&cmd->cmd[0x0]);
			break ;
		case CENTRAL_SCENE_CONFIGURATION_GET_V3:
			rs = _central_scene_configuration_report(channel);
			break ;
		case CENTRAL_SCENE_SUPPORTED_GET_V3:
			rs = _central_scene_supported_report(channel);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

static void _lock(ZunoCentralSceneParameterTimer_t *timer, uint8_t channel, uint64_t ms) {
	uint64_t								ms_old;

	ms_old = timer->ms;
	if (ms == 0x0) {
		if (ms_old != 0x0) {
			CENTRAL_SCENE_COUNT(channel)--;
			if (CENTRAL_SCENE_COUNT(channel) == 0x0)
				_mask_channel = _mask_channel ^ (0x1 << channel);
			g_sleep_data.latch--;
		}
	}
	else {
		if (ms_old == 0x0) {
			CENTRAL_SCENE_COUNT(channel)++;
			g_sleep_data.latch++;
			_mask_channel = _mask_channel | (0x1 << channel);
		}
	}
	timer->ms = ms;
}

void zuno_CCCentralSceneTimer(void) {
	const ZunoCentralSceneParameterArray_t						*parametr_array;
	size_t														channel;
	uint64_t													mask;
	uint64_t													ms;
	uint64_t													ms_old;
	ZunoCentralSceneParameterTimer_t							*timer_b;
	ZunoCentralSceneParameterTimer_t							*timer_e;

	channel = 0x0;
	mask = _mask_channel;
	if (mask == 0x0)
		return ;
	ms = (rtcc_micros() / 1000);
	while (mask != 0x0) {
		if ((mask & 0x1) != 0x0) {
			parametr_array = _central_scene_GetParameterArray(channel);
			timer_b = &parametr_array->timer[0x0];
			timer_e = &parametr_array->timer[parametr_array->count];
			zunoEnterCritical();
			while (timer_b < timer_e) {
				ms_old = timer_b->ms;
				if (ms_old != 0 && ms_old <= ms)
					zuno_CCCentralSceneReport(channel + 0x1, timer_b - &parametr_array->timer[0x0] + 0x1, CENTRAL_SCENE_KEY_HELD_DOWN);
				timer_b++;
			}
			zunoExitCritical();
		}
		mask = mask >> 0x1;
		channel++;
	}
}
extern uint8_t             g_outgoing_report_data[MAX_ZW_PACKAGE];

void zuno_CCCentralSceneReport(uint8_t channel, uint8_t sceneNumber, uint8_t event) {
	static uint8_t												sequenceNumber = 0x0;
	const ZunoCentralSceneParameterArray_t						*parametr_array;
	ZW_CENTRAL_SCENE_NOTIFICATION_V3_FRAME						*report;
	size_t														properties1;
	uint64_t													ms;

	channel--;
	if (ZUNO_CFG_CHANNEL(channel).type != ZUNO_CENTRAL_SCENE_CHANNEL_NUMBER)
		return ;
	parametr_array = _central_scene_GetParameterArray(channel);
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
			_lock(&parametr_array->timer[sceneNumber- 0x1], channel, 0x0);
			zunoExitCritical();
			break ;
		case CENTRAL_SCENE_KEY_HELD_DOWN:
			if (CENTRAL_SCENE_FAST_REFRESH(channel) == false)
				ms = CENTRAL_SCENE_UPDATE_MS_SLOW;
			else
				ms = CENTRAL_SCENE_UPDATE_MS_FAST;
			ms = ms + (rtcc_micros() / 1000);
			zunoEnterCritical();
			_lock(&parametr_array->timer[sceneNumber- 0x1], channel, ms);
			zunoExitCritical();
			break ;
		default:
			return ;
			break ;
	}
	fillOutgoingRawPacket(&g_outgoing_report_packet, g_outgoing_report_data, channel, 0, ZUNO_LIFELINE_GRP);
	// fillOutgoingReportPacket(ZUNO_CFG_CHANNEL(channel).zw_channel);
	report = (ZW_CENTRAL_SCENE_NOTIFICATION_V3_FRAME *)&CMD_REPORT_CC;
	report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE;
	report->cmd = CENTRAL_SCENE_NOTIFICATION;
	report->sequenceNumber = sequenceNumber++;
	if (CENTRAL_SCENE_FAST_REFRESH(channel) == false)
		properties1 = CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3;
	else
		properties1 = 0x0;
	report->properties1 = properties1 | event;
	report->sceneNumber = sceneNumber;
	CMD_REPORT_LEN = sizeof(report[0x0]);
	zunoSendZWPackage(&g_outgoing_report_packet);
}