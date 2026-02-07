#include "Telemetry/TelemetryObjects/Controller/Axis1Telemetry.h"

Axis1Telemetry::Axis1Telemetry(vex::controller& c) : Telemetry <int>(1), controllerRef(c) {
	previousData = TelemetryDataPoint<int>::create(
		0,
		0,
		vex::timer::system(),
		newData()
	);
}

int Axis1Telemetry::newData() {
	return controllerRef.Axis1.position();
}