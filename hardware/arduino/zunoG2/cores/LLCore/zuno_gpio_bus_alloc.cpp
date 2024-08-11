#include "Arduino.h"
#include "zuno_gpio_bus_alloc.h"
#include "Threading.h"

#if defined(_SILICON_LABS_32B_SERIES_2)

#define ZME_GPIO_BUSALLOC_EVEN0_SHIFT				0
#define ZME_GPIO_BUSALLOC_EVEN1_SHIFT				8
#define ZME_GPIO_BUSALLOC_ODD0_SHIFT				16
#define ZME_GPIO_BUSALLOC_ODD1_SHIFT				24

#define ZME_GPIO_BUSALLOC_REAL_TYPE_MASK			0xF
#define ZME_GPIO_BUSALLOC_REAL_TYPE_ADC0			0x1
#define ZME_GPIO_BUSALLOC_REAL_TYPE_VDAC0_CH0		0x4
#define ZME_GPIO_BUSALLOC_REAL_TYPE_VDAC0_CH1		0x4

static_assert(ZME_GPIO_BUSALLOC_EVEN0_SHIFT == _GPIO_ABUSALLOC_AEVEN0_SHIFT, "GPIO_AEVEN0 - Faled!!!");
static_assert(ZME_GPIO_BUSALLOC_EVEN0_SHIFT == _GPIO_BBUSALLOC_BEVEN0_SHIFT, "GPIO_BEVEN0 - Faled!!!");
static_assert(ZME_GPIO_BUSALLOC_EVEN0_SHIFT == _GPIO_CDBUSALLOC_CDEVEN0_SHIFT, "GPIO_CDEVEN0 - Faled!!!");

static_assert(ZME_GPIO_BUSALLOC_EVEN1_SHIFT == _GPIO_ABUSALLOC_AEVEN1_SHIFT, "GPIO_AEVEN1 - Faled!!!");
static_assert(ZME_GPIO_BUSALLOC_EVEN1_SHIFT == _GPIO_BBUSALLOC_BEVEN1_SHIFT, "GPIO_BEVEN1 - Faled!!!");
static_assert(ZME_GPIO_BUSALLOC_EVEN1_SHIFT == _GPIO_CDBUSALLOC_CDEVEN1_SHIFT, "GPIO_CDEVEN1 - Faled!!!");

static_assert(ZME_GPIO_BUSALLOC_ODD0_SHIFT == _GPIO_ABUSALLOC_AODD0_SHIFT, "GPIO_AODD0 - Faled!!!");
static_assert(ZME_GPIO_BUSALLOC_ODD0_SHIFT == _GPIO_BBUSALLOC_BODD0_SHIFT, "GPIO_BODD0 - Faled!!!");
static_assert(ZME_GPIO_BUSALLOC_ODD0_SHIFT == _GPIO_CDBUSALLOC_CDODD0_SHIFT, "GPIO_CDODD0 - Faled!!!");

static_assert(ZME_GPIO_BUSALLOC_ODD1_SHIFT == _GPIO_ABUSALLOC_AODD1_SHIFT, "GPIO_AODD1 - Faled!!!");
static_assert(ZME_GPIO_BUSALLOC_ODD1_SHIFT == _GPIO_BBUSALLOC_BODD1_SHIFT, "GPIO_BODD1 - Faled!!!");
static_assert(ZME_GPIO_BUSALLOC_ODD1_SHIFT == _GPIO_CDBUSALLOC_CDODD1_SHIFT, "GPIO_CDODD1 - Faled!!!");



