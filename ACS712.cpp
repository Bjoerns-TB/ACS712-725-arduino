#include "ACS712.h"
int zero; 
ACS712::ACS712(ACS712_type type, uint8_t _pin) {
	switch (type) {
		case ACS712_05B:
			sensitivity = 185;
			break;
		case ACS712_20A:
			sensitivity = 100;
			break;
		case ACS712_30A:
			sensitivity = 66;
			break;
		case ACS725_05AB:
			sensitivity = 264;
			break;
		case ACS725_10AB:
			sensitivity = 132;
			break;
		case ACS725_10AU:
			sensitivity = 264;
			break;
		case ACS725_20AB:
			sensitivity = 66;
			break;
		case ACS725_20AU:
			sensitivity = 132;
			break;
		default:
			sensitivity = 66;
			break;
	}
	pin = _pin;
}

int ACS712::calibrate() {
	int _zero = 0;
	for (int i = 0; i < 150; i++) {
		_zero += analogRead(pin);
		delay(10);
	}
	_zero /= 150;
	zero = _zero;
	return _zero;
}

void ACS712::setZeroPoint(int _zero) {
	zero = _zero;
}

void ACS712::setSensitivity(float sens) {
	sensitivity = sens;
}

float ACS712::getCurrentDC() {
	float I = (zero - analogRead(pin)) / ADC_SCALE * VREF / sensitivity;
	return I;
}

float ACS712::getCurrentAC() {
	return getCurrentAC(DEFAULT_FREQUENCY);
}

float ACS712::getCurrentAC(uint16_t frequency) {
	uint32_t period = 1000000 / frequency;
	uint32_t t_start = micros();

	uint32_t Isum = 0, measurements_count = 0;
	int32_t Inow;

	while (micros() - t_start < period) {
		Inow = zero - analogRead(pin);
		Isum += Inow*Inow;
		measurements_count++;
	}

	float Irms = sqrt(Isum / measurements_count) / ADC_SCALE * VREF / sensitivity;
	return Irms;
}
