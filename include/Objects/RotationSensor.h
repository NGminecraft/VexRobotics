#pragma once
#include "Telemetry/Telemetry Objects/Rotation Sensors/RotationTelemetryHeaders.h"
#include "Objects/StateObject.h"

class RotationSensorState : StateObject<vex::rotation> {
public:
	RotationSensorState(vex::rotation& r);

	inline const RotationAngle& getAngle() const { return angle; }

	void update(unsigned long tick) override;

private:
	RotationAngle angle;
};