static bool _gpioAllocBus(volatile uint32_t *bus, const uint8_t *shift, uint8_t lenght, bool alloc, uint8_t real_type) {
	uint8_t											i;
	volatile uint32_t								bus_loc;
	uint32_t										value;

	i = 0x0;
	bus_loc = bus[0x0];
	while (i < lenght) {
		value = (bus_loc >> shift[i]) & ZME_GPIO_BUSALLOC_REAL_TYPE_MASK;
		if (value == real_type) {
			if (alloc == true)
				return (true);
			bus[0x0] = bus_loc & (~(ZME_GPIO_BUSALLOC_REAL_TYPE_MASK << shift[i]));
			return (true);
		}
		if (value == 0x0 && alloc == true) {
			bus[0x0] = bus_loc | (real_type << shift[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool _gpioAllocBusAdc0(volatile uint32_t *bus_loc, const uint8_t *shift, uint8_t lenght, bool alloc) {
	return (_gpioAllocBus(bus_loc, shift, lenght, alloc, ZME_GPIO_BUSALLOC_REAL_TYPE_ADC0));
}

static bool _gpioAllocBusVdac0Ch0(volatile uint32_t *bus_loc, const uint8_t *shift, uint8_t lenght, bool alloc) {
	return (_gpioAllocBus(bus_loc, shift, lenght, alloc, ZME_GPIO_BUSALLOC_REAL_TYPE_VDAC0_CH0));
}

static bool _gpioAllocBusVdac0Ch1(volatile uint32_t *bus_loc, const uint8_t *shift, uint8_t lenght, bool alloc) {
	return (_gpioAllocBus(bus_loc, shift, lenght, alloc, ZME_GPIO_BUSALLOC_REAL_TYPE_VDAC0_CH1));
}

static bool _zme_gpio_bus_alloc(uint8_t pin, ZunoGpioBus_t type, bool alloc) {
	static const uint8_t				shift_adc0_even[] = {ZME_GPIO_BUSALLOC_EVEN0_SHIFT, ZME_GPIO_BUSALLOC_EVEN1_SHIFT};
	static const uint8_t				shift_adc0_oddo[] = {ZME_GPIO_BUSALLOC_ODD0_SHIFT, ZME_GPIO_BUSALLOC_ODD1_SHIFT};
	static const uint8_t				shift_vdac0_ch0_even[] = {ZME_GPIO_BUSALLOC_EVEN0_SHIFT};
	static const uint8_t				shift_vdac0_ch1_even[] = {ZME_GPIO_BUSALLOC_EVEN1_SHIFT};
	static const uint8_t				shift_vdac0_ch0_oddo[] = {ZME_GPIO_BUSALLOC_ODD0_SHIFT};
	static const uint8_t				shift_vdac0_ch1_oddo[] = {ZME_GPIO_BUSALLOC_ODD1_SHIFT};
	uint8_t								real_port;
	uint8_t								real_pin;
	volatile uint32_t					*bus_loc;

	real_port = getRealPort(pin);
	switch (real_port) {
		case gpioPortA:
			bus_loc = &GPIO->ABUSALLOC;
			break ;
		case gpioPortB:
			bus_loc = &GPIO->BBUSALLOC;
			break ;
		case gpioPortC:
		case gpioPortD:
			bus_loc = &GPIO->CDBUSALLOC;
			break ;
		default:
			return (false);
			break ;
	}
	real_pin = getRealPin(pin);
	switch (type) {
		case ZunoGpioBusAdc0:
			if ((real_pin & 0x1) == 0x0)
				return (_gpioAllocBusAdc0(bus_loc, &shift_adc0_even[0x0], (sizeof(shift_adc0_even) / sizeof(shift_adc0_even[0x0])), alloc));
			return (_gpioAllocBusAdc0(bus_loc, &shift_adc0_oddo[0x0], (sizeof(shift_adc0_oddo) / sizeof(shift_adc0_oddo[0x0])), alloc));
			break ;
		case ZunoGpioBusVdac0Ch0:
			if ((real_pin & 0x1) == 0x0)
				return (_gpioAllocBusVdac0Ch0(bus_loc, &shift_vdac0_ch0_even[0x0], (sizeof(shift_vdac0_ch0_even) / sizeof(shift_vdac0_ch0_even[0x0])), alloc));
			return (_gpioAllocBusVdac0Ch0(bus_loc, &shift_vdac0_ch0_oddo[0x0], (sizeof(shift_vdac0_ch0_oddo) / sizeof(shift_vdac0_ch0_oddo[0x0])), alloc));
			break ;
		case ZunoGpioBusVdac0Ch1:
			if ((real_pin & 0x1) == 0x0)
				return (_gpioAllocBusVdac0Ch1(bus_loc, &shift_vdac0_ch1_even[0x0], (sizeof(shift_vdac0_ch1_even) / sizeof(shift_vdac0_ch1_even[0x0])), alloc));
			return (_gpioAllocBusVdac0Ch1(bus_loc, &shift_vdac0_ch1_oddo[0x0], (sizeof(shift_vdac0_ch1_oddo) / sizeof(shift_vdac0_ch1_oddo[0x0])), alloc));
			break ;
		case ZunoGpioBusUnknown:
			break ;
	}
	return (false);
}

bool zme_gpio_bus_alloc(uint8_t pin, ZunoGpioBus_t type) {
	bool									out;

	zunoEnterCritical();
	out = _zme_gpio_bus_alloc(pin, type, true);
	zunoExitCritical();
	return (out);
}

bool zme_gpio_bus_free(uint8_t pin, ZunoGpioBus_t type) {
	bool									out;

	zunoEnterCritical();
	out = _zme_gpio_bus_alloc(pin, type, false);
	zunoExitCritical();
	return (out);
}
#endif