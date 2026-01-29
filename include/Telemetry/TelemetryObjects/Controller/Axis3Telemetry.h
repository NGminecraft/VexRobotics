#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis3Telemetry : public Telemetry<double> {
public:
	Axis3Telemetry(vex::controller& c);

	double newData();

private:
	vex::controller& controllerRef;
};