#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis4Telemetry : public Telemetry<double> {
public:
	Axis4Telemetry(vex::controller& c);

	double newData();

private:
	vex::controller& controllerRef;
};