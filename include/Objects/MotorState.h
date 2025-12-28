#pragma once
// This class is for combining a motor and its state as stored in telemetry
// The point is to keep measurements consistent between calls and to have a single unified class representing the State of The Motor
#include "vex.h"
#include "Telemetry/Telemetry Objects/Motors/MotorTelemetryHeaders.h"
#include "Objects/StateObject.h"

class MotorState : public StateObject<vex::motor> {
public:

	MotorState(vex::motor& m);

	inline const MotorAmperage& getCurrent() const { return current; }
	inline const MotorTemperature& getTemperature() const { return temperature; }

	void update(unsigned long tick) {
		current.update(tick);
		temperature.update(tick);
	}

protected:
	MotorAmperage current;
	MotorTemperature temperature;
};