#include "main.h"

//motors
pros::Motor combine(-4, pros::v5::MotorGears::green);
pros::Motor hooks(16, pros::v5::MotorGears::blue);
pros::Motor ladyBrown(18, pros::v5::MotorGears::green);


//Pneumatics
pros::adi::Pneumatics clamp1('A', false);
pros::adi::Pneumatics hang('B', false);

//Sensors
pros::Optical optical_sensor(14);
pros::Rotation rotation_sensor(19);
pros::Distance distance_sensor(12);
pros::adi::DigitalIn limitSwitch('H');
int alliance = 1;
int team = 1;