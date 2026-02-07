#include "Telemetry/TelemetryObjects/Controller/ButtonR2Telemetry.h"

ButtonR2Telemetry::ButtonR2Telemetry(vex::controller& c) : Telemetry<bool>(1), controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonR2Telemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonR2.pressing());
}
