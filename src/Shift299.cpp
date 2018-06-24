#include "Arduino.h"
#include "Shift299.h"

// Constructor
Shift299::Shift299(int clockPin, int inDataPin, int outDataPin, int pinS0, int pinS1, int pinOE1, int pinOE2)
{
	pinMode(clockPin, OUTPUT);
	pinMode(inDataPin, INPUT);   // Connect to Q0
	pinMode(outDataPin, OUTPUT); // Connect to DS0
	pinMode(pinS0, OUTPUT);
	pinMode(pinS1, OUTPUT);
	pinMode(pinOE1, OUTPUT);
	pinMode(pinOE2, OUTPUT);

	// set local variables for the pins
	_clockPin = clockPin;
	_inDataPin = inDataPin;
	_outDataPin = outDataPin;
	_pinS0 = pinS0;
	_pinS1 = pinS1;
	_pinOE1 = pinOE1;
	_pinOE2 = pinOE2;
	
	// disable outputs and clear register
	digitalWrite(_pinOE1, HIGH);
	Shift299::clear();
}

// This method shifts data into the register
void Shift299::load(byte in)
{
	digitalWrite(_pinOE1, HIGH);
	digitalWrite(_pinOE2, HIGH);
	digitalWrite(_pinS0, HIGH);
	digitalWrite(_pinS1, LOW);

	shiftOut(_outDataPin, _clockPin, MSBFIRST, in);
}

// This method writes the contents of the register to the output
void Shift299::write()
{
	// configures register to present data at output pins
	digitalWrite(_pinOE1, LOW);
	digitalWrite(_pinOE2, LOW);
	digitalWrite(_pinS0, LOW);
	digitalWrite(_pinS1, LOW);
}

// This method overloads writeRegister allowing a byte to be written
// to the outputs directly
void Shift299::write(byte in)
{
	Shift299::load(in);

	Shift299::write();
}

// This method reads the data  presented at the register inputs
// and returns them as a byte
byte Shift299::read()
{
	byte outputByte = 52;
	//int currentBit;

	// configure register to load the register with data presented
	// at the input pins
	digitalWrite(_pinOE1, LOW);
	digitalWrite(_pinOE2, LOW);
	digitalWrite(_pinS0, HIGH);
	digitalWrite(_pinS1, HIGH);

	digitalWrite(_clockPin, LOW);
	delayMicroseconds(0.2);
	digitalWrite(_clockPin, HIGH);

	// configure for shift left
	digitalWrite(_pinS0, LOW);
	digitalWrite(_pinS1, HIGH);

	outputByte = shiftIn(_inDataPin, _clockPin, LSBFIRST);
	
	return outputByte;
}

// This method clears the register by shifting in "00000000"
void Shift299::clear()
{
	Shift299::load(0);
}