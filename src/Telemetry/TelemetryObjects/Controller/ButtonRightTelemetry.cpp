#include "Telemetry/TelemetryObjects/Controller/ButtonRightTelemetry.h"

ButtonRightTelemetry::ButtonRightTelemetry(vex::controller& c) : Telemetry<bool>(1), controllerRef(c) {
	previousData = TelemetryDataPoint<bool>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

bool ButtonRightTelemetry::newData() {
	return static_cast<bool>(controllerRef.ButtonRight.pressing());
}
