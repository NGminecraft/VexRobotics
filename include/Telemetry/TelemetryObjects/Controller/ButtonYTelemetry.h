#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonYTelemetry : public Telemetry<bool> {
public:
	ButtonYTelemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};