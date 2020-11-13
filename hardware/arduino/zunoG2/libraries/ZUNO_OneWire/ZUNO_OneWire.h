#ifndef ZUNO_ONEWIRE_LIB
#define ZUNO_ONEWIRE_LIB

typedef struct				ZunoOneWireDate_s
{
	byte					ows_ROM_NO[8];
	byte					LastDiscrepancy;
	//byte					LastFamilyDiscrepancy;// не использовалось по факту
	bool					LastDeviceFlag;
}							ZunoOneWireDate_t;

class OneWire {
	public:
		OneWire(byte pin);
		void						reset_search();
		byte						reset(void);
		void						write(byte v, byte power);
		inline void					write(byte v) {this->write(v, true);};
		byte						read();
		void						select(byte * rom);
		inline void					skip() {this->write(0xCC);}; // Skip ROM
		void						depower();
		void						readROM(byte * rom);
		static byte					crc8(byte *addr, byte len);
		bool						search(uint8_t * newAddr);

	private:
		inline void						_digitalWriteFast(uint8_t val);
		inline size_t					_digitalReadFast();
		inline void						_pinModeFast(uint8_t);
		inline bool						_read_bit();
		inline void						_write_bit(bool bit);
		size_t							_aliasAddr_in;
		size_t							_aliasAddr_out;
		uint8_t							_real_port;
		uint8_t							_real_pin;
		ZunoOneWireDate_t				_date;
	

};

#endif // ZUNO_ONEWIRE_LIB