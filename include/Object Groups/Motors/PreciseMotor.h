#pragma once
// A motor with a rotation sensor for precise control
#include "vex.h"
#include "Objects/MotorState.h"
#include "Objects/RotationState.h"


struct PreciseMotor {
public:
	PreciseMotor(MotorState& m, RotationState& r);
	MotorState& getMotor();
	RotationState& getRotationState();
protected:
	MotorState& motor;
	RotationState& rotationSensor;
};