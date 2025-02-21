#include "main.h" // Include the main file for refrences to all motors and files

// Motors
pros::Motor combine(-4, pros::v5::MotorGears::green); // Motor is a reversed green motor on port 4
pros::Motor hooks(16, pros::v5::MotorGears::blue); // Motor is a normal blue motor on port 16
pros::Motor ladyBrown(18, pros::v5::MotorGears::green); // Motor is a normal green motor on port 10

//Pneumatics
pros::adi::Pneumatics clamp1('A', true); // Starts clamp in the false (Down) position when the code starts in port A
pros::adi::Pneumatics tipper('H', false); // Starts tipper in the false (Down) position when the code starts in port A

//Sensors
pros::Optical optical_sensor(14); // Optical Sensor in port 14
pros::Rotation rotation_sensor(19); // Rotation Sensor in port 19
pros::Distance distance_sensor(12); // Distance Sensor in port 12
pros::adi::DigitalIn limitSwitch('B'); // Limit Switch in port B
int alliance = 1; // Default alliance is 1 which is red
