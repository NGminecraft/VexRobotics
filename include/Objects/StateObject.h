#pragma once
#include "Objects/StateObjectMacros.h"
#include "Telemetry/TelemetryObjects/Telemetry.h"

class StateObjectBase {
public:
	virtual size_t getTelemetryCount() const = 0;
	virtual TelemetryBase** getTelemetryPointers() = 0;
};


// A abstract class representing a stateful object (e.g., motor, sensor)
template <typename T, size_t COUNT>
class StateObject : public StateObjectBase {
public:
	StateObject(T& obj) : object(obj) {}

	void update(const unsigned long tick) {
		for (size_t i = 0; i < COUNT; i++) {
			if (telemetryObjects[i] != nullptr) {
				telemetryObjects[i]->update(tick);
			}
		}
	};

	T& getObject() { return object; }

	size_t getTelemetryCount() const override { return COUNT; }

	TelemetryBase** getTelemetryPointers() override { return telemetryObjects; }

	void setTelemetryIntervals(const unsigned int(&intervals)[COUNT]) {
		for (size_t i = 0; i < COUNT; i++) {
			if (telemetryObjects[i] != nullptr) {
				telemetryObjects[i]->setUpdateInterval(intervals[i]);
			}
		}
	}
protected:
	TelemetryBase* telemetryObjects[COUNT];

	T& object;

	void setTelemetryInterval(int idx, unsigned int interval) {
		if (telemetryObjects[idx] != nullptr) {
			telemetryObjects[idx]->setUpdateInterval(interval);
		}
	}
};
