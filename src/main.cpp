#include "include.hpp"

//USING OKAPI

std::shared_ptr<ChassisController> drive;
okapi::Controller controller;
auto opticalHue = OpticalSensor(15);
okapi::Motor upperIntake(-19);
okapi::Motor middleIntake(-11);
okapi::Motor Lintake(14);
okapi::Motor Rintake(18);



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
			9, //  front left
			-6, // front right (reversed)
			-3, // back right (reversed)
			10 //   back left
		) //                green cartridge           wheel diam  11.5in wheelbase
		.withDimensions({AbstractMotor::gearset::green}, {{4_in, 11.5_in}, imev5GreenTPR})
		.withOdometry()
		.buildOdometry();
		upperIntake.setGearing(okapi::Motor::gearset::red);
		middleIntake.setGearing(okapi::Motor::gearset::green);
		Lintake.setGearing(okapi::Motor::gearset::green);
		Rintake.setGearing(okapi::Motor::gearset::green);
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
	okapi::ControllerButton R1(ControllerDigital::R1);
	okapi::ControllerButton R2(ControllerDigital::R2);
	okapi::ControllerButton L1(ControllerDigital::L1);
	okapi::ControllerButton L2(ControllerDigital::L2);
	while (true) {
		auto xModel = std::dynamic_pointer_cast<XDriveModel>(drive->getModel());
		xModel->xArcade(controller.getAnalog(ControllerAnalog::leftY),
						controller.getAnalog(ControllerAnalog::leftX),
						controller.getAnalog(ControllerAnalog::rightX)
		);

		if(R1.isPressed()){
			upperIntake.moveVoltage(12000);
			middleIntake.moveVoltage(12000);
		}
		else if(R2.isPressed()){
			upperIntake.moveVoltage(-12000);
			middleIntake.moveVoltage(12000);
		}
		else{
			upperIntake.moveVoltage(0);
			middleIntake.moveVoltage(0);
		}

		if(L1.isPressed()){
			Lintake.moveVoltage(12000);
			Rintake.moveVoltage(-12000);
		}
		else if(L2.isPressed()){
			Lintake.moveVoltage(-12000);
			Rintake.moveVoltage(12000);
		}
		else{
			Lintake.moveVoltage(0);
			Rintake.moveVoltage(0);
		}

		pros::delay(10);
	}
}
