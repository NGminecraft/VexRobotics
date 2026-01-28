#include "Telemetry/TelemetryObjects/Motors/MotorAmperage.h"

MotorAmperage::MotorAmperage(vex::motor& motor) : Telemetry<double>(), motorRef(motor) {
}

double MotorAmperage::newData() { return motorRef.current(); }