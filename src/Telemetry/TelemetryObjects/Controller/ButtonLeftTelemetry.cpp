#include "Telemetry/TelemetryObjects/Controller/ButtonLeftTelemetry.h"

ButtonLeftTelemetry::ButtonLeftTelemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonLeftTelemetry::newData() {
	return controllerRef.buttonLeft.pressing();
}
