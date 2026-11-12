#pragma once

#include <Arduino.h>
#include <stdio.h>
#include "Hardware.h"
#include <math.h>

#define MOTOR_MAX_PWM 255
#ifndef MOTOR_MIN_PWM
#define MOTOR_MIN_PWM 0 
#endif         // tune on robot: lowest PWM that actually turns the wheels
#define DEFAULT_PWM 200

// speed is signed: positive = forward, negative = reverse, 0 = coast stop. Range -255..255 (clamped)
void Motors_Drive(Motors* side, int speed);

void Motors_Stop(Motors* side);

void Motors_Tank(Motors* left, Motors* right, int leftSpeed, int rightSpeed);


float ms_to_time(float distance_m, int PWM);

float angle_to_time(float angle_degrees, int PWM);

void Motors_Move_Distance(Motors* left_side, Motors* right_side, float distance_m);

void Motors_Rotate_Angle(Motors* left_side, Motors* right_side, float angle_degrees);


//ideas for future: Give distance input and compute a delay using the given speed (delay = distance/speed) to move the rover a certain distance
//we will have to gather data for m/s to PWM conversion formula, and attempt a rough account for how long it takes the motors to accelerate/decellerate
