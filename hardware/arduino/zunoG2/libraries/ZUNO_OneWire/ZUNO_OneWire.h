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
		inline void					write(byte v) {this->write(v, false);};
		void						write_bytes(const uint8_t *buf, uint16_t count, bool power = 0);
		byte						read();
		void						read_bytes(uint8_t *buf, uint16_t count);
		void						select(byte * rom);
		inline void					skip() {this->write(0xCC);}; // Skip ROM
		void						depower();
		void						readROM(byte * rom);
		static byte					crc8(byte *addr, byte len);
		static bool					check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc = 0);
		static uint16_t				crc16(const uint8_t* input, uint16_t len, uint16_t crc = 0);
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