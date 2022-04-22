#ifndef ZUNO_ERROR_H
#define ZUNO_ERROR_H

typedef uint32_t ZUNO_ERROR_TYPE;

#define ZUNO_ERROR_TYPE_SYSTEM											0x0
#define ZUNO_ERROR_TYPE_SPI_FLASH										0x1
#define ZUNO_ERROR_TYPE_USER											0xFFF

#define ZUNO_ERROR_CONSTRUCTOR_USER(VALUE)								((ZUNO_ERROR_TYPE)(((ZUNO_ERROR_TYPE_USER & 0x3FFF) << 11) | (VALUE & 0xFFF)))
#define ZUNO_ERROR_CONSTRUCTOR_SYSTEM(TYPE, VALUE)						((ZUNO_ERROR_TYPE)(((TYPE & 0xFFF) << 11) | (VALUE & 0xFFF)))


/* The operation completed successfully. */
#define ZUNO_ERROR_SUCCESS										(ZUNO_ERROR_CONSTRUCTOR_SYSTEM(ZUNO_ERROR_TYPE_SYSTEM, 0x0))



#define ZUNO_ERROR_SYSTEM_TMP_FOR_REPLACE								0xFFFFFFFF

#endif//ZUNO_ERROR_H
