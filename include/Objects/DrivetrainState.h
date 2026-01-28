#pragma once
#include "Objects/StateObject.h"
#include "Telemetry/TelemetryObjects/Drivetrain/Dumb/DumbDrivetrainTelemetryHeaders.h"
#include "vex.h"

class DrivetrainState : StateObject<vex::drivetrain> {
	DrivetrainState(vex::drivetrain& dt);

	void update(unsigned long tick) override;
private:
	DrivetrainVelocity velocity;
};