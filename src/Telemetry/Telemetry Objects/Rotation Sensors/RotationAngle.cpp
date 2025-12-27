#include "Telemetry/Telemetry Objects/Rotation Sensors/RotationAngle.h"

RotationAngle::RotationAngle(vex::rotation& sensor) : sensorRef(sensor) {}

void RotationAngle::updateData() {
	data = sensorRef.angle(vex::rotationUnits::deg);
}