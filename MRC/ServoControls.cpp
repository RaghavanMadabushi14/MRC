#include <stdio.h>
#include <Servo.h>
#include "include/ServoControls.h"

#pragma once

void MoveServo(Servo* myServo, int angle){
    (*myServo).write(angle);
}
