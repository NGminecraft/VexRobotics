#pragma once
#include "Telemetry/Telemetry Objects/Telemetry.h"
#include "vex.h"

class MotorAmperage : public Telemetry<double> {
public:
	MotorAmperage(vex::motor& motor);

	double newData() override;
private:
	vex::motor& motorRef;
};