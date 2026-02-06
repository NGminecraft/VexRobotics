#pragma once
#include "Objects/StateObjectMacros.h"
// A abstract class representing a stateful object (e.g., motor, sensor)
template <typename T, size_t COUNT>
class StateObject {
public:
	StateObject(T& obj) : object(obj) {}

	virtual void update(const unsigned long tick) {
		for (size_t i = 0; i < COUNT; i++) {
			if (telemetryObjects[i] != nullptr) {
				telemetryObjects[i]->update(tick);
			}
		}
	};

	T& getObject() { return object; }

protected:
	TelemetryBase* telemetryObjects[COUNT];

	T& object;

	void updateTelemetryObjects(TelemetryObjects);

	void setTelemetryInterval(int idx, unsigned int interval) {
		if (telemetryObjects[idx] != nullptr) {
			telemetryObjects[idx]->setUpdateInterval(interval);
		}
	}
};