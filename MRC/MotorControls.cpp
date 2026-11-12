#include <Arduino.h>
#include <stdio.h>
#include "include/Hardware.h"
#include "include/MotorControls.h"


void Motors_Drive(Motors* side, int speed){
    if (speed > MOTOR_MAX_PWM){
        speed = MOTOR_MAX_PWM;
    }
    else if (speed < -MOTOR_MAX_PWM){
        speed = -MOTOR_MAX_PWM;
    }

    if (speed == 0){
        Motors_Stop(side);
        return;
    }

    int magnitude = abs(speed);
    if (magnitude < MOTOR_MIN_PWM){
        magnitude = MOTOR_MIN_PWM;
    }
    
    digitalWrite(side->IN13, LOW);
    digitalWrite(side->IN24, HIGH);
    analogWrite(side->EN, magnitude);
}

void Motors_Stop(Motors* side){
    digitalWrite(side->IN13, LOW);
    digitalWrite(side->IN24, LOW);
    analogWrite(side->EN, 0);
}

void Motors_Tank(Motors* left, Motors* right, int leftSpeed, int rightSpeed){
    Motors_Drive(left, leftSpeed, LEFT_MOTORS_REVERSED);
    Motors_Drive(right, rightSpeed, RIGHT_MOTORS_REVERSED);
}
