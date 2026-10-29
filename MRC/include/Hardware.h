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