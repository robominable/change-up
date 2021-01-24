#include "include.hpp"

//USING OKAPI

std::shared_ptr<ChassisController> drive;
okapi::Controller controller;

void initialize() {
	/*Logger::setDefaultLogger( //log output to pros terminal
		std::make_shared<Logger>(
			TimeUtilFactory::createDefault().getTimer(),
			"/ser/sout",
			Logger::LogLevel::debug
		)
	);*/
	//pros::lcd::initialize();
	//pros::lcd::set_text(1, "Robominable | 4454A");
	drive = ChassisControllerBuilder()
		.withMotors(
			1, //  front left
			-2, // front right (reversed)
			-3, // back right (reversed)
			4 //   back left
		) //                green cartridge           wheel diam  11.5in wheelbase
		.withDimensions({AbstractMotor::gearset::green}, {{4_in, 11.5_in}, imev5GreenTPR})
		.withOdometry()
		.buildOdometry();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}


void autonomous() {

}


void opcontrol() {
	while (true) {
		auto xModel = std::dynamic_pointer_cast<XDriveModel>(drive->getModel());
		xModel->xArcade(controller.getAnalog(ControllerAnalog::leftY), 
						controller.getAnalog(ControllerAnalog::leftX),
						controller.getAnalog(ControllerAnalog::rightX)
		);



		pros::delay(15);
	}
}