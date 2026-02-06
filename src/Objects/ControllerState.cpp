#include "Objects/ControllerState.h"


ControllerState::ControllerState(controller& c) : StateObject<controller, 16>(c)
{}

void ControllerState::addTelemetryObject(TelemetryTypes type) {
	int idx = static_cast<int>(type);
	if (telemetryObjects[idx] != nullptr) {
		delete telemetryObjects[idx];
	}
	telemetryObjects[idx] = instantiateTelemetry(type);
}

TelemetryBase* ControllerState::instantiateTelemetry(TelemetryTypes type) {
	switch (type) {
	case TelemetryTypes::Axis1:
		return new Axis1Telemetry(object);
	case TelemetryTypes::Axis2:
		return new Axis2Telemetry(object);
	case TelemetryTypes::Axis3:
		return new Axis3Telemetry(object);
	case TelemetryTypes::Axis4:
		return new Axis4Telemetry(object);
	case TelemetryTypes::ButtonA:
		return new ButtonATelemetry(object);
	case TelemetryTypes::ButtonB:
		return new ButtonBTelemetry(object);
	case TelemetryTypes::ButtonX:
		return new ButtonXTelemetry(object);
	case TelemetryTypes::ButtonY:
		return new ButtonYTelemetry(object);
	case TelemetryTypes::ButtonLeft:
		return new ButtonLeftTelemetry(object);
	case TelemetryTypes::ButtonRight:
		return new ButtonRightTelemetry(object);
	case TelemetryTypes::ButtonUp:
		return new ButtonUpTelemetry(object);
	case TelemetryTypes::ButtonDown:
		return new ButtonDownTelemetry(object);
	case TelemetryTypes::ButtonL1:
		return new ButtonL1Telemetry(object);
	case TelemetryTypes::ButtonL2:
		return new ButtonL2Telemetry(object);
	case TelemetryTypes::ButtonR1:
		return new ButtonR1Telemetry(object);
	case TelemetryTypes::ButtonR2:
		return new ButtonR2Telemetry(object);
	default:
		return nullptr;
	}
}