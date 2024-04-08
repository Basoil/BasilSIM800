#include <BasilSIM800.h>
#include "Arduino.h"



SIM800::SIM800(HardwareSerial *gsm,uint32_t baudRate = 115200, uint8_t rx_pin = 0, uint8_t tx_pin = 0) {
	
	_hardwareSerial = gsm;
	_hardwareSerial -> begin(baudRate, SERIAL_8N1, rx_pin, tx_pin);

}

bool SIM800::init() {
	
	_buffer.reserve(255);

	
	_hardwareSerial -> write("ATE1&W");
	_hardwareSerial -> write('\r\n');	
	_readSerial(10000);
	_hardwareSerial -> write("ATV1&W");
	_hardwareSerial -> write('\r\n');	
	_readSerial(10000);
	
	_hardwareSerial -> write("AT\r\n");
	_buffer = _readSerial(10000);
	if ((_buffer.indexOf("OK")) != -1) 
	return true; else return false;
	
}

bool SIM800::sendSMS(const char *number, const char *text) {
	_hardwareSerial -> write("AT+CMGF=1\r");
	_readSerial();
	_hardwareSerial -> write("AT+CMGS=\"");
	_hardwareSerial -> write(number);
	_hardwareSerial -> write("\"\r");
	_readSerial();
	_hardwareSerial -> write(text);
	_hardwareSerial -> write("\r");
	_readSerial();
	_hardwareSerial -> write((char)26);	
	_buffer = _readSerial(60000);
	if ((_buffer.indexOf("ER")) != -1) {
		return true;
	} else if ((_buffer.indexOf("CMGS")) != -1) {
		return false;
	  } else {
		return true;
	  }
	
}

String SIM800::readSMS(uint8_t count) {
return "OK";
}



String SIM800::_readSerial(uint64_t timeOut)
{
	
	uint64_t timeOld = millis();

	while (!_hardwareSerial->available() && !(millis() > timeOld + timeOut))
	{
		delay(13);
	}

	String str;

	while(_hardwareSerial->available())
	{	 
		 if (_hardwareSerial->available()>0)
		{
			str += (char) _hardwareSerial->read();
		}
	}	
 Serial.println(str);
	return str;

}