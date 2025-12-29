#include "Object Groups/Motors/ArmSegment.h"
#include <cmath>

ArmSegment::ArmSegment(MotorState& m, RotationState& r, double len)
	: motor(m, r), length(len) {}

ArmSegment::ArmSegment(const PreciseMotor& motor, double len) : motor(motor), length(len) {}

const Vector2D<double> ArmSegment::getEndPosition() {
	double angleRad = motor.getRotationState().getAngleRadians();
	if (angleRad == cachedAngleRad) {
		return cachedEndPos;
	}
	else
	{
		Vector2D<double> endPos = Vector2D(length * cos(angleRad), length * sin(angleRad));
		cachedAngleRad = angleRad;
		cachedEndPos = endPos;
		return endPos;
	}
}