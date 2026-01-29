#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonL2Telemetry : public Telemetry<bool> {
public:
	ButtonL2Telemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};