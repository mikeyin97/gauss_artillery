//#include <Arduino.h>
//#include <../functions.h>
// #include <../lib/AccelStepper.h>

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  Serial.println("Done Setup");
  //add(1, 2); // test function
}

void loop() {
  while (Serial.available() > 0) {
    int firetime = Serial.parseInt();
    Serial.println(firetime);
    if (Serial.read() == '\n') {
      Serial.println(firetime);
      digitalWrite(8, HIGH);
      delayMicroseconds(firetime);
      digitalWrite(8, LOW);
    }
  }
}

