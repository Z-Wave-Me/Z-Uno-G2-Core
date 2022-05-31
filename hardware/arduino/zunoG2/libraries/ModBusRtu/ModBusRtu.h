#ifndef MOD_BUS_RTU_H
#define MOD_BUS_RTU_H

#include "Arduino.h"

#define MOD_BUS_RTU_FN_READ_HOLDING_REGISTERS						0x3
#define MOD_BUS_RTU_FN_READ_INPUT_REGISTERS							0x4

#define MOD_BUS_RTU_FN_READ_COILS									0x1
#define MOD_BUS_RTU_FN_READ_DISCRETE_INPUTS							0x2

/* The function code received in the query is not an 
allowable action for the server (or slave). This 
may be because the function code is only 
applicable to newer devices, and was not 
implemented in the unit selected. It could also 
indicate that the server (or slave) is in the wrong 
state to process a request of this type, for 
example because it is unconfigured and is being 
asked to return register values. */
#define MOD_BUS_RTU_STATUS_ILLEGAL_FUNCTION							0x1

/* The data address received in the query is not an 
allowable address for the server (or slave). More 
specifically, the combination of reference number 
and transfer length is invalid. For a controller with 
100 registers, the PDU addresses the first 
register as 0, and the last one as 99. If a request 
is submitted with a starting register address of 96 
and a quantity of registers of 4, then this request 
will successfully operate (address-wise at least) 
on registers 96, 97, 98, 99. If a request is 
submitted with a starting register address of 96 
and a quantity of registers of 5, then this request 
will fail with Exception Code 0x02 “Illegal Data 
Address” since it attempts to operate on registers 
96, 97, 98, 99 and 100, and there is no register 
with address 100.  */
#define MOD_BUS_RTU_STATUS_ILLEGAL_DATA_ADDRESS						0x2


/* A value contained in the query data field is not an 
allowable value for server (or slave). This 
indicates a fault in the structure of the remainder 
of a complex request, such as that the implied 
length is incorrect. It specifically does NOT mean 
that a data item submitted for storage in a register 
has a value outside the expectation of the 
application program, since the MODBUS protocol 
is unaware of the significance of any particular 
value of any particular register. */
#define MOD_BUS_RTU_STATUS_ILLEGAL_DATA_VALUE						0x3

/* An unrecoverable error occurred while the server 
(or slave) was attempting to perform the 
requested action. */
#define MOD_BUS_RTU_STATUS_SLAVE_DEVICE_FAILURE						0x4

/* Specialized use in conjunction with programming 
commands. 
The server (or slave) has accepted the request 
and is processing it, but a long duration of time 
will be required to do so. This response is 
returned to prevent a timeout error from occurring 
in the client (or master). The client (or master) 
can next issue a Poll Program Complete message 
to determine if processing is completed. */
#define MOD_BUS_RTU_STATUS_ACKNOWLEDGE								0x5

/* Specialized use in conjunction with programming 
commands. 
The server (or slave) is engaged in processing a 
long–duration program command. The client (or 
master) should retransmit the message later when 
the server (or slave) is free. */
#define MOD_BUS_RTU_STATUS_SLAVE_DEVICE_BUSY						0x6

/* Specialized use in conjunction with function codes 
20 and 21 and reference type 6, to indicate that 
the extended file area failed to pass a consistency 
check. The server (or slave) attempted to read record 
file, but detected a parity error in the memory. 
The client (or master) can retry the request, but 
service may be required on the server (or slave) 
device. */
#define MOD_BUS_RTU_STATUS_MEMORY_PARITY_ERROR						0x8

/* Specialized use in conjunction with gateways, 
indicates that the gateway was unable to allocate 
an internal communication path from the input 
port to the output port for processing the request. 
Usually means that the gateway is misconfigured 
or overloaded. */
#define MOD_BUS_RTU_STATUS_GATEWAY_PATH_UNAVAILABLE					0xA

/* Specialized use in conjunction with gateways, 
indicates that no response was obtained from the 
target device. Usually means that the device is 
not present on the network. */
#define MOD_BUS_RTU_STATUS_GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND	0xB

/* Unknown function */
#define MOD_BUS_RTU_STATUS_UNKNOWN_FN								(0xFF + 0x1)

/* The expected length of the response from the slave does not match */
#define MOD_BUS_RTU_STATUS_RESPONSE_LEN_NOT_MATCH					(0xFF + 0x2)

