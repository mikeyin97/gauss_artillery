#include <Arduino.h>
#include <functions.h>

void cannonTest() {
	voltage = 0;
	Serial.println("Initializing cannon test: input the firetime");
	while (Serial.available() <= 0);
	while (Serial.available() > 0){
		int temp_firetime = Serial.parseInt();
		if (Serial.read() == '\n') {
			digitalWrite(discharge_pin, HIGH);
			do {
				voltage = cannonVoltage();
				Serial.print("Current Voltage: ");
				Serial.println(voltage);
			} while(voltage > 85.21*0.9);
			digitalWrite(discharge_pin, LOW);
			Serial.print("FIRING with firetime: ");
			Serial.println(temp_firetime);
			digitalWrite(cannon_pin, HIGH);
			delayMicroseconds(temp_firetime);
			digitalWrite(cannon_pin, LOW);
		}
	}
}

void setup_steppers() {
	pinMode(pan_dir_pin, OUTPUT);
	pinMode(pan_pulse_pin, OUTPUT);
	pinMode(tilt_dir_pin, OUTPUT);
	pinMode(tilt_pulse_pin, OUTPUT);

	pan_stepper.setMaxSpeed(max_speed);
	pan_stepper.setAcceleration(stepper_acc);
	tilt_stepper.setMaxSpeed(max_speed);
	tilt_stepper.setAcceleration(stepper_acc);
}

void setup_cannon() {
	pinMode(cannon_pin, OUTPUT);
	pinMode(discharge_pin, OUTPUT);
}

void stepperTest(AccelStepper stepper) {
	Serial.println("This motor should now run for 800 steps and back");
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
	Serial.println("STEPPER/CANNON TEST: INPUT'FIRETIME PAN TILT'");
	while (Serial.available() <= 0){
		voltage = cannonVoltage();
		Serial.print("Voltage: ");
		Serial.println(voltage);
		delay(500);
	}
	while (Serial.available() > 0) {
		int temp_firetime = Serial.parseInt();
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
					} while(voltage > 85.21*0.9);
					digitalWrite(discharge_pin, LOW);
					Serial.println("FIRING");
					Serial.println(temp_firetime);
					digitalWrite(cannon_pin, HIGH);
					delayMicroseconds(temp_firetime);
					digitalWrite(cannon_pin, LOW);
				}
			}
		}
	}
}


float cannonVoltage() {
	return (float) analogRead(A0) * division * volt_factor;
}

float pan_deg2steps(float deg){
	return (-deg*PAN_STEPS_PER_DEG);
}

float tilt_deg2steps(float deg){
	return (-deg*TILT_STEPS_PER_DEG);
}

float get_distance(float x, float y){
	return sqrt(pow(x, 2) + pow(y, 2));
}

float get_pan_angle(float x, float y){
	return atan2(y, x)*180/M_PI;
}

float get_tilt_angle(float d){
 
	float inner_sqrt_arg = pow(2*b*c*pow(d, 2) + pow(d, 2), 2) - 4*(pow(d, 2) + pow(c, 2))*(pow(b, 2) * pow(d, 4));
	if (inner_sqrt_arg < 0){
	Serial.println("Invalid distance - negative inner square root argument");
	return 0;
	}

	float inner_sqrt = sqrt(inner_sqrt_arg);
	float outer_sqrt_arg1 = ((2*b*c*pow(d, 2) + pow(d, 2)) + inner_sqrt) / 2 / (pow(c, 2) + pow(d, 2));
	float outer_sqrt1 = sqrt(outer_sqrt_arg1);
	float t = acos(outer_sqrt1)*180/M_PI;
	return t;
}

void main(){
	delay(500);
	voltage = cannonVoltage();
	Serial.print("Voltage: ");
	Serial.println(voltage);
	while (Serial.available() > 0) {
		x = Serial.parseFloat();
		if (Serial.read() == ' ') {
			y = Serial.parseFloat();
			if (Serial.read() == '\n') {
				Serial.print("X: ");
				Serial.println(x);
				Serial.print("Y ");
				Serial.println(y);
				d = get_distance(x, y);
				tilt_angle = get_theta(d);
				Serial.print("Distance: ");
				Serial.println(d);
				Serial.print("Tilt angle: ");
				Serial.println(tilt_angle);
				pan_angle = get_angle(x, y);
				Serial.print("Pan angle: ");
				Serial.println(pan_angle);
				pan_stepper.runToNewPosition(pan_deg2steps(pan_angle));
				tilt_stepper.runToNewPosition(tilt_deg2steps(tilt_angle));
				delay(2000);
				digitalWrite(discharge_pin, HIGH);
				do {
				voltage = cannonVoltage();
				Serial.print("Voltage at firing: ");
				Serial.println(voltage);
				} while(voltage > 85.21*0.9);
				digitalWrite(discharge_pin, LOW);
				Serial.println("FIRING");
				Serial.println(firetime);
				digitalWrite(cannon_pin, HIGH);
				delayMicroseconds(firetime);
				digitalWrite(cannon_pin, LOW);
			}
		}
		else{ //reset cannon position
			pan_stepper.runToNewPosition(0);
			tilt_stepper.runToNewPosition(0);
		}
	}
}	