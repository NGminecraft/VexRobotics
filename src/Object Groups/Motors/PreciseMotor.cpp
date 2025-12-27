#include "Object Groups/Motors/PreciseMotor.h"

PreciseMotor::PreciseMotor(vex::motor& m, vex::rotation& r) : motor(m), rotationSensor(r) {}

vex::motor& PreciseMotor::getMotor() { return motor; }

vex::rotation& PreciseMotor::getRotationSensor() { return rotationSensor; }