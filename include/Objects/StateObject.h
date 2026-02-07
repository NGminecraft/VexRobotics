#pragma once
#include "Objects/StateObjectMacros.h"
#include "Telemetry/TelemetryObjects/Telemetry.h"
class StateObjectBase {

public:
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

	TelemetryBase** getTelemetryPointers() override const { return telemetryObjects; }
protected:
	TelemetryBase* telemetryObjects[COUNT];

	T& object;

	void setTelemetryInterval(int idx, unsigned int interval) {
		if (telemetryObjects[idx] != nullptr) {
			telemetryObjects[idx]->setUpdateInterval(interval);
		}
	}
};