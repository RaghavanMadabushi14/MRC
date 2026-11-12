#pragma once

#include <Arduino.h>
#include <stdio.h>
#include "Hardware.h"

#define MOTOR_MAX_PWM 255
#ifndef MOTOR_MIN_PWM
#define MOTOR_MIN_PWM 0 
#endif         // tune on robot: lowest PWM that actually turns the wheels

// speed is signed: positive = forward, negative = reverse, 0 = coast stop. Range -255..255 (clamped)
void Motors_Drive(Motors* side, int speed);

void Motors_Stop(Motors* side);

void Motors_Tank(Motors* left, Motors* right, int leftSpeed, int rightSpeed);


float ms_to_time(float distance_ms, int PWM);

float angle_to_time(float angle_degrees, int PWM);

void Motors_Move_Distance(Motors* right_side, Motors* left_side, float distance_ms);

void Motors_Rotate_Angle(Motors* right_side, Motors* left_side, float angle_degrees);


//ideas for future: Give distance input and compute a delay using the given speed (delay = distance/speed) to move the rover a certain distance
//we will have to gather data for m/s to PWM conversion formula, and attempt a rough account for how long it takes the motors to accelerate/decellerate
