#include "Objects/MotorState.h"

MotorState::MotorState(vex::motor& m) :
	motor(m),
	current(motor),
	temperature(motor) 
{}
