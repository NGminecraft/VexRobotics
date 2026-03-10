#pragma once
#include "Precision/PreciseSegment.h"
#include "Precision/ReferencePreciseSegment.h"
#include "Precision/SensorPreciseSegment.h"

#include "Telemetry/Logging/Logger.h"

#include "Algorithms/InverseKinematics.h"

#include "vex.h"

template <size_t Joints>
class Arm {
public:
	Arm(Rotation baseOrientation) : baseOrientation(baseOrientation) {};

	void addJoint(size_t jointIdx, MotorState& motor, double length, RotationState& rotation) {
		if (jointIdx >= Joints) {
			Logger::getInstance("Main").log("Attempted to add a joint at an index that exceeds the number of joints in the arm", Logger::LogLevel::ERROR);
			return;
		}
		segments[jointIdx] = new ReferencePreciseSegment(motor, length, rotation);
	}

	void addJoint(size_t jointIdx, MotorState& motor, double length, bool clockwiseReference) {
		if (jointIdx >= Joints) {
			Logger::getInstance("Main").log("Attempted to add a joint at an index that exceeds the number of joints in the arm", Logger::LogLevel::ERROR);
			return;
		}
		segments[jointIdx] = new ReferencePreciseSegment(motor, length, clockwiseReference);
	}
	
	void moveEndEffector(const Vector3D<double>& targetVelocity) {
		Vector<double, Joints> targetVelocities = InverseKinematics<Joints>(segments, baseOrientation, targetVelocity);
		for (size_t i = 0; i < Joints; i++) {
			segments[i]->getMotorState().getMotor().setVelocity(targetVelocities[i] * (180 / M_PI), vex::velocityUnits::dps);
		}
	}

	void setArmVelocities(const Vector<double, Joints>& velocities) {
		for (size_t i = 0; i < Joints; i++) {
			segments[i]->getMotorState().getMotor().setVelocity(velocities[i], vex::velocityUnits::rpm);
		}
	}

	void stopArm() {
		for (size_t i = 0; i < Joints; i++) {
			segments[i]->getMotorState().getMotor().setVelocity(0, vex::velocityUnits::rpm);
		}
	}

private:
	std::array<PreciseSegment*, Joints> segments;

	Rotation baseOrientation; // The orientation of the base of the arm
};