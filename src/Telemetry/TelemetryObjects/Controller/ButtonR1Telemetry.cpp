#include "Telemetry/TelemetryObjects/Controller/ButtonR1Telemetry.h"

ButtonR1Telemetry::ButtonR1Telemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonR1Telemetry::newData() {
	return controllerRef.buttonR1.pressing();
}
