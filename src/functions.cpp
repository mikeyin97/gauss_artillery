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

void cannonTest() {
	float division = 19.0;
	float volt_factor = 5.0/1023.0;
	float voltage = 0;
	while (Serial.available() > 0) {
	int firetime = Serial.parseInt();
	if (Serial.read() == '\n') {
		digitalWrite(drain_pin, HIGH);
		do {
            voltage = cannonVoltage();
            Serial.println(voltage);
		} while(voltage > 66.0);
            digitalWrite(discharge_pin, LOW);
            Serial.println("FIRING");
            Serial.println(firetime);
            digitalWrite(cannon_pin, HIGH);
            delayMicroseconds(firetime);
            digitalWrite(cannon_pin, LOW);
	    }
	}
}