#include "Cycle/Phases/LoopPhase.h"
#include "Objects/ControllerState.h"
#include "Objects/DrivetrainState.h"

class UserPhase : public LoopPhase {
public:
	UserPhase(ControllerState& controller, DrivetrainState& drivetrain);

	void execute(const unsigned long tick);
private:
	ControllerState& controller;
	DrivetrainState& drivetrain;
};