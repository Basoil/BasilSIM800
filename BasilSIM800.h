#ifndef _BasilSIM800_h
#define _BasilSIM800_h

#include <Arduino.h>
#include <HardwareSerial.h>

class SIM800 { 
	public:
	SIM800(HardwareSerial *gsm, uint32_t baudRate, uint8_t rx, uint8_t tx);
	void init();
	bool sendSMS(String number, String text);
	String readSMS(uint8_t count);
	
	private:
	Stream *_gsm;
	uint8_t	_rx_pin;
	uint8_t _tx_pin; 
	uint8_t _baudRate;
	HardwareSerial *_hardwareSerial;
	
};

#endif

