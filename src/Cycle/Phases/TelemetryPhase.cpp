#include "Cycle/Phases/TelemetryPhase.h"
#

TelemetryPhase::TelemetryPhase() : LoopPhase() {}

void TelemetryPhase::registerTelemetryUpdate(StateObjectBase* base) {
	if (base != nullptr) {
		TelemetryBase** telemetryObjects = base->getTelemetryPointers();
		size_t count = base->getTelemetryCount();
		for (size_t i = 0; i < count; ++i) {
			if (telemetryObjects[i] != nullptr) {
				minHeap.push(telemetryObjects[i]);
			} else {
				Logger::getInstance("Main").log("Warning: Attempted to register null telemetry object from StateObjectBase", Logger::LogLevel::WARNING);
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
	Logger::getInstance("Main").log("Executing TelemetryPhase", Logger::LogLevel::DEBUG);
	unsigned int updatesThisTick = 0;
	while (!minHeap.empty() && minHeap.top()->getNextUpdate() <= tick) {
		TelemetryBase* current = minHeap.top();
		minHeap.pop();
		current->update(tick);
		updatesThisTick++;
		if (current->getUpdateInterval() > 0) {
			minHeap.push(current);
		}
	}
	if (updatesThisTick > 0) {
		char buffer[64];
		sprintf(buffer, "Telemetry updates: %u", updatesThisTick);
		Logger::getInstance("Main").log(buffer, Logger::LogLevel::DEBUG);
	}
}