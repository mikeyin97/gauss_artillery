#include <Arduino.h>
#include <functions.h>
// #include <../lib/AccelStepper.h>

const int triggerPin = 8;

void setup() {
  Serial.begin(115200);
  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.println("Done Setup");
  //add(1, 2); // test function
}

void loop() {
  float division = 19.0;
  float volt_factor = 5.0/1023.0;
  float voltage = 0;
  while (Serial.available() > 0) {
    int firetime = Serial.parseInt();
    if (Serial.read() == '\n') {
      digitalWrite(5 ,HIGH);
      do {
        voltage = cannonVoltage();
        Serial.println(voltage);
      } while(voltage > 66.0);
      digitalWrite(5, LOW);
      Serial.println("FIRING");
      Serial.println(firetime);
      digitalWrite(8, HIGH);
      delayMicroseconds(firetime);
      digitalWrite(8, LOW);
    }
  }
}
