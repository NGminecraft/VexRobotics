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
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

vex::controller Controller1;
ControllerState controllerState(Controller1);

vex::motor DriveLeftMotor(vex::PORT1, false);
vex::motor DriveRightMotor(vex::PORT2, true);

vex::motor_group leftMotors(DriveLeftMotor);
vex::motor_group rightMotors(DriveRightMotor);

vex::drivetrain Drivetrain(leftMotors, rightMotors);
DrivetrainState drivetrainState(Drivetrain);

// define your global instances of motors and other devices here

int main() {
	Logger::getInstance(Brain, "Main").log("Starting main()");
	MainLoop mainLoop;

	/* ---Controller Setup--- */
	// Enable only the telemetry axis classes to be updated every tick
	controllerState.setTelemetryIntervals({ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

	// Register the controller state with it's dedicated telemetry phase
	TelemetryPhase controllerTelemetryPhase;
	controllerTelemetryPhase.registerTelemetryUpdate(&controllerState);

	// Register the controllers telemetry phase
	mainLoop.registerPhase(&controllerTelemetryPhase);

	/* ---User Phase Setup--- */
	// Set the movement logic for the user
	ArcadeMovement<ControllerAxis::Axis3, ControllerAxis::Axis1> movementLogic;
	// Create the user phase with the movement logic
	UserPhase<decltype(movementLogic)> userPhase(controllerState, drivetrainState);

	// Register the user phase
	mainLoop.registerPhase(&userPhase);

	// Start the main loop
	mainLoop.loop();
}
