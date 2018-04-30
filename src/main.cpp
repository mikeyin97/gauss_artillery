#include <Arduino.h>
#include <functions.h>

void setup() {
    setup_steppers();
	setup_cannon();
	Serial.begin(115200);
	Serial.println("Done Setup");
}

void loop() {
	main();
}
