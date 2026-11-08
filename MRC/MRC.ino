#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "include/MotorControls.h"
#include "include/BluetoothReadWrite.h"
#include "include/ServoControls.h"
#include "include/Pin_assignments.h"
#include "include/Hardware.h"
#include "include/CommandDecodeExecute.h"

//------------------------------------------------//
// Create objects
Motors LeftSideMotors;
Motors RightSideMotors;

Servo servo1, servo2;
SoftwareSerial HC06(BLUETOOTH_RX, BLUETOOTH_TX);
//------------------------------------------------//


void setup(){
    
    Init_Hardware(&RightSideMotors, &LeftSideMotors, &servo1, &servo2, &HC06);

}

void loop(){
    String BTcommand = Bluetooth_Read(&HC06); //read command

    //decode and execute command
    Command_Decode_Execute(BTcommand, &servo1, &servo2, &LeftSideMotors, &RightSideMotors, &HC06);
}