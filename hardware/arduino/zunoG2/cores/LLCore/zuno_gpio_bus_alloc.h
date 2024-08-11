#ifndef ZUNO_GPIO_BUS_ALLOC_H
#define ZUNO_GPIO_BUS_ALLOC_H

#if defined(_SILICON_LABS_32B_SERIES_2)
#include <stdint.h>

typedef enum							ZunoGpioBus_e
{
	ZunoGpioBusAdc0,
	ZunoGpioBusVdac0Ch0,
	ZunoGpioBusVdac0Ch1,
	ZunoGpioBusUnknown,
}										ZunoGpioBus_t;

bool zme_gpio_bus_alloc(uint8_t pin, ZunoGpioBus_t type);
bool zme_gpio_bus_free(uint8_t pin, ZunoGpioBus_t type);
#endif

#endif//ZUNO_GPIO_BUS_ALLOC_H