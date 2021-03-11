#ifndef ZWCC_CONFIGURATION_DEFINE_H
#define ZWCC_CONFIGURATION_DEFINE_H

uint32_t zunoLoadCFGParam(uint8_t param);
void zunoSaveCFGParam(uint8_t param, uint32_t value);

typedef enum						ZunoCFGParameterFormat_e
{
	ZunoCFGParameterFormatSigned = 0,
	ZunoCFGParameterFormatUnsigned
}									ZunoCFGParameterFormat_t;

typedef enum						ZunoCFGParameterSize_e
{
	ZunoCFGParameterSize8bit = 1,
	ZunoCFGParameterSize16bit = 2,
	ZunoCFGParameterSize32bit = 4
}									ZunoCFGParameterSize_t;

typedef struct						ZunoCFGParameter_s
{
	const char						*name;
	const char						*info;
	ssize_t							minValue;
	ssize_t							maxValue;
	ssize_t							defaultValue;
	ZunoCFGParameterFormat_t		format;
	ZunoCFGParameterSize_t			size;
}									ZunoCFGParameter_t;

#define ZUNO_CFG_PARAMETER_UNKNOWN			((const ZunoCFGParameter_t *)0)
#define ZUNO_CFG_PARAMETER_DEFAULT			((const ZunoCFGParameter_t *)1)

#endif // ZWCC_CONFIGURATION_DEFINE_H