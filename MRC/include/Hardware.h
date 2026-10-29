#include <stdio.h>
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

Motors Init_Right_Motors(Motors* MotorSide);

Motors Init_Left_Motors(Motors* MotorSide);

hc06 Init_hc06(hc06* MyHC06);

servo Init_Top_Servo(servo* MyServo);

servo Init_Bottom_Servo(servo* MyServo);