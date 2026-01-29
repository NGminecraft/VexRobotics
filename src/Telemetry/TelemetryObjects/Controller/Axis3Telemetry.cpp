#include "Telemetry/TelemetryObjects/Controller/Axis3Telemetry.h"

Axis3Telemetry::Axis3Telemetry(vex::controller& c) : Telemetry <double>(), controllerRef(c) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double Axis3Telemetry::newData() {
	return controllerRef.Axis3.position();
}
