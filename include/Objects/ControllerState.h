#include "vex.h"
#include "Objects/StateObject.h"
#include "Telemetry/TelemetryObjects/Controller/ControllerTelemetryHeaders.h"

using controller = vex::controller;

class ControllerState : public StateObject<controller> {
	ControllerState(controller& c);
};