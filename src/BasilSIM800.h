#ifndef _BasilSIM800_h
#define _BasilSIM800_h

#include <Arduino.h>
#include <HardwareSerial.h>



class SIM800 { 
	public:
	SIM800(HardwareSerial *gsm, uint32_t baudRate, uint8_t rx, uint8_t tx);
	bool init();
	bool sendSMS(const char *number, const char *text);
	String readSMS(uint8_t count);
	
	private:
	String _readSerial(uint64_t timeOut = 5000);
	HardwareSerial *_hardwareSerial;
	String _buffer;
	
	
};

#endif

