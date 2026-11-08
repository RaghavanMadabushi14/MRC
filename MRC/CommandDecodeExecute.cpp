#pragma once

#include <Ardunio.h>
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

    if (command == ""){
            return;
        }

    // remove need for deferencing 
    Servo& ServoA = *Servo_a;
    Servo& ServoB = *Servo_b;
    Motors& Left = *LeftMotors;
    Motors& Right = *RightMotors;
    SoftwareSerial& Bluetooth = *BTdevice;

    // Seperate Command Words

    // TODO: implement invalid command detection in python control code (>3 word commands are rejected below)
    // possible edit to 4 word command structure, if so we will have to implement change in command tree as well
    String CommandArray[3];
    int CommandArrayIndex = 0;
    int j = 0;

    for(int i = 0; i < command.length(); i++){
        if (command.charAt(i) == ' '){
<<<<<<< HEAD
            if (CommandArrayIndex == 2){
                Bluetooth_Write(&Bluetooth, "Too many words in command");
                return;
            }

=======
            if (CommandArrayIndex == 3){
                Bluetooth_Write(&Bluetooth, "Invalid command: Enter only 3 words");
                return;
            }
            
>>>>>>> 0e7540e41453f36023817f9c7eb77ce9c3b02fff
            CommandArray[CommandArrayIndex] = command.substring(j, i);

            CommandArrayIndex++;
            j = i + 1;
        }
    }
    
    if (CommandArrayIndex < 2){
        Bluetooth_Write(&Bluetooth, "Invalid command:: Enter 3 words");
        return;
    }
    
    CommandArray[CommandArrayIndex] = command.substring(j);
    
    String Word1 = CommandArray[0];
    String Word2 = CommandArray[1];
    int value = CommandArray[2].toInt();
    
    //command tree

    //check if motor or servo control
    if (Word1 == "move"){
        // motors

        //check which side(s)
        if (Word2 == "both"){
            //Move both sides at speed value
            Motors_Tank(&Left, &Right, value, value);
            Bluetooth_Write(&Bluetooth, "OK both " + String(value));
            return;
        }
        else if (Word2 == "left"){
            //Move left side at speed value
            Motors_Drive(&Left, value, LEFT_MOTORS_REVERSED);
            Bluetooth_Write(&Bluetooth, "OK left " + String(value));
            return;
        }
        else if(Word2 == "right"){
            //Move right side at speed value
            Motors_Drive(&Right, value, RIGHT_MOTORS_REVERSED);
            Bluetooth_Write(&Bluetooth, "OK right " + String(value));
            return;
        }
        else if(Word2 == "spin"){
            //Pivot in place, positive = clockwise
            Motors_Tank(&Left, &Right, value, -value);
            Bluetooth_Write(&Bluetooth, "OK spin " + String(value));
            return;
        }
        else if(Word2 == "stop"){
            //Stop both motors
            Motors_Stop(&Left);
            Motors_Stop(&Right);
            Bluetooth_Write(&Bluetooth, "OK stop");
            return;
        }
        else{
            //error sender
            Bluetooth_Write(&Bluetooth, "Motor(s) not detected");
            return;
        }
    }
    else if (Word1 == "servo"){
        // servos

        //check which servos
        if (Word2 == "bottom"){
            MoveServo(&ServoA, value);
            return;
        }
        else if (Word2 == "top"){
            MoveServo(&ServoB, value);
            return;
        }
        else{
            Bluetooth_Write(&Bluetooth, "Servo not detected");
            return;
        }
    }
    else{
        Bluetooth_Write(&Bluetooth, "Device type not detected");
        return;
    }
}
