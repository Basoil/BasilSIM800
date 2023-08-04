#include <BasilSIM800.h>


SIM800::SIM800(HardwareSerial *gsm,uint32_t baudRate, uint8_t rx_pin, uint8_t tx_pin) {
	_hardwareSerial = gsm;
	_rx_pin = rx_pin;
	_tx_pin = tx_pin;
	_baudRate = baudRate;
}

void SIM800::init() {
	_hardwareSerial -> begin(_baudRate, SERIAL_8N1, _rx_pin, _tx_pin);
	_hardwareSerial -> println("AT0");
}

bool SIM800::sendSMS(const char *number, const char *text) {
	_hardwareSerial -> write("AT+GMGS=\"");
	_hardwareSerial -> write(number);
	_hardwareSerial -> write("\"\r");
	_hardwareSerial -> write(text);
	_hardwareSerial -> write((char)26);
	_hardwareSerial -> write('\n');		
return true;
}

String SIM800::readSMS(uint8_t count) {
return "OK";
}

