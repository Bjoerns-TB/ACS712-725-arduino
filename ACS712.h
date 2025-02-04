#ifndef ACS712_h
#define ACS712_h

#include <Arduino.h>

#define ADC_SCALE 1024.0
// #define VREF 5.0
#define DEFAULT_FREQUENCY 50

extern int VREF;

enum ACS712_type {ACS712_05B, ACS712_20A, ACS712_30A, ACS725_05AB, ACS725_10AB, ACS725_10AU, ACS725_20AB, ACS725_20AU};

class ACS712 {
public:
	ACS712(ACS712_type type, uint8_t _pin);
	int calibrate();
	void setZeroPoint(int _zero);
	void setSensitivity(float sens);
	float getCurrentDC();
	float getCurrentAC();
	float getCurrentAC(uint16_t frequency);
	float getCurrentAC2();

private:
	float zero = 512.0;
	int sensitivity;
	// float VREF;
	uint8_t pin;

};

#endif
