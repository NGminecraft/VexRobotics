#include "Telemetry/TelemetryObjects/Controller/ButtonUpTelemetry.h"

ButtonUpTelemetry::ButtonUpTelemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonUpTelemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonUp.pressing());
}
