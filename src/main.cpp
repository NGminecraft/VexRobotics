/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       minec                                                     */
/*    Created:      12/12/2025, 2:46:19 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "Cycle/MainLoop.h"
#include "Cycle/Phases/DisplayPhase.h"
#include "Cycle/Phases/TelemetryPhase.h"
#include "Cycle/Phases/UserPhase.h"
#include "Objects/ControllerState.h"
#include "Objects/DrivetrainState.h"
#include "Telemetry/Displaying/Widgets/Items/VaraibleString.h"
#include "Telemetry/Logging/Logger.h"

#include "Telemetry/Logging/LogMethods/Formatting/LogLevelElement.h"
#include "Telemetry/Logging/LogMethods/Formatting/LogStringElement.h"
#include "Telemetry/Logging/LogMethods/Formatting/LogTimestamp.h"

#include "Telemetry/Logging/LogMethods/LogHandling/ScrollingStringsHandle.h"
#include "Telemetry/Logging/LogMethods/LogHandling/SerialLogger.h"

#include <cmath>
#include <cstdio>
#include <DataTypes/Rotations.h>
#include <ObjectGroups/Motors/Arm.h>
#include <Objects/MotorState.h>
#include <string>
#include <Telemetry/Displaying/ScreenItem.h>
#include <Telemetry/Displaying/Widgets/Items/ScrollingString.h>
#include <Telemetry/Logging/LogMethods/Formatting/LogFormat.h>
#include <vex_brain.h>
#include <vex_controller.h>
#include <vex_drivetrain.h>
#include <vex_global.h>
#include <vex_motor.h>
#include <vex_motorgroup.h>

// Define M_PI if not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

vex::controller Controller1;
ControllerState controllerState(Controller1);

vex::motor DriveLeftMotor(vex::PORT10, false);
vex::motor DriveRightMotor(vex::PORT1, true);

//ARM MOTORS
vex::motor ArmMotor1(vex::PORT11, false);
vex::motor ArmMotor2(vex::PORT12, false);
vex::motor ArmMotor3(vex::PORT13, false);

vex::rotation ArmMotor1Rotation = vex::rotation(vex::PORT16);

MotorState armMotorState1(ArmMotor1);
MotorState armMotorState2(ArmMotor2);
MotorState armMotorState3(ArmMotor3);

RotationState armMotorRotationState1(ArmMotor1Rotation);

Arm<3> robotArm{Rotation()};

vex::motor_group leftMotors(DriveLeftMotor);
vex::motor_group rightMotors(DriveRightMotor);

vex::drivetrain Drivetrain(leftMotors, rightMotors);
DrivetrainState drivetrainState(Drivetrain);

int main() {
	Brain.Screen.print("Initializing...");
	printf("Initializing... \n");
	/* Create the logger */
	Logger& logger = Logger::getInstance("Main");
	
	// Add some formatting to the logger
	LogLevelElement logLevelElement(LogElementSeperators::BRACKET);
	logger.prependElement(&logLevelElement);

	LogTimestamp logTimestamp(LogElementSeperators::BRACKET);
	logger.prependElement(&logTimestamp);	

	LogStringElement string("-", LogElementSeperators::SPACE);
	logger.prependElement(&string);

	// Logger handles
	ScrollingString<5> logDisplay(0, 15);
	ScrollingStringsHandle<5> logHandle(logDisplay);

	logger.addHandle(&logHandle);
	logger.addHandle(new SerialLoggerHandle());

	logger.log(std::string("Logger initialized"));

	// Our event loop
	MainLoop mainLoop;

	/* ---Controller Setup--- */
	// Enable only the telemetry axis classes to be updated every tick
	controllerState.setInterval({ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

	// Register the controller state with it's dedicated telemetry phase
	TelemetryPhase controllerTelemetryPhase;
	controllerTelemetryPhase.registerTelemetryUpdate(&controllerState);

	// Register the controllers telemetry phase
	logger.log("Registering controller telemetry", Logger::LogLevel::INFO);
	mainLoop.registerPhase(&controllerTelemetryPhase);


	logger.log("Initializing arm");

	robotArm.addJoint(0, armMotorState1, 12.5, Rotation::XAxis(0), armMotorRotationState1);
	robotArm.addJoint(1, armMotorState2, 12.5, Rotation::XAxis(0), true);
	robotArm.addJoint(2, armMotorState3, 1.0, Rotation::XAxis(0), false);

	armMotorState1.setTelemetryIntervals(2);
	armMotorState2.setTelemetryIntervals(2);
	armMotorState3.setTelemetryIntervals(2);

	armMotorRotationState1.setTelemetryIntervals(5);


	/* ---User Phase Setup--- */
	// Set the movement logic for the user
	ArcadeMovement<ControllerState::TelemetryTypes::Axis3, ControllerState::TelemetryTypes::Axis4> movementLogic;
	ArmMovement<ControllerState::TelemetryTypes::Axis1, ControllerState::TelemetryTypes::Axis2, 3> armMovementLogic;
	// Create the user phase with the movement logic
	UserPhase<decltype(movementLogic), decltype(armMovementLogic)> userPhase(controllerState, drivetrainState, robotArm);

	// Register the user phase
	logger.log("Registering user control phase", Logger::LogLevel::INFO);
	mainLoop.registerPhase(&userPhase);

	TelemetryPhase telemetryPhase;
	telemetryPhase.registerTelemetryUpdate(&drivetrainState);
	telemetryPhase.registerTelemetryUpdate(&armMotorState1);
	telemetryPhase.registerTelemetryUpdate(&armMotorState2);
	telemetryPhase.registerTelemetryUpdate(&armMotorState3);

	telemetryPhase.registerTelemetryUpdate(&armMotorRotationState1);

	mainLoop.registerPhase(&telemetryPhase);

	/* ---Display Phase Setup-- */
	
	DisplayPhase displayPhase(10, Brain);
	logger.log("Setting up display phase", Logger::LogLevel::INFO);
	
	// Example displayPhase usage: displaying the joystick values
	ScreenItem* joystickDisplay = makeVariableString(
		"Axis 1/2: %d %d | Axis 3/4: %d %d", 
		10, 14,  // x, y screen coordinates
		&controllerState.getTelemetry<ControllerState::TelemetryTypes::Axis1>()->getData().value,
		&controllerState.getTelemetry<ControllerState::TelemetryTypes::Axis2>()->getData().value,
		&controllerState.getTelemetry<ControllerState::TelemetryTypes::Axis3>()->getData().value,
		&controllerState.getTelemetry<ControllerState::TelemetryTypes::Axis4>()->getData().value
	);

	// Add to display phase
	displayPhase.addToScreen(joystickDisplay);

	// Add the log display to the screen as well
	displayPhase.addToScreen(&logDisplay);

	logger.log("Registering display phase", Logger::LogLevel::INFO);
	// Register the display phase
	mainLoop.registerPhase(&displayPhase);

	robotArm.calibrateArm();

	// Start the main loop
	mainLoop.loop();
}
