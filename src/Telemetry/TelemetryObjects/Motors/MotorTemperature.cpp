#include "Telemetry/TelemetryObjects/Motors/MotorTemperature.h"

MotorTemperature::MotorTemperature(vex::motor& motor) : Telemetry<double>(100), motorRef(motor) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double MotorTemperature::newData() { return motorRef.temperature(); }