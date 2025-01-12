#include "main.h"

// These are out of 127
const int drive_speed = 70;
const int TURN_SPEED = 90;
const int SWING_SPEED = 95;

void redLeftSide() // 4 ring
{
  alliance = 1;
  
}

void redRightSide() // Auton for right (or far) side of the field scores 2 rings on mobile goal and touches the ladder
{
  alliance = 1;

}

void blueLeftSide()
{
  alliance = 2;
 
}

void blueRightSide() { // 4 ring
  alliance = 2;
  
}
void soloWp() //Scores 1 ring on alliance wall stake and 2 rings on alliance mobile goal and touches the ladder
{

}

void skills() //Auton for skills matches
{
  alliance = 1;
  
}


void test() // auton for testing purposes
{
  
}
void autonTest() // auton for testing purposes
{

}

void setAllianceRed() // Sets alliance to red for driver control color sorting test
{
  alliance  = 1;
}
void setAllianceBlue() // Sets alliance to blue for driver control color sorting test
{
  alliance = 2;
}

// add more normal autons here
//
//