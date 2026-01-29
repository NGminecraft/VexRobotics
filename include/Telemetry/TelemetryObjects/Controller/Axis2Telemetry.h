#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis2Telemetry : public Telemetry<int> {
public:
	Axis2Telemetry(vex::controller& c);

	int newData();

private:
	vex::controller& controllerRef;
};