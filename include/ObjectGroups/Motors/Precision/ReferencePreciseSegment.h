#pragma once
#include "PreciseSegment.h"

class ReferencePreciseSegment : public PreciseSegment {
public:
	ReferencePreciseSegment(MotorState& motor, double length, bool clockwiseReference) : PreciseSegment(motor, length), clockwiseReference(clockwiseReference) {}
	double getAngle() override {
		return motor.
			getTelemetry<MotorState::TelemetryTypes::Current>()
			->getData()
			.value;
	}

private:
	bool clockwiseReference; // Whether the reference stopper for the segment is clockwise (if it rotates clockwise, will it hit the reference point)

};