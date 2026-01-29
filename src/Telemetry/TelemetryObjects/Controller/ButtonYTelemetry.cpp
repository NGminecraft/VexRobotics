#include "Telemetry/TelemetryObjects/Controller/ButtonYTelemetry.h"

ButtonYTelemetry::ButtonYTelemetry(vex::controller& c) : controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonYTelemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonY.pressing());
}
