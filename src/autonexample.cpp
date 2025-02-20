#include "main.h"

void autonomous() {
    // 1. Drive forward 30 inches.
    // Assume your field coordinate system is set up so that moving forward places you at (-30, 0).
    chassis.moveToPoint(-30, 0, 4000);
    chassis.waitUntilSettled();

    // 2. Extend the clamp.
    clamp1.extend();
    pros::delay(350);

    // 3. Activate the reverse combine motor.
    setIntake(-127);

    // 4. Turn to a heading of 285°.
    chassis.turnToHeading(285, 4000);
    chassis.waitUntilSettled();

    // 5. Drive forward 28 inches.
    // For example, move to (-58, 0). Adjust these coordinates to suit your robot's path.
    chassis.moveToPoint(-58, 0, 4000);
    chassis.waitUntilSettled();

    // 6. Turn to a heading of 110°.
    chassis.turnToHeading(110, 4000);
    chassis.waitUntilSettled();

    // 7. Drive forward 45 inches.
    // For example, move to (-103, 0). Update these coordinates as needed.
    chassis.moveToPoint(-103, 0, 4000);
    chassis.waitUntilSettled();

    // 8. Optionally, move to a specific pose.
    // This command will move the robot to position (10, 10) with a heading of 90°.
    chassis.moveToPose(10, 10, 90, 4000);
    chassis.waitUntilSettled();
}
