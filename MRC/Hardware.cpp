#include <stdio.h>
#include "Pin_assignments.h"
#include "Hardware.h"

void pinModes(){
    pinMode(RIGHT_MOTORS_IN13, OUTPUT);
    pinMode(RIGHT_MOTORS_IN24, OUTPUT);
    pinMode(EN_MOTORS_RIGHT, OUTPUT);

    pinMode(LEFT_MOTORS_IN13, OUTPUT);
    pinMode(LEFT_MOTORS_IN24, OUTPUT);
    pinMode(EN_MOTORS_LEFT, OUTPUT);
}
void Init_Right_Motors(Motors* MotorSide){
    MotorSide->IN13 = RIGHT_MOTORS_IN13;
    MotorSide->IN24 = RIGHT_MOTORS_IN24;
    MotorSide->EN = EN_MOTORS_RIGHT;
}

void Init_Left_Motors(Motors* MotorSide){
    MotorSide->IN13 = LEFT_MOTORS_IN13;
    MotorSide->IN24 = LEFT_MOTORS_IN24;
    MotorSide->EN = EN_MOTORS_LEFT;
}

void Init_Top_Servo(servo* MyServo){
    MyServo->servo_control = SERVO_1;
}

void Init_Bottom_Servo(servo* MyServo){
    MyServo->servo_control = SERVO_2;
}

void Init_hc06(hc06* MyHC06){
    MyHC06->rx = BLUETOOTH_RX;
    MyHC06->tx = BLUETOOTH_TX;
}
