#include "Telemetry/TelemetryObjects/Motors/MotorTemperature.h"

MotorTemperature::MotorTemperature(vex::motor& motor) : Telemetry<double>(), motorRef(motor) {
}

double MotorTemperature::newData() { return motorRef.temperature(); }