#include <stdio.h>
#include <SoftwareSerial.h>
#include "Pin_assignments.h"

typedef struct{
  int IN13;
  int IN24;
  int EN;
} Motors;

typedef struct{
  int rx;
  int tx;
} hc06;

typedef struct{
  int servo_control;
} servo;

void Init_Right_Motors(Motors* MotorSide);

void Init_Left_Motors(Motors* MotorSide);

void Init_hc06(hc06* MyHC06);

void Init_Top_Servo(servo* MyServo);

void Init_Bottom_Servo(servo* MyServo);
