#include <stdio.h>
#include <SoftwareSerial.h>
#include "include/BluetoothReadWrite.h"

String Bluetooth_Read(SoftwareSerial* BTdevice){
    if((*BTdevice).available()){
        return (*BTdevice).readStringUntil('\n');
    }
    return "";
}

void Bluetooth_Write(SoftwareSerial* BTdevice, String Response){
    (*BTdevice).println(Response);
}
