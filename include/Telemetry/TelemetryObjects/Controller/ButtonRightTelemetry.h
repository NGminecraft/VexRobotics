#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonRightTelemetry : public Telemetry<bool> {
public:
	ButtonRightTelemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};