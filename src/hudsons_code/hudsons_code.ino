//#include <Arduino.h>
//#include <functions.h>
// #include <../lib/AccelStepper.h>

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  Serial.println("Done Setup");
  //add(1, 2); // test function
}

void loop() {
  float division = 1.0;
  float volt_factor = 5.0/1023.0;
  Serial.println(analogRead(A0) * division * volt_factor);
  while (Serial.available() > 0) {
    Serial.println(analogRead(A0) * division * volt_factor);
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

