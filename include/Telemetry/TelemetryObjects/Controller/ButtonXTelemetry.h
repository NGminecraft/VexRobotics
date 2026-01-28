#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonXTelemetry : public Telemetry<bool> {
public:
	ButtonXTelemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};