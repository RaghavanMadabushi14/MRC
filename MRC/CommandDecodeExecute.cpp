#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "include/Hardware.h"
#include "include/MotorControls.h"
#include "include/BluetoothReadWrite.h"
#include "include/ServoControls.h"
#include "include/Pin_assignments.h"


void Command_Decode_Execute(String command, Servo* Servo_a, Servo* Servo_b, Motors* LeftMotors, Motors* RightMotors, SoftwareSerial* BTdevice){
    // terminal apps often append '\r' or spaces, which would break the == checks
    command.trim();
    command.toLowerCase();

    // Seperate Command Words

    // TODO: implement invalid command detection in python control code (>3 word commands are rejected below)
    // possible edit to 4 word command structure, if so we will have to implement change in command tree as well
    String CommandArray[3];
    int CommandArrayIndex = 0;
    int j = 0;

    for(int i = 0; i < command.length(); i++){
        if (command.charAt(i) == ' '){
            if (CommandArrayIndex == 2){
                Bluetooth_Write(BTdevice, "Invalid command: Enter 3 words");
                return;
            }

            CommandArray[CommandArrayIndex] = command.substring(j, i);

            CommandArrayIndex++;
            j = i + 1;
        }
    }
    
    if (CommandArrayIndex != 2){
        Bluetooth_Write(BTdevice, "Invalid command: 3 words");
        return;
    }
    
    CommandArray[CommandArrayIndex] = command.substring(j);
    
    String Word1 = CommandArray[0];
    String Word2 = CommandArray[1];
    float value = CommandArray[2].toFloat();
    
    //command tree

    //check if motor or servo control
    if (Word1 == "move"){
        // motors

        //check which side(s)
        if (Word2 == "walk"){
            //Move both sides at speed value
            if (fabs(value) > 3){
                Bluetooth_Write(BTdevice, "Error: move only under 3 meters");
                return;
            }
            Motors_Move_Distance(LeftMotors, RightMotors, value);
            Bluetooth_Write(BTdevice, "OK move " + String(value) + " meters");
            return;
        }
        else if(Word2 == "spin"){
            //Pivot in place, positive = clockwise
            if (fabs(value) > 360) {
                Bluetooth_Write(BTdevice, "Error: rotate between -360 and 360 degrees");
                return;
            }
            Motors_Rotate_Angle(LeftMotors, RightMotors, value);
            Bluetooth_Write(BTdevice, "OK spin " + String(value) + " degrees");
            return;
        }
        else{
            //error sender
            Bluetooth_Write(BTdevice, "Motor(s) not detected");
            return;
        }
    }
    else if (Word1 == "servo"){
        // servos
        if ( (value < 0) || (value > 180) ){
            Bluetooth_Write(BTdevice, "Error: move servo between 0 and 180 degrees");
            return;
        }

        //check which servos
        if (Word2 == "bottom"){
            MoveServo(Servo_a, value);
            Bluetooth_Write(BTdevice, "OK bottom servo moved");
            return;
        }
        else if (Word2 == "top"){
            MoveServo(Servo_b, value);
            Bluetooth_Write(BTdevice, "OK Top servo moved");
            return;
        }
        else{
            Bluetooth_Write(BTdevice, "Servo not detected");
            return;
        }
    }
    else{
        Bluetooth_Write(BTdevice, "Device type not detected");
        return;
    }
}
