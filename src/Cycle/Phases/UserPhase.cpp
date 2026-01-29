#include "Cycle/Phases/UserPhase.h"
#include "vex.h"

template <typename MovementStruct>
UserPhase::UserPhase(ControllerState& c, DrivetrainState& dt) : LoopPhase(), 
	controller(c),
	drivetrain(dt)
{
	// Ok so originally I wanted to use async to get the controller values, but the callback functions don't actually
	// Give us the new value, so we might as well just get the values on our schedule 
}