#include "Telemetry/TelemetryObjects/Controller/Axis2Telemetry.h"

Axis2Telemetry::Axis2Telemetry(vex::controller& c) : Telemetry <double>(), controllerRef(c) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double Axis2Telemetry::newData() {
	return controllerRef.Axis2.position();
}
