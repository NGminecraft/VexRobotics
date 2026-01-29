#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis1Telemetry : public Telemetry<int> {
public:
	Axis1Telemetry(vex::controller& c);

	int newData();

private:
	vex::controller& controllerRef;
};