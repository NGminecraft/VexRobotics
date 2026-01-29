#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class Axis4Telemetry : public Telemetry<int> {
public:
	Axis4Telemetry(vex::controller& c);

	int newData();

private:
	vex::controller& controllerRef;
};