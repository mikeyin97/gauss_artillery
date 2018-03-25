#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>

const uint8_t cannon_pin = 5;
const uint8_t discharge_pin = 8;

int add(int a, int b);
float cannonVoltage();
void cannonTest();

#endif
