#pragma once
// This class is for combining a motor and its state as stored in telemetry
// The point is to keep measurements consistent between calls and to have a single unified class representing the State of The Motor
#include "vex.h"
#include "../Telemetry/TelemetryObjects/Motors/MotorTelemetryHeaders.h"
#include "Objects/StateObject.h"

// X-Macro list: Single source of truth for all motor telemetry
// Format: X(EnumName, DataType, ClassName)
#define MOTOR_TELEMETRY_LIST(X) \
	X(Current, double, MotorAmperage) \
	X(Temperature, double, MotorTemperature) \
	X(Angle, double, MotorAngle)

class MotorState : public StateObject<vex::motor, 3> {
public:
	MotorState(vex::motor& m);

	// Generate everything: enum, type traits, methods, and switch

	inline vex::motor& getMotor() {
		return motor;
	}

	TELEMETRY_GENERATE_ALL(MOTOR_TELEMETRY_LIST, 3)

private:
	vex::motor& motor;
};