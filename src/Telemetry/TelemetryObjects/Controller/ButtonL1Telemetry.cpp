#include "Telemetry/TelemetryObjects/Controller/ButtonL1Telemetry.h"

ButtonL1Telemetry::ButtonL1Telemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonL1Telemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonL1.pressing());
}
