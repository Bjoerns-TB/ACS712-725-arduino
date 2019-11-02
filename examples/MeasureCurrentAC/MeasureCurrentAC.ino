#include "ACS712.h"

/*
  This example shows how to measure DC current
*/

// We have 30 amps version sensor connected to A1 pin of arduino
// Replace with your version if necessary
ACS712 sensor(ACS712_30A, A1);

long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1125300L / result; // Back-calculate AVcc in mV
  return result;
}

void setup() {
  Serial.begin(9600);

  // This method calibrates zero point of sensor,
  // It is not necessary, but may positively affect the accuracy
  // Ensure that no current flows through the sensor at this moment
  sensor.calibrate();
}

void loop() {
  // Get current from sensor
  float I = sensor.getCurrentAC();
  
  // Send it to serial
  Serial.println(String("I = ") + I + " A");
  
  // Wait one second before the new cycle
  delay(1000);
}
