#ifndef GENERAL_PURPOSE_H
#define GENERAL_PURPOSE_H

typedef enum
{
	ZUNO_GPT_BASIC
} ZunoGeneralPurposeTimerType_t;

// GPT constants
#define ZUNO_GPT_CYCLIC				0x1
#define ZUNO_GPT_IMWRITE			0x2
#define ZUNO_GPT_SCALE1024			0x4

void zunoGPTDeInit(void);
void zunoGPTInit(uint8_t flags);
ZunoError_t zunoGPTEnable(uint8_t bEnable);
void zunoGPTSet(uint16_t interval);

#endif // GENERAL_PURPOSE_H