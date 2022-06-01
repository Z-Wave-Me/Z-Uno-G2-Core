#ifndef ZWCC_CENTRAL_SCENE_H
#define ZWCC_CENTRAL_SCENE_H

#include "ZWSupport.h"

#define CENTRAL_SCENE_VERSION															CENTRAL_SCENE_VERSION_V3
#define CENTRAL_SCENE_NOTIFICATION														CENTRAL_SCENE_NOTIFICATION_V3
#define CENTRAL_SCENE_CONFIGURATION_SET													CENTRAL_SCENE_CONFIGURATION_SET_V3

#define CENTRAL_SCENE_KEY_PRESSED_1														0x0
#define CENTRAL_SCENE_KEY_PRESSED_1_MASK												(0x1 << CENTRAL_SCENE_KEY_PRESSED_1)
#define CENTRAL_SCENE_KEY_RELEASED														0x1
#define CENTRAL_SCENE_KEY_RELEASED_MASK													(0x1 << CENTRAL_SCENE_KEY_RELEASED)
#define CENTRAL_SCENE_KEY_HELD_DOWN														0x2
#define CENTRAL_SCENE_KEY_HELD_DOWN_MASK												(0x1 << CENTRAL_SCENE_KEY_HELD_DOWN)
#define CENTRAL_SCENE_KEY_PRESSED_2														0x3
#define CENTRAL_SCENE_KEY_PRESSED_2_MASK												(0x1 << CENTRAL_SCENE_KEY_PRESSED_2)
#define CENTRAL_SCENE_KEY_PRESSED_3														0x4
#define CENTRAL_SCENE_KEY_PRESSED_3_MASK												(0x1 << CENTRAL_SCENE_KEY_PRESSED_3)
#define CENTRAL_SCENE_KEY_PRESSED_4														0x5
#define CENTRAL_SCENE_KEY_PRESSED_4_MASK												(0x1 << CENTRAL_SCENE_KEY_PRESSED_4)
#define CENTRAL_SCENE_KEY_PRESSED_5														0x6
#define CENTRAL_SCENE_KEY_PRESSED_5_MASK												(0x1 << CENTRAL_SCENE_KEY_PRESSED_5)
#define CENTRAL_SCENE_KEY_ALL_MASK														(CENTRAL_SCENE_KEY_PRESSED_1_MASK | CENTRAL_SCENE_KEY_RELEASED_MASK | CENTRAL_SCENE_KEY_HELD_DOWN_MASK | CENTRAL_SCENE_KEY_PRESSED_2_MASK | CENTRAL_SCENE_KEY_PRESSED_3_MASK | CENTRAL_SCENE_KEY_PRESSED_4_MASK | CENTRAL_SCENE_KEY_PRESSED_5_MASK)

#define CENTRAL_SCENE_UPDATE_MS_SLOW					55000
#define CENTRAL_SCENE_UPDATE_MS_FAST					200

/* Central Scene command class commands */
#define CENTRAL_SCENE_VERSION_V3                                                         0x03
#define CENTRAL_SCENE_SUPPORTED_GET_V3                                                   0x01
#define CENTRAL_SCENE_SUPPORTED_REPORT_V3                                                0x02
#define CENTRAL_SCENE_NOTIFICATION_V3                                                    0x03
#define CENTRAL_SCENE_CONFIGURATION_SET_V3                                               0x04
#define CENTRAL_SCENE_CONFIGURATION_GET_V3                                               0x05
#define CENTRAL_SCENE_CONFIGURATION_REPORT_V3                                            0x06
/* Values used for Central Scene Supported Report command */
#define CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_IDENTICAL_BIT_MASK_V3                 0x01
#define CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASK_BYTES_MASK_V3      0x06
#define CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASK_BYTES_SHIFT_V3     0x01
#define CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_RESERVED_MASK_V3                      0x78
#define CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_RESERVED_SHIFT_V3                     0x03
#define CENTRAL_SCENE_SUPPORTED_REPORT_PROPERTIES1_SLOW_REFRESH_SUPPORT_BIT_MASK_V3      0x80
/* Values used for Central Scene Notification command */
#define CENTRAL_SCENE_NOTIFICATION_PROPERTIES1_KEY_ATTRIBUTES_MASK_V3                    0x07
#define CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_1_TIME_V3                  0x00
#define CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V3                        0x01
#define CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V3                       0x02
#define CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_2_TIMES_V3                 0x03
#define CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_3_TIMES_V3                 0x04
#define CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_4_TIMES_V3                 0x05
#define CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_5_TIMES_V3                 0x06
#define CENTRAL_SCENE_NOTIFICATION_PROPERTIES1_RESERVED_MASK_V3                          0x78
#define CENTRAL_SCENE_NOTIFICATION_PROPERTIES1_RESERVED_SHIFT_V3                         0x03
#define CENTRAL_SCENE_NOTIFICATION_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3                  0x80
/* Values used for Central Scene Configuration Set command */
#define CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_RESERVED_MASK_V3                     0x7F
#define CENTRAL_SCENE_CONFIGURATION_SET_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3             0x80
/* Values used for Central Scene Configuration Report command */
#define CENTRAL_SCENE_CONFIGURATION_REPORT_PROPERTIES1_RESERVED_MASK_V3                  0x7F
#define CENTRAL_SCENE_CONFIGURATION_REPORT_PROPERTIES1_SLOW_REFRESH_BIT_MASK_V3          0x80

