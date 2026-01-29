#include "Telemetry/TelemetryObjects/Controller/Axis1Telemetry.h"

Axis1Telemetry::Axis1Telemetry(vex::controller& c) : Telemetry <double>(), controllerRef(c) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double Axis1Telemetry::newData() {
	return controllerRef.Axis1.position();
}