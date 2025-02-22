#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autons.hpp"
#include "globals.hpp"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pros/llemu.hpp"
#include "pros/apix.h"
#include "robodash/apix.h"


double hue;
bool intakeActive = false;
ASSET(BlueLeft1_txt);
ASSET(BlueLeft2_txt);

rd::Selector selector({
    {"Red Left", redLeftSide},
    {"Red Right", redRightSide},
    {"Blue Left", blueLeftSide},
    {"Blue Right", blueRightSide},
    {"Skills", skills}
});

rd::Console console;

//rd_view_t *image_view = rd_view_create("Image");

//int autonSelected = 0; // 0 = no auton selected

const int numStates = 3;
int states[numStates] = {0, 80, 2000}; // or try 0,300,2000
int currentState = 0;
int target = 0;

void nextState() {
    currentState += 1;
    if (currentState == numStates) {
        currentState = 0;
    }
    target = states[currentState];
}

void liftControl() {
    double kp = 2.80;
    //double error = target - rotation_sensor.get_position();
    //double velocity = kp * error;
   // ladyBrown.move(velocity);
   ladyBrown.move(kp * (target - (rotation_sensor.get_position()/100.0)));
}


// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motor groups
pros::MotorGroup leftMotors({-3, -2, -20}, pros::MotorGearset::blue);  // left motor group
pros::MotorGroup rightMotors({1, 5, 9}, pros::MotorGearset::blue); // right motor group

pros::Imu imu(7);

// Drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 14, lemlib::Omniwheel::OLD_275, 360, 2);

// Lateral motion controller
lemlib::ControllerSettings linearController(10, 0, 3, 3, 1, 100, 3, 500, 20);

// Angular motion controller
lemlib::ControllerSettings angularController (2, 0, 10, 3, 1, 100, 3, 500, 0); //(0.35, 0, 15, 0, 0, 0, 0, 0, 0); //(.25, 0.00000025, .25, 0, 0, 0, 0, 0, 0); 

// Sensors for odometry
lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);

// Input curves for driver control
lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);

// Create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

/**
 * Color sorting functions.
 */

void colorSortRed() {
    static int ejectState = 0;
    static uint32_t ejectStartTime = 0;
    const int intakeTime = 200;  // Time to intake after detection (ms)
    const int waitTime = 170;    // Time to wait before ejecting (ms)
    const int ejectTime = 400;   // Time to eject (ms)

    if (!intakeActive) {
        setIntake(0);
        ejectState = 0;
        return;
    }

    double hue = optical_sensor.get_hue();
    int proximity = optical_sensor.get_proximity();

    switch (ejectState) {
        case 0: // Normal operation
            setIntake(-127); // Intake in
            if ((hue >= 200 && hue <= 240)) {
                ejectStartTime = pros::millis();
                ejectState = 1;
            }
            break;

        case 1: // Intake for a bit longer
            setIntake(-127);
            if (pros::millis() - ejectStartTime >= intakeTime) {
                ejectStartTime = pros::millis();
                ejectState = 2;
                setIntake(0);
            }
            break;

        case 2: // Wait for ring to move up
            if (pros::millis() - ejectStartTime >= waitTime) {
                ejectStartTime = pros::millis();
                ejectState = 3;
                setIntake(127); // Eject out
            }
            break;

        case 3: // Eject the ring
            if (pros::millis() - ejectStartTime >= ejectTime) {
                ejectState = 0;
                setIntake(-127); // Resume intake
            }
            break;
    }
}

void colorSortBlue() {
    static int ejectState = 0;
    static uint32_t ejectStartTime = 0;
    const int intakeTime = 200;
    const int waitTime = 300;
    const int ejectTime = 500;

    if (!intakeActive) {
        setIntake(0);
        ejectState = 0;
        return;
    }

    double hue = optical_sensor.get_hue();
    int proximity = optical_sensor.get_proximity();

    switch (ejectState) {
        case 0:
            setIntake(-127);
            if ((hue < 10 || hue > 350)) {
                ejectStartTime = pros::millis();
                ejectState = 1;
            }
            break;

        case 1:
            setIntake(-127);
            if (pros::millis() - ejectStartTime >= intakeTime) {
                ejectStartTime = pros::millis();
                ejectState = 2;
                setIntake(0);
            }
            break;

        case 2:
            if (pros::millis() - ejectStartTime >= waitTime) {
                ejectStartTime = pros::millis();
                ejectState = 3;
                setIntake(127);
            }
            break;

        case 3:
            if (pros::millis() - ejectStartTime >= ejectTime) {
                ejectState = 0;
                setIntake(-127);
            }
            break;
    }
}



/**
 * Runs initialization code.
 */
void initialize() {
    chassis.calibrate(); // calibrate chassis
    

    rotation_sensor.reset_position();

    // Launch the lift control task with proper yielding
    pros::Task liftControlTask([]{
        while (true) {
            liftControl();
            pros::delay(10);
        }
    });


    // Launch the color sort task with a delay in each loop iteration
    
    optical_sensor.set_led_pwm(100);
    optical_sensor.set_integration_time(5);

    pros::Task colorSortTask([]{
        while (true) {
            if (alliance == 1) {
                colorSortRed();
            } else if (alliance == 2) {
                colorSortBlue();
            }
            pros::delay(20); // Reduce CPU usage
        }
    });

    // You can include other initialization code here as needed.
}
    


/**
 * Runs while the robot is disabled.
 */
void disabled() {}

/**
 * Runs competition initialization routines.
 */
void competition_initialize() {}

/**
 * Autonomous routine.
 */



void autonomous() {
    
    // Run selected autonomous
    selector.run_auton();
    

    // set position to x:0, y:0, heading:0
   // chassis.setPose(64.31, -23.326, 270);
    // turn to face heading 90 with a very long timeout
    // chassis.turnToHeading(90, 100000);
    //chassis.moveToPose(47, -7, 33, 1500, {.maxSpeed = 127});
    //pros::delay(500);
    //lift.setTarget(190);
    //pros::delay(500);
    //chassis.moveToPoint(-36, -12, 1500, {.forwards = false}, true);
    //pros::delay(500);
    //lift.setTarget(0);
   // chassis.follow(BlueLeft1_txt, 5, 5000);

   // pros::Task liftControlTask([]{
     //  clamp1.retract();
     //  setIntake(127);
   // });

}

/**
 * Operator control code.
 */
void opcontrol() {
    while (true) {
        // Retrieve joystick values for tank control.
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        chassis.tank(-leftY, -rightY);


        
        if (controller.get_digital(DIGITAL_B) && controller.get_digital(DIGITAL_DOWN)) {
            autonomous();
        }
        
        if (controller.get_digital(DIGITAL_UP)) {
          intakeActive = true;
          optical_sensor.set_led_pwm(100);
       }
        //if (controller.get_digital(DIGITAL_DOWN)) {
           
         //   intakeActive = true;
         //   setIntake(115);
       // }
        if (controller.get_digital(DIGITAL_RIGHT)) {
            intakeActive = false;
            setIntake(0);
        }

        if (controller.get_digital_new_press(DIGITAL_R1)) {
            clamp1.toggle();
        }

        if (controller.get_digital_new_press(DIGITAL_Y)) {
            tipper.toggle();
        }

        if (controller.get_digital_new_press(DIGITAL_L1)) {
          nextState();
        }
    }
}
