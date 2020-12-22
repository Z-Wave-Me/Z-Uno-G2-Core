#ifndef MERCURY_206_METER_H
#define MERCURY_206_METER_H

struct MercuryFWVersion{
    byte version_major;
    byte version_minor;
    byte separator;
    byte hex_day;
    byte hex_month;
    byte hex_year;
};
struct MercuryVAW {
    word volts;
    word amps;
    word watts;
};
struct MercuryTimeDate {
    byte hour;
    byte minutes;
    byte seconds;
    byte day;
    byte month;
    byte year;
};
struct MercuryMaximums {
    word                system_value;
    MercuryTimeDate     system_datetime;
    word                custom_value;
    MercuryTimeDate     custom_datetime;
};
struct MercuryRelayParams {
    byte tries;
    byte delay;
    byte timeout;
};
enum {
    MERCURY_MAX_VOLTAGE,
    MERCURY_MAX_CURRENT,
    MERCURY_MAX_POWER
};

struct MercuryTarifH{
    byte nH;
    byte mm;
};
struct MercuryTarifTimeTable {
    MercuryTarifH entries[16];
};


class Mercury206Meter{
	public:
		Mercury206Meter(uint32_t serialnumber = 0, uint8_t dir_pin = 0);
		void begin();
		bool getVersion(MercuryFWVersion * p_fw_version);
		bool getCurrentLoadPower(word * p_power);
		bool getCurrentVAW(MercuryVAW * vaw);
		word getBatteryVoltage();
		bool getKWhCounter(byte ci, dword * counter);
		byte getRelayMode();
		byte getFrequencyTarif(word * freq);
		word getReactivePower();
		int  getCosFi();
		bool getMaximums(byte type, MercuryMaximums * maxs);
		word getEnergyLimit();
		word getPowerLimit();
		bool getCurrentDateTime(MercuryTimeDate * dt);
		bool getLastEnergyFail(MercuryTimeDate * dt);
		bool getLastEnergyRecover(MercuryTimeDate * dt);
		byte getRelayState();
		bool getMercuryTarifTable(byte ii2, MercuryTarifTimeTable * tt);
		bool setTarifCount(byte tc);
		bool setRelayMode(byte mode);
		bool setEnergyLimit(word energy);
		bool setPowerLimit(word power);
		bool resetMaximums(byte type);
		bool setMainDisplay(byte main);
		bool setAuxDisplay(byte aux);
		bool setTarif(byte tarif);
		bool setTarifTable(byte ii2, MercuryTarifTimeTable * tt);

	private:
		inline size_t								_fillCmd(byte cmd, size_t len, uint8_t *b);
		inline uint8_t								_bcd2dec(uint8_t c);
		inline void									_fullDateTime(MercuryTimeDate *dt, uint8_t *b);
		inline uint16_t								_bcd2Word2(uint8_t *b);
		inline int									_bcd2Int2(uint8_t *b);
		inline uint16_t								_bcd2Word3(uint8_t *b);
		inline uint32_t								_bcd2Dword(uint8_t *b);
		byte _sn[4];
		byte _dir_pin;
};

#endif//MERCURY_206_METER_H