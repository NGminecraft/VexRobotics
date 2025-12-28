#pragma once
// A motor with a rotation sensor for precise control
#include "vex.h"
#include "Objects/MotorState.h"


struct PreciseMotor {
public:
	PreciseMotor(MotorState& m, vex::rotation& r);
	MotorState& getMotor();
	vex::rotation& getRotationSensor();
protected:
	MotorState& motor;
	vex::rotation& rotationSensor;
};