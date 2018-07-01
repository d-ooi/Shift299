#ifndef Shift299_h
#define Shift299_h

#include "Arduino.h"

class Shift299
{
public:
	Shift299(int clockPin, int inDataPin, int outDataPin, int pinS0,
		    int pinS1, int pinOE1, int pinOE2);
	
	void load(byte in);
	void write();
	void write(byte in);
	byte read();
	String read(int chainLength);
	void clear();
private:
	String bytetostring(byte inByte);
	int _clockPin;
	int _inDataPin;
	int _outDataPin;
	int _pinS0;
	int _pinS1;
	int _pinOE1;
	int _pinOE2;
};

#endif // !Shift299_h
