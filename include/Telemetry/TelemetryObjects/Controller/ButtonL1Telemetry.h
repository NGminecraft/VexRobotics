#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonL1Telemetry : public Telemetry<bool> {
public:
	ButtonL1Telemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};