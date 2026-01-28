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
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

int main() {
	MainLoop mainLoop;

	// Build and register phases for the main loop here

	// Start the main loop
	mainLoop.loop();
}
