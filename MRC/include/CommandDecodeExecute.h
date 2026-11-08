#pragma once

#include <stdio.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "Hardware.h"

void Command_Decode_Execute(String command, Servo* Servo_a, Servo* Servo_b, Motors* LeftMotors, Motors* RightMotors, SoftwareSerial* BTdevice);
