#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonATelemetry : public Telemetry<bool> {
public:
	ButtonATelemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};