#include "Objects/ControllerState.h"


ControllerState::ControllerState(controller& c) : StateObject<controller>(c),
	axis1(c),
	axis2(c),
	axis3(c),
	axis4(c),

	buttonA(c),
	buttonB(c),
	buttonX(c),
	buttonY(c),
	buttonLeft(c),
	buttonRight(c),
	buttonUp(c),
	buttonDown(c),

	buttonL1(c),
	buttonL2(c),
	buttonR1(c),
	buttonR2(c)
{}

void ControllerState::update(const unsigned long tick) {}