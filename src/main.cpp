/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       minec                                                     */
/*    Created:      12/12/2025, 2:46:19 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Cycle/MainLoop.h"
#include "Cycle/Phases/UserPhase.h"
#include "Objects/ControllerState.h"
#include "Objects/DrivetrainState.h"
#include "Telemetry/Logging/Logger.h"
#include "Cycle/Phases/TelemetryPhase.h"
#include "Cycle/Phases/DisplayPhase.h"
#include "Telemetry/Displaying/Widgets/Items/VaraibleString.h"
#include "Telemetry/TelemetryObjects/Controller/ControllerTelemetryHeaders.h"

#include "Telemetry/Logging/LogMethods/Formatting/LogLevelElement.h"
#include "Telemetry/Logging/LogMethods/Formatting/LogStringElement.h"
#include "Telemetry/Logging/LogMethods/Formatting/LogTimestamp.h"

#include "Telemetry/Logging/LogMethods/LogHandling/ScrollingStringsHandle.h"
#include "Telemetry/Logging/LogMethods/LogHandling/SerialLogger.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

vex::controller Controller1;
ControllerState controllerState(Controller1);

vex::motor DriveLeftMotor(vex::PORT10, false);
vex::motor DriveRightMotor(vex::PORT1, true);

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
	controllerState.setInterval({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 });

	// Register the controller state with it's dedicated telemetry phase
	TelemetryPhase controllerTelemetryPhase;
	controllerTelemetryPhase.registerTelemetryUpdate(&controllerState);

	// Register the controllers telemetry phase
	mainLoop.registerPhase(&controllerTelemetryPhase);


	/* ---User Phase Setup--- */
	// Set the movement logic for the user
	ArcadeMovement<ControllerAxis::Axis2, ControllerAxis::Axis4> movementLogic;
	// Create the user phase with the movement logic
	UserPhase<decltype(movementLogic)> userPhase(controllerState, drivetrainState);

	// Register the user phase
	mainLoop.registerPhase(&userPhase);

	/* ---Display Phase Setup-- */
	DisplayPhase displayPhase(10, Brain);

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


	// Register the display phase
	mainLoop.registerPhase(&displayPhase);


	// Start the main loop
	mainLoop.loop();
}
