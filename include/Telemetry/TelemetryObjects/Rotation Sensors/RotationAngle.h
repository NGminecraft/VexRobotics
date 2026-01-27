#pragma once
#include "vex.h"
#include "Telemetry/TelemetryObjects/Telemetry.h"

class RotationAngle : public Telemetry<double> {
public:
	RotationAngle(vex::rotation& sensor);

	double newData() override;
private:
	vex::rotation& sensorRef;
};