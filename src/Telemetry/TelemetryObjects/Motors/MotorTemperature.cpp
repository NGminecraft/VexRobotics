#include "Telemetry/Telemetry Objects/Motors/MotorTemperature.h"

MotorTemperature::MotorTemperature(vex::motor& motor) : motorRef(motor) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double MotorTemperature::newData() { return motorRef.temperature(); }