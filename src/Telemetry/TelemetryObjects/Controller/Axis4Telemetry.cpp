#include "Telemetry/TelemetryObjects/Controller/Axis4Telemetry.h"

Axis4Telemetry::Axis4Telemetry(vex::controller& c) : Telemetry <int>(), controllerRef(c) {
	previousData = TelemetryDataPoint<int>::create(
		0,
		0,
		vex::timer::system(),
		newData()
	);
}

int Axis4Telemetry::newData() {
	return controllerRef.Axis4.position();
}
