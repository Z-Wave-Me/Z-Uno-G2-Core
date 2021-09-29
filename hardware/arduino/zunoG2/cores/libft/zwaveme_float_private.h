#ifndef ZWAVEME_FLOAT_PRIVATE_H
#define ZWAVEME_FLOAT_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif


/* Float */
typedef struct					LibftFloatValue_s
{
	union
	{
		float					value;
		uint32_t				uvalue;
	};
}								LibftFloatValue_t;

#define LIBFT_FLOAT_ENGINE_PRESC				(FLT_DIG + 1)//7

typedef enum			LibftFloatType_s
{
	LibftFloatTypeInf,
	LibftFloatTypeNan,
	LibftFloatTypeNull,
	LibftFloatTypeNumber
}						LibftFloatType_t;

typedef struct			LibftFloatEngine_s
{
	size_t				lenSingle;
	size_t				lenSingleNull;
	size_t				lenFraction;
	size_t				lenFractionNull;
	size_t				neg;
	uint8_t				number[LIBFT_FLOAT_ENGINE_PRESC + 1];//+1 - null
}						LibftFloatEngine_t;

#define LIBFT_FLOAT_NAN				(0x7F820000)
#define LIBFT_FLOAT_OVF(neg)		(neg << 31)
#define LIBFT_FLOAT_INF(neg)		(neg << 31 | 0x7F800000)

#ifdef __cplusplus
}
#endif

#endif//ZWAVEME_FLOAT_PRIVATE_H