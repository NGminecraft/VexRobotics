#include "Telemetry/TelemetryObjects/Drivetrain/Dumb/DrivetrainVelocity.h"

DrivetrainVelocity::DrivetrainVelocity(vex::drivetrain& drivetrain) : Telemetry<double>(), drivetrainRef(drivetrain) {
	previousData = TelemetryDataPoint<double>::create(
		0,
		0.0,
		vex::timer::system(),
		newData()
	);
}

double DrivetrainVelocity::newData() {
	return drivetrainRef.velocity(vex::velocityUnits::rpm);
}