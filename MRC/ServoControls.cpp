#pragma once

#include <Ardunio.h>
#include <stdio.h>
#include <Servo.h>
#include "include/ServoControls.h"


void MoveServo(Servo* myServo, int angle){
    (*myServo).write(angle);
}
