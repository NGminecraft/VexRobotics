#include "Telemetry/Telemetry Objects/Motors/MotorAmperage.h"

MotorAmperage::MotorAmperage(vex::motor& motor) : motorRef(motor) {}

double MotorAmperage::getData() {
	return motorRef.current();
}