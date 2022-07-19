#include "PN7160.h"
#include "Status.h"

ZUNO_ENABLE(LOGGING_DBG);

byte dimmerValue=0;
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE);
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(&dimmerValue,NULL));

#define MY_SERIAL							Serial0

uint8_t bCart = false;

static const PN7160ClassEeprom_t _eeprom_set = {{__TIMESTAMP__}};


PN7160Class nfc(&Wire, SCL, SDA, 0x7, 0x8);

static void _event(void) {
	bCart = true;
}

uint32_t loop_count = 0; // the variable that illustrates that RAM is alive during FLiRS mode too

void _wakeHandler(void){
	MY_SERIAL.print("wake time:");
	MY_SERIAL.println(millis());
	MY_SERIAL.print("loop count =");
	MY_SERIAL.println(loop_count);
	MY_SERIAL.print("WAKEUP REASON:");
	MY_SERIAL.println(zunoGetWakeReason(), HEX);
}

static void _error(const char *str) {
	MY_SERIAL.printf(str, GetLastStatus());
	while (0xFF)
		delay(0x40);
}

void setup(void) {
	uint16_t								ms;
	PN7160ClassEeprom_t						eeprom;
	uint8_t									bClear;

	// while (true)
	// 	delay(200);
	MY_SERIAL.begin(115200);
	MY_SERIAL.print("BOOT REASON:");
	MY_SERIAL.println(zunoGetWakeReason(), HEX);
	zunoAttachSysHandler(ZUNO_HANDLER_WUP, 0, (void*) &_wakeHandler);
	pinMode(LED_BUILTIN, OUTPUT);
	MY_SERIAL.print("\n\n");
	bClear = false;
	if (nfc.connect(bClear) != true)
		_error("Error: cannot connect to NFC PN7160 device - 0x%lx\n");
	MY_SERIAL.print("Connect to NFC PN7160                                     OK\n\n");
	MY_SERIAL.printf("Hardware version number:         0x%02X\n", nfc.getHardwareVersion());
	MY_SERIAL.printf("ROM Code version number:         0x%02X\n", nfc.getRomVersion());
	MY_SERIAL.printf("Firmware major version:          0x%02X\n", nfc.getFwMajorVersion());
	MY_SERIAL.printf("Firmware minor version:          0x%02X\n\n", nfc.getFwMinorVersion());
	if (nfc.getDuration(&ms) != true)
		_error("Error: cannot get total duration - 0x%lx\n");
	MY_SERIAL.printf("Total duration ms:               %4d\n\n", ms);
	if (nfc.getEEPROM(&eeprom) == true) {
		MY_SERIAL.print("Read EEPROM                                               OK\n");
		if (bClear == true || memcmp(&_eeprom_set, &eeprom, sizeof(_eeprom_set)) != 0x0) {
			MY_SERIAL.print("Start configure to NFC PN7160                              OK\n");
			if (nfc.setDuration(256) != true)
				_error("Error: cannot configure total delay - 0x%lx\n");
			MY_SERIAL.print("Configure NFC PN7160 total delay                           OK\n");
			if (nfc.setPowerMode(PN7160_CLASS_POWER_MODE_STANDBY) != true)
				_error("Error: cannot configure power mode - 0x%lx\n");
			MY_SERIAL.print("Configure NFC PN7160 power mode                            OK\n");
			if (nfc.setPowerTransmitter(PN7160_CLASS_POWER_TRANSMITTER_3_3V) != true)
				_error("Error: cannot configure power transmitter - 0x%lx\n");
			MY_SERIAL.print("Configure power transmitter                                OK\n");
			if (nfc.setRf() != true)
				_error("Error: cannot configure RF - 0x%lx\n");
			MY_SERIAL.print("Configure RF                                               OK\n");
			memcpy(&eeprom, &_eeprom_set, sizeof(eeprom));
			if (nfc.setEEPROM(&eeprom) != true)
				_error("Error: cannot write EEPROM - 0x%lx\n");
			MY_SERIAL.print("Write EEPROM                                               OK\n");
			if (nfc.applySettings() != true)
				_error("Error: cannot new settings apply - 0x%lx\n");
			MY_SERIAL.print("New settings apply                                         OK\n");
			MY_SERIAL.print("Finish configure to NFC PN7160                             OK\n\n");
		}
	}
	else
		_error("Error: cannot read EEPROM - 0x%lx\n");
	if (nfc.configureMode() != true)
		_error("Error: cannot configure mode - 0x%lx\n");
	MY_SERIAL.print("Configure mode                                            OK\n");
	if (nfc.discovery(_event) != true)
		_error("Error: cannot start discovery - 0x%lx\n");
	MY_SERIAL.print("Start discovery                                           OK\n");
	// static const PN7150ClassCmdGetConfig_t NCIReadDuration = PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT(PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_TOTAL_DURATION, 7);
	// Serial0.dumpPrint((uint8_t *)&NCIReadDuration, sizeof(NCIReadDuration.header) + NCIReadDuration.header.len, sizeof(NCIReadDuration.header) + NCIReadDuration.header.len);
}

static void _event_removal(uint8_t protocol) {
	switch(protocol) {
		case PN7160_CLASS_PROT_T1T:
		case PN7160_CLASS_PROT_T2T:
		case PN7160_CLASS_PROT_T3T:
		case PN7160_CLASS_PROT_ISODEP:
			MY_SERIAL.printf("Remote T%dT card removal.\n", protocol);
			break;
		case PN7160_CLASS_PROT_T5T:
			MY_SERIAL.print("Remote T5T card removal.\n");
			break;
		case PN7160_CLASS_PROT_MIFARE:
			MY_SERIAL.print("Remote MIFARE card removal.\n");
			break;
		default:
			MY_SERIAL.print("Undetermined target.\n");
			break;
	}
}

static void _processing(void) {
	size_t									len;
	size_t									BitRate;
	uint8_t									count;
	uint8_t									index;
	uint8_t									buffer[0x20];

	MY_SERIAL.print("Processing START                                           OK\n\n");
	if ((count = nfc.info()) != 0x0) {
		MY_SERIAL.print("Processing                                                 OK\n\n");
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
					MY_SERIAL.printf("Remote T%dT card activated.\n", nfc.infoProtocol(index));
					break;
				case PN7160_CLASS_PROT_T5T:
					MY_SERIAL.print("Remote T5T card activated.\n");
					break;
				case PN7160_CLASS_PROT_MIFARE:
					MY_SERIAL.print("Remote MIFARE card activated.\n");
					break;
				default:
					MY_SERIAL.print("Undetermined target.\n");
					break;
			}
			if ((len = nfc.infoSens(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				MY_SERIAL.print("Sens: ");
				MY_SERIAL.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.infoNfcid(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				MY_SERIAL.print("Nfcid: ");
				MY_SERIAL.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.infoSel(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				MY_SERIAL.print("Sel: ");
				MY_SERIAL.dumpPrint(&buffer[0x0], len, len);
			}
			if ((BitRate = nfc.infoBitRate(index)) != 0x0)
				MY_SERIAL.printf("Bitrate: %d kbps\n", BitRate);
			if ((len = nfc.infoId(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				MY_SERIAL.print("Id: ");
				MY_SERIAL.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.infoAfi(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				MY_SERIAL.print("Afi: ");
				MY_SERIAL.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.infoDsfid(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				MY_SERIAL.print("Dsfid: ");
				MY_SERIAL.dumpPrint(&buffer[0x0], len, len);
			}
			if ((len = nfc.ppsePaymentSystem(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
				MY_SERIAL.print("Payment system: ");
				MY_SERIAL.write(&buffer[0x0], len);
				MY_SERIAL.print("\n");
			}
			if ((len = nfc.ppseCardNumber(index, &buffer[0x0], sizeof(buffer))) == 0x8)
				MY_SERIAL.printf("Card number: %02X%02X %02X%02X %02X%02X %02X%02X\n", buffer[0x0], buffer[0x1], buffer[0x2], buffer[0x3], buffer[0x4], buffer[0x5], buffer[0x6], buffer[0x7]);
			if ((len = nfc.ppseExpirationDate(index, &buffer[0x0], sizeof(buffer))) == 0x2)
				MY_SERIAL.printf("Expiration Date: %02X/%02X\n", buffer[0x0], buffer[0x1]);
			index++;
		}
		MY_SERIAL.print("\n");
		delay(500);
	}
	else
		MY_SERIAL.print("Processing                                                 FALID\n");
	nfc.infoWaitRemoval(_event_removal);
	MY_SERIAL.print("Card removal                                               OK\n");
	if (nfc.discoveryRestart(_event) == true)
		MY_SERIAL.print("Restart discovery                                          OK\n");
	else
		MY_SERIAL.print("Restart discovery                                          FALID\n");
}

void loop(void) {
	if (bCart == true) {
		_processing();
		bCart = false;
	}
	if(zunoIsSleepLocked()){
		// Here we do all sleep uninterruptable logic
		analogWrite(LED_BUILTIN, dimmerValue); // Apply dimmer value from controller to builtin LED
		MY_SERIAL.print("go sleep time:");
		MY_SERIAL.println(millis()); // Print moment when we are ready to go to sleep
		MY_SERIAL.print("loop count =");
		MY_SERIAL.println(loop_count);
		zunoSendDeviceToSleep(); // We don't need parameter for FLiRS here, Z-Uno will ingore parameter anyway
	}
	// Here you can do something that could be interrupted by sleep mode
	loop_count++; // Increment variable
}