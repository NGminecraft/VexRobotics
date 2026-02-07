#include "Telemetry/TelemetryObjects/RotationSensors/RotationAngle.h"

RotationAngle::RotationAngle(vex::rotation& sensor) : Telemetry<double>(3), sensorRef(sensor) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double RotationAngle::newData() { return sensorRef.angle(vex::rotationUnits::deg); }