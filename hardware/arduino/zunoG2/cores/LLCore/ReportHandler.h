#ifndef ZWCC_REPORT_HANDLER_H
#define ZWCC_REPORT_HANDLER_H

#include "ZWCCBasic.h"
#include "ZWCCSwitchBinary.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSensorMultilevel.h"
#include "ZWCCMeter.h"
#include "ZWCCNotification.h"
#include "ZWCCBattery.h"

typedef struct						ReportAuxData_s
{
	uint8_t							nodeIdSource;
	uint8_t							channelSource;
	uint8_t							cmdClass;
	uint8_t							*rawReportData;
}									ReportAuxData_t;

typedef struct						ReportAuxDataAdd_s
{
	ReportAuxData_t					main;
	float							value;
}									ReportAuxDataAdd_t;

typedef enum
{
	Basic = COMMAND_CLASS_BASIC,
	SwitchBinary = COMMAND_CLASS_SWITCH_BINARY,
	SwitchMultilevel = COMMAND_CLASS_SWITCH_MULTILEVEL,
	SensorBinary = COMMAND_CLASS_SENSOR_MULTILEVEL,
	SensorMultilevel = COMMAND_CLASS_SENSOR_MULTILEVEL,
	Meter = COMMAND_CLASS_METER,
	Notification = COMMAND_CLASS_NOTIFICATION,
	Battery = COMMAND_CLASS_BATTERY
} ZunoReportHandlerType_t;

typedef void zuno_user_zuno_handler_report(ReportAuxData_t *);

static inline void zunoSetReportHandler(ZunoReportHandlerType_t type, void(*handler)(ReportAuxData_t *report_data)) {
	zunoAttachSysHandler(ZUNO_HANDLER_REPORT, type, (void *)handler);
}

void zunoReportHandler(ZUNOCommandPacket_t *cmd);

//#undef ZUNO_REPORTS_HANDLER
//#define ZUNO_REPORTS_HANDLER(reportType, reportHandler)		zunoSetReportHandler(reportType, reportHandler)

#define REPORT_NODE_ID(report_data)							(((ReportAuxData_t *)report_data)->nodeIdSource)

#define REPORT_BASIC_VALUE(report_data)						(((ZwBasicReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v1.value)

#define REPORT_SWITCH_BINARY_VALUE(report_data)				(((ZwBasicBinaryReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v1.value)

#define REPORT_SWITCH_MULTILEVEL_VALUE(report_data)			(((SwitchMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v1.value)

#define REPORT_SENSOR_BINARY_VALUE(report_data)				((void)0)
#define REPORT_SENSOR_BINARY_TYPE(report_data)				((void)0)

#define REPORT_SENSOR_MULTILEVEL_TYPE(report_data)			(((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte1.sensorType)
#define REPORT_SENSOR_MULTILEVEL_SIZE(report_data)			(((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte1.level & SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK)
#define REPORT_SENSOR_MULTILEVEL_SCALE(report_data)			((((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte1.level & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) >> SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT)
#define REPORT_SENSOR_MULTILEVEL_PRECISION(report_data)		((((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte1.level) >> SENSOR_MULTILEVEL_PROPERTIES_PRECISION_SHIFT)
#define REPORT_SENSOR_MULTILEVEL_VALUE_1B(report_data)		(((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte1.sensorValue1)
#define REPORT_SENSOR_MULTILEVEL_VALUE_2B(report_data)		((uint16_t)(((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte2.sensorValue1 << 0x8) | ((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte2.sensorValue2)
#define REPORT_SENSOR_MULTILEVEL_VALUE_4B(report_data)		((uint32_t)((((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.sensorValue1 << 0x18) | (((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.sensorValue2 << 0x10) | (((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.sensorValue3 << 0x8) | ((ZwSensorMultilevelReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.sensorValue4))

#define REPORT_METER_TYPE(report_data)						(((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte1.properties1 & METER_PROPERTIES_TYPE_MASK)
#define REPORT_METER_SIZE(report_data)						(((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte1.properties2 & METER_PROPERTIES_SIZE_MASK)
#define REPORT_METER_SCALE(report_data)						((((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte1.properties1 & METER_PROPERTIES_SCALE_MSB_MASK) >> METER_PROPERTIES_SCALE_MSB_SHIFT | (((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte1.properties2 & METER_PROPERTIES_SCALE_LSB_MASK) >> METER_PROPERTIES_SCALE_LSB_SHIFT)
#define REPORT_METER_PRECISION(report_data)					(((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte1.properties2 >> METER_PROPERTIES_PRECISION_SHIFT)
#define REPORT_METER_VALUE_1B(report_data)					(((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte1.meterValue1)
#define REPORT_METER_VALUE_2B(report_data)					((uint16_t)(((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte2.meterValue1 << 0x8) | ((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte2.meterValue2)
#define REPORT_METER_VALUE_4B(report_data)					((uint32_t)((((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte4.meterValue1 << 0x18) | (((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte4.meterValue2 << 0x10) | (((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte4.meterValue3 << 0x8) | ((ZwMeterReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->v2.byte4.meterValue4))

#define REPORT_NOTIFICATION_STATUS(report_data)				(((ZwNotificationReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.notificationStatus)
#define REPORT_NOTIFICATION_TYPE(report_data)				(((ZwNotificationReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.notificationType)
#define REPORT_NOTIFICATION_EVENT(report_data)				(((ZwNotificationReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.mevent)
#define REPORT_NOTIFICATION_PARAM_LENGTH(report_data)		(((ZwNotificationReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.properties1 & NOTIFICATION_PROPERTIES_PARAMLENGTH_MASK)
#define REPORT_NOTIFICATION_EVENT_PARAM(report_data, N)		(((uint8_t *)&(((ZwNotificationReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->byte4.eventParameter1))[N])

#define REPORT_BATTERY_VALUE(report_data)					(((ZwBatteryReportFrame_t *)((ReportAuxData_t *)report_data)->rawReportData)->batteryLevel)

#endif // ZWCC_REPORT_HANDLER_H