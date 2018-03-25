#include <Arduino.h>
#include <functions.h>

int add(int a, int b) {
	return a + b; // test func
}

float cannonVoltage() {
	float division = 22.15;
  	float volt_factor = 5.0/1024.0;
	return (float) analogRead(A0) * division * volt_factor;
}
