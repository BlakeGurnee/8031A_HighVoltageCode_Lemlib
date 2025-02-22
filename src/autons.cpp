#include "main.h"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep

// These are out of 127
const int drive_speed = 70;
const int TURN_SPEED = 90;
const int SWING_SPEED = 95;

ASSET(BlueLeft1_txt);
ASSET(BlueLeft2_txt);
ASSET(BlueRight1_txt);
ASSET(BlueRight2_txt);
ASSET(RedLeft1_txt);
ASSET(RedLeft2_txt);
ASSET(RedRight1_txt);
ASSET(RedRight2_txt);

void redLeftSide() // 4 ring
{
  alliance = 1;
  chassis.setPose(64.609, -23.528, 90);
  chassis.follow(RedLeft1, 5, 5000);
  chassis.setPose(-28.338, 26.722, 308.4)
  chassis.follow(RedLeft2, 5, 5000, false);

  pros::Task redleft([]{
  setIntake(0);
  clamp1.retract();
  pros::delay(500);
  setIntake(-127);
});
  
}


void redRightSide() // Auton for right (or far) side of the field scores 2 rings on mobile goal and touches the ladder
{
  alliance = 1;
  chassis.setPose(65.276, 23.73, 81);
  chassis.follow(RedRight1, 5, 5000);
  chassis.setPose(-27.753, -20.153, 100);
  chassis.follow(RedRight2, 5, 5000, false);

pros::Task redRight([]{
  setIntake(0);
  clamp1.retract();
  pros::delay(500);
  setIntake(-127);
});
}

void blueLeftSide()
{
  alliance = 2;
  chassis.setPose(64.609, -23.528, 226);
  chassis.follow(BlueLeft1_txt, 5, 5000);
  chassis.setPose(27.88, -21.275, 62.7);
  chassis.follow(BlueLeft2_txt, 5, 5000, false);
 
 pros::Task blueleft([]{
  setIntake(0);
  clamp1.retract();
  pros::delay(500);
  setIntake(-127);
});

}

void blueRightSide() { // 4 ring

  chassis.setPose(65.276, 23.73, 270.4);
  chassis.follow(BlueRight1, 5, 5000);
  chassis.setPose(28.311, 20.986, 123.2);
  chassis.follow(BlueRight2, 5, 5000, false);

  pros::Task blueright([]{
  setIntake(0);
  clamp1.retract();
  pros::delay(500);
  setIntake(-127);
});

  /*
  alliance = 2;
  clamp1.retract();
  pros::delay(500);

  chassis.moveToPose(0, 24, 180, 1000);
  chassis.waitUntilDone();

  clamp1.extend();
  pros::delay(500);

  chassis.turnToHeading(90, 1000);
  chassis.waitUntilDone();

  setIntake(-115);
  chassis.moveToPoint(36, 0, 1500);
  chassis.waitUntilDone();

  pros::delay(1000);
  setIntake(0);

  chassis.turnToHeading(450, 2000);
  chassis.waitUntilDone();

  chassis.moveToPoint(48, 48, 2000);
  chassis.waitUntilDone();
  */
}
  

void skills() //Auton for skills matches
{
  alliance = 1;
  chassis.setPose(-64.804, 35.429, 100);

  
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

void best_auton() {
  alliance = 2;
}

void simple_auton() {
  // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 100000);
}

void good_auton() {
  
}

// add more normal autons here
//
//