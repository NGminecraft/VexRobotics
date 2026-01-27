#include "ObjectGroups/Motors/ArmSegment.h"
#include <DataTypes/Rotations.h>
#include <ObjectGroups/Motors/PreciseMotor.h>
#include <Objects/MotorState.h>
#include <Objects/RotationState.h>

ArmSegment::ArmSegment(MotorState& m, RotationState& r, Rotation axis, double len)
	: motor(m, r), rotationAxis(axis), length(len) {}

ArmSegment::ArmSegment(const PreciseMotor& motor, Rotation axis, double len) : motor(motor), rotationAxis(axis), length(len) {}