#pragma once

#include <stdio.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "include/Hardware.h"
#include "include/MotorControls.h"
#include "include/BluetoothReadWrite.h"
#include "include/ServoControls.h"
#include "include/Pin_assignments.h"


void Command_Decode_Execute(String command, Servo* Servo_a, Servo* Servo_b, Motors* LeftMotors, Motors* RightMotors, SoftwareSerial* BTdevice){
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

    // TODO: implement invalid command detection in python control code (giving a >3 word command will do bad things)

    String CommandArray[3];
    int CommandArrayIndex = 0;
    int j = 0;

    for(int i = 0; i < command.length(); i++){
        if (command.charAt(i) == ' '){
            
            CommandArray[CommandArrayIndex] = command.substring(j, i);

            CommandArrayIndex++;
            j = i + 1;
        }
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

        }
        else if (Word2 == "left"){
            //Move left side at speed value

        }
        else if(Word2 == "right"){
            //Move right side at speed value
        }
        else if(word2 == "stop"){
            //Stop both motors
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
