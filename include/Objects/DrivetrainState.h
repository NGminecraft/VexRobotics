#pragma once
#include "Objects/StateObject.h"
#include "Telemetry/TelemetryObjects/Drivetrain/Dumb/DumbDrivetrainTelemetryHeaders.h"
#include "vex.h"

class DrivetrainState : public StateObject<vex::drivetrain, 1> {
public:
	DrivetrainState(vex::drivetrain& dt);
private:
	DrivetrainVelocity velocity;
};