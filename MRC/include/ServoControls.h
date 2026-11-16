#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>

void MoveServo(Servo* myServo, float angle);

void MoveBothServos(Servo* myServo1, Servo* myServo2, float angle1, float angle2);
