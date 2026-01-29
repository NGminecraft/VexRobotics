#pragma once
#include "Objects/StateObject.h"
#include <cmath>
#include <Telemetry/TelemetryObjects/RotationSensors/RotationAngle.h>
#include <vex_rotation.h>

class RotationState : StateObject<vex::rotation> {
public:
	RotationState(vex::rotation& r);

	inline const RotationAngle& getAngle() const { return angle; }
	inline const double getAngleRadians() const { return angle.getData().value * (M_PI / 180); }

	void update(const unsigned long tick) override;

private:
	RotationAngle angle;
};