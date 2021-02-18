#include "Mercury206Meter.h"

#define MERCURY_METERSEL_PIN			2
#define MERCURY_SERIAL					39950007
#define MERCURY_TARIF_KWH0				0//Много тарифность 0
#define MERCURY_TARIF_KWH1				1//Много тарифность 1
#define MERCURY_TARIF_KWH_N				3//Каличество тарифов +  сумма
#define MERCURY_DEFAULT_INTERVAL_KHW	180
#define MERCURY_DEFAULT_INTERVAL_METER	60
#define MERCURY_PARAM_BAD_RETURN		0xFFFF
#define MERCURY_ON						0x55
#define MERCURY_OFF						0xAA

#define MERCURY_HYSTEREZIS_KHW			1
#define MERCURY_HYSTEREZIS_WATTS		3
#define MERCURY_HYSTEREZIS_VOLTS		5
#define MERCURY_HYSTEREZIS_AMPS			50
#define MERCURY_HYSTEREZIS_HZ			50

typedef struct			s_khw_mecrury//Структура для для тарифов квтч
{
	dword				value = 0;
	dword				tmp = 0;
}						t_khw_mecrury;

enum
{
	MERCURY_PARAM_KHW_INTERVAL = 64,
	MERCURY_PARAM_METER_INTERVAL
};

enum
{
	MERCURY_INDEX_SWITCH_BINARY = 1,
	MERCURY_INDEX_ELECTRIC_KHW0,
	MERCURY_INDEX_ELECTRIC_KHW1,
	MERCURY_INDEX_ELECTRIC_KHW2,
	MERCURY_INDEX_ELECTRIC_WATTS,
	MERCURY_INDEX_ELECTRIC_VOLTS,
	MERCURY_INDEX_ELECTRIC_AMPS,
	MERCURY_INDEX_MULTILEVEL_HERTZ
};

ZUNO_SETUP_CHANNELS(
	ZUNO_SWITCH_BINARY(ft_get_switch, ft_set_switch),
	ZUNO_METER(ZUNO_METER_TYPE_ELECTRIC, METER_RESET_DISABLE, ZUNO_METER_ELECTRIC_SCALE_KWH, METER_SIZE_FOUR_BYTES, METER_PRECISION_TWO_DECIMALS, ft_get_kwh0, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_ELECTRIC, METER_RESET_DISABLE, ZUNO_METER_ELECTRIC_SCALE_KWH, METER_SIZE_FOUR_BYTES, METER_PRECISION_TWO_DECIMALS, ft_get_kwh1, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_ELECTRIC, METER_RESET_DISABLE, ZUNO_METER_ELECTRIC_SCALE_KWH, METER_SIZE_FOUR_BYTES, METER_PRECISION_TWO_DECIMALS, ft_get_kwh2, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_ELECTRIC, METER_RESET_DISABLE, ZUNO_METER_ELECTRIC_SCALE_WATTS, METER_SIZE_TWO_BYTES, METER_PRECISION_ZERO_DECIMALS, ft_get_watts, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_ELECTRIC, METER_RESET_DISABLE, ZUNO_METER_ELECTRIC_SCALE_VOLTS, METER_SIZE_TWO_BYTES, METER_PRECISION_ONE_DECIMAL, ft_get_volts, ft_empty),
	ZUNO_METER(ZUNO_METER_TYPE_ELECTRIC, METER_RESET_DISABLE, ZUNO_METER_ELECTRIC_SCALE_AMPS, METER_SIZE_TWO_BYTES, METER_PRECISION_TWO_DECIMALS, ft_get_amps, ft_empty),
	ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_FREQUENCY, SENSOR_MULTILEVEL_SCALE_HERTZ, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, SENSOR_MULTILEVEL_SIZE_TWO_BYTES, ft_get_hz)
);

ZUNO_SETUP_CFGPARAMETER_HANDLER(ft_parameter_changed);

Mercury206Meter		g_mercury_meter(MERCURY_SERIAL, MERCURY_METERSEL_PIN);
t_khw_mecrury		g_kwh[MERCURY_TARIF_KWH_N];
word				g_kwh_interv;
MercuryVAW			g_vaw = {0, 0, 0};
MercuryVAW			g_vaw_tmp = {0, 0, 0};
word				g_hz = 0;
word				g_hz_tmp = 0;
word				g_meter_interv;
word				g_loop_count = 0;
byte				g_swich_state;
byte				g_swich_update;


void	fn_report(int32_t value, byte index)
{
	if ((value & (1 << 31)) != 0)
		value = ~value + 1;
	switch (index)
	{
		case (MERCURY_INDEX_ELECTRIC_KHW0):
			if ((dword)value < MERCURY_HYSTEREZIS_KHW)
				return;
			g_kwh[0].tmp = g_kwh[0].value;
			break ;
		case (MERCURY_INDEX_ELECTRIC_KHW1):
			if ((dword)value < MERCURY_HYSTEREZIS_KHW)
				return;
			g_kwh[1].tmp = g_kwh[1].value;
			break ;
		case (MERCURY_INDEX_ELECTRIC_KHW2):
			if ((dword)value < MERCURY_HYSTEREZIS_KHW)
				return;
			g_kwh[2].tmp = g_kwh[2].value;
			break ;
		case (MERCURY_INDEX_MULTILEVEL_HERTZ):
			if ((dword)value < MERCURY_HYSTEREZIS_HZ)
				return;
			g_hz_tmp = g_hz;
			break ;
		case (MERCURY_INDEX_ELECTRIC_AMPS):
			if ((dword)value < MERCURY_HYSTEREZIS_AMPS)
				return;
			g_vaw_tmp.amps = g_vaw.amps;
			break ;
		case (MERCURY_INDEX_ELECTRIC_WATTS):
			if ((dword)value < MERCURY_HYSTEREZIS_WATTS)
				return;
			g_vaw_tmp.watts = g_vaw.watts;
			break ;
		case (MERCURY_INDEX_ELECTRIC_VOLTS):
			if ((dword)value < MERCURY_HYSTEREZIS_VOLTS)
				return ;
			g_vaw_tmp.volts = g_vaw.volts;
			break ;
		default:
			return ;
	}
	zunoSendReport(index);
}
	
void	setup(void)
{
	byte		tmp;

	g_mercury_meter.begin();
	ft_parameter_changed(MERCURY_PARAM_KHW_INTERVAL, zunoLoadCFGParam(MERCURY_PARAM_KHW_INTERVAL));
	ft_parameter_changed(MERCURY_PARAM_METER_INTERVAL, zunoLoadCFGParam(MERCURY_PARAM_METER_INTERVAL));
	tmp = (g_mercury_meter.getRelayState() == MERCURY_OFF) ? 0 : 0xFF;
	g_swich_state = tmp;
	g_swich_update = tmp;
}

void	loop(void)
{
	if((g_loop_count % g_meter_interv) == 0)
	{
		g_mercury_meter.getCurrentVAW(&g_vaw);
		fn_report(g_vaw.amps - g_vaw_tmp.amps, MERCURY_INDEX_ELECTRIC_AMPS);
		fn_report(g_vaw.watts - g_vaw_tmp.watts, MERCURY_INDEX_ELECTRIC_WATTS);
		fn_report(g_vaw.volts - g_vaw_tmp.volts, MERCURY_INDEX_ELECTRIC_VOLTS);
		g_mercury_meter.getFrequencyTarif(&g_hz);
		fn_report(g_hz - g_hz_tmp, MERCURY_INDEX_MULTILEVEL_HERTZ);
	}
	if((g_loop_count % g_kwh_interv) == 0)
	{
		g_mercury_meter.getKWhCounter(MERCURY_TARIF_KWH0, &g_kwh[0].value);
		fn_report(g_kwh[0].value - g_kwh[0].tmp, MERCURY_INDEX_ELECTRIC_KHW0);
		g_mercury_meter.getKWhCounter(MERCURY_TARIF_KWH1, &g_kwh[1].value);
		fn_report(g_kwh[1].value - g_kwh[1].tmp, MERCURY_INDEX_ELECTRIC_KHW1);
		g_kwh[2].value = g_kwh[0].value + g_kwh[1].value;
		fn_report(g_kwh[2].value - g_kwh[2].tmp, MERCURY_INDEX_ELECTRIC_KHW2);
	}
	if (g_swich_update != g_swich_state)
	{
		if (g_swich_update != 0)
		{
			g_mercury_meter.setRelayMode(0xFF);//Включаем реле без слежения
			g_mercury_meter.setRelayMode(0x5A);//Эмулируем кнопку
		}
		else
		{
			g_mercury_meter.setRelayMode(0xAA);//Выключить
		}
		g_swich_state = g_swich_update;
		zunoSendReport(MERCURY_INDEX_SWITCH_BINARY);
	}
	g_loop_count++;
	delay(500);
}

void	ft_parameter_changed(byte param, word value)
{
	switch (param)
	{
		case (MERCURY_PARAM_KHW_INTERVAL):
			if (value <= 60 || value >= MERCURY_PARAM_BAD_RETURN)
			{
				g_kwh_interv = MERCURY_DEFAULT_INTERVAL_KHW;
				zunoSaveCFGParam(MERCURY_PARAM_KHW_INTERVAL, MERCURY_DEFAULT_INTERVAL_KHW);
			}
			else
				g_kwh_interv = value;
			return;
		case (MERCURY_PARAM_METER_INTERVAL):
			if (value < 60 || value >= MERCURY_PARAM_BAD_RETURN)
			{
				g_meter_interv = MERCURY_DEFAULT_INTERVAL_METER;
				zunoSaveCFGParam(MERCURY_PARAM_METER_INTERVAL, MERCURY_DEFAULT_INTERVAL_METER);
			}
			else
				g_meter_interv = value;
			return;
	}
}

void	ft_set_switch(byte value)
{
	g_swich_update = value;
}

byte	ft_get_switch(void)
{
	return g_swich_state;
}

void	ft_empty(byte value)
{
	(void)value;
}

dword	ft_get_kwh0(void)
{
	return (g_kwh[0].value);
}

dword	ft_get_kwh1(void)
{
	return (g_kwh[1].value);
}

dword	ft_get_kwh2(void)
{
	return (g_kwh[2].value);
}

word	ft_get_hz(void)
{
	return (g_hz);
}

word	ft_get_watts(void)
{
	return (g_vaw.watts);
}

word	ft_get_volts(void)
{
	return (g_vaw.volts);
}

word	ft_get_amps(void)
{
	return (g_vaw.amps);
}
