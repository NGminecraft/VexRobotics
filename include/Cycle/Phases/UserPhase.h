#include "Cycle/Phases/LoopPhase.h"
#include "Objects/ControllerState.h"
#include "Objects/DrivetrainState.h"
#include <functional>

class UserPhase : public LoopPhase {
public:
	UserPhase(ControllerState& controller, DrivetrainState& drivetrain);

	void execute(const unsigned long tick);
private:
	ControllerState& controller;
	DrivetrainState& drivetrain;
};

enum ControllerAxis {
	Axis1,
	Axis2,
	Axis3,
	Axis4
};

// Helper function - evaluated at compile time
template<ControllerAxis Axis>
static int getAxisPosition(ControllerState& c) {
	if constexpr (Axis == ControllerAxis::Axis1) {
		return c.;
	} else if constexpr (Axis == ControllerAxis::Axis2) {
		return c.Axis2.position();
	} else if constexpr (Axis == ControllerAxis::Axis3) {
		return c.Axis3.position();
	} else {
		return c.Axis4.position();
	}
}

template <ControllerAxis ForwardAxis, ControllerAxis SideAxis>
struct ArcadeMovement {
	static int execute(ControllerState& c, vex::drivetrain& dt) {
		int x = getAxisPosition<ForwardAxis>(c);
		int y = getAxisPosition<SideAxis>(c);
		return dt.arcade(x, y);
	}
};