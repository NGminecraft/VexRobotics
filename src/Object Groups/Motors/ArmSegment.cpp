#include "Object Groups/Motors/ArmSegment.h"
#include <Data Types/Vectors.h>
#include <Object Groups/Motors/PreciseMotor.h>
#include <Objects/MotorState.h>
#include <Objects/RotationState.h>

ArmSegment::ArmSegment(MotorState& m, RotationState& r, double len)
	: motor(m, r), length(len) {}

ArmSegment::ArmSegment(const PreciseMotor& motor, double len) : motor(motor), length(len) {}