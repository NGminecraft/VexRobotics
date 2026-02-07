#pragma once
#include "vex.h"
#include "Objects/StateObject.h"
#include "Telemetry/TelemetryObjects/Controller/ControllerTelemetryHeaders.h"
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "Cycle/Phases/TelemetryPhase.h"
#include <vector>

using controller = vex::controller;

// X-Macro list: Single source of truth for all controller telemetry
// Format: X(EnumName, DataType, ClassName)
#define CONTROLLER_TELEMETRY_LIST(X) \
	X(Axis1, int, Axis1Telemetry) \
	X(Axis2, int, Axis2Telemetry) \
	X(Axis3, int, Axis3Telemetry) \
	X(Axis4, int, Axis4Telemetry) \
	X(ButtonA, bool, ButtonATelemetry) \
	X(ButtonB, bool, ButtonBTelemetry) \
	X(ButtonX, bool, ButtonXTelemetry) \
	X(ButtonY, bool, ButtonYTelemetry) \
	X(ButtonLeft, bool, ButtonLeftTelemetry) \
	X(ButtonRight, bool, ButtonRightTelemetry) \
	X(ButtonUp, bool, ButtonUpTelemetry) \
	X(ButtonDown, bool, ButtonDownTelemetry) \
	X(ButtonL1, bool, ButtonL1Telemetry) \
	X(ButtonL2, bool, ButtonL2Telemetry) \
	X(ButtonR1, bool, ButtonR1Telemetry) \
	X(ButtonR2, bool, ButtonR2Telemetry)

class ControllerState : public StateObject<controller, 16> {
public:
	ControllerState(controller& c);

	// Generate everything: enum, type traits, methods, and switch
	TELEMETRY_GENERATE_ALL(CONTROLLER_TELEMETRY_LIST, 16)
};