#include "Arduino.h"
#include "ZUNO_Neptun.h"

#define MY_SERIAL Serial0

uint8_t bAlarmLine1 = false;
uint8_t bAlarmLine2 = false;
uint8_t bAlarmLine3 = false;
uint8_t bAlarmLine4 = false;

enum
{
	INDEX_SWITCH_BINARY1 = 1,
	INDEX_SWITCH_BINARY2,
	INDEX_ZUNO_SENSOR_BINARY1,
	INDEX_ZUNO_SENSOR_BINARY2,
	INDEX_ZUNO_SENSOR_BINARY3,
	INDEX_ZUNO_SENSOR_BINARY4,
	INDEX_ZUNO_METER_TYPE_WATER1,
	INDEX_ZUNO_METER_TYPE_WATER2,
	INDEX_ZUNO_METER_TYPE_WATER3,
	INDEX_ZUNO_METER_TYPE_WATER4
};

ZUNO_SETUP_CHANNELS(
	ZUNO_SWITCH_BINARY(getterTaps1, setterTaps1),
	ZUNO_SWITCH_BINARY(getterTaps2, setterTaps2),
	ZUNO_SENSOR_BINARY(ZUNO_SENSOR_BINARY_TYPE_WATER, bAlarmLine1),
	ZUNO_SENSOR_BINARY(ZUNO_SENSOR_BINARY_TYPE_WATER, bAlarmLine2),
	ZUNO_SENSOR_BINARY(ZUNO_SENSOR_BINARY_TYPE_WATER, bAlarmLine3),
	ZUNO_SENSOR_BINARY(ZUNO_SENSOR_BINARY_TYPE_WATER, bAlarmLine4),
	ZUNO_METER(ZUNO_METER_TYPE_WATER, METER_RESET_DISABLE, ZUNO_METER_WATER_SCALE_METERS3, METER_SIZE_FOUR_BYTES, METER_PRECISION_ZERO_DECIMALS, ft_get_water1, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_WATER, METER_RESET_DISABLE, ZUNO_METER_WATER_SCALE_METERS3, METER_SIZE_FOUR_BYTES, METER_PRECISION_ZERO_DECIMALS, ft_get_water2, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_WATER, METER_RESET_DISABLE, ZUNO_METER_WATER_SCALE_METERS3, METER_SIZE_FOUR_BYTES, METER_PRECISION_ZERO_DECIMALS, ft_get_water3, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_WATER, METER_RESET_DISABLE, ZUNO_METER_WATER_SCALE_METERS3, METER_SIZE_FOUR_BYTES, METER_PRECISION_ZERO_DECIMALS, ft_get_water4, ft_empty)
);

NeptunClass gNeptun;

uint8_t bTapsStatusGroup1 = true;
uint8_t bTapsStatusGroup2 = true;
uint8_t bTapsStatusGroup1Old = bTapsStatusGroup1;
uint8_t bTapsStatusGroup2Old = bTapsStatusGroup2;

uint32_t water1 = 0;
uint32_t water2 = 0;
uint32_t water3 = 0;
uint32_t water4 = 0;

// the setup function runs once, when you press reset or power the board
void setup() {

	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Setup");
	gNeptun.begin();

	// Предварительная настройка если нужно
	// NeptunStatusDev_t					status;
	// NeptunConfigLine1And2_t				value1;
	// NeptunConfigLine3And4_t				value2;
	// status.value = 0;
	// status.bGrouping = true;
	// status.bTapsStatusGroup1 = bTapsStatusGroup1;
	// status.bTapsStatusGroup2 = bTapsStatusGroup2;
	// status.bFloorCleaning = false;
	// status.bStartConnectionSensorsWireless = false;
	// status.bTapsClosingWhenLossSensors = true;
	// status.bKeypadLocks = false;
	// gNeptun.devSetStatus(status);
	// value1.bLineControl1 = NeptunSensorsGroopFirst;
	// value1.bLineControl2 = NeptunSensorsGroopFirst;
	// gNeptun.devSetConfigLine1And2(value1);
	// value2.bLineControl3 = NeptunSensorsGroopSecond;
	// value2.bLineControl4 = NeptunSensorsGroopSecond;
	// gNeptun.devSetConfigLine3And4(value2);

}


