#ifndef ZPRINTF_DISPLAY_H
#define ZPRINTF_DISPLAY_H

uint8_t *Zprintf_display_unknown(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
uint8_t *Zprintf_display_c(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
uint8_t *Zprintf_display_s(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
uint8_t *Zprintf_display_n(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
uint8_t *Zprintf_display_x(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
uint8_t *Zprintf_display_p(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
uint8_t *Zprintf_display_o(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
uint8_t *Zprintf_display_d(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);
uint8_t *Zprintf_display_u(FtPrintf_t *array, uint8_t *b, uint8_t *e, uint32_t flags);

#endif//ZPRINTF_DISPLAY_H