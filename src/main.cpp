#include <Arduino.h>
#include <functions.h>
#include <../lib/AccelStepper.h>

const int triggerPin = 8;

void setup() {
    set_up_steppers();
	Serial.begin(115200);
	pinMode(cannon_pin, OUTPUT);
	pinMode(drain_pin, OUTPUT);
	Serial.println("Done Setup");
}

void loop() {
	cannonTest();
}
