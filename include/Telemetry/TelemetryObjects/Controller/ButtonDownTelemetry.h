#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonDownTelemetry : public Telemetry<bool> {
public:
	ButtonDownTelemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};