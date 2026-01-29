#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonR2Telemetry : public Telemetry<bool> {
public:
	ButtonR2Telemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};