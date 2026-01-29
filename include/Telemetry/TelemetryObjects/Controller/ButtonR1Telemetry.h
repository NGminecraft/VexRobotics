#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonR1Telemetry : public Telemetry<bool> {
public:
	ButtonR1Telemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};