void	_change(void) {
	NeptunStatusDev_t					status;
	NeptunStatusDev_t					status_cmp;
	NeptunConfigLine_t					status_line;
	uint32_t							value;

	status = gNeptun.devGetStatus();
	if (status.status == ZunoErrorOk) {
		status_cmp = status;
		if (bTapsStatusGroup1 != bTapsStatusGroup1Old) {
			status.bTapsStatusGroup1 = bTapsStatusGroup1;
			bTapsStatusGroup1Old = bTapsStatusGroup1;
		}
		else if (bTapsStatusGroup1 != status.bTapsStatusGroup1) {
			bTapsStatusGroup1 = status.bTapsStatusGroup1;
			zunoSendReport(INDEX_SWITCH_BINARY1);
		}
		if (bTapsStatusGroup2 != bTapsStatusGroup2Old) {
			status.bTapsStatusGroup2 = bTapsStatusGroup2;
			bTapsStatusGroup2Old = bTapsStatusGroup2;
		}
		else if (bTapsStatusGroup2 != status.bTapsStatusGroup2) {
			bTapsStatusGroup2 = status.bTapsStatusGroup2;
			zunoSendReport(INDEX_SWITCH_BINARY2);
		}
		if (status_cmp.raw != status.raw)
			gNeptun.devSetStatus(status);
		
	}
	status_line = gNeptun.devGetStatusLine();
	if (status_line.status == ZunoErrorOk) {
		if (bAlarmLine1 != status_line.bLine1)
		{
			bAlarmLine1 = status_line.bLine1;
			zunoSendReport(INDEX_ZUNO_SENSOR_BINARY1);
		}
		if (bAlarmLine2 != status_line.bLine2)
		{
			bAlarmLine2 = status_line.bLine2;
			zunoSendReport(INDEX_ZUNO_SENSOR_BINARY2);
		}
		if (bAlarmLine3 != status_line.bLine3)
		{
			bAlarmLine3 = status_line.bLine3;
			zunoSendReport(INDEX_ZUNO_SENSOR_BINARY3);
		}
		if (bAlarmLine4 != status_line.bLine4)
		{
			bAlarmLine4 = status_line.bLine4;
			zunoSendReport(INDEX_ZUNO_SENSOR_BINARY4);
		}
	}
	if (gNeptun.devGetMeter(NeptunConfigMeterIdOne, NeptunConfigMeterSlotOne, &value) == ZunoErrorOk && value != water1) {
		water1 = value;
		zunoSendReport(INDEX_ZUNO_METER_TYPE_WATER1);
	}
	if (gNeptun.devGetMeter(NeptunConfigMeterIdTwo, NeptunConfigMeterSlotOne, &value) == ZunoErrorOk && value != water2) {
		water2 = value;
		zunoSendReport(INDEX_ZUNO_METER_TYPE_WATER2);
	}
	if (gNeptun.devGetMeter(NeptunConfigMeterIdOne, NeptunConfigMeterSlotTwo, &value) == ZunoErrorOk && value != water3) {
		water3 = value;
		zunoSendReport(INDEX_ZUNO_METER_TYPE_WATER3);
	}
	if (gNeptun.devGetMeter(NeptunConfigMeterIdTwo, NeptunConfigMeterSlotTwo, &value) == ZunoErrorOk && value != water4) {
		water4 = value;
		zunoSendReport(INDEX_ZUNO_METER_TYPE_WATER4);
	}
}

// the loop function runs over and over again forever
void loop() {
	_change();
	delay(500);
}


void	setterTaps1(byte value)
{
	bTapsStatusGroup1 = value;
}

byte	getterTaps1(void)
{
	return (bTapsStatusGroup1);
}

byte	getterTaps2(void)
{
	return (bTapsStatusGroup2);
}


void	setterTaps2(byte value)
{
	bTapsStatusGroup2 = value;
}

void	ft_empty(byte value)
{
	(void)value;
}

dword	ft_get_water1(void)
{
	return (water1);
}

dword	ft_get_water2(void)
{
	return (water2);
}

dword	ft_get_water3(void)
{
	return (water3);
}

dword	ft_get_water4(void)
{
	return (water4);
}