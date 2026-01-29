#include "Objects/MotorState.h"

MotorState::MotorState(vex::motor& m) :
	StateObject<vex::motor>(m),
	current(m),
	temperature(m) 
{}

void MotorState::update(const unsigned long tick
) {
	current.update(tick);
	temperature.update(tick);
}