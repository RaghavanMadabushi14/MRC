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
#include "include/CommandDecodeExecute.h"

FirstWordEnum DeviceSwitchInput(String device){
    if (device == "move") return MOVE;
    if (device == "servo") return SERVO;
    if (device == "servos") return SERVOS;
    else return NONE;
}

bool Valid_toFloat(String num_maybe){
    // maybe will do (?)
}

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
            if (i == j){
                j++;
                continue;
            }
            
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
    String Word3 = CommandArray[2];

    float Word3_value = Word3.toFloat();
    
    //command tree

    FirstWordEnum DeviceInstructionEnum = DeviceSwitchInput(Word1);
    switch(DeviceInstructionEnum){
        case MOVE:
            if (Word2 == "walk")
            {
                if (fabs(Word3_value) > 3){
                    Bluetooth_Write(BTdevice, "Error: move only under 3 meters");
                    return;
                }
                Motors_Move_Distance(LeftMotors, RightMotors, Word3_value);
                Bluetooth_Write(BTdevice, "OK move " + String(Word3_value) + " meters");
                return;
            }
            else if(Word2 == "spin")
            {
                if (fabs(Word3_value) > 360){
                    Bluetooth_Write(BTdevice, "Error: rotate between -360 and 360 degrees");
                    return;
                }
                Motors_Rotate_Angle(LeftMotors, RightMotors, Word3_value);
                Bluetooth_Write(BTdevice, "OK spin " + String(Word3_value) + " degrees");
                return;
            }
            else
            {
                //error sender
                Bluetooth_Write(BTdevice, "Movement mode not detected");
                return;
            }

        case SERVO:
            if ( (Word3_value < 0) || (Word3_value > 180) ){
                Bluetooth_Write(BTdevice, "Error: move servo between 0 and 180 degrees");
                return;
            }
            if (Word2 == "bottom"){
                MoveServo(Servo_a, Word3_value);
                Bluetooth_Write(BTdevice, "Bottom servo moved to" + String(Word3_value) + " degrees");
                return;
            }
            else if (Word2 == "top"){
                MoveServo(Servo_b, Word3_value);
                Bluetooth_Write(BTdevice, "Top servo moved to" + String(Word3_value) + " degrees");
                return;
            }
            else{
                Bluetooth_Write(BTdevice, "Servo not detected");
                return;
            }

        case SERVOS:
            float Word2_value = Word2.toFloat();
            
            if ( (Word3_value < 0) || (Word3_value > 180) || (Word2_value < 0) || (Word2_value > 180) ){
                Bluetooth_Write(BTdevice, "Error: move servos between 0 and 180 degrees");
                return;
            }
            MoveBothServos(Servo_a, Servo_b, Word2_value, Word3_value);
            Bluetooth_Write(BTdevice, "Both servos moved to " + String(Word2_value) + " and " + String(Word3_value) + " degrees");
            return;
            
        case NONE:
            Bluetooth_Write(BTdevice, "Device type not detected");
            return;            
    }
}