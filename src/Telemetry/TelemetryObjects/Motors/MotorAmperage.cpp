#include "Telemetry/TelemetryObjects/Motors/MotorAmperage.h"

MotorAmperage::MotorAmperage(vex::motor& motor) : Telemetry<double> (30), motorRef(motor) {
	// Initial value for the previous data point
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double MotorAmperage::newData() { return motorRef.current(); }