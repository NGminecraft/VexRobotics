#include "Telemetry/TelemetryObjects/RotationSensors/RotationAngle.h"

RotationAngle::RotationAngle(vex::rotation& sensor) : Telemetry<double>(), sensorRef(sensor) {
}

double RotationAngle::newData() { return sensorRef.angle(vex::rotationUnits::deg); }