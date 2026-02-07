#include "Cycle/Phases/TelemetryPhase.h"

TelemetryPhase::TelemetryPhase() : LoopPhase() {}

void TelemetryPhase::registerTelemetryUpdate(TelemetryBase** objects, unsigned int count) {
	for (unsigned int i = 0; i < count; ++i) {
		if (objects[i] != nullptr) {
			minHeap.push(objects[i]);
		}
	}
}

void TelemetryPhase::registerTelemetryUpdate(TelemetryBase* object) {
	minHeap.push(object);
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