/************************************************************/
/* Central Scene Notification V3 command class structs */   
/************************************************************/
typedef struct _ZW_CENTRAL_SCENE_NOTIFICATION_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   sequenceNumber;               /**/
    uint8_t   properties1;                  /* masked byte */
    uint8_t   sceneNumber;                  /**/
} ZW_CENTRAL_SCENE_NOTIFICATION_V3_FRAME;


/************************************************************/
/* Central Scene Configuration Set V3 command class structs */
/************************************************************/
typedef struct _ZW_CENTRAL_SCENE_CONFIGURATION_SET_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
} ZW_CENTRAL_SCENE_CONFIGURATION_SET_V3_FRAME;


/************************************************************/
/* Central Scene Configuration Report V3 command class structs */
/************************************************************/
typedef struct _ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
} ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME;

/************************************************************/
/* Central Scene Supported Report V3 command class structs */
/************************************************************/
typedef struct									ZwCentralSceneSupportedReportFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										supportedScenes;/**/
	uint8_t										properties1;/* masked byte */
	uint8_t										supportedKeyAttributesForScene[];/**/
}												ZwCentralSceneSupportedReportFrame_t;

typedef struct						ZunoCentralSceneParameter_s
{
	const char						*name;
}									ZunoCentralSceneParameter_t;

typedef struct						ZunoCentralSceneParameterTimer_s
{
	uint64_t						ms;
}									ZunoCentralSceneParameterTimer_t;

typedef struct								ZunoCentralSceneParameterArray_s
{
	ZunoCentralSceneParameterTimer_t		*timer;
	uint8_t									mask;
	uint8_t									count;
}											ZunoCentralSceneParameterArray_t;

const ZunoCentralSceneParameterArray_t *zunoCentralSceneGetParameterArray(size_t channel);

#define ZUNO_SETUP_CENTRAL_SCENE(MASK, ...) 	\
	const ZunoCentralSceneParameterArray_t *zunoCentralSceneGetParameterArrayUser(void) {					\
		static const ZunoCentralSceneParameter_t _central_scene_parameter[]= \
		{ \
			__VA_ARGS__, \
		};\
		static ZunoCentralSceneParameterTimer_t _central_scene_parameter_timer[((sizeof(_central_scene_parameter) / sizeof(_central_scene_parameter[0x0])))]; \
		static const ZunoCentralSceneParameterArray_t _central_scene_parameter_array = \
		{ \
			.timer = &_central_scene_parameter_timer[0x0],									\
			.mask = MASK, \
			.count = ((sizeof(_central_scene_parameter) / sizeof(_central_scene_parameter[0x0])))			\
		};\
		return (&_central_scene_parameter_array);					\
	}					\


#define ZUNO_SETUP_CENTRAL_SCENE_SET()	\
{\
	.name = 0x0\
}\


int zuno_CCCentralSceneHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);
void zuno_CCCentralSceneReport(uint8_t sceneNumber, uint8_t event);

#endif// ZWCC_CENTRAL_SCENE_H