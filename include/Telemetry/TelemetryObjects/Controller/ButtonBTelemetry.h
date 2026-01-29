#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class ButtonBTelemetry : public Telemetry<bool> {
public:
	ButtonBTelemetry(vex::controller& c);

	bool newData();

private:
	vex::controller& controllerRef;
};