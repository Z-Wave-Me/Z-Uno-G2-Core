ZUNO_ENABLE(
			// DBG_CONSOLE_BAUDRATE=921600
			// DBG_CONSOLE_PIN=0xFE
			// LOGGING_DBG
			// ZUNO_PIN_V=6
			CONFIGPARAMETERS_MAX_COUNT=0
			CERT_BUILD
);

enum
{
	INDEX_ELECTRIC_KHW = 1,
	INDEX_GAS,
	INDEX_WATER,
	INDEX_HEATING,
	INDEX_COOLING,
	INDEX_ELECTRIC_KVAR
};

ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);

ZUNO_SETUP_CHANNELS(
	ZUNO_METER(ZUNO_METER_TYPE_ELECTRIC, METER_RESET_ENABLE, ZUNO_METER_ELECTRIC_SCALE_KWH, METER_SIZE_FOUR_BYTES, METER_PRECISION_TWO_DECIMALS, ft_get_kwh, ft_get_kwh_reset),
	ZUNO_METER(ZUNO_METER_TYPE_GAS, METER_RESET_DISABLE, ZUNO_METER_GAS_SCALE_METERS3, METER_SIZE_TWO_BYTES, METER_PRECISION_ONE_DECIMAL, ft_get_gas, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_WATER, METER_RESET_DISABLE, ZUNO_METER_WATER_SCALE_PULSECOUNT, METER_SIZE_ONE_BYTE, METER_PRECISION_ZERO_DECIMALS, ft_get_water, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_HEATING, METER_RESET_DISABLE, ZUNO_METER_HEATING_SCALE_KWH, METER_SIZE_FOUR_BYTES, METER_PRECISION_TWO_DECIMALS, ft_get_heating, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_COOLING, METER_RESET_DISABLE, ZUNO_METER_COOLING_SCALE_KWH, METER_SIZE_FOUR_BYTES, METER_PRECISION_TWO_DECIMALS, ft_get_cooling, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_ELECTRIC, METER_RESET_ENABLE, ZUNO_METER_ELECTRIC_SCALE_KWH, METER_SIZE_TWO_BYTES, METER_PRECISION_ONE_DECIMAL, ft_get_kvar, ft_get_kvar_reset)
);

static uint32_t _kwh = 0x0;
static uint16_t _gas = 0x0;
static uint8_t _water = 0x0;
static uint32_t _heating = 0x0;
static uint32_t _cooling = 0x0;
static uint16_t _kvar = 0x0;

void setup(void) {

}

void loop(void) {
	_kwh = random(300, 10000);
	zunoSendReport(INDEX_ELECTRIC_KHW);
	_gas = random(100, 500);
	zunoSendReport(INDEX_GAS);
	_water = random(1, 255);
	zunoSendReport(INDEX_WATER);
	_heating = random(1000, 5555);
	zunoSendReport(INDEX_HEATING);
	_cooling = random(3000, 44000);
	zunoSendReport(INDEX_COOLING);
	_kvar = random(333, 11111);
	zunoSendReport(INDEX_ELECTRIC_KVAR);
	delay(1000);
}

void ft_get_kwh_reset(uint32_t value)
{
	_kwh = value;
}

uint32_t ft_get_kwh(void)
{
	return (_kwh);
}

uint16_t ft_get_gas(void)
{
	return (_gas);
}

uint8_t ft_get_water(void)
{
	return (_water);
}


uint32_t ft_get_heating(void)
{
	return (_heating);
}

uint32_t ft_get_cooling(void)
{
	return (_cooling);
}

uint16_t ft_get_kvar(void)
{
	return (_kvar);
}

void ft_get_kvar_reset(uint16_t value)
{
	_kvar = value;
}


void ft_empty(uint32_t value)
{
	(void)value;
}
