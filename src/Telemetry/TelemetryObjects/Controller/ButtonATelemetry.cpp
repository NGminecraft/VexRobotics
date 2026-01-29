#include "Telemetry/TelemetryObjects/Controller/ButtonATelemetry.h"

ButtonATelemetry::ButtonATelemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonATelemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonA.pressing());
}