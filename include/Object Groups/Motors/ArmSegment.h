#pragma once
#include "Object Groups/Motors/PreciseMotor.h"
#include "Objects/MotorState.h"
#include "Objects/RotationState.h"
#include "Data Types/Vectors.h"
#include <math.h>

class ArmSegment {
public:
	ArmSegment(MotorState& m, RotationState& r, double len);
	ArmSegment(const PreciseMotor& motor, double len);

	const Vector2D getEndPosition();
protected:
	PreciseMotor motor;
	double length; // Length of the arm segment in inches
};