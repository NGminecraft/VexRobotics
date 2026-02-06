#pragma once
#include "Objects/StateObject.h"
#include "Telemetry/TelemetryObjects/Drivetrain/Dumb/DumbDrivetrainTelemetryHeaders.h"
#include "vex.h"

// X-Macro list: Single source of truth for all drivetrain telemetry
// Format: X(EnumName, DataType, ClassName)
#define DRIVETRAIN_TELEMETRY_LIST(X) \
	X(Velocity, double, DrivetrainVelocity)

class DrivetrainState : public StateObject<vex::drivetrain, 1> {
public:
	DrivetrainState(vex::drivetrain& dt);

	// Generate everything: enum, type traits, methods, and switch
	TELEMETRY_GENERATE_ALL(DRIVETRAIN_TELEMETRY_LIST, 1)
};