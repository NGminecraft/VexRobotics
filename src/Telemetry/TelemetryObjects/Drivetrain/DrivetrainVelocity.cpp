#include "Telemetry/TelemetryObjects/Drivetrain/Dumb/DrivetrainVelocity.h"

DrivetrainVelocity::DrivetrainVelocity(vex::drivetrain& drivetrain) : Telemetry<double>(), drivetrainRef(drivetrain) {
}

double DrivetrainVelocity::newData() {
	return drivetrainRef.velocity(vex::velocityUnits::rpm);
}