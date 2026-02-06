#pragma once
#include "Objects/StateObject.h"
#include <cmath>
#include <Telemetry/TelemetryObjects/RotationSensors/RotationAngle.h>
#include <vex_rotation.h>

// X-Macro list: Single source of truth for all rotation telemetry
// Format: X(EnumName, DataType, ClassName)
#define ROTATION_TELEMETRY_LIST(X) \
	X(Angle, double, RotationAngle)

class RotationState : public StateObject<vex::rotation, 1> {
public:
	RotationState(vex::rotation& r);

	// Generate everything: enum, type traits, methods, and switch
	TELEMETRY_GENERATE_ALL(ROTATION_TELEMETRY_LIST, 1)

	inline double getAngleRadians() { 
		return getTelemetry<TelemetryTypes::Angle>()->getData().value * (M_PI / 180.0); 
	}
};