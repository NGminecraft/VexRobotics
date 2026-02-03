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

void ControllerState::update(const unsigned long tick) {
	axis1.update(tick);
	axis2.update(tick);
	axis3.update(tick);
	axis4.update(tick);

	buttonA.update(tick);
	buttonB.update(tick);
	buttonX.update(tick);
	buttonY.update(tick);
	buttonLeft.update(tick);
	buttonRight.update(tick);
	buttonUp.update(tick);
	buttonDown.update(tick);

	buttonL1.update(tick);
	buttonL2.update(tick);
	buttonR1.update(tick);
	buttonR2.update(tick);
}