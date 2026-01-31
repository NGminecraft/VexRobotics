#pragma once
#include "Cycle/Phases/LoopPhase.h"
#include "Objects/ControllerState.h"
#include "Objects/DrivetrainState.h"
#include <functional>

template <typename MovementStruct>
class UserPhase : public LoopPhase {
public:
	UserPhase(ControllerState& c, DrivetrainState& dt) : LoopPhase(),
		controller(c),
		drivetrain(dt)
	{
		// Ok so originally I wanted to use async to get the controller values, but the callback functions don't actually
		// Give us the new value, so we might as well just get the values on our schedule 
	};

	inline void execute(const unsigned long tick) {
		controller.update(tick);
		MovementStruct::execute(controller, drivetrain);
	}

private:
	ControllerState& controller;
	DrivetrainState& drivetrain;
};

enum class ControllerAxis {
	Axis1,
	Axis2,
	Axis3,
	Axis4
};

// Template specialization for axis position getter (C++11 compatible)
template<ControllerAxis Axis>
struct AxisPositionGetter;

template<>
struct AxisPositionGetter<ControllerAxis::Axis1> {
	static int get(ControllerState& c) {
		return c.axis1.getData().value;
	}
};

template<>
struct AxisPositionGetter<ControllerAxis::Axis2> {
	static int get(ControllerState& c) {
		return c.axis2.getData().value;
	}
};

template<>
struct AxisPositionGetter<ControllerAxis::Axis3> {
	static int get(ControllerState& c) {
		return c.axis3.getData().value;
	}
};

template<>
struct AxisPositionGetter<ControllerAxis::Axis4> {
	static int get(ControllerState& c) {
		return c.axis4.getData().value;
	}
};

template<ControllerAxis Axis>
static int getAxisPosition(ControllerState& c) {
	return AxisPositionGetter<Axis>::get(c);
}

enum ControllerScaling {
	Linear
};

// Template specialization for scaling (C++11 compatible)
template<ControllerScaling Scale>
struct ValueScaler;

template<>
struct ValueScaler<ControllerScaling::Linear> {
	static double scale(double x) {
		return x;
	}
};

template<ControllerScaling Scale>
static double scaleValue(double x) {
	return ValueScaler<Scale>::scale(x);
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