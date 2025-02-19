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

int autonSelected = 0; // 0 = no auton selected

const int numStates = 3;
int states[numStates] = {0, 1600, 19500}; // or try 0,300,2000
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
    double kp = 1.14;
    double error = target - rotation_sensor.get_position();
    double velocity = kp * error;
    ladyBrown.move(velocity);
}

rd_view_t *image_view = rd_view_create("Image");


rd::Selector selector({
    {"Best auton", best_auton},
    {"Simple auton", simple_auton},
    {"Good auton", good_auton},
});

rd::Console console;

rd::Image image("S/usd/logo.bin", "Team Logo");


// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motor groups
pros::MotorGroup leftMotors({3, 2, 20}, pros::MotorGearset::blue);  // left motor group
pros::MotorGroup rightMotors({-1, -5, -9}, pros::MotorGearset::blue); // right motor group

pros::Imu imu(7);

// Drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 10, lemlib::Omniwheel::OLD_275, 360, 4);

// Lateral motion controller
lemlib::ControllerSettings linearController(10, 0, 3, 0, 0, 0, 0, 0, 0);

// Angular motion controller
lemlib::ControllerSettings angularController(5.5, 0, 45.5, 3, 1, 150, 3, 500, 0);

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
    if (intakeActive) {
        optical_sensor.set_led_pwm(100);
        // Use a single check without a blocking infinite loop.
        double hue = optical_sensor.get_hue();
        optical_sensor.set_integration_time(3);
        if ((hue < 10 || hue > 355)) {
            setIntake(0);
            pros::delay(1000);
        }
    }
    else {
        setIntake(0);
    }
}

void colorSortBlue() {
    if (intakeActive) {
        setIntake(-115);
        double hue = optical_sensor.get_hue();
        optical_sensor.set_integration_time(3);
        if ((200 < hue && hue < 240)) {
            setIntake(0);
            pros::delay(1000);
        }
    }
    else {
        setIntake(0);
    }
}
*/

/**
 * Runs initialization code.
 */
void initialize() {
    chassis.calibrate(); // calibrate chassis
    console.println("Console inititalized!");
    console.printf("System time: %d\n", pros::millis());
    imu.reset();

    rotation_sensor.reset_position();

    // Launch the lift control task with proper yielding
    pros::Task liftControlTask([]{
        while (true) {
            liftControl();
            pros::delay(10);
        }
    });

    // Launch the color sort task with a delay in each loop iteration
    /*
    pros::Task colorSortTask([]{
        while (true) {
            if (alliance == 1) {
                colorSortRed();
            }
            else if (alliance == 2) {
                colorSortBlue();
            }
            pros::delay(50); // Yield to allow other tasks to run
        }
    });

    // You can include other initialization code here as needed.
    */
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
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);

    // turn to face heading 90 with a very long timeout
    //chassis.turnToHeading(90, 100000);
    chassis.moveToPoint(0, 48, 100000);

    //selector.run_auton();
    // Additional autonomous actions can be added here if needed.
}

/**
 * Operator control code.
 */
void opcontrol() {
    while (true) {
        // Retrieve joystick values for tank control.
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        chassis.tank(leftY, rightY);

        pros::delay(25); // Delay to save resources

        
        if (controller.get_digital(DIGITAL_B) && controller.get_digital(DIGITAL_DOWN)) {
            autonomous();
        }


       // if (controller.get_digital_new_press(DIGITAL_UP)) {
            //angularController.kD += 0.1;
            //console.printf("New Kd: %.2f\n", angularController.kD);
        //}
        
        if (controller.get_digital(DIGITAL_UP)) {
          intakeActive = true;
          //colorSortRed();
          setIntake(-115);
       }
        //if (controller.get_digital(DIGITAL_DOWN)) {
           
         //   intakeActive = true;
          //  setIntake(115);
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
