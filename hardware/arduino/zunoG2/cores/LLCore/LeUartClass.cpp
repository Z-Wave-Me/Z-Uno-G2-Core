

#include "em_device.h"
#if defined(LEUART_COUNT) && (LEUART_COUNT > 0)
#include "Arduino.h"
#include "stdio.h"
#include "stdarg.h"
#include "LeUartClass.h"
#include "zwaveme_libft.h"
#include "em_leuart.h"

#define LE_UART_MIN_WRITE_ZDMA			2
#define LE_UART_BUFFER_LENGTH			128

static void LEUART_Sync(LEUART_TypeDef *leuart, uint32_t mask)
{
  /* Avoid deadlock if modifying the same register twice when freeze mode is */
  /* activated. */
  if (leuart->FREEZE & LEUART_FREEZE_REGFREEZE) {
    return;
  }

  /* Wait for any pending previous write operation to have been completed */
  /* in the low-frequency domai. */
  while ((leuart->SYNCBUSY & mask) != 0U) {
  }
}

/* Public Constructors */
LeUartClass::LeUartClass(void): _channel(-1), _lpKey(false), _bFree(false) {
}

/* Public Methods */

ZunoError_t LeUartClass::begin(size_t speed, uint32_t config, uint8_t rx, uint8_t tx) {
	void				*b;

	if ((b = malloc(LE_UART_BUFFER_LENGTH)) == 0)
		return (ZunoErrorMemory);
	return (this->_begin(speed, config, rx, tx, b, LE_UART_BUFFER_LENGTH, true));
}

void LeUartClass::end() {
	zunoSyncClose(&gSyncLeUart, SyncMasterLeUart, LeUartClass::_deInit, (size_t)this, &this->_lpKey);
}

int LeUartClass::available(void) {
	int											out;

	if (zunoSyncLockRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey) != ZunoErrorOk)
		return (0);
	out = LdmaClass::receivedAvailable(this->_channel);
	zunoSyncReleseRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey);
	return (out);
}

int LeUartClass::peek(void) {
	return (this->_readLock(false));
}
int LeUartClass::read(void) {
	return (this->_readLock(true));
}

// V_uart — скорость UART (например: 9600, 115200), бод;
// d — количество бит данных;
// D — количество байт всех данных;
// s — количество стоповых бит;
// p — количество бит четности, p = 1 если бит четности присутствует, или p = 0 если бит четности отсутствует;
// t = 8 * D * (d + 1 + s + p) * 1000 / (d * V_uart) - мс
size_t LeUartClass::write(const uint8_t *b, size_t count) {
	LEUART_TypeDef								*usart;
	const uint8_t								*e;
	ssize_t										channel;
	LdmaClassTransferSingle_t					array;
	uint32_t									ctrl;
	uint32_t									ms;

	if (zunoSyncLockWrite(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey) != ZunoErrorOk)
		return (0);
	usart = LEUART0;
	ctrl = usart->CTRL;
	ms = 1000 * 0x8 * count * ((((ctrl & _LEUART_CTRL_DATABITS_MASK) >> _LEUART_CTRL_DATABITS_SHIFT) + 0x8) + 0x1 + ((ctrl & _LEUART_CTRL_STOPBITS_MASK) == LEUART_CTRL_STOPBITS_TWO ? 0x2 : 0x1) + ((ctrl & _LEUART_CTRL_PARITY_MASK) == LEUART_CTRL_PARITY_EVEN ? 0x1 : 0x0)) / ((((ctrl & _LEUART_CTRL_DATABITS_MASK) >> _LEUART_CTRL_DATABITS_SHIFT) + 0x8) * this->_baudrate);
	ms = ms + ms / 100;//intercharacter spacing takes into account, or rather its absence
	if (count <= LE_UART_MIN_WRITE_ZDMA) {
		e = b + count;
		ms = ms / count;
		while (b < e) {
			LEUART_Tx(usart, b++[0]);
			delay(ms);
		}
		while (!(usart->STATUS & LEUART_STATUS_TXC))/* Check that transmit buffer is empty */
			__NOP();
	}
	else if ((channel = LdmaClass::transferSingle(b, (void*)&(usart->TXDATA), count, ldmaPeripheralSignal_LEUART0_TXBL, ldmaCtrlSizeByte, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &array)) >= 0x0) {
		delay(ms);
		while (!(usart->STATUS & LEUART_STATUS_TXC))/* Check that transmit buffer is empty */
			__NOP();
		LdmaClass::transferStop(channel);
	}
	zunoSyncReleseWrite(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey);
	return (count);
}

void LeUartClass::wakeUpDisabled(void) {
	if (zunoSyncLockRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey) != ZunoErrorOk)
		return ;
	LEUART_Sync(LEUART0, LEUART_SYNCBUSY_SIGFRAME | LEUART_SYNCBUSY_CMD);
	LEUART0->IEN = _LEUART_IEN_RESETVALUE;
	zunoSyncReleseRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey);
}

void LeUartClass::startFrame(uint16_t value) {
	if (zunoSyncLockRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey) != ZunoErrorOk)
		return ;
	LEUART_Sync(LEUART0, LEUART_SYNCBUSY_STARTFRAME | LEUART_SYNCBUSY_CTRL | LEUART_SYNCBUSY_CMD);
	LEUART0->STARTFRAME = value & _LEUART_STARTFRAME_MASK;
	LEUART0->CTRL = LEUART0->CTRL | LEUART_CTRL_SFUBRX;
	LEUART0->CMD = LEUART_CMD_RXBLOCKEN;
	zunoSyncReleseRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey);
}

void LeUartClass::startFrameDisabled(void) {
	if (zunoSyncLockRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey) != ZunoErrorOk)
		return ;
	LEUART_Sync(LEUART0,LEUART_SYNCBUSY_CTRL | LEUART_SYNCBUSY_CMD);
	LEUART0->CTRL = LEUART0->CTRL & (~LEUART_CTRL_SFUBRX);
	LEUART0->CMD = LEUART_CMD_RXBLOCKDIS;
	zunoSyncReleseRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey);
}


/* Private Methods */
void LeUartClass::_wakeUp(size_t value) {
	if (zunoSyncLockRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey) != ZunoErrorOk)
		return ;
	LEUART_Sync(LEUART0, LEUART_SYNCBUSY_SIGFRAME | LEUART_SYNCBUSY_CMD);
	if (value == (size_t)-1)
		LEUART0->IEN = LEUART_IEN_RXDATAV;
	else {
		LEUART0->SIGFRAME = value & _LEUART_SIGFRAME_MASK;
		LEUART0->IEN = LEUART_IEN_SIGF;
	}
	zunoSyncReleseRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey);
}

inline int LeUartClass::_readLock(uint8_t bOffset) {
	int											out;

	if (zunoSyncLockRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey) != ZunoErrorOk)
		return (-1);
	out = LdmaClass::receivedReadPeek(this->_channel, bOffset);
	zunoSyncReleseRead(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey);
	return (out);
}

ZunoError_t LeUartClass::_deInit(size_t param) {
	LeUartClass								*serial;
	ssize_t										channel;

	serial = (LeUartClass *)param;
	if ((channel = serial->_channel) > 0x0) {
		LdmaClass::transferStop(channel);
		serial->_channel = -1;
	}
	LEUART_Reset(LEUART0);
	if (serial->_bFree == true) {
		serial->_bFree = false;
		free(serial->_buffer);
	}
	return (ZunoErrorOk);
}

inline ZunoError_t LeUartClass::_beginFaill(ZunoError_t ret, uint8_t bFree, void *b) {
	if (bFree == true)
		free(b);
	return (ret);
}

