#include <Arduino.h>
#include <functions.h>

float cannonVoltage() {
	float division = 21;
	float volt_factor = 5.0/1024.0;
	return (float) analogRead(A0) * division * volt_factor;
}

void cannonTest() {
	float voltage = 0;
	Serial.println("Initializing cannon test: input the firetime")
	while (Serial.available() <= 0);
	while (Serial.available() > 0){
		int firetime = Serial.parseInt();
		if (Serial.read() == '\n') {
			digitalWrite(discharge_pin, HIGH);
			do {
				voltage = cannonVoltage();
				Serial.print("Current Voltage: ");
				Serial.println(voltage);
			} while(voltage > 66.0);
			digitalWrite(discharge_pin, LOW);
			Serial.print("FIRING with firetime: ");
			Serial.println(firetime);
			digitalWrite(cannon_pin, HIGH);
			delayMicroseconds(firetime);
			digitalWrite(cannon_pin, LOW);
		}
	}
}

void set_up_steppers() {
	pinMode(pan_dir_pin, OUTPUT);
	pinMode(pan_pulse_pin, OUTPUT);
	pinMode(tilt_dir_pin, OUTPUT);
	pinMode(tilt_pulse_pin, OUTPUT);

	pinMode(enable_pin, OUTPUT);
	digitalWrite(enable_pin, HIGH);

	pan_stepper.setMaxSpeed(max_speed);
	pan_stepper.setAcceleration(stepper_acc);
	tilt_stepper.setMaxSpeed(max_speed);
	tilt_stepper.setAcceleration(stepper_acc);
}

void set_up_cannon() {
	pinMode(cannon_pin, OUTPUT);
	pinMode(discharge_pin, OUTPUT);
}

void stepperTest(AccelStepper stepper) {
	Serial.println("This motor should now run for 800 steps and back")
	pan_stepper.moveTo(800);
	while(pan_stepper.distanceToGo()) {
		pan_stepper.run();
	}
	pan_stepper.moveTo(-800);
	while(pan_stepper.distanceToGo()) {
		pan_stepper.run();
	}
	Serial.print("Current position: ");
	Serial.println(pan_stepper.currentPosition());
}

void stepper_cannon_test(){
  voltage = cannonVoltage();
  Serial.print("Voltage: ");
  Serial.println(voltage);
  while (Serial.available() <= 0);
  while (Serial.available() > 0) {
    int firetime = Serial.parseInt();
    if (Serial.read() == ' ') {
      pan_angle = Serial.parseInt();
      if (Serial.read() == ' ') {
        tilt_angle = Serial.parseInt();
        if (Serial.read() == '\n') {
          Serial.print("Pan angle: ");
          Serial.println(pan_angle);
          Serial.print("Tilt angle: ");
          Serial.println(tilt_angle);
          pan_stepper.runToNewPosition(pan_angle);
          tilt_stepper.runToNewPosition(tilt_angle);
          delay(2000);
          digitalWrite(discharge_pin, HIGH);
          do {
            voltage = cannonVoltage();
            Serial.print("Voltage at firing: ");
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
	  else
		Serial.println("Invalid format");
    }
	else
		Serial.println("Invalid format");
  }
  delay(500);

}

int deg2steps(float degrees){
	float steps = degrees/360*STEPS_PER_REV;
	if (step % 1 != 0)
		Serial.println("WARNING: Exact number of steps is not a whole number - angle may not be precise" );
	return (int)steps;
}