#include "Telemetry/TelemetryObjects/Controller/ButtonRightTelemetry.h"

ButtonRightTelemetry::ButtonRightTelemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonRightTelemetry::newData() {
	return controllerRef.buttonRight.pressing();
}
