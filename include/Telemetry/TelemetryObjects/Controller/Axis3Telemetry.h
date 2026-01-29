#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis3Telemetry : public Telemetry<int> {
public:
	Axis3Telemetry(vex::controller& c);

	int newData();

private:
	vex::controller& controllerRef;
};