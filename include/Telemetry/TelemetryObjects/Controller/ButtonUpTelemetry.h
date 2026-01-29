#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonUpTelemetry : public Telemetry<bool> {
public:
	ButtonUpTelemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};