#include "Telemetry/TelemetryObjects/Controller/ButtonXTelemetry.h"

ButtonXTelemetry::ButtonXTelemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonXTelemetry::newData() {
	return controllerRef.buttonX.pressing();
}