/* Еhe address in the response from the slave does not match */
#define MOD_BUS_RTU_STATUS_RESPONSE_ADDR_NOT_MATCH					(0xFF + 0x3)

class ModBusRtuClass {
	public:
		ModBusRtuClass(HardwareSerial *hardwareSerial, uint16_t timout_ms, uint8_t dir_pin = UNKNOWN_PIN);
		bool								begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx);
		inline bool							readCoils(uint8_t addr, uint16_t reg, uint16_t count, uint8_t *dest)  {return (this->_readCoilsDiscreteInputs(addr, reg, count, dest, MOD_BUS_RTU_FN_READ_COILS));};
		inline bool							readDiscreteInputs(uint8_t addr, uint16_t reg, uint16_t count, uint8_t *dest)  {return (this->_readCoilsDiscreteInputs(addr, reg, count, dest, MOD_BUS_RTU_FN_READ_DISCRETE_INPUTS));};
		bool								writeSingleRegisters(uint8_t addr, uint16_t reg, uint16_t value);
		bool								writeSingleCoils(uint8_t addr, uint16_t reg, bool value);
		bool								writeMultipleCoils(uint8_t addr, uint16_t reg, uint16_t count, const uint8_t *src);
		inline bool							writeMultipleRegisters(uint8_t addr, uint16_t reg, uint8_t count, const int16_t *src) {return (this->writeMultipleRegisters(addr, reg, count, (const uint16_t *)src));};
		inline bool							writeMultipleRegisters(uint8_t addr, uint16_t reg, uint8_t count, const uint16_t *src) {return (this->_writeMultipleRegisters(addr, reg, count, src, false));};
		inline bool							writeMultipleRegisters(uint8_t addr, uint16_t reg, uint8_t count, const void *src) {return (this->_writeMultipleRegisters(addr, reg, count, (uint16_t *)src, true));};
		inline bool							readHoldingRegisters(uint8_t addr, uint16_t reg, uint8_t count, int16_t *dest) {return (this->readHoldingRegisters(addr, reg, count, (uint16_t *)dest));};
		inline bool							readInputRegisters(uint8_t addr, uint16_t reg, uint8_t count, int16_t *dest) {return (this->readInputRegisters(addr, reg, count, (uint16_t *)dest));};
		inline bool							readHoldingRegisters(uint8_t addr, uint16_t reg, uint8_t count, uint16_t *dest) {return (this->_readHoldingInputRegisters(addr, reg, count, dest, MOD_BUS_RTU_FN_READ_HOLDING_REGISTERS, false));};
		inline bool							readInputRegisters(uint8_t addr, uint16_t reg, uint8_t count, uint16_t *dest) {return (this->_readHoldingInputRegisters(addr, reg, count, dest, MOD_BUS_RTU_FN_READ_INPUT_REGISTERS, false));};
		inline bool							readHoldingRegisters(uint8_t addr, uint16_t reg, uint8_t count, void *dest) {return (this->_readHoldingInputRegisters(addr, reg, count, (uint16_t *)dest, MOD_BUS_RTU_FN_READ_HOLDING_REGISTERS, true));};
		inline bool							readInputRegisters(uint8_t addr, uint16_t reg, uint8_t count, void *dest) {return (this->_readHoldingInputRegisters(addr, reg, count, (uint16_t *)dest, MOD_BUS_RTU_FN_READ_INPUT_REGISTERS, true));};

	private:
		bool								_writeMultipleRegisters(uint8_t addr, uint16_t reg, uint8_t count, const uint16_t *src, uint8_t bMemcpy);
		bool								_readCoilsDiscreteInputs(uint8_t addr, uint16_t reg, uint16_t count, uint8_t *dest, uint8_t fn);
		bool								_readHoldingInputRegisters(uint8_t addr, uint16_t reg, uint8_t count, uint16_t *dest, uint8_t fn, uint8_t bMemcpy);
		inline bool							_last_status(uint32_t status, bool ret);
		inline bool							_sendRtu(void *buffer, uint8_t len, uint8_t dest_len);
		inline bool							_send(void *src, uint8_t len);
		inline uint8_t						_receive(uint8_t addr, uint8_t fn, void *dest, uint8_t len);
		HardwareSerial						*_hardwareSerial;
		uint16_t							_timout_ms;
		uint8_t								_dir_pin;
};

#endif//MOD_BUS_RTU_H