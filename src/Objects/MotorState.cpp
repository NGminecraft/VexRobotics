#include "Objects/MotorState.h"

MotorState::MotorState(vex::motor& m) :
	StateObject<vex::motor>(m),
	current(object),
	temperature(object) 
{}
