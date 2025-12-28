#pragma once
#include "Telemetry/Telemetry Objects/Rotation Sensors/RotationTelemetryHeaders.h"
#include "Objects/StateObject.h"
#include <cmath>

class RotationState : StateObject<vex::rotation> {
public:
	RotationState(vex::rotation& r);

	inline const RotationAngle& getAngle() const { return angle; }
	inline const double getAngleRadians() const { return angle.getData().value * (M_PI / 180); }

	void update(unsigned long tick) override;

private:
	RotationAngle angle;
};