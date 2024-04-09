#include <BasilSIM800.h>
#include "Arduino.h"


SIM800::SIM800(HardwareSerial *gsm,uint32_t baudRate = 115200, uint8_t rx_pin = 0, uint8_t tx_pin = 0, bool log = false) {
	
	_logger = log;
	_hardwareSerial = gsm;
	_hardwareSerial -> begin(baudRate, SERIAL_8N1, rx_pin, tx_pin);
	_hardwareSerial -> setTimeout(250);
}

String SIM800::sendCmd(char* command) {
	
	if (_logger){
		Serial.print(" SIM800 command:");
		Serial.println(command);
	}
	
	_hardwareSerial -> write(command);
	_hardwareSerial -> write("\r");
	_readSerial(10000);
	return _buffer;
}


bool SIM800::init() {
	
	_buffer.reserve(255);
	sendCmd("ATE0");
	sendCmd("AT+CMGF=1");
	sendCmd("AT+CNMI=2,1,0,0,0");
	sendCmd("AT+CREG=1");
	sendCmd("AT");
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

String SIM800::readSMS(uint8_t _count) {
	
	//AT+CMGR=<index>[,<mode>]
	char _cmd[25] = { 0 };
	snprintf(_cmd, sizeof(_cmd), "AT+CMGR=%d\r", _count);

    sendCmd(_cmd);	
	return _buffer;
}



void SIM800::deleteAllSMS() {
	sendCmd("AT+CMGDA=\"DEL ALL\"\r");
}


uint8_t SIM800::isNewSMS() {
	sendCmd("AT+CMGL=\"ALL\"");
	//_readSerial(30000);
	
	Serial.println("isNewSMS():");
	_buffer = sendCmd("AT+CPMS?");
	
	int8_t _start = _buffer.indexOf("+CPMS:");
	Serial.print("_start = "); 
	Serial.println(_start);
	
	// Если нашли ответ:
	// +CPMS: "ME",11,100,"ME",11,100,"ME",11,100
	if (_start != -1) {
		_start += 12;
		int8_t _finish = _buffer.indexOf(",",_start + 1);
		Serial.print("_finish = ");
		Serial.println(_finish);
		String _num = _buffer.substring(_start, _finish);
		//Serial.println(_num);
		return _num.toInt();
	}
	
	return 0;
}


String SIM800::_readSerial(uint64_t timeOut)
{
	uint64_t timeOld = millis();
	while (!_hardwareSerial->available() && !(millis() > timeOld + timeOut))
	{
		delay(10);
	}

	if(_hardwareSerial->available()) { _buffer = _hardwareSerial->readString(); }
	_buffer.trim();
		if(_logger) {
 			Serial.print(" SIM800 answer [");
 			Serial.print(_buffer);
 			Serial.println("]");
		}
	return _buffer;
}