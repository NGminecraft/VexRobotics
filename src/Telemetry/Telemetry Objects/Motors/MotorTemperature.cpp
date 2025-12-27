#include "Telemetry/Telemetry Objects/Motors/MotorTemperature.h"

MotorTemperature::MotorTemperature(vex::motor& motor) : motorRef(motor) {}

double MotorTemperature::updateData() {
	data = motorRef.temperature();
}