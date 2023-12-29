#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCCentralScene.h"
#include "LinkedList.h"

#if defined(WITH_CC_CENTRAL_SCENE)

#if (CENTRAL_SCENE_KEY_ALL_MASK) > 0xFF
#error "ENTRAL_SCENE range"
#else
#define CENTRAL_SCENE_KEY_ATR_LEN				1
#define CENTRAL_SCENE_KEY_ATR_MAX_COUNT			((ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwCentralSceneSupportedReportFrame_t)) / CENTRAL_SCENE_KEY_ATR_LEN)

typedef struct								ZunoCentralSceneParameterList_s
{
	uint64_t								ms;
	uint32_t								uuid;
	uint32_t								mask;
}											ZunoCentralSceneParameterList_t;

#endif

// ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT

static ZNLinkedList_t *_central_scene = NULL;

static bool _zuno_CCCentralSceneAdd(uint32_t uuid, uint32_t mask) {
	ZunoCentralSceneParameterList_t						*parameter;
	uint32_t											test_mask;
	const ZNLinkedList_t								*linked_list;
	const ZunoCentralSceneParameterList_t				*parameter_list;
	size_t												count;

	if ((mask & CENTRAL_SCENE_KEY_ALL_MASK) != mask)
		return (false);
	test_mask = mask & (CENTRAL_SCENE_KEY_HELD_DOWN_MASK | CENTRAL_SCENE_KEY_RELEASED_MASK);
	if (test_mask != 0x0 && test_mask != (CENTRAL_SCENE_KEY_HELD_DOWN_MASK | CENTRAL_SCENE_KEY_RELEASED_MASK))
		return (false);
	linked_list = _central_scene;
	count = 0x0;
	while (linked_list != NULL) {
		parameter_list = (const ZunoCentralSceneParameterList_t *)linked_list->data;
		if (parameter_list->uuid == uuid)
			break ;
		count++;
		linked_list = linked_list->next;
	}
	if (linked_list != NULL)
		return (false);
	if (count > (CENTRAL_SCENE_KEY_ATR_MAX_COUNT))
		return (false);
	if ((parameter = (ZunoCentralSceneParameterList_t *)malloc(sizeof(parameter[0x0]))) == NULL)
		return (false);
	parameter->ms = 0x0;
	parameter->uuid = uuid;
	parameter->mask = mask;
	if (znllPushBack(&_central_scene, parameter) == false) {
		free(parameter);
		return (false);
	}
	return (true);
}

bool zuno_CCCentralSceneAdd(uint32_t uuid, uint32_t mask) {
	bool									out;

	zunoEnterCritical();
	out = _zuno_CCCentralSceneAdd(uuid, mask);
	zunoExitCritical();
	return (out);
}

static uint8_t _lock_count = 0x0;
static uint8_t _slow_mode = true;

uint64_t rtcc_micros(void);

