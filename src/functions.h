#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <../lib/AccelStepper.h>
#include <math.h>

// Stepper pins and specs
const uint8_t pan_dir_pin = 43;
const uint8_t pan_pulse_pin = 45;
const float PAN_STEPS_PER_DEG = 13.33333;
const uint8_t tilt_dir_pin = 33;
const uint8_t tilt_pulse_pin = 35;
const float TILT_STEPS_PER_DEG = 26.66667;

const int microsteps = 4;
const int STEPS_PER_REV = 400;
const float max_speed = 2.0 * microsteps * STEPS_PER_REV;
const float acc = max_speed / 2;

// Cannon pins and constants
const uint8_t cannon_pin = 50;
const uint8_t discharge_pin = 48;


// Variables
float volt_factor = 5.0/1024.0;
float division = 21;
float voltage = 0;
float pan_angle = 0;
float tilt_angle = 0;
float x = 0;
float y = 0;
float d = 0;
float theta = 0;
const int firetime = 3000;

// Constants for solving quadratic equation
const float v0 = 7.5;
const float g = 9.81;
const float b = g/2/pow(v0, 2);
const float c = 0.2;

AccelStepper pan_stepper(AccelStepper::DRIVER, pan_pulse_pin, pan_dir_pin);
AccelStepper tilt_stepper(AccelStepper::DRIVER, tilt_pulse_pin, tilt_dir_pin);

// Test functions
void cannonTest();
void setup_steppers();
void setup_cannon();
void stepperTest();
void stepper_cannon_test();

// Primary functions
float cannonVoltage();
float pan_deg2steps(float deg);
float tilt_deg2steps(float deg);
float get_distance(float x, float y);
float get_pan_angle(float x, float y);
float get_tilt_angle(float d)
void main();

#endif
