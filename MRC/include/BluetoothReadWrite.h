#include <stdio.h>
#include <SoftwareSerial.h>
#include "Hardware.h"

#pragma once

String Bluetooth_Read(SoftwareSerial* BTdevice);

void Bluetooth_Write(SoftwareSerial* BTdevice, String Respone);