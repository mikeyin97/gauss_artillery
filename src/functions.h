#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>

// Stepper pins
const uint8_t pan_dir_pin = 4;
const uint8_t pan_pulse_pin = 5;
const uint8_t tilt_dir_pin = 7;
const uint8_t tilt_pulse_pin = 8;
const uint8_t enable_pin = 6;

// Cannon pins and constants
const uint8_t cannon_pin = 10;
const uint8_t discharge_pin = 11;

const int microsteps = 2;
const int STEPS_PER_REV = 400;
const float max_speed = 1.5 * microsteps * STEPS_PER_REV;
const float acc = max_speed / 2;

int pan_angle = 0;
int tilt_angle = 0;

AccelStepper pan_stepper(AccelStepper::DRIVER, pan_pulse_pin, pan_dir_pin);
AccelStepper tilt_stepper(AccelStepper::DRIVER, tilt_pulse_pin, tilt_dir_pin)

float cannonVoltage();
void cannonTest();
void set_up_steppers();
void set_up_cannon();
void stepperTest();
void stepper_cannon_test();
int deg2steps(float degrees);

#endif
