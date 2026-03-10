#pragma once
#include "Cycle/Phases/LoopPhase.h"
#include "Objects/ControllerState.h"
#include "Objects/DrivetrainState.h"
#include "Telemetry/Logging/Logger.h"
#include "ObjectGroups/Motors/Arm.h"
#include "Algorithms/InverseKinematics.h"
#include <functional>
#include <sstream>
#include <string>

template <typename MovementStruct, typename ArmStruct, size_t ArmJoints>
class UserPhase : public LoopPhase {
public:
	UserPhase(ControllerState& c, DrivetrainState& dt, Arm<ArmJoints>& arm) : LoopPhase(),
		controller(c),
		drivetrain(dt),
		arm(arm)
	{
		// Ok so originally I wanted to use async to get the controller values, but the callback functions don't actually
		// Give us the new value, so we might as well just get the values on our schedule 
	};

	inline void execute(const unsigned long tick) {
		MovementStruct::execute(controller, drivetrain);
		ArmStruct::execute(controller, arm);
		
	}

private:
	ControllerState& controller;
	DrivetrainState& drivetrain;
	Arm<ArmJoints>& arm;

};

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

template <ControllerState::TelemetryTypes ForwardAxis, ControllerState::TelemetryTypes SideAxis, ControllerScaling Scale = ControllerScaling::Linear>
struct ArcadeMovement {
	static void execute(ControllerState& c, DrivetrainState& dt) {
		// Gets the axis positions from the controller
		int x = c.getTelemetry<ForwardAxis>()->getData().value;
		int y = c.getTelemetry<SideAxis>()->getData().value;

		// Scales the values
		x = scaleValue<Scale>(x);
		y = scaleValue<Scale>(y);
		std::stringstream logMsg;
		logMsg << "Controller input - X: " << x << " Y: " << y;
		Logger::getInstance("Main").log(logMsg.str(), Logger::LogLevel::DEBUG);

		// Runs the arcade drive
		return dt.getObject().arcade(x, y);
	}
};

template <ControllerState::TelemetryTypes UpDown, ControllerState::TelemetryTypes LeftRight, ControllerScaling Scale = ControllerScaling::Linear>
struct ArmMovement {
	template <size_t joints>
	static void execute(ControllerState& c, Arm<joints>& arm) {
		int z = c.getTelemetry<UpDown>()->getData().value;
		int y = c.getTelemetry<LeftRight>()->getData().value;

		z = scaleValue<Scale>(z);
		y = scaleValue<Scale>(y);

		std::stringstream logMsg;
		logMsg << "Arm control input - Up/Down: " << z << " Left/Right: " << y;
		Logger::getInstance("Main").log(logMsg.str(), Logger::LogLevel::DEBUG);

		arm.moveEndEffector(Vector3D<double>(0, y, z));
	}
};