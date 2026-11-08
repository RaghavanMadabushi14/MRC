#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>
#include "include/ServoControls.h"


void MoveServo(Servo* myServo, int angle){
    (*myServo).write(angle);
}