static int _central_scene_supported_report(ZUNOCommandPacketReport_t *frame_report) {
	ZwCentralSceneSupportedReportFrame_t						*report;
	const ZNLinkedList_t										*linked_list;
	const ZunoCentralSceneParameterList_t						*parameter_list;
	size_t														i;

	report = (ZwCentralSceneSupportedReportFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE; set in - fillOutgoingPacket
	// report->cmd = CENTRAL_SCENE_SUPPORTED_REPORT_V3; set in - fillOutgoingPacket
	zunoEnterCritical();
	i = 0x0;
	linked_list = _central_scene;
	while (linked_list != NULL) {
		parameter_list = (const ZunoCentralSceneParameterList_t *)linked_list->data;
		memcpy(&report->supportedKeyAttributesForScene[i * CENTRAL_SCENE_KEY_ATR_LEN], (uint8_t *)&parameter_list->mask, CENTRAL_SCENE_KEY_ATR_LEN);
		i++;
		linked_list = linked_list->next;
	}
	zunoExitCritical();
	report->supportedScenes = i;
	report->properties1 = CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_SLOW_REFRESH_SUPPORT_BIT_MASK_V3 |((CENTRAL_SCENE_KEY_ATR_LEN << CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASK_BYTES_SHIFT_V3) & CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASK_BYTES_MASK_V3);
	frame_report->packet.len = sizeof(report[0x0]) + (i * CENTRAL_SCENE_KEY_ATR_LEN);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _central_scene_configuration_report(ZUNOCommandPacketReport_t *frame_report) {
	ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME				*report;
	size_t														properties1;

	report = (ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE; set in - fillOutgoingPacket
	// report->cmd = CENTRAL_SCENE_CONFIGURATION_REPORT_V3; set in - fillOutgoingPacket
	if (_slow_mode == true)
		properties1 = CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3;
	else
		properties1 = 0x0;
	report->properties1 = properties1;
	frame_report->packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _zunoCentralSceneSaveSet(bool slow_mode);
static int _central_scene_configuration_set(const ZW_CENTRAL_SCENE_CONFIGURATION_SET_V3_FRAME *frame) {
	size_t														properties1;
	size_t														slow_mode;

	properties1 = frame->properties1;
	if ((properties1 & CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3) != 0x0)
		slow_mode = true;
	else
		slow_mode = false;
	_zunoCentralSceneSaveSet(slow_mode);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCCentralSceneHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
		case CENTRAL_SCENE_CONFIGURATION_SET_V3:
			rs = _central_scene_configuration_set((const ZW_CENTRAL_SCENE_CONFIGURATION_SET_V3_FRAME *)&cmd->cmd[0x0]);
			break ;
		case CENTRAL_SCENE_CONFIGURATION_GET_V3:
			rs = _central_scene_configuration_report(frame_report);
			break ;
		case CENTRAL_SCENE_SUPPORTED_GET_V3:
			rs = _central_scene_supported_report(frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

static void _lock(ZunoCentralSceneParameterList_t *parameter_list, uint64_t ms) {
	
	uint64_t								ms_old;

	ms_old = parameter_list->ms;
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
	parameter_list->ms = ms;
}

static void _zuno_CCCentralSceneReport_held_down(ZunoCentralSceneParameterList_t *parameter_list, uint8_t sceneNumber);

void zuno_CCCentralSceneTimer(void) {
	const ZNLinkedList_t								*linked_list;
	ZunoCentralSceneParameterList_t						*parameter_list;
	size_t												sceneNumber;
	uint64_t											ms;
	uint64_t											ms_old;

	if (_lock_count == 0x0)
		return ;
	ms = (rtcc_micros() / 1000);
	zunoEnterCritical();
	sceneNumber = 0x1;
	linked_list = _central_scene;
	while (linked_list != NULL) {
		parameter_list = (ZunoCentralSceneParameterList_t *)linked_list->data;
		ms_old = parameter_list->ms;
		if (ms_old != 0 && ms_old <= ms)
			_zuno_CCCentralSceneReport_held_down(parameter_list, sceneNumber);
		sceneNumber++;
		linked_list = linked_list->next;
	}
	zunoExitCritical();
}

static void _CCCentralSceneReport_common(uint8_t event, ZunoCentralSceneParameterList_t *parameter_list, uint64_t ms, uint8_t sceneNumber) {
	static uint8_t												sequenceNumber = 0x0;
	ZW_CENTRAL_SCENE_NOTIFICATION_V3_FRAME						*report;
	size_t														properties1;
	ZUNOCommandPacketReport_t									frame;

	_lock(parameter_list, ms);
	fillOutgoingReportPacketAsync(&frame, 0x0);
	report = (ZW_CENTRAL_SCENE_NOTIFICATION_V3_FRAME *)&frame.packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_CENTRAL_SCENE;
	report->cmd = CENTRAL_SCENE_NOTIFICATION;
	report->sequenceNumber = sequenceNumber++;
	properties1 = (_slow_mode) ? CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3 : 0;
	report->properties1 = properties1 | event;
	report->sceneNumber = sceneNumber;
	frame.packet.len = sizeof(report[0x0]);
	zunoSendZWPackage(&frame.packet);
}

static void _zuno_CCCentralSceneReport_held_down(ZunoCentralSceneParameterList_t *parameter_list, uint8_t sceneNumber) {
	uint64_t									ms;

	if (_slow_mode == true)
		ms = CENTRAL_SCENE_UPDATE_MS_SLOW;
	else
		ms = CENTRAL_SCENE_UPDATE_MS_FAST;
	ms = ms + (rtcc_micros() / 1000);
	_CCCentralSceneReport_common(CENTRAL_SCENE_KEY_HELD_DOWN, parameter_list, ms, sceneNumber);
}

static bool _zuno_CCCentralSceneReport(uint32_t uuid, uint8_t event) {
	const ZNLinkedList_t								*linked_list;
	ZunoCentralSceneParameterList_t						*parameter_list;
	size_t												sceneNumber;

	switch (event) {
		case CENTRAL_SCENE_KEY_PRESSED_1:
		case CENTRAL_SCENE_KEY_PRESSED_2:
		case CENTRAL_SCENE_KEY_PRESSED_3:
		case CENTRAL_SCENE_KEY_PRESSED_4:
		case CENTRAL_SCENE_KEY_PRESSED_5:
		case CENTRAL_SCENE_KEY_RELEASED:
		case CENTRAL_SCENE_KEY_HELD_DOWN:
			break ;
		default:
			return (false);
			break ;
	}
	sceneNumber = 0x1;
	linked_list = _central_scene;
	while (linked_list != NULL) {
		parameter_list = (ZunoCentralSceneParameterList_t *)linked_list->data;
		if (parameter_list->uuid == uuid)
			break ;
		sceneNumber++;
		linked_list = linked_list->next;
	}
	if (linked_list == NULL)
		return (false);
	if ((parameter_list->mask & (0x1 << event)) == 0x0)
		return (false);
	switch (event) {
		case CENTRAL_SCENE_KEY_PRESSED_1:
		case CENTRAL_SCENE_KEY_PRESSED_2:
		case CENTRAL_SCENE_KEY_PRESSED_3:
		case CENTRAL_SCENE_KEY_PRESSED_4:
		case CENTRAL_SCENE_KEY_PRESSED_5:
		case CENTRAL_SCENE_KEY_RELEASED:
			_CCCentralSceneReport_common(event, parameter_list, 0x0, sceneNumber);
			break ;
		case CENTRAL_SCENE_KEY_HELD_DOWN:
			_zuno_CCCentralSceneReport_held_down(parameter_list, sceneNumber);
			break ;
		default:
			break ;
	}
	return (true);
}

bool zuno_CCCentralSceneReport(uint32_t uuid, uint8_t event) {
	bool									out;

	zunoEnterCritical();
	out = _zuno_CCCentralSceneReport(uuid, event);
	zunoExitCritical();
	return (out);
}

void zuno_CCCentralSceneRemoveAll(void) {
	void												*data;

	while (true) {
		data = znllRemove(&_central_scene, 0x0);
		if (data == NULL)
			break;
		free(data);
	}
}

typedef struct								ZunoCentralSceneConfig_s
{
	bool									slow_mode;
}											ZunoCentralSceneConfig_t;

static void _zunoCentralSceneSaveSet(bool slow_mode) {
	uint8_t								buffer[EEPROM_CENTRAL_SCENE_SAVE_SIZE];
	ZunoCentralSceneConfig_t			*config;

	config = (ZunoCentralSceneConfig_t *)&buffer[0x0];
	config->slow_mode = slow_mode;
	_slow_mode = slow_mode;
	zunoEEPROMWrite(EEPROM_CENTRAL_SCENE_SAVE_ADDR, EEPROM_CENTRAL_SCENE_SAVE_SIZE, &buffer[0x0]);
}

void zunoCentralSceneSaveInit(void) {
	_zunoCentralSceneSaveSet(true);
}

void zunoCentralSceneSaveLoad(void) {
	uint8_t								buffer[EEPROM_CENTRAL_SCENE_SAVE_SIZE];
	ZunoCentralSceneConfig_t			*config;

	zunoEEPROMRead(EEPROM_CENTRAL_SCENE_SAVE_ADDR, EEPROM_CENTRAL_SCENE_SAVE_SIZE, &buffer[0x0]);
	config = (ZunoCentralSceneConfig_t *)&buffer[0x0];
	_slow_mode = config->slow_mode;
}
#endif//WITH_CC_CENTRAL_SCENE