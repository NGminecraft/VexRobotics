#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis1Telemetry : public Telemetry<bool> {
public:
	Axis1Telemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};