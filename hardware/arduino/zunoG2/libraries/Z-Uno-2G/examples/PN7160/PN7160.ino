#include "PN7160.h"
#include "Status.h"

ZUNO_ENABLE(
	LOGGING_UART=Serial0
	LOGGING_DBG
	DBG_CONSOLE_BAUDRATE=921600
	);

byte dimmerValue=0;
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE);
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(&dimmerValue,NULL));

static const PN7160ClassEeprom_t _eeprom_set = {{__TIMESTAMP__}};

PN7160Class nfc(_event, &Wire, SCL, SDA, 17, 19);

static void _event(void) {
	nfc.eventIrq();
}

uint32_t loop_count = 0; // the variable that illustrates that RAM is alive during FLiRS mode too

void _wakeHandler(void){
	LOGGING_UART.print("wake time:");
	LOGGING_UART.println(millis());
	LOGGING_UART.print("loop count =");
	LOGGING_UART.println(loop_count);
	LOGGING_UART.print("WAKEUP REASON:");
	LOGGING_UART.println(zunoGetWakeReason(), HEX);
}

void _error() {
	while (0xFF) {
		#ifdef LOGGING_DBG
		LOGGING_UART.print("Feill!!!\n");
		#endif
		delay(500);
	}
}


void setup(void) {
	uint16_t								ms;
	PN7160ClassEeprom_t						eeprom;

	if (nfc.connect(true) != true) {
		#ifdef LOGGING_DBG
		LOGGING_UART.printf("Error: cannot connect to NFC PN7160 device - 0x%lx\n", GetLastStatus());
		#endif
		_error();
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.print("Connect to NFC PN7160                                     OK\n\n");
	LOGGING_UART.printf("Hardware version number:         0x%02X\n", nfc.getHardwareVersion());
	LOGGING_UART.printf("ROM Code version number:         0x%02X\n", nfc.getRomVersion());
	LOGGING_UART.printf("Firmware major version:          0x%02X\n", nfc.getFwMajorVersion());
	LOGGING_UART.printf("Firmware minor version:          0x%02X\n\n", nfc.getFwMinorVersion());
	if (nfc.getDuration(&ms) != true)
		LOGGING_UART.printf("Error: cannot get total duration - 0x%lx\n", GetLastStatus());
	LOGGING_UART.printf("Total duration ms:               %4d\n\n", ms);
	#endif
	if (nfc.setDuration(255) != true) {
		#ifdef LOGGING_DBG
		LOGGING_UART.printf("Error: cannot configure total delay - 0x%lx\n", GetLastStatus());
		#endif
		_error();
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.print("Configure NFC PN7160 total delay                           OK\n");
	#endif
	if (nfc.setPowerMode(PN7160_CLASS_POWER_MODE_STANDBY) != true) {
		#ifdef LOGGING_DBG
		LOGGING_UART.printf("Error: cannot configure power mode - 0x%lx\n", GetLastStatus());
		#endif
		_error();
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.print("Configure NFC PN7160 power mode                            OK\n");
	#endif
	if (nfc.getEEPROM(&eeprom) == false) {
		#ifdef LOGGING_DBG
		LOGGING_UART.printf("Error: cannot read EEPROM - 0x%lx\n", GetLastStatus());
		#endif
		_error();
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.print("Read EEPROM                                               OK\n");
	#endif
	if (memcmp(&_eeprom_set, &eeprom, sizeof(_eeprom_set)) != 0x0) {
		#ifdef LOGGING_DBG
		LOGGING_UART.print("Start configure to NFC PN7160                              OK\n");
		#endif
		if (nfc.setCore() != true) {
			#ifdef LOGGING_DBG
			LOGGING_UART.printf("Error: cannot configure CORE - 0x%lx\n", GetLastStatus());
			#endif
			_error();
		}
		#ifdef LOGGING_DBG
		LOGGING_UART.print("Configure CORE                                          OK\n");
		#endif
		if (nfc.setPowerTransmitter(PN7160_CLASS_POWER_TRANSMITTER_4_75_V) != true) {
			#ifdef LOGGING_DBG
			LOGGING_UART.printf("Error: cannot configure power transmitter - 0x%lx\n", GetLastStatus());
			#endif
			_error();
		}
		#ifdef LOGGING_DBG
		LOGGING_UART.print("Configure power transmitter                                OK\n");
		#endif
		if (nfc.setRf() != true) {
			#ifdef LOGGING_DBG
			LOGGING_UART.printf("Error: cannot configure RF - 0x%lx\n", GetLastStatus());
			#endif
			_error();
		}
		#ifdef LOGGING_DBG
		LOGGING_UART.print("Configure RF                                               OK\n");
		#endif
		memset(&eeprom, 0x0, sizeof(eeprom));
		memcpy(&eeprom, &_eeprom_set, sizeof(_eeprom_set));
		if (nfc.setEEPROM(&eeprom) != true) {
			#ifdef LOGGING_DBG
			LOGGING_UART.printf("Error: cannot write EEPROM - 0x%lx\n", GetLastStatus());
			#endif
			_error();;
		}
		#ifdef LOGGING_DBG
		LOGGING_UART.print("Write EEPROM                                               OK\n");
		LOGGING_UART.print("Finish configure to NFC PN7160                             OK\n\n");
		#endif
	}
	if (nfc.applySettings() != true) {
		#ifdef LOGGING_DBG
		LOGGING_UART.printf("Error: cannot new settings apply - 0x%lx\n", GetLastStatus());
		#endif
		_error();
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.print("settings apply                                         OK\n");
	#endif
	if (nfc.configureMode() != true) {
		#ifdef LOGGING_DBG
		LOGGING_UART.printf("Error: cannot configure mode - 0x%lx\n", GetLastStatus());
		#endif
		_error();
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.print("Configure mode                                            OK\n");
	#endif
	if (nfc.discovery() != true) {
		#ifdef LOGGING_DBG
		LOGGING_UART.printf("Error: cannot start discovery - 0x%lx\n", GetLastStatus());
		#endif
		_error();
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.print("Start discovery                                           OK\n");
	#endif
}

static void _event_removal(uint8_t protocol) {
	switch(protocol) {
		case PN7160_CLASS_PROT_T1T:
		case PN7160_CLASS_PROT_T2T:
		case PN7160_CLASS_PROT_T3T:
		case PN7160_CLASS_PROT_ISODEP:
			LOGGING_UART.printf("Remote T%dT card removal.\n", protocol);
			break;
		case PN7160_CLASS_PROT_T5T:
			LOGGING_UART.print("Remote T5T card removal.\n");
			break;
		case PN7160_CLASS_PROT_MIFARE:
			LOGGING_UART.print("Remote MIFARE card removal.\n");
			break;
		default:
			LOGGING_UART.print("Undetermined target.\n");
			break;
	}
}

static void _processing(void) {
	size_t									len;
	size_t									BitRate;
	uint8_t									count;
	uint8_t									index;
	uint8_t									buffer[0x20];

	LOGGING_UART.print("Processing START                                           OK\n\n");
	if ((count = nfc.info()) != 0x0) {
		LOGGING_UART.print("Processing                                                 OK\n\n");
		index = 0x0;
		while (index < count) {
			nfc.ppse(index);
			index++;
		}
		index = 0x0;
		while (index < count) {
			switch(nfc.infoProtocol(index)) {
				case PN7160_CLASS_PROT_T1T:
				case PN7160_CLASS_PROT_T2T:
				case PN7160_CLASS_PROT_T3T:
				case PN7160_CLASS_PROT_ISODEP:
					LOGGING_UART.printf("Remote T%dT card activated.\n", nfc.infoProtocol(index));
					break;
				case PN7160_CLASS_PROT_T5T:
					LOGGING_UART.print("Remote T5T card activated.\n");
					break;
				case PN7160_CLASS_PROT_MIFARE:
					LOGGING_UART.print("Remote MIFARE card activated.\n");
					break;
				default:
					LOGGING_UART.print("Undetermined target.\n");
					break;
			}
			if ((len = nfc.infoSens(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				LOGGING_UART.print("Sens: ");
				LOGGING_UART.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.infoNfcid(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				LOGGING_UART.print("Nfcid: ");
				LOGGING_UART.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.infoSel(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				LOGGING_UART.print("Sel: ");
				LOGGING_UART.dumpPrint(&buffer[0x0], len, len);
			}
			if ((BitRate = nfc.infoBitRate(index)) != 0x0)
				LOGGING_UART.printf("Bitrate: %d kbps\n", BitRate);
			if ((len = nfc.infoId(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				LOGGING_UART.print("Id: ");
				LOGGING_UART.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.infoAfi(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				LOGGING_UART.print("Afi: ");
				LOGGING_UART.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.infoDsfid(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				LOGGING_UART.print("Dsfid: ");
				LOGGING_UART.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.ppsePaymentSystem(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				LOGGING_UART.print("Payment system: ");
				LOGGING_UART.write(&buffer[0x0], len);
				LOGGING_UART.print("\n");
			}
			if ((len = nfc.ppseCardNumber(index, &buffer[0x0], sizeof(buffer))) == 0x8)
				LOGGING_UART.printf("Card number: %02X%02X %02X%02X %02X%02X %02X%02X\n", buffer[0x0], buffer[0x1], buffer[0x2], buffer[0x3], buffer[0x4], buffer[0x5], buffer[0x6], buffer[0x7]);
			if ((len = nfc.ppseExpirationDate(index, &buffer[0x0], sizeof(buffer))) == 0x2)
				LOGGING_UART.printf("Expiration Date: %02X/%02X\n", buffer[0x0], buffer[0x1]);
			index++;
		}
		LOGGING_UART.print("\n");
		delay(500);
	}
	else
		LOGGING_UART.print("Processing                                                 FALID\n");
	nfc.infoWaitRemoval(_event_removal);
	LOGGING_UART.print("Card removal                                               OK\n");
	if (nfc.discoveryRestart() == true)
		LOGGING_UART.print("Restart discovery                                          OK\n");
	else
		LOGGING_UART.print("Restart discovery                                          FALID\n");
}

void loop(void) {
	bool					out;

	zunoEnterCritical();
	out = nfc.eventIrqIs();
	zunoExitCritical();
	if (out == true)
		_processing();
	if(zunoIsSleepLocked()){
		// Here we do all sleep uninterruptable logic
		analogWrite(LED_BUILTIN, dimmerValue); // Apply dimmer value from controller to builtin LED
		LOGGING_UART.print("go sleep time:");
		LOGGING_UART.println(millis()); // Print moment when we are ready to go to sleep
		LOGGING_UART.print("loop count =");
		LOGGING_UART.println(loop_count);
		zunoSendDeviceToSleep(); // We don't need parameter for FLiRS here, Z-Uno will ingore parameter anyway
	}
	// Here you can do something that could be interrupted by sleep mode
	loop_count++; // Increment variable
}
