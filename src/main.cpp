#include <Arduino.h>
#include <functions.h>
#include <../lib/AccelStepper.h>

void setup() {
    set_up_steppers();
	set_up_cannon();
	Serial.begin(115200);
	Serial.println("Done Setup");
}

void loop() {
	cannonTest();
}
