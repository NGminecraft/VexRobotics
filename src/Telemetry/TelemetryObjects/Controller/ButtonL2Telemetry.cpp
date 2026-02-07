#include "Telemetry/TelemetryObjects/Controller/ButtonL2Telemetry.h"

ButtonL2Telemetry::ButtonL2Telemetry(vex::controller& c) : Telemetry<bool>(1), controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonL2Telemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonL2.pressing());
}
