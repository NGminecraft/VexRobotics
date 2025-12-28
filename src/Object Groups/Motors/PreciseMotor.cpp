#include "Object Groups/Motors/PreciseMotor.h"

PreciseMotor::PreciseMotor(MotorState& m, vex::rotation& r) : motor(m), rotationSensor(r) {}

MotorState& PreciseMotor::getMotor() { return motor; }

vex::rotation& PreciseMotor::getRotationSensor() { return rotationSensor; }