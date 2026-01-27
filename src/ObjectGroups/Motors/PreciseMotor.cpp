#include "Object Groups/Motors/PreciseMotor.h"

PreciseMotor::PreciseMotor(MotorState& m, RotationState& r) : motor(m), rotationSensor(r) {}

MotorState& PreciseMotor::getMotor() { return motor; }

RotationState& PreciseMotor::getRotationState() { return rotationSensor; }