/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       minec                                                     */
/*    Created:      12/12/2025, 2:46:19 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Data Types/Rotations.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

vex::motor spin1 = vex::motor(vex::PORT1);
vex::motor spin2 = vex::motor(vex::PORT2);
vex::motor spin3 = vex::motor(vex::PORT3);

int main() {

    spin3.setReversed(true);

    Brain.Screen.printAt( 10, 50, "Hello V5" );
    Rotation rot = Rotation::about(Rotation::Axis::XAxis, 3.14 / 4);
   
    while(1) {
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
