#include "Cycle/Phases/TelemetryPhase.h"

TelemetryPhase::TelemetryPhase() : LoopPhase() {}

void TelemetryPhase::registerTelemetryUpdate(StateObjectBase* base) {
	if (base != nullptr) {
		TelemetryBase** telemetryObjects = base->getTelemetryPointers();
		size_t count = base->getTelemetryCount();
		for (size_t i = 0; i < count; ++i) {
			if (telemetryObjects[i] != nullptr) {
				minHeap.push(telemetryObjects[i]);
			}
		}
	}
}

void TelemetryPhase::registerTelemetryUpdate(TelemetryBase** objects, unsigned int count) {
	for (unsigned int i = 0; i < count; ++i) {
		if (objects[i] != nullptr) {
			minHeap.push(objects[i]);
		}
	}
}

void TelemetryPhase::registerTelemetryUpdate(TelemetryBase* object) {
	if (object != nullptr) {
		minHeap.push(object);
	}
}

void TelemetryPhase::execute(const unsigned long tick) {
	while (minHeap.top()->getNextUpdate() <= tick) {
		TelemetryBase* current = minHeap.top();
		minHeap.pop();
		current->update(tick);
		if (current->getUpdateInterval() > 0) {
			minHeap.push(current);
		}
	}
}