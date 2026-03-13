#pragma once
#include "Cycle/Phases/LoopPhase.h"
#include "Objects/ControllerState.h"
#include "Objects/DrivetrainState.h"
#include "Telemetry/Logging/Logger.h"
#include "ObjectGroups/Motors/Arm.h"
#include "Algorithms/InverseKinematics.h"
#include <functional>
#include <cmath>
#include <sstream>
#include <string>

template <typename MovementStruct, typename ArmStruct>
class UserPhase : public LoopPhase {
public:
	UserPhase(ControllerState& c, DrivetrainState& dt, typename ArmStruct::arm_type& arm) : LoopPhase(),
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
	typename ArmStruct::arm_type& arm;

};

enum ControllerScaling {
	Linear,
	Linear100,
	Logarithmic
};

// Template specialization for scaling (C++11 compatible)
template<ControllerScaling Scale>
struct ValueScaler {
	static double scale(double x) {
		Logger::getInstance("Main").log("Undefined scaling method", Logger::LogLevel::ERROR);
		return x;
	}
};

template<>
struct ValueScaler<ControllerScaling::Linear> {
	static double scale(double x) {
		return x;
	}
};

template<>
struct ValueScaler<ControllerScaling::Linear100> {
	static double scale(double x) {
		return x * 100.0;
	}
};

template<>
struct ValueScaler<ControllerScaling::Logarithmic> {
	static double scale(double x) {
		double sign = (x >= 0) ? 1 : -1;
		return sign * std::max(0.0, std::log(std::abs(x)) + 1); // Logarithmic scaling to range [-1, 1]
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

template <ControllerState::TelemetryTypes UpDown, ControllerState::TelemetryTypes LeftRight, size_t Joints, ControllerScaling Scale = ControllerScaling::Linear>
struct ArmMovement {
	using arm_type = Arm<Joints>;

	static void execute(ControllerState& c, Arm<Joints>& arm) {
		double z = c.getTelemetry<UpDown>()->getData().value;
		double y = c.getTelemetry<LeftRight>()->getData().value;

		z = scaleValue<Scale>(z);
		y = scaleValue<Scale>(y);

		std::stringstream logMsg;
		logMsg << "Arm control input - Up/Down: " << z << " Left/Right: " << y;
		Logger::getInstance("Main").log(logMsg.str(), Logger::LogLevel::DEBUG);

		arm.moveEndEffector(Vector3D<double>(0, y, z));
	}
};