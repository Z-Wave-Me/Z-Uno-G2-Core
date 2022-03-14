#include "PN7150.h"

ZUNO_ENABLE(LOGGING_DBG);

byte dimmerValue=0;
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE);
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(&dimmerValue,NULL));

#define MY_SERIAL							Serial0

uint8_t bCart = false;

static const uint8_t _eeprom_set[PN7150_CLASS_EEPROM_SIZE] = "__TIMESTAMP__";

PN7150Class nfc(&Wire, SCL, SDA, 0x7, 0x8);

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

void setup(void) {
	PN7150ClassStatus_t						ret;
	uint16_t								ms;
	uint8_t									eeprom[PN7150_CLASS_EEPROM_SIZE];
	PN7150ClassPowerTransmitter_t			power_transmitter;

	MY_SERIAL.begin(115200);
	MY_SERIAL.print("BOOT REASON:");
	MY_SERIAL.println(zunoGetWakeReason(), HEX);
	zunoAttachSysHandler(ZUNO_HANDLER_WUP, 0, (void*) &_wakeHandler);
	pinMode(LED_BUILTIN, OUTPUT);
	MY_SERIAL.print("\n\n");
	if ((ret = nfc.connect(false) ) != PN7150ClassStatusOk && ret != PN7150ClassStatusClearConfig) {
		MY_SERIAL.printf("Error: cannot connect to NXPNCI device - %d\n", ret);
		while (0xFF)
			delay(0x1);
	}
	MY_SERIAL.print("Connect to NXPNCI device                                  OK\n\n");
	MY_SERIAL.printf("Hardware version number:         0x%02X\n", nfc.getHardwareVersion());
	MY_SERIAL.printf("ROM Code version number:         0x%02X\n", nfc.getRomVersion());
	MY_SERIAL.printf("Firmware major version:          0x%02X\n", nfc.getFwMajorVersion());
	MY_SERIAL.printf("Firmware minor version:          0x%02X\n\n", nfc.getFwMinorVersion());
	if (nfc.getDuration(&ms) == PN7150ClassStatusOk)
		MY_SERIAL.printf("Total duration %d ms.\n", ms);
	if (nfc.getPowerTransmitter(&power_transmitter) == PN7150ClassStatusOk) {
		switch (power_transmitter) {
			case PN7150ClassPowerTransmitter_2_7_V:
				MY_SERIAL.print("Power transmitter 2.7V.\n");
				break;
			case PN7150ClassPowerTransmitter_3_0_V:
				MY_SERIAL.print("Power transmitter 3.0V.\n");
				break;
			case PN7150ClassPowerTransmitter_3_1_V:
				MY_SERIAL.print("Power transmitter 3.1V.\n");
				break;
			case PN7150ClassPowerTransmitter_3_3_V:
				MY_SERIAL.print("Power transmitter 3.3V.\n");
				break;
			case PN7150ClassPowerTransmitter_3_6_V:
				MY_SERIAL.print("Power transmitter 3.6V.\n");
				break;
			case PN7150ClassPowerTransmitter_4_5_V:
				MY_SERIAL.print("Power transmitter 4.5V.\n");
				break;
			case PN7150ClassPowerTransmitter_4_7_V:
				MY_SERIAL.print("Power transmitter 4.7V.\n");
				break;
			default:
				MY_SERIAL.print("Power transmitter unknown.\n");
				break;
		}
	}
	if (ret == PN7150ClassStatusClearConfig || nfc.getEEPROM(&eeprom[0x0]) == PN7150ClassStatusOk) {
		if (memcmp(&_eeprom_set[0x0], &eeprom[0x0], sizeof(_eeprom_set)) != 0x0) {
			MY_SERIAL.print("\nStart configure to NXPNCI device                           OK\n");
			if ((ret = nfc.setDuration(256)) != PN7150ClassStatusOk) {
				MY_SERIAL.printf("Error: cannot configure NXPNCI total delay - %d\n", ret);
				while (0xFF)
					delay(0x1);
			}
			MY_SERIAL.print("Configure NXPNCI total delay                               OK\n");
			if ((ret = nfc.setPowerMode(PN7150ClassPowerModeStandby)) != PN7150ClassStatusOk) {
				MY_SERIAL.printf("Error: cannot configure NXPNCI power mode - %d\n", ret);
				while (0xFF)
					delay(0x1);
			}
			MY_SERIAL.print("Configure NXPNCI power mode                                OK\n");
			memcpy(&eeprom[0x0], &_eeprom_set[0x0], sizeof(eeprom));
			if ((ret = nfc.setEEPROM(&eeprom[0x0])) != PN7150ClassStatusOk) {
				MY_SERIAL.printf("Error: cannot write NXPNCI EEPROM - %d\n", ret);
				while (0xFF)
					delay(0x1);
			}
			MY_SERIAL.print("Write EEPROM                                               OK\n");
			if ((ret = nfc.setPowerTransmitter(PN7150ClassPowerTransmitter_4_7_V)) != PN7150ClassStatusOk) {
				MY_SERIAL.printf("Error: cannot configure power transmitter - %d\n", ret);
				while (0xFF)
					delay(0x1);
			}
			MY_SERIAL.print("Configure power transmitter                                OK\n");
			if ((ret = nfc.setRf()) != PN7150ClassStatusOk) {
				MY_SERIAL.printf("Error: cannot configure RF - %d\n", ret);
				while (0xFF)
					delay(0x1);
			}
			MY_SERIAL.print("Configure RF                                               OK\n");
			if ((ret = nfc.applySettings()) != PN7150ClassStatusOk) {
				MY_SERIAL.printf("Error: cannot new settings apply - %d\n", ret);
				while (0xFF)
					delay(0x1);
			}
			MY_SERIAL.print("New settings apply                                         OK\n");
			MY_SERIAL.print("Finish configure to NXPNCI device                          OK\n\n");
		}
	}
	if ((ret = nfc.configureMode() )!= PN7150ClassStatusOk) {
		MY_SERIAL.printf("Error: cannot configure mode NXPNCI - %d\n", ret);
		while (0xFF)
			delay(0x1);
	}
	MY_SERIAL.print("\nConfigure mode                                             OK\n");
	if ((ret = nfc.discovery(_event)) != PN7150ClassStatusOk) {
		MY_SERIAL.printf("Error: cannot start discovery - %d\n", ret);
		while (0xFF)
			delay(0x1);
	}
	MY_SERIAL.print("Start discovery                                            OK\n");
	// static const PN7150ClassCmdGetConfig_t NCIReadDuration = PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT(PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_TOTAL_DURATION, 7);
	// Serial0.dumpPrint((uint8_t *)&NCIReadDuration, sizeof(NCIReadDuration.header) + NCIReadDuration.header.len, sizeof(NCIReadDuration.header) + NCIReadDuration.header.len);
}

static void _event_removal(uint8_t protocol) {
	switch(protocol) {
		case PN7150_CLASS_PROT_T1T:
		case PN7150_CLASS_PROT_T2T:
		case PN7150_CLASS_PROT_T3T:
		case PN7150_CLASS_PROT_ISODEP:
			MY_SERIAL.printf("Remote T%dT card removal.\n", protocol);
			break;
		case PN7150_CLASS_PROT_T5T:
			MY_SERIAL.print("Remote T5T card removal.\n");
			break;
		case PN7150_CLASS_PROT_MIFARE:
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
	PN7150ClassStatus_t						ret;

	if (nfc.info(&count) == PN7150ClassStatusOk) {
		MY_SERIAL.print("Processing                                                 OK\n\n");
		index = 0x0;
		while (index++ < count) {
			if ((ret = nfc.ppse(index)) == PN7150ClassStatusOk) {
				if ((len = nfc.ppsePaymentSystem(index, &buffer[0x0], sizeof(buffer))) != 0x0) {
					MY_SERIAL.print("Payment system: ");
					MY_SERIAL.write(&buffer[0x0], len);
					MY_SERIAL.print("\n");
				}
				if ((len = nfc.ppseCardNumber(index, &buffer[0x0], sizeof(buffer))) == 0x8)
					MY_SERIAL.printf("Card number: %02X%02X %02X%02X %02X%02X %02X%02X\n", buffer[0x0], buffer[0x1], buffer[0x2], buffer[0x3], buffer[0x4], buffer[0x5], buffer[0x6], buffer[0x7]);
				if ((len = nfc.ppseExpirationDate(index, &buffer[0x0], sizeof(buffer))) == 0x2)
					MY_SERIAL.printf("Expiration Date: %02X/%02X\n", buffer[0x0], buffer[0x1]);
				MY_SERIAL.print("\n");
			}
			switch(nfc.infoProtocol(index)) {
				case PN7150_CLASS_PROT_T1T:
				case PN7150_CLASS_PROT_T2T:
				case PN7150_CLASS_PROT_T3T:
				case PN7150_CLASS_PROT_ISODEP:
					MY_SERIAL.printf("Remote T%dT card activated.\n", nfc.infoProtocol(index));
					break;
				case PN7150_CLASS_PROT_T5T:
					MY_SERIAL.print("Remote T5T card activated.\n");
					break;
				case PN7150_CLASS_PROT_MIFARE:
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
		}
		MY_SERIAL.print("\n");
		delay(500);
	}
	else
		MY_SERIAL.print("Processing                                                 FALID\n");
	if (nfc.infoWaitRemoval(_event_removal) == PN7150ClassStatusOk)
		MY_SERIAL.print("Card removal                                               OK\n");
	else
		MY_SERIAL.print("Card removal                                               FALID\n");
	if (nfc.discoveryRestart(_event) == PN7150ClassStatusOk)
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