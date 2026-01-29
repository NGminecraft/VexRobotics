#pragma once
#include "Objects/StateObject.h"
#include "Telemetry/TelemetryObjects/Drivetrain/Dumb/DumbDrivetrainTelemetryHeaders.h"
#include "vex.h"

class DrivetrainState : public StateObject<vex::drivetrain> {
public:
	DrivetrainState(vex::drivetrain& dt);

	void update(const unsigned long tick) override;
private:
	DrivetrainVelocity velocity;
};