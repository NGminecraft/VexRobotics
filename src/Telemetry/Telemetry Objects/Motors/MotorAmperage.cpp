#include "Telemetry/Telemetry Objects/Motors/MotorAmperage.h"

MotorAmperage::MotorAmperage(vex::motor& motor) : motorRef(motor) {}

void MotorAmperage::updateData() {
	data = motorRef.current();
}