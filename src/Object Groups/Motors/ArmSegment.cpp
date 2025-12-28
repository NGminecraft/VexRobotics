#include "Object Groups/Motors/ArmSegment.h"
#include <cmath>

ArmSegment::ArmSegment(MotorState& m, RotationState& r, double len)
	: motor(m, r), length(len) {}

ArmSegment::ArmSegment(const PreciseMotor& motor, double len) : motor(motor), length(len) {}

Vector2D ArmSegment::getEndPosition() {
	double angleRad = motor.getRotationState().getAngleRadians();
	return Vector2D(length * cos(angleRad), length * sin(angleRad));
}