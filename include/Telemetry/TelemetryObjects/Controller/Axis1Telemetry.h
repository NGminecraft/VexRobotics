#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis1Telemetry : public Telemetry<double> {
public:
	Axis1Telemetry(vex::controller& c);

	double newData();

private:
	vex::controller& controllerRef;
};