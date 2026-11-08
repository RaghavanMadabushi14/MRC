#pragma once

#include <Ardunio.h>
#include <stdio.h>
#include "Hardware.h"

<<<<<<< HEAD
#define MOTOR_MAX_PWM 255
#ifndef MOTOR_MIN_PWM
#define MOTOR_MIN_PWM 0          // tune on robot: lowest PWM that actually turns the wheels
#endif
#define LEFT_MOTORS_REVERSED  0  // flip to 1 on robot if that side spins backward
#define RIGHT_MOTORS_REVERSED 0

// speed is signed: positive = forward, negative = reverse, 0 = coast stop. Range -255..255 (clamped)
void Motors_Drive(Motors* side, int speed, bool reversed);

void Motors_Stop(Motors* side);

void Motors_Tank(Motors* left, Motors* right, int leftSpeed, int rightSpeed);


//ideas for future: Give distance input and compute a delay using the given speed (delay = distance/speed) to move the rover a certain distance
//we will have to gather data for m/s to PWM conversion formula, and attempt a rough account for how long it takes the motors to accelerate/decellerate
=======
>>>>>>> 0e7540e41453f36023817f9c7eb77ce9c3b02fff
