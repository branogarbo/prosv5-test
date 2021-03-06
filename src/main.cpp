#include "main.h"

// DEFINE DEVICES
/////////////////////////////////////////////

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor FL_wheel(1);
pros::Motor FR_wheel(2);

pros::Motor BL_wheel(3);
pros::Motor BR_wheel(4);

pros::ADIButton limitSwitch('a');

/////////////////////////////////////////////

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol()
{
	pros::lcd::clear();

	while (true)
	{
		int joyLY = master.get_analog(ANALOG_LEFT_Y);
		int joyRY = master.get_analog(ANALOG_RIGHT_Y);

		bool A_btn = master.get_digital(DIGITAL_A);

		FL_wheel.move(joyLY);
		BL_wheel.move(joyLY);

		FR_wheel.move(joyRY);
		BR_wheel.move(joyRY);

		if (A_btn)
		{
			pros::lcd::set_text(1, "A is pressed");
		}

		if (limitSwitch.get_value())
		{
			pros::lcd::set_text(1, "Ow!!");
		}

		pros::delay(20);
	}
}
