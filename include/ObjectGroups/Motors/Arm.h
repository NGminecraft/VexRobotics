#pragma once
#include "Precision/PreciseSegment.h"
#include "Precision/ReferencePreciseSegment.h"
#include "Precision/SensorPreciseSegment.h"

#include "Telemetry/Logging/Logger.h"

#include "Algorithms/InverseKinematics.h"

#include "vex.h"
#include <cmath>

template <size_t Joints>
class Arm {
public:
	Arm(Rotation baseOrientation) : baseOrientation(baseOrientation) {};

	void addJoint(size_t jointIdx, MotorState& motor, double length, Rotation axis, RotationState& rotation) {
		if (jointIdx >= Joints) {
			Logger::getInstance("Main").log("Attempted to add a joint at an index that exceeds the number of joints in the arm", Logger::LogLevel::ERROR);
			return;
		}
		segments[jointIdx] = new SensorPreciseSegment(motor, length, axis, rotation);
	}

	void addJoint(size_t jointIdx, MotorState& motor, double length, Rotation axis, bool clockwiseReference) {
		if (jointIdx >= Joints) {
			Logger::getInstance("Main").log("Attempted to add a joint at an index that exceeds the number of joints in the arm", Logger::LogLevel::ERROR);
			return;
		}
		segments[jointIdx] = new ReferencePreciseSegment(motor, length, axis, clockwiseReference);
	}
	
	void moveEndEffector(const Vector3D<double>& targetVelocity) {
		Logger& logger = Logger::getInstance("Main");
		std::stringstream logMsg;
		logMsg << "Moving arm with target velocity: [" << targetVelocity[0] << ", " << targetVelocity[1] << ", " << targetVelocity[2] << "]";
		logger.log(logMsg.str(), Logger::LogLevel::DEBUG);

		for (size_t i = 0; i < Joints; i++) {
			if (segments[i] == nullptr) {
				logMsg.str("");
				logMsg << "Arm segment " << i << " is not initialized; skipping IK update";
				logger.log(logMsg.str(), Logger::LogLevel::ERROR);
				return;
			}
		}
		
		Vector<double, Joints> targetVelocities = InverseKinematics<Joints>(segments, baseOrientation, targetVelocity);
		
		logMsg.str("");
		logMsg << "Calculated joint velocities: [";
		for (size_t i = 0; i < Joints; i++) {
			if (i > 0) {
				logMsg << ", ";
			}
			logMsg << targetVelocities[i];
		}
		logMsg << "]";
		logger.log(logMsg.str(), Logger::LogLevel::DEBUG);

		for (size_t i = 0; i < Joints; i++) {
			double dps = targetVelocities[i] * (180.0 / M_PI);
			if (!std::isfinite(dps)) {
				logMsg.str("");
				logMsg << "Joint " << i << " velocity is non-finite; setting to 0";
				logger.log(logMsg.str(), Logger::LogLevel::ERROR);
				dps = 0.0;
			}
			auto& motor = segments[i]->getMotorState().getMotor();
			double magnitude = std::abs(dps);
			if (magnitude < 1e-6) {
				motor.stop(vex::brakeType::hold);
			}
			else {
				motor.spin((dps >= 0.0) ? vex::directionType::fwd : vex::directionType::rev, magnitude, vex::velocityUnits::dps);
			}
		}
	}

	void setArmVelocities(const Vector<double, Joints>& velocities) {
		for (size_t i = 0; i < Joints; i++) {
			auto& motor = segments[i]->getMotorState().getMotor();
			double magnitude = std::abs(velocities[i]);
			if (magnitude < 1e-6) {
				motor.stop(vex::brakeType::hold);
			}
			else {
				motor.spin((velocities[i] >= 0.0) ? vex::directionType::fwd : vex::directionType::rev, magnitude, vex::velocityUnits::dps);
			}
		}
	}

	void stopArm() {
		for (size_t i = 0; i < Joints; i++) {
			segments[i]->getMotorState().getMotor().stop(vex::brakeType::hold);
		}
	}

	void calibrateArm() {
		for (size_t i = 0; i < Joints; i++) {
			if (segments[i] != nullptr) {
				segments[i]->calibrate();
			}
		}

		for (size_t i = 0; i < Joints; i++) {
			if (segments[i] != nullptr) {
				segments[i]->getMotorState().getMotor().stop(vex::brakeType::hold);
				segments[i]->getMotorState().getMotor().setPosition(0, vex::rotationUnits::deg);
			}
		}
	}

private:
	std::array<PreciseSegment*, Joints> segments{};

	Rotation baseOrientation; // The orientation of the base of the arm
};