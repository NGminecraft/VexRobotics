#include "Telemetry/TelemetryObjects/Motors/MotorAngle.h"

MotorAngle::MotorAngle(vex::motor& motor) : Telemetry<double>(), motorRef(motor) {
    previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double MotorAngle::newData() {
    return motorRef.position(vex::degrees);
}