#pragma once
#include "PreciseSegment.h"

class ReferencePreciseSegment : public PreciseSegment {
public:
	ReferencePreciseSegment(MotorState& motor, double length, Rotation axis, bool clockwiseReference) : PreciseSegment(motor, length, axis), clockwiseReference(clockwiseReference) {}
	double getAngle() override {
		const double degreesToRadians = 3.14159265358979323846 / 180.0;
		auto* telemetry = motor.getTelemetry<MotorState::TelemetryTypes::Angle>();
		double degrees = (telemetry != nullptr)
			? telemetry->getData().value
			: motor.getMotor().position(vex::rotationUnits::deg);
		double radians = degrees * degreesToRadians;
		return clockwiseReference ? radians : -radians;
	}

	void calibrate() override {
		motor.getMotor().spin(vex::forward, 20, vex::velocityUnits::pct);
	}

private:
	bool clockwiseReference; // Whether the reference stopper for the segment is clockwise (if it rotates clockwise, will it hit the reference point)

};