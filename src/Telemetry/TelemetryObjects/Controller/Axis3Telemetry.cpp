#include "Telemetry/TelemetryObjects/Controller/Axis3Telemetry.h"

Axis3Telemetry::Axis3Telemetry(vex::controller& c) : Telemetry <int>(), controllerRef(c) {
	previousData = TelemetryDataPoint<int>::create(
		0,
		0,
		vex::timer::system(),
		newData()
	);
}

int Axis3Telemetry::newData() {
	return controllerRef.Axis3.position();
}
