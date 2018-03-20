#include <Arduino.h>
#include <functions.h>

int add(int a, int b) {
	return a + b; // test func
}

int cannonVoltage() {
	float division = 19.0;
  	float volt_factor = 5.0/1023.0;
	return analogRead(A0) * division * volt_factor;
}