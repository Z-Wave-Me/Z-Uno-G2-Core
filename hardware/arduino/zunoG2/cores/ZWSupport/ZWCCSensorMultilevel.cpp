#include "Arduino.h"
#include "ZWCCSensorMultilevel.h"

#ifdef WITH_CC_SENSOR_MULTILEVEL

static uint8_t _get_sensor_type(uint8_t channel) {
	return (ZUNO_CFG_CHANNEL(channel).sub_type);
}

int zuno_CCSensorMultilevelReport(byte channel, ZUNOCommandPacket_t *packet) {
	ZwSensorMultilevelReportFrame_t					*report;
	size_t											channel_size;
	size_t											value;

	channel_size = ZUNO_CFG_CHANNEL(channel).params[0];
	uint8_t sz = channel_size & SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK;
	report = (ZwSensorMultilevelReportFrame_t *)&packet->packet.cmd[0x0];
	packet->packet.len = sz + sizeof(report[0x0]);
	report->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL;
	report->cmd = SENSOR_MULTILEVEL_REPORT;
	report->sensorType = _get_sensor_type(channel);
	report->level = channel_size;
	value = zuno_universalGetter1P(channel);
	_zme_memcpy(&report->sensorValue[0], (uint8_t *)&value, sz);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_scale(ZwSensorMultilevelSupportedGetScaleFrame_t *cmd, size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwSensorMultilevelSupportedScaleReportFrame_t				*report;
	size_t														sensorType;
	size_t														properties1;
	size_t														i;

	report = (ZwSensorMultilevelSupportedScaleReportFrame_t *)frame_report->info.packet.cmd;
	report->cmd = SENSOR_MULTILEVEL_SUPPORTED_SCALE_REPORT;
	sensorType = cmd->sensorType;
	// report->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL; set in - fillOutgoingPacket
	// report->cmd = SENSOR_MULTILEVEL_SUPPORTED_SCALE_REPORT; set in - fillOutgoingPacket
	report->sensorType = sensorType;
	properties1 = 0x0;
	if (ZUNO_CFG_CHANNEL(channel).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER) {
		if (_get_sensor_type(channel) == sensorType)
			properties1 = 1 << ((ZUNO_CFG_CHANNEL(channel).params[0] & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) >> SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT);
	}
	else {
		i = 0x0;
		while (i < ZUNO_CFG_CHANNEL_COUNT) {
			if (ZUNO_CFG_CHANNEL(i).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER && _get_sensor_type(i) == sensorType) {
				properties1 = 1 << ((ZUNO_CFG_CHANNEL(i).params[0] & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) >> SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT);
				break ;
			}
			i++;
		}
	}

	report->properties1 = properties1;
	frame_report->info.packet.len = sizeof(ZwSensorMultilevelSupportedScaleReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_sensor(const ZUNOCommandCmd_t *pack, size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwSensorMultilevelSupportedSensorReportFrame_t		*report;
	size_t												i;

	report = (ZwSensorMultilevelSupportedSensorReportFrame_t *)frame_report->info.packet.cmd;
	memset(&report->bitMask[0], 0, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);// clear reply bit mask
	// report->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL; set in - fillOutgoingPacket
	// report->cmd = SENSOR_MULTILEVEL_SUPPORTED_SENSOR_REPORT; set in - fillOutgoingPacket
	if(pack->dst_zw_channel == 0) {// In case it's a 0 channel mapping we have to declare all the types.
		for (i = 0; i < ZUNO_CFG_CHANNEL_COUNT; i++){
			if (ZUNO_CFG_CHANNEL(i).type != ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER)
				continue;
			if ((ZUNO_CFG_CHANNEL(i).zw_channel & 0x80) || (ZUNO_CFG_CHANNEL(i).zw_channel == 0))
				zunoSetupBitMask(&report->bitMask[0], _get_sensor_type(i) - 1, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);// bit index starts from 0
		}
	}
	else// If we use multichannel => just one bit in one mask bit index starts from 0
		zunoSetupBitMask(&report->bitMask[0], _get_sensor_type(channel) - 1, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);
	frame_report->info.packet.len = sizeof(ZwSensorMultilevelSupportedSensorReportFrame_t) + SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _sensor_multilevel_get(size_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	const ZwSensorMultilevelGetV11Frame_t			*paket;
	size_t											i;
	size_t											sensorType;

	_zunoMarkChannelRequested(channel);
	paket = (const ZwSensorMultilevelGetV11Frame_t *)cmd->cmd;
	if (cmd->len != sizeof(ZwSensorMultilevelGetV4Frame_t))
		sensorType = paket->sensorType;
	else
		sensorType = (size_t)-1;
	if (ZUNO_CFG_CHANNEL(channel).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER)
		return (zuno_CCSensorMultilevelReport(channel, &frame_report->info));
	i = 0x0;
	while (i < ZUNO_CFG_CHANNEL_COUNT) {
		if (ZUNO_CFG_CHANNEL(i).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER) {
			channel = i;
			if (_get_sensor_type(i) == sensorType)
				return (zuno_CCSensorMultilevelReport(i, &frame_report->info));
		}
		i++;
	}
	return (zuno_CCSensorMultilevelReport(channel, &frame_report->info));
}

int zuno_CCSensorMultilevelHandler(byte channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int							rs;

	switch (ZW_CMD) {
		case SENSOR_MULTILEVEL_GET:
			rs = _sensor_multilevel_get(channel, cmd, frame_report);
			break;
		case SENSOR_MULTILEVEL_SUPPORTED_GET_SENSOR:
			rs = _supported_sensor(cmd, channel, frame_report);
			break;
		case SENSOR_MULTILEVEL_SUPPORTED_GET_SCALE:
			rs = _supported_scale((ZwSensorMultilevelSupportedGetScaleFrame_t *)cmd->cmd,channel, frame_report);
			break;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}

#include "ZWCCZWavePlusInfo.h"

#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_TEMPERATURE                             0x0D01   //Sensor Multilevel Device Type (Sensor type Air Temperature)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_GENERAL_PURPOSE_VALUE                       0x0D02   //Sensor Multilevel Device Type (Sensor type General Purpose Value)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LUMINANCE                                   0x0D03   //Sensor Multilevel Device Type (Sensor type Luminance)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_POWER                                       0x0D04   //Sensor Multilevel Device Type (Sensor type Power)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_HUMIDITY                                    0x0D05   //Sensor Multilevel Device Type (Sensor type Humidity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VELOCITY                                    0x0D06   //Sensor Multilevel Device Type (Sensor type Velocity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DIRECTION                                   0x0D07   //Sensor Multilevel Device Type (Sensor type Direction)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ATMOSPHERIC_PRESSURE                        0x0D08   //Sensor Multilevel Device Type (Sensor type Atmospheric Pressure)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BAROMETRIC_PRESSURE                         0x0D09   //Sensor Multilevel Device Type (Sensor type Barometric Pressure)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOLOR_RADIATION                             0x0D0A   //Sensor Multilevel Device Type (Sensor type Solar Radiation)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DEW_POINT                                   0x0D0B   //Sensor Multilevel Device Type (Sensor type Dew Point)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RAIN_RATE                                   0x0D0C   //Sensor Multilevel Device Type (Sensor type Rain Rate)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIDE_LEVEL                                  0x0D0D   //Sensor Multilevel Device Type (Sensor type Tide Level)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WEIGHT                                      0x0D0E   //Sensor Multilevel Device Type (Sensor type Weight)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VOLTAGE                                     0x0D0F   //Sensor Multilevel Device Type (Sensor type Voltage)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CURRENT                                     0x0D10   //Sensor Multilevel Device Type (Sensor type Current)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CO2_LEVEL                                   0x0D11   //Sensor Multilevel Device Type (Sensor type CO2 Level)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_FLOW                                    0x0D12   //Sensor Multilevel Device Type (Sensor type Air Flow)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TANK_CAPACITY                               0x0D13   //Sensor Multilevel Device Type (Sensor type Tank Capacity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DISTANCE                                    0x0D14   //Sensor Multilevel Device Type (Sensor type Distance)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ANGLE_POSITION                              0x0D15   //Sensor Multilevel Device Type (Sensor type Angle Position)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ROTATION                                    0x0D16   //Sensor Multilevel Device Type (Sensor type Rotation)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_TEMPERATURE                           0x0D17   //Sensor Multilevel Device Type (Sensor type Water Temperature)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOIL_TEMPERATURE                            0x0D18   //Sensor Multilevel Device Type (Sensor type Soil Temperature)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_INTENSITY                           0x0D19   //Sensor Multilevel Device Type (Sensor type Seismic Intensity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_MAGNITUDE                           0x0D1A   //Sensor Multilevel Device Type (Sensor type Seismic Magnitude)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ULTRAVIOLET                                 0x0D1B   //Sensor Multilevel Device Type (Sensor type Ultraviolet)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_RESISTIVITY                      0x0D1C   //Sensor Multilevel Device Type (Sensor type Electrical Resistivity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_CONDUCTIVITY                     0x0D1D   //Sensor Multilevel Device Type (Sensor type Electrical Conductivity)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LOUDNESS                                    0x0D1E   //Sensor Multilevel Device Type (Sensor type Loudness)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MOISTURE                                    0x0D1F   //Sensor Multilevel Device Type (Sensor type Moisture)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_FREQUENCY                                   0x0D20   //Sensor Multilevel Device Type (Sensor type Frequency)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIME                                        0x0D21   //Sensor Multilevel Device Type (Sensor type Time )
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TARGET_TEMPERATURE                          0x0D22   //Sensor Multilevel Device Type (Sensor type Target Temperature)
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_PARTICULATE_MATTER_2_5                      0x0D23
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_FORMALDEHYDE_CH2O_LEVEL                     0x0D24
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RADON_CONCENTRATION                         0x0D25
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_METHANE_DENSITY                             0x0D26
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VOLATILE_ORGANIC_COMPOUND_LEVEL             0x0D27
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CARBON_MONOXIDE_LEVEL                       0x0D28
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOIL_HUMIDITY                               0x0D29
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOIL_REACTIVITY                             0x0D2A
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOIL_SALINITY                               0x0D2B
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_HEART_RATE                                  0x0D2C
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BLOOD_PRESSURE                              0x0D2D
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MUSCLE_MASS                                 0x0D2E
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_FAT_MASS                                    0x0D2F
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BONE_MASS                                   0x0D30
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TOTAL_BODY_WATER                            0x0D31
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BASIS_METABOLIC_RATE                        0x0D32
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BODY_MASS_INDEX                             0x0D33
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ACCELERATION_X_AXIS                         0x0D34
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ACCELERATION_Y_AXIS                         0x0D35
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ACCELERATION_Z_AXIS                         0x0D36
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SMOKE_DENSITY                               0x0D37
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_FLOW                                  0x0D38
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_DENSITY                               0x0D39
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RF_SIGNAL_STRENGTH                          0x0D3A
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_PARTICULATE_MATTER_10                       0x0D3B
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RESPIRATORY_RATE                            0x0D3C
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RELATIVE_MODULATION_LEVEL                   0x0D3D
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BOILER_WATER_TEMPERATURE                    0x0D3E
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DOMESTIC_HOT_WATER_TEMPERATURE              0x0D3F
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_OUTSIDE_TEMPERATURE                         0x0D40
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_EXHAUST_TEMPERATURE                         0x0D41
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_CHLORINE_LEVEL                        0x0D42
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_ACIDITY                               0x0D43
#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_OXIDATION_REDUCTION_POTENTIAL         0x0D44

#define ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LAST                                        ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_OXIDATION_REDUCTION_POTENTIAL



void zuno_CCSensorMultilevelGetIcon(uint8_t channel, ZwZwavePlusInfoIcon_t *icon) {
	uint8_t							sensorType;
	uint16_t						icon_type;

	sensorType = _get_sensor_type(channel);
	icon_type = ICON_TYPE_GENERIC_SENSOR_MULTILEVEL;
	if (sensorType <= (ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LAST - ICON_TYPE_GENERIC_SENSOR_MULTILEVEL))
		icon_type = icon_type + sensorType;
	icon->installerIconType = icon_type;
	icon->userIconType = icon_type;
}

#include "ZWCCAssociation.h"

void zuno_CCSensorMultilevelGetProfile(uint8_t channel, ZwAssociationInfoOut_t *agi) {
	agi->profile1 = COMMAND_CLASS_SENSOR_MULTILEVEL;
	agi->profile2 = _get_sensor_type(channel);
}

#endif // WITH_CC_SENSOR_MULTILEVEL

	// switch (sensorType) {
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_TEMPERATURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_GENERAL_PURPOSE_VALUE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_GENERAL_PURPOSE_VALUE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_LUMINANCE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LUMINANCE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_POWER:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_POWER;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_RELATIVE_HUMIDITY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_HUMIDITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_VELOCITY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VELOCITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_DIRECTION:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DIRECTION;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_ATMOSPHERIC_PRESSURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ATMOSPHERIC_PRESSURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_BAROMETRIC_PRESSURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BAROMETRIC_PRESSURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_SOLAR_RADIATION:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOLOR_RADIATION;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_DEW_POINT:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DEW_POINT;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_RAIN_RATE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RAIN_RATE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_TIDE_LEVEL:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIDE_LEVEL;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_WEIGHT:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WEIGHT;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_VOLTAGE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VOLTAGE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_CURRENT:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CURRENT;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_CO2_LEVEL:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CO2_LEVEL;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_AIR_FLOW:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_AIR_FLOW;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_TANK_CAPACITY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TANK_CAPACITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_DISTANCE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DISTANCE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_ANGLE_POSITION:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ANGLE_POSITION;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_ROTATION:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ROTATION;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_WATER_TEMPERATURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_TEMPERATURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_SOIL_TEMPERATURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SOIL_TEMPERATURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_SEISMIC_INTENSITY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_INTENSITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_SEISMIC_MAGNITUDE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_SEISMIC_MAGNITUDE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_ULTRAVIOLET:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ULTRAVIOLET;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_ELECTRICAL_RESISTIVITY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_RESISTIVITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_ELECTRICAL_CONDUCTIVITY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_ELECTRICAL_CONDUCTIVITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_LOUDNESS:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_LOUDNESS;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_MOISTURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_MOISTURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_FREQUENCY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_FREQUENCY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_TIME:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TIME;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_TARGET_TEMPERATURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_TARGET_TEMPERATURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_PARTICULATE_MATTER_2_5:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_PARTICULATE_MATTER_2_5;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_FORMALDEHYDE_CH2O_LEVEL:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_FORMALDEHYDE_CH2O_LEVEL;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_RADON_CONCENTRATION:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RADON_CONCENTRATION;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_METHANE_DENSITY_CH4:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_METHANE_DENSITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_VOLATILE_ORGANIC_COMPOUND:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_VOLATILE_ORGANIC_COMPOUND_LEVEL;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_CARBON_MONOXIDE_CO:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_CARBON_MONOXIDE_LEVEL;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_WATER_FLOW:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_FLOW;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_WATER_DENSITY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_DENSITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_RF_SIGNAL_STRENGTH:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RF_SIGNAL_STRENGTH;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_PARTICULATE_MATTER_10:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_PARTICULATE_MATTER_10;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_RESPIRATORY_RATE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RESPIRATORY_RATE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_RELATIVE_MODULATION_LEVEL:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_RELATIVE_MODULATION_LEVEL;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_BOILER_WATER_TEMPERATURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_BOILER_WATER_TEMPERATURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_DOMESTIC_HOT_WATER_TEMPERATURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_DOMESTIC_HOT_WATER_TEMPERATURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_OUTSIDE_TEMPERATURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_OUTSIDE_TEMPERATURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_EXHAUST_TEMPERATURE:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_EXHAUST_TEMPERATURE;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_WATER_CHLORINE_LEVEL:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_CHLORINE_LEVEL;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_WATER_ACIDITY:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_ACIDITY;
	// 		break ;
	// 	case ZUNO_SENSOR_MULTILEVEL_TYPE_WATER_OXIDATION_REDUCTION_POTENTIAL:
	// 		icon_type = ICON_TYPE_SPECIFIC_SENSOR_MULTILEVEL_WATER_OXIDATION_REDUCTION_POTENTIAL;
	// 		break ;
	// 	default:
	// 		icon_type = ICON_TYPE_GENERIC_SENSOR_MULTILEVEL;
	// 		break ;
	// }