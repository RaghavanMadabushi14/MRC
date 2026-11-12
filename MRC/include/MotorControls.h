#pragma once

#include <Arduino.h>
#include <stdio.h>
#include "Hardware.h"

#define MOTOR_MAX_PWM 255
#ifndef MOTOR_MIN_PWM
#define MOTOR_MIN_PWM 0          // tune on robot: lowest PWM that actually turns the wheels

// speed is signed: positive = forward, negative = reverse, 0 = coast stop. Range -255..255 (clamped)
void Motors_Drive(Motors* side, int speed);

void Motors_Stop(Motors* side);

void Motors_Tank(Motors* left, Motors* right, int leftSpeed, int rightSpeed);


//ideas for future: Give distance input and compute a delay using the given speed (delay = distance/speed) to move the rover a certain distance
//we will have to gather data for m/s to PWM conversion formula, and attempt a rough account for how long it takes the motors to accelerate/decellerate
