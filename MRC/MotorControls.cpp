#pragma once

#include <Arduino.h>
#include <stdio.h>
#include "include/Hardware.h"
#include "include/MotorControls.h"
#include <math.h>


void Motors_Drive(Motors* side, int speed){

    // enforce PWM limits
    speed = (speed > MOTOR_MAX_PWM) ? MOTOR_MAX_PWM : (speed < -MOTOR_MAX_PWM) ? -MOTOR_MAX_PWM : speed;

    if (speed == 0){
        Motors_Stop(side);
        return;
    }

    int magnitude = abs(speed);
    
    if (speed > 0){
        digitalWrite(side->IN13, LOW);
        digitalWrite(side->IN24, HIGH);
    }
    else {
        digitalWrite(side->IN13, HIGH);
        digitalWrite(side->IN24, LOW);
    }
    
    analogWrite(side->EN, magnitude);
}

void Motors_Stop(Motors* side){
    digitalWrite(side->IN13, LOW);
    digitalWrite(side->IN24, LOW);
    analogWrite(side->EN, 0);
}

void Motors_Tank(Motors* left, Motors* right, int leftSpeed, int rightSpeed){
    Motors_Drive(left, leftSpeed);
    Motors_Drive(right, rightSpeed);
}


float ms_to_time(float distance_m, int PWM); // TODO

float angle_to_time(float angle_degrees, int PWM); // TODO

void Motors_Move_Distance(Motors* left_side, Motors* right_side, float distance_m){

    if (distance_m == 0) return;
    
    unsigned long time_ms = ms_to_time(fabs(distance_m), DEFAULT_PWM)*1000;
    
    if (distance_m > 0){
        Motors_Tank(left_side, right_side, DEFAULT_PWM, DEFAULT_PWM);
    }
    else {
        Motors_Tank(left_side, right_side, -DEFAULT_PWM, -DEFAULT_PWM);
    }

    delay(time_ms);
    Motors_Stop(left_side);
    Motors_Stop(right_side);
}

void Motors_Rotate_Angle(Motors* left_side, Motors* right_side, float angle_degrees){
    
    if (angle_degrees == 0) return;

    unsigned long time_ms = angle_to_time(fabs(angle_degrees), DEFAULT_PWM)*1000;

    bool anticlockwise = (angle_degrees < 0);
    
    if (anticlockwise){
        Motors_Tank(left_side, right_side, -DEFAULT_PWM, DEFAULT_PWM);
    }
    else {
        Motors_Tank(left_side, right_side, DEFAULT_PWM, -DEFAULT_PWM);
    }

    delay(time_ms);
    Motors_Stop(left_side);
    Motors_Stop(right_side);
}