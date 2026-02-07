#include "Telemetry/TelemetryObjects/Controller/ButtonBTelemetry.h"

ButtonBTelemetry::ButtonBTelemetry(vex::controller& c) : Telemetry<bool>(1), controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonBTelemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonB.pressing());
}
