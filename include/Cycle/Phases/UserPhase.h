#include "Cycle/Phases/LoopPhase.h"
#include "Objects/ControllerState.h"
#include "Objects/DrivetrainState.h"
#include <functional>

template <typename MovementStruct>
class UserPhase : public LoopPhase {
public:
	UserPhase(ControllerState& controller, DrivetrainState& drivetrain);

	inline void execute(const unsigned long tick) {
		MovementStruct::execute(controller, drivetrain);
	}

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
		return c.axis1.getData().value;
	} else if constexpr (Axis == ControllerAxis::Axis2) {
		return c.axis2.getData().value;
	} else if constexpr (Axis == ControllerAxis::Axis3) {
		return c.axis3.getData().value;
	} else {
		return c.axis4.getData().value;
	}
}

enum ControllerScaling {
	Linear
};

template<ControllerScaling Scale>
static double scaleValue(double x) {
	if constexpr (Scale == ControllerScaling::Linear) {
		return x;
	}
}

template <ControllerAxis ForwardAxis, ControllerAxis SideAxis, ControllerScaling Scale = ControllerScaling::Linear>
struct ArcadeMovement {
	static void execute(ControllerState& c, DrivetrainState& dt) {
		// Gets the axis positions from the controller
		int x = getAxisPosition<ForwardAxis>(c);
		int y = getAxisPosition<SideAxis>(c);

		// Scales the values
		x = scaleValue<Scale>(x);
		y = scaleValue<Scale>(y);

		// Runs the arcade drive
		return dt.getObject().arcade(x, y);
	}
};