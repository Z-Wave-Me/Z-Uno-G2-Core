#ifndef ZUNO_NEPTUN_H
#define ZUNO_NEPTUN_H

#include "Arduino.h"
#include "ZUNO_ModBus.h"

typedef enum								NeptunBaudrate_e
{
	NeptunBaudrate1200 = 0,
	NeptunBaudrate2400,
	NeptunBaudrate4800,
	NeptunBaudrate9600,
	NeptunBaudrate19200,
	NeptunBaudrate38400,
	NeptunBaudrate57600,
	NeptunBaudrate115200,
	NeptunBaudrate230400,
	NeptunBaudrate460800,
	NeptunBaudrate921600
}											NeptunBaudrate_t;

typedef struct								NeptunStatusDev_s
{
	union
	{
		struct
		{
			union
			{
				struct
				{
					uint16_t				bFloorCleaning: 1;/* Флаг состояния режима мойка пола.  false = выключено; true = включено */
					uint16_t				bAlarmsGroup1: 1;/* Флаг наличия тревоги по первой группе. false = нет; true = есть - const */
					uint16_t				bAlarmsGroup2: 1;/* Флаг наличия тревоги по второй группе. false = нет; true = есть - const */
					uint16_t				bSensorsWirelessBatteriesDischarge: 1;/* Флаг разряда батарей в беспроводных датчиках. false = нет; true = есть - const */
					uint16_t				bSensorsWirelessLoss: 1;/* Флаг потери беспроводных датчиков. false = нет; true = есть - const */
					uint16_t				bTapsClosingLossSensorsGroup1: 1;/* Флаг закрытия кранов первой группе по потере датчиков. false = нет; true = есть - const */
					uint16_t				bTapsClosingLossSensorsGroup2: 1;/* Флаг закрытия кранов второй группе по потере датчиков. false = нет; true = есть - const */
					uint16_t				bStartConnectionSensorsWireless: 1;/* Флаг запуска процедуры подключения беспроводных устройств. false = нет; true = есть */
					uint16_t				bTapsStatusGroup1: 1;/* Состояние кранов первой группы. false = закрыты; true = открыты */
					uint16_t				bTapsStatusGroup2: 1;/* Состояние кранов второй группы. false = закрыты; true = открыты */
					uint16_t				bGrouping: 1;/* Включение группирования. false =  одна группа; true = две группы */
					uint16_t				bTapsClosingWhenLossSensors: 1;/* Закрывания кранов при потере беспроводного датчика протечки. false = выключено; true = включено */
					uint16_t				bKeypadLocks: 1;/* Блокировки клавиатуры. false = разблокирована; true = заблокирована */
				};
				uint16_t					value;
			};
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunStatusDev_t;

typedef struct								NeptunConfigModule_s
{
	union
	{
		struct
		{
			union
			{
				struct
				{
					NeptunBaudrate_t		baudrate;/* Адрес модуля для MODBUS */
					uint8_t					adress;/* Скорость порта */
				};
				uint16_t					value;
			};
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunConfigModule_t;

typedef struct								NeptunSensorsWirelessCount_s
{
	union
	{
		struct
		{
			uint16_t						count;
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunSensorsWirelessCount_t;

typedef enum								NeptunSensorsWirelessSignalLevel_e
{
	NeptunSensorsWirelessSignalLevelNoConnection = 0,
	NeptunSensorsWirelessSignalLevelWeak,
	NeptunSensorsWirelessSignalLevelMiddle,
	NeptunSensorsWirelessSignalLevelGood,
	NeptunSensorsWirelessSignalLevelGreat
}											NeptunSensorsWirelessSignalLevel_t;

typedef struct								NeptunSensorsWirelessStatus_s
{
	union
	{
		struct
		{
			union
			{
				struct
				{
					uint16_t							bAlarm: 1;/* Наличие тревоги.  false = нет; true = есть  const */
					uint16_t							bDischargeAvailability: 1;/* Наличие разряда.  false = нет; true = есть  const */
					uint16_t							bLossSensor : 1;/* Потеря датчика.  false = нет; true = есть  const */
					NeptunSensorsWirelessSignalLevel_t	sensorSignalLevel: 3;/* Уровень сигнала от датчика. const */
					uint16_t							reserved: 2;/* const */
					uint16_t							batteryLevel: 8;/* Уровень заряда батареи.  0-100  const */
				};
				uint16_t					value;
			};
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunSensorsWirelessStatus_t;

typedef enum								NeptunSensorsGroop_e
{
	NeptunSensorsGroopFirst = 1,
	NeptunSensorsGroopSecond,
	NeptunSensorsGroopBoth
}											NeptunSensorsGroop_t;

typedef struct								NeptunSensorsWirelessConfig_s
{
	union
	{
		struct
		{
			NeptunSensorsGroop_t			value;/* Отработка событий по группам */
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunSensorsWirelessConfig_t;

typedef enum								NeptunRelayGroop_e
{
	NeptunRelayGroopNotSwitch = 0,
	NeptunRelayGroopFirst,
	NeptunRelayGroopSecond,
	NeptunRelayGroopBoth
}											NeptunRelayGroop_t;

typedef struct								NeptunConfigRelay_s
{
	union
	{
		struct
		{
			union
			{
				struct
				{
					NeptunRelayGroop_t		bSwitchingAlarm: 2;/* Переключение по тревоге. */
					NeptunRelayGroop_t		bSwitchingClosingTaps: 2;/* Переключение по закрыванию кранов. */
				};
				uint16_t					value;
			};
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunConfigRelay_t;

typedef struct								NeptunConfigLine_s
{
	union
	{
		struct
		{
			union
			{
				struct
				{
					uint16_t				bLine1: 1;/* Статус первой линии. false = Тревоги нет; true = Тревога есть */
					uint16_t				bLine2: 1;/* Статус второй линии. false = Тревоги нет; true = Тревога есть */
					uint16_t				bLine3: 1;/* Статус третьей линии. false = Тревоги нет; true = Тревога есть */
					uint16_t				bLine4: 1;/* Статус четвертой линии. false = Тревоги нет; true = Тревога есть */
				};
				uint16_t					value;
			};
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunConfigLine_t;

typedef struct								NeptunConfigLine1And2_s
{
	union
	{
		struct
		{
			union
			{
				struct
				{
					NeptunSensorsGroop_t	bLineControl2: 2;/* Управление линиями кранов. */
					uint16_t				bLineType2: 1;/* Конфигурация типа входа линии. false = датчики; true = кнопка */
					uint16_t				reserved: 5;
					NeptunSensorsGroop_t	bLineControl1: 2;/* Управление линиями кранов. */
					uint16_t				bLineType1: 1;/* Конфигурация типа входа линии. false = датчики; true = кнопка */
				};
				uint16_t					value;
			};
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunConfigLine1And2_t;

typedef struct								NeptunConfigLine3And4_s
{
	union
	{
		struct
		{
			union
			{
				struct
				{
					NeptunSensorsGroop_t	bLineControl4: 2;/* Управление линиями кранов. */
					uint16_t				bLineType4: 1;/* Конфигурация типа входа линии. false = датчики; true = кнопка */
					uint16_t				reserved: 5;
					NeptunSensorsGroop_t	bLineControl3: 2;/* Управление линиями кранов. */
					uint16_t				bLineType3: 1;/* Конфигурация типа входа линии. false = датчики; true = кнопка */
				};
				uint16_t					value;
			};
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunConfigLine3And4_t;

typedef struct								NeptunGetOut_s
{
	union
	{
		struct
		{
			uint16_t						value;
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunGetOut_t;

typedef enum								NeptunConfigMeterConnect_e
{
	NeptunConfigMeterConnectNormal = 0,
	NeptunConfigMeterConnectNamur
}											NeptunConfigMeterConnect_t;

typedef enum								NeptunConfigMeterError_e
{
	NeptunConfigMeterErrorSuccess = 0,
	NeptunConfigMeterErrorShortCircuit,
	NeptunConfigMeterErrorLineBreak
}											NeptunConfigMeterError_t;

typedef enum								NeptunConfigMeterStep_e
{
	NeptunConfigMeterStep1 = 1,
	NeptunConfigMeterStep10 = 10,
	NeptunConfigMeterStep100 = 100
}											NeptunConfigMeterStep_t;

typedef struct								NeptunConfigMeter_s
{
	union
	{
		struct
		{
			union
			{
				struct
				{
					uint16_t					bStatus: 1;/* Статус счетчика. false = выключен; true = включен */
					NeptunConfigMeterConnect_t	bTypeConnect: 1;/* Тип подключения счетчика. */
					NeptunConfigMeterError_t	bError: 2;/* Наличие ошибок при типе подключения Namur. const */
					uint16_t					reserved: 4;
					NeptunConfigMeterStep_t		step;
				};
				uint16_t					value;
			};
			ZunoError_t						status;
		};
		uint32_t							raw;
	};
}											NeptunConfigMeter_t;

typedef enum								NeptunConfigMeterId_e
{
	NeptunConfigMeterIdOne = 0,
	NeptunConfigMeterIdTwo
}											NeptunConfigMeterId_t;

typedef enum								NeptunConfigMeterSlot_e
{
	NeptunConfigMeterSlotOne = 0,
	NeptunConfigMeterSlotTwo = 2
}											NeptunConfigMeterSlot_t;

class NeptunClass: private ModBusRtuClass {
	public:
		NeptunClass(HardwareSerial *hardwareSerial = &Serial1, uint16_t timeout = 3000);
		ZunoError_t							begin(NeptunBaudrate_t baudrate, uint8_t rx, uint8_t tx, uint8_t dir_pin);
		inline ZunoError_t					begin(void) { return (this->begin(NeptunBaudrate9600, RX1, TX1, 2)); };
		void								end(void);
		inline void							setAdress(uint8_t adress) {
			if (adress == 0 || adress > 247)
				return ;
			this->_adress = adress;
		};
		inline size_t						convertInBaudrate(NeptunBaudrate_t baudrate) {
			size_t							tempos;

			tempos = (1 << baudrate);
			if (baudrate > NeptunBaudrate38400)
				tempos = tempos + tempos / 4;
			return (1200 * tempos);
		};
		inline NeptunStatusDev_t			devGetStatus(void) { NeptunStatusDev_t out; out.raw = this->_read(0x0).raw; return(out); };
		inline ZunoError_t					devSetStatus(NeptunStatusDev_t value) { return (this->_write(0x0, value.value)); };
		inline NeptunConfigModule_t			devGetConfigModule(void) { NeptunConfigModule_t out; out.raw = this->_read(0x5).raw; return(out); };
		inline ZunoError_t					devSetConfigModule(NeptunConfigModule_t value) { return (this->_write(0x5, value.value)); };
		inline NeptunSensorsWirelessCount_t	devGetSensorsWirelessCount(void) { NeptunSensorsWirelessCount_t out; out.raw = this->_read(0x6).raw; return(out); };
		NeptunSensorsWirelessStatus_t		devGetSensorsWirelessStatus(size_t id);
		NeptunSensorsWirelessConfig_t		devGetSensorsWirelessConfig(size_t id);
		ZunoError_t							devSetSensorsWirelessConfig(size_t id, NeptunSensorsGroop_t value);
		inline NeptunConfigRelay_t			devGetConfigRelay(void) { NeptunConfigRelay_t out; out.raw = this->_read(0x4).raw; return(out); };
		inline ZunoError_t					devSetConfigRelay(NeptunConfigRelay_t value) { return (this->_write(0x4, value.value)); };
		inline NeptunConfigLine_t			devGetStatusLine(void) { NeptunConfigLine_t out; out.raw = this->_read(0x3).raw; return(out); };
		inline NeptunConfigLine1And2_t		devGetConfigLine1And2(void) { NeptunConfigLine1And2_t out; out.raw = this->_read(0x1).raw; return(out); };
		inline NeptunConfigLine3And4_t		devGetConfigLine3And4(void) { NeptunConfigLine3And4_t out; out.raw = this->_read(0x2).raw; return(out); };
		inline ZunoError_t					devSetConfigLine1And2(NeptunConfigLine1And2_t value) { return (this->_write(0x1, value.value)); };
		inline ZunoError_t					devSetConfigLine3And4(NeptunConfigLine3And4_t value) { return (this->_write(0x2, value.value)); };
		inline NeptunConfigMeter_t			devGetMeterConfig(NeptunConfigMeterId_t id, NeptunConfigMeterSlot_t slot) {NeptunConfigMeter_t out; out.raw = this->_read(0x7B + id + slot).raw; return(out); };
		inline ZunoError_t					devSetMeterConfig(NeptunConfigMeterId_t id, NeptunConfigMeterSlot_t slot, NeptunConfigMeter_t value) { return (this->_write(0x7B + id + slot, value.value)); };
		ZunoError_t							devGetMeter(NeptunConfigMeterId_t id, NeptunConfigMeterSlot_t slot, uint32_t *value);
		ZunoError_t							devSetMeter(NeptunConfigMeterId_t id, NeptunConfigMeterSlot_t slot, uint32_t value);

	private:
		ZunoError_t							_write(uint16_t reg, uint16_t value);
		NeptunGetOut_t						_read(size_t reg);
		static ZunoSync_t					_syncNeptun;
		uint8_t								_key;
		uint8_t								_adress;
		uint8_t								*lp;
};

#endif//ZUNO_NEPTUN_H