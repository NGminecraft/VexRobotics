#include "Telemetry/TelemetryObjects/Controller/ButtonBTelemetry.h"

ButtonBTelemetry::ButtonBTelemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonBTelemetry::newData() {
	return controllerRef.buttonB.pressing();
}
