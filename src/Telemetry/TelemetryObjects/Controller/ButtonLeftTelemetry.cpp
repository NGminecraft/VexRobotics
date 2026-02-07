#include "Telemetry/TelemetryObjects/Controller/ButtonLeftTelemetry.h"

ButtonLeftTelemetry::ButtonLeftTelemetry(vex::controller& c) : Telemetry<bool>(1), controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonLeftTelemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonLeft.pressing());
}
