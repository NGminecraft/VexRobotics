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
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

vex::controller Controller1;
ControllerState controllerState(Controller1);

vex::motor DriveLeftMotor(vex::PORT1);
vex::motor DriveRightMotor(vex::PORT2);

vex::motor_group leftMotors(DriveLeftMotor);
vex::motor_group rightMotors(DriveRightMotor);

vex::drivetrain Drivetrain(leftMotors, rightMotors, 319.19, 320, 40, vex::distanceUnits::mm, 1);
DrivetrainState drivetrainState(Drivetrain);

// define your global instances of motors and other devices here

int main() {
	MainLoop mainLoop;

	ArcadeMovement<ControllerAxis::Axis1, ControllerAxis::Axis2> movementLogic;
	UserPhase<decltype(movementLogic)> userPhase(controllerState, drivetrainState);

	mainLoop.registerPhase(&userPhase);

	// Build and register phases for the main loop here

	// Start the main loop
	mainLoop.loop();
}
