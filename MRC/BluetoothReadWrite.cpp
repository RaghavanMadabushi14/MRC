#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include "include/BluetoothReadWrite.h"

String Bluetooth_Read(SoftwareSerial* BTdevice){
    if (YesSerial){
        if(Serial.available()){
            return Serial.readStringUntil('\n');
        }
        return "";
    }
    else{
        if((*BTdevice).available()){
            return (*BTdevice).readStringUntil('\n');
        }
        return "";
    }
}

void Bluetooth_Write(SoftwareSerial* BTdevice, String Response){
    if (YesSerial) Serial.println(Response);
    else (*BTdevice).println(Response);
}

void Serial_Bluetooth_Switch(){
    YesSerial = !YesSerial;
}
