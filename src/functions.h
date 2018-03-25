#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>

const uint8_t cannon_pin = 5;
const uint8_t discharge_pin = 8;

const uint8_t dir_pin = 8;
const uint8_t pulse_pin = 9;
const uint8_t enable_pin = 10;
const uint16_t microsteps = 2;
const uint16_t pulse_per_rev = microsteps * 400;

const float max_speed = 1.5 * microsteps * 200;
const float acc = max_speed;

AccelStepper pan_stepper(AccelStepper::DRIVER, pulse_pin, dir_pin);

int add(int a, int b);
float cannonVoltage();
void cannonTest();
void stepperTest();
void set_up_steppers();

#endif
