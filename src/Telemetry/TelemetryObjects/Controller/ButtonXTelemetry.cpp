#include "Telemetry/TelemetryObjects/Controller/ButtonXTelemetry.h"

ButtonXTelemetry::ButtonXTelemetry(vex::controller& c) : Telemetry<bool>(1), controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonXTelemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonX.pressing());
}
