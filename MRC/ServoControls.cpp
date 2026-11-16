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
    float CurrentAngle1 = (*myServo1).read();
    float CurrentAngle2 = (*myServo2).read();
    
    bool Servo1done = (angle1 == CurrentAngle1);
    bool Servo2done = (angle2 == CurrentAngle2);

    if (Servo1done && Servo2done) return;

    int direction1 = (angle1 > CurrentAngle1) ? 1 : -1;
    int direction2 = (angle2 > CurrentAngle2) ? 1 : -1;

    while(true){
        if (!Servo1done){
            CurrentAngle1 += 20 * direction1;
            if (direction1 * (angle1 - CurrentAngle1) <= 0){
                (*myServo1).write(angle1);
                Servo1done = true;
            }
            else{
                (*myServo1).write(CurrentAngle1);
            }
        }
        if (!Servo2done){
            CurrentAngle2 += 20 * direction2;
            if (direction2 * (angle2 - CurrentAngle2) <= 0){
                (*myServo2).write(angle2);
                Servo2done = true;
            }
            else{
                (*myServo2).write(CurrentAngle2);
            }
        }
        if (Servo1done && Servo2done) return;
        delay(50);
    }
}
