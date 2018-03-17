#include <Arduino.h>
#include <functions.h>
#include <../lib/AccelStepper.h>

const int triggerPin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  Serial.println("Done Setup");
  add(1, 2); // test function
}

void loop() {
  while (Serial.available() > 0) {
    int firetime = Serial.parseInt();
    Serial.println(firetime);
    if (Serial.read() == '\n') {
      Serial.println(firetime);
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(firetime);
      digitalWrite(triggerPin, LOW);
    }
  }
}
