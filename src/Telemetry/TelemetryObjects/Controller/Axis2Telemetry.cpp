#include "Telemetry/TelemetryObjects/Controller/Axis2Telemetry.h"

Axis2Telemetry::Axis2Telemetry(vex::controller& c) : Telemetry <int>(), controllerRef(c) {
	previousData = TelemetryDataPoint<int>::create(
		0,
		0,
		vex::timer::system(),
		newData()
	);
}

int Axis2Telemetry::newData() {
	return controllerRef.Axis2.position();
}
