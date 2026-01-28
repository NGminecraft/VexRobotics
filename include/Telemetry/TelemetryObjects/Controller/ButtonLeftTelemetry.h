#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonLeftTelemetry : public Telemetry<bool> {
public:
	ButtonLeftTelemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};