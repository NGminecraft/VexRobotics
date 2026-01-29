#include "Telemetry/TelemetryObjects/Controller/Axis4Telemetry.h"

Axis4Telemetry::Axis4Telemetry(vex::controller& c) : Telemetry <double>(), controllerRef(c) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double Axis4Telemetry::newData() {
	return controllerRef.Axis4.position();
}
