#pragma once
#include "vex.h"
#include "Objects/StateObject.h"
#include "Telemetry/TelemetryObjects/Controller/ControllerTelemetryHeaders.h"

using controller = vex::controller;

class ControllerState : public StateObject<controller> {
public:
	ControllerState(controller& c);

	void update(const unsigned long tick) override;

	// There got to have been a better way to do this...
	Axis1Telemetry axis1;
	Axis2Telemetry axis2;
	Axis3Telemetry axis3;
	Axis4Telemetry axis4;

	ButtonATelemetry buttonA;
	ButtonBTelemetry buttonB;
	ButtonXTelemetry buttonX;
	ButtonYTelemetry buttonY;

	ButtonLeftTelemetry buttonLeft;
	ButtonRightTelemetry buttonRight;
	ButtonUpTelemetry buttonUp;
	ButtonDownTelemetry buttonDown;

	ButtonL1Telemetry buttonL1;
	ButtonL2Telemetry buttonL2;
	ButtonR1Telemetry buttonR1;
	ButtonR2Telemetry buttonR2;
};