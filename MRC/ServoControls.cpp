#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>
#include "include/ServoControls.h"


void MoveServo(Servo* myServo, float angle){

    float CurrentAngle = (*myServo).read();

    if (angle == CurrentAngle){
        return;
    }

    int direction = (angle > CurrentAngle) ? 1 : -1;

    while(true){
        CurrentAngle += 20 * direction;
        if (direction * (angle - CurrentAngle) <= 0){
            (*myServo).write(angle);
            return;
        }
        (*myServo).write(CurrentAngle);
        delay(50);
    }
}

void MoveBothServos(Servo* myServo1, Servo* myServo2, float angle1, float angle2){
    MoveServo(myServo1, angle1);
    MoveServo(myServo2, angle2);
}