ZunoError_t LeUartClass::_begin(size_t baudrate, uint32_t option, uint8_t rx, uint8_t tx, void *b, size_t len, uint8_t bFree) {
	LEUART_TypeDef								*usart;
	const uint8_t								*location_ptr;
	size_t										location_sz;
	ZunoError_t									ret;
	size_t 										rx_loc;
	size_t 										tx_loc;
	LEUART_Init_TypeDef							usartInit;
	ssize_t										channel;

	usart = LEUART0;
	location_ptr = g_loc_pa0_pf7_all;
	location_sz = sizeof(g_loc_pa0_pf7_all);
	// Extract base locations for pins 
	rx_loc = getLocation(location_ptr, location_sz, rx);
	tx_loc = getLocation(location_ptr, location_sz, tx);
	if (rx == tx || rx_loc == INVALID_PIN_INDEX || tx_loc == INVALID_PIN_INDEX)
		return (this->_beginFaill(ZunoErrorInvalidPin, bFree, b));// wrong index or pin combination // The pin is valid, but it doesn't support by this USART interface
	if ((ret = zunoSyncOpen(&gSyncLeUart, SyncMasterLeUart, 0x0, 0x0, &this->_lpKey)) != ZunoErrorOk)
		return (this->_beginFaill(ret, bFree, b));
	// Enable LE (low energy) clocks
	CMU_ClockEnable(cmuClock_HFLE, true); // Necessary for accessing LE modules
	CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFRCO); // Set a reference clock
	// Enable clocks for LEUART0
	CMU_ClockEnable(cmuClock_LEUART0, true);
	CMU_ClockDivSet(cmuClock_LEUART0, cmuClkDiv_1); // Don't prescale LEUART clock
	CMU->LFRCOCTRL	= CMU->LFRCOCTRL & (~(CMU_LFRCOCTRL_ENDEM | CMU_LFRCOCTRL_ENCHOP));//Setting the ENCHOP and/or EN- DEM bitfields to 1 in the CMU_LFRCOCTRL register will improve the average LFRCO frequency accuracy at the cost of a worse cycle- to-cycle accuracy.
	usartInit = LEUART_INIT_DEFAULT;
	usartInit.baudrate = baudrate;
	usartInit.databits = (LEUART_Databits_TypeDef)(option & _LEUART_CTRL_DATABITS_MASK);
	usartInit.parity = (LEUART_Parity_TypeDef)(option & _LEUART_CTRL_PARITY_MASK);
	usartInit.stopbits = (LEUART_Stopbits_TypeDef)(option & _LEUART_CTRL_STOPBITS_MASK);
	LEUART_Init(usart, &usartInit);
	LEUART_RxDmaInEM2Enable(usart, true);
	LEUART_TxDmaInEM2Enable(usart, true);
	pinMode(tx, OUTPUT_UP);
	pinMode(rx, INPUT_PULLUP);
	if (this->_bFree == true)
		free(this->_buffer);
	this->_buffer = (uint8_t *)b;
	this->_buffer_len = len;
	this->_bFree = bFree;
	rx_loc = rx_loc ? rx_loc - 1 : MAX_VALID_PINLOCATION;// Now we have to shift rx location back, it always stands before tx location
	usart->ROUTELOC0 = tx_loc << _LEUART_ROUTELOC0_TXLOC_SHIFT | rx_loc << _LEUART_ROUTELOC0_RXLOC_SHIFT;
	usart->ROUTEPEN = LEUART_ROUTEPEN_TXPEN | LEUART_ROUTEPEN_RXPEN;
	NVIC_ClearPendingIRQ(LEUART0_IRQn);
	NVIC_EnableIRQ(LEUART0_IRQn);
	if ((channel = this->_channel) > 0x0)
		LdmaClass::transferStop(channel);
	if (len != 0x0) {
		channel = LdmaClass::receivedCyclical((void *)&usart->RXDATA, b, len, ldmaPeripheralSignal_LEUART0_RXDATAV, ldmaCtrlSizeByte, &this->_arrayReceivedCyclical);
		this->_channel = channel;
	}
	else
		this->_channel = -1;
	this->_baudrate = LEUART_BaudrateGet(usart);
	zunoSyncReleseWrite(&gSyncLeUart, SyncMasterLeUart, &this->_lpKey);
	if (len != 0x0 && channel < 0x0) {
		this->end();
		return (ZunoErrorDmaLimitChannel);
	}
	return (ZunoErrorOk);
}

/* Preinstantiate Objects */
LeUartClass LeUart;

// //For printf
// ssize_t write(int fd, const void *buf, size_t count) {
// 	switch (fd) {
// 		case 0:
// 			return (Serial0.write((const uint8_t *)buf, count));
// 			break ;
// 		case 1:
// 			return (Serial1.write((const uint8_t *)buf, count));
// 			break ;
// 		case 2:
// 			return (Serial.write((const uint8_t *)buf, count));
// 			break ;
// 		default:
// 			break ;
// 	}
// 	return (-1);
// }

#endif//#if defined(LEUART_COUNT) && (LEUART_COUNT > 0)