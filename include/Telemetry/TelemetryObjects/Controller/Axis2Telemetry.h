#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis2Telemetry : public Telemetry<double> {
public:
	Axis2Telemetry(vex::controller& c);

	double newData();

private:
	vex::controller& controllerRef;
};