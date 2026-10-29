#include <stdio.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "Pin_assignments.h"

typedef struct{
  int IN13;
  int IN24;
  int EN;
} Motors;

void Init_Right_Motors(Motors* MotorSide);

void Init_Left_Motors(Motors* MotorSide);

void Init_Servos();

void Init_Bluetooth();

void Init_Hardware(Motors* MotorsRightSide, Motors* MotorsLeftSide, Servo* servo_a, Servo* servo_b, SoftwareSerial* BTdevice);
