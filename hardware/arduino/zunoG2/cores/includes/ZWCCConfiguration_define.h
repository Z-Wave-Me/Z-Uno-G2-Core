#ifndef ZWCC_CONFIGURATION_DEFINE_H
#define ZWCC_CONFIGURATION_DEFINE_H

uint32_t zunoLoadCFGParam(uint8_t param);
void zunoSaveCFGParam(uint8_t param, uint32_t value);

#define ZUNO_CFG_PARAMETER_FORMAT_SIGNED			0x0
#define ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED			0x1

#define ZUNO_CFG_PARAMETER_SIZE_8BIT				0x1
#define ZUNO_CFG_PARAMETER_SIZE_16BIT				0x2
#define ZUNO_CFG_PARAMETER_SIZE_32BIT				0x4

typedef struct						ZunoCFGParameter_s
{
	const char						*name;
	const char						*info;
	ssize_t							minValue;
	ssize_t							maxValue;
	ssize_t							defaultValue;
	uint8_t							size: 3;
	uint8_t							format: 3;
	uint8_t							readOnly: 1;
	uint8_t							altering: 1;
	uint8_t							advanced: 1;
	
}									ZunoCFGParameter_t;

#define ZUNO_CFG_PARAMETER_UNKNOWN			((const ZunoCFGParameter_t *)0)

#endif // ZWCC_CONFIGURATION_DEFINE_H