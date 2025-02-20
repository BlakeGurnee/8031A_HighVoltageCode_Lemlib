#include "main.h"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep

// These are out of 127
const int drive_speed = 70;
const int TURN_SPEED = 90;
const int SWING_SPEED = 95;

void redLeftSide() // 4 ring
{
  alliance = 1;
  pros::lcd::clear();
  pros::lcd::print(1, "Red Left side Auton Running.");
  
}

void redRightSide() // Auton for right (or far) side of the field scores 2 rings on mobile goal and touches the ladder
{
  alliance = 1;
  pros::lcd::clear();
  pros::lcd::print(1, "Red Right side Auton Running.");
  chassis.moveToPoint(30, )
}

void blueLeftSide()
{
  alliance = 2;
  pros::lcd::clear();
  pros::lcd::print(1, "Blue Left side Auton Running.");
}

void blueRightSide() { // 4 ring
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
}
  
void soloWp() //Scores 1 ring on alliance wall stake and 2 rings on alliance mobile goal and touches the ladder
{

}

void skills() //Auton for skills matches
{
  alliance = 1;
  pros::lcd::clear();
  pros::lcd::print(1, "Skills Auton Running.");
  
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
  pros::lcd::clear();
  pros::lcd::print(1, "Red Auton Running.");
}
void setAllianceBlue() // Sets alliance to blue for driver control color sorting test
{
  alliance = 2;
  pros::lcd::clear();
  pros::lcd::print(1, "Blue Auton Running.");
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