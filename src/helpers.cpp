#include "main.h"



void setIntake(int intakePower) 
{
  combine.move(intakePower);
  hooks.move(intakePower);
}

void clampSwitch()
{
 if (clamp1.is_extended())
  {
    clamp1.retract();
  }
 else
  {
    clamp1.extend();
  }
}