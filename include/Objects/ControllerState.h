#pragma once
#include "vex.h"
#include "Objects/StateObject.h"
#include "Telemetry/TelemetryObjects/Controller/ControllerTelemetryHeaders.h"
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "Cycle/Phases/TelemetryPhase.h"
#include <vector>

using controller = vex::controller;

class ControllerState : public StateObject<controller, 16> {
public:
	ControllerState(controller& c);

	// Create the enum for all the telemetry types
	TELEMETRY_ENUM(Axis1, Axis2, Axis3, Axis4,
		ButtonA, ButtonB, ButtonX, ButtonY,
		ButtonLeft, ButtonRight, ButtonUp, ButtonDown,
		ButtonL1, ButtonL2, ButtonR1, ButtonR2
	)

	// Generate the telemetry method implementations
	TELEMETRY_METHODS_IMPL(ControllerState, 16)

	void registerTelemetryObjects(TelemetryPhase& phase);
private:
	// Generate the telemetry switch statement
	BEGIN_TELEMETRY_SWITCH()
		TELEMETRY_CASE(Axis1, Axis1Telemetry)
		TELEMETRY_CASE(Axis2, Axis2Telemetry)
		TELEMETRY_CASE(Axis3, Axis3Telemetry)
		TELEMETRY_CASE(Axis4, Axis4Telemetry)
		TELEMETRY_CASE(ButtonA, ButtonATelemetry)
		TELEMETRY_CASE(ButtonB, ButtonBTelemetry)
		TELEMETRY_CASE(ButtonX, ButtonXTelemetry)
		TELEMETRY_CASE(ButtonY, ButtonYTelemetry)
		TELEMETRY_CASE(ButtonLeft, ButtonLeftTelemetry)
		TELEMETRY_CASE(ButtonRight, ButtonRightTelemetry)
		TELEMETRY_CASE(ButtonUp, ButtonUpTelemetry)
		TELEMETRY_CASE(ButtonDown, ButtonDownTelemetry)
		TELEMETRY_CASE(ButtonL1, ButtonL1Telemetry)
		TELEMETRY_CASE(ButtonL2, ButtonL2Telemetry)
		TELEMETRY_CASE(ButtonR1, ButtonR1Telemetry)
		TELEMETRY_CASE(ButtonR2, ButtonR2Telemetry)
	END_TELEMETRY_SWITCH()
};