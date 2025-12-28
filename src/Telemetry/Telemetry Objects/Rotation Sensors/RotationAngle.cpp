#include "Telemetry/Telemetry Objects/Rotation Sensors/RotationAngle.h"

RotationAngle::RotationAngle(vex::rotation& sensor) : sensorRef(sensor) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double RotationAngle::newData() { return sensorRef.angle(vex::rotationUnits::deg); }