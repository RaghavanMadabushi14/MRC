#include <stdio.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "include/Pin_assignments.h"
#include "include/Hardware.h"

Motors LeftSideMotors;
Motors RightSideMotors;

Servo servo1, servo2;
SoftwareSerial HC06(BLUETOOTH_RX, BLUETOOTH_TX);

void setup(){
    Init_Hardware(&RightSideMotors, &LeftSideMotors, &servo1, &servo2, &HC06);

}

void loop(){

}