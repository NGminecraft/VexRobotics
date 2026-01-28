#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class DrivetrainVelocity : public Telemetry<double> {
public:
	DrivetrainVelocity(vex::drivetrain& drivetrain);
	double newData() override;
private:
	vex::drivetrain& drivetrainRef;
};