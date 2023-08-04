#include <BasilSIM800.h>


SIM800::SIM800(HardwareSerial *gsm,uint32_t baudRate, uint8_t rx_pin, uint8_t tx_pin) {
	_hardwareSerial = gsm;
	_rx_pin = rx_pin;
	_tx_pin = tx_pin;
	_baudRate = baudRate;
}

void SIM800::init() {
	_hardwareSerial -> begin(_baudRate, SERIAL_8N1, _rx_pin, _tx_pin);
	
}

bool SIM800::sendSMS(String number, String text) {
return true;
}

String SIM800::readSMS(uint8_t count) {
return "OK";
}

