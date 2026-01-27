#pragma once
#include "ObjectGroups/Motors/PreciseMotor.h"
#include "Objects/MotorState.h"
#include "Objects/RotationState.h"
#include "DataTypes/Rotations.h"

class ArmSegment {
public:
	ArmSegment(MotorState& m, RotationState& r, Rotation axis, double len);
	ArmSegment(const PreciseMotor& motor, Rotation axis, double len);

	PreciseMotor getPreciseMotor() { return motor; }
	const PreciseMotor getPreciseMotor() const { return motor; }

	const Rotation& getRotationAxis() const { return rotationAxis; }

	const double getLength() const { return length; }

protected:
	PreciseMotor motor;
	Rotation rotationAxis;
	double length; // Length of the arm segment in inches
};