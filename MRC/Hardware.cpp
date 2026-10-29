#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "include/Pin_assignments.h"
#include "include/Hardware.h"

void MotorsPinModes(){
    pinMode(RIGHT_MOTORS_IN13, OUTPUT);
    pinMode(RIGHT_MOTORS_IN24, OUTPUT);
    pinMode(EN_MOTORS_RIGHT, OUTPUT);

    pinMode(LEFT_MOTORS_IN13, OUTPUT);
    pinMode(LEFT_MOTORS_IN24, OUTPUT);
    pinMode(EN_MOTORS_LEFT, OUTPUT);
}
void Init_Right_Motors(Motors* MotorsRightSide){
    MotorsRightSide->IN13 = RIGHT_MOTORS_IN13;
    MotorsRightSide->IN24 = RIGHT_MOTORS_IN24;
    MotorsRightSide->EN = EN_MOTORS_RIGHT;
}

void Init_Left_Motors(Motors* MotorsLeftSide){
    MotorsLeftSide->IN13 = LEFT_MOTORS_IN13;
    MotorsLeftSide->IN24 = LEFT_MOTORS_IN24;
    MotorsLeftSide->EN = EN_MOTORS_LEFT;
}

void Init_Servos(Servo* servo_a, Servo* servo_b){
    (*servo_a).attach(SERVO_1);
    (*servo_b).attach(SERVO_2);
}

void Init_Bluetooth(SoftwareSerial* BTdevice){
    (*BTdevice).begin(9600);
}

void Init_Hardware(Motors* MotorsRightSide, Motors* MotorsLeftSide, Servo* servo_a, Servo* servo_b, SoftwareSerial* BTdevice){
    Init_Right_Motors(MotorsRightSide);
    Init_Left_Motors(MotorsLeftSide);
    MotorsPinModes();

    Init_Servos(servo_a, servo_b);

    Init_Bluetooth(BTdevice);
}