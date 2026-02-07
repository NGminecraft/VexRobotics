#include "Telemetry/TelemetryObjects/Controller/ButtonDownTelemetry.h"

ButtonDownTelemetry::ButtonDownTelemetry(vex::controller& c) : Telemetry<bool>(1), controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonDownTelemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonDown.pressing());
}
