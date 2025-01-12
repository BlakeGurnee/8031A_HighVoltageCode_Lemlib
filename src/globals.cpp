#include "main.h"

//motors
//pros::Motor combine(4, pros::v5::MotorGears::green);
pros::Motor combine(4, pros::v5::MotorGears::green);
pros::Motor hooks(16, pros::v5::MotorGears::blue);
pros::Motor ladyBrown(18, pros::v5::MotorGears::green);
 

//Pneumatics
pros::adi::Pneumatics clamp1('A', false);

//Sensors
pros::Optical optical_sensor(14);
pros::Rotation rotation_sensor(3);
int alliance = 1;