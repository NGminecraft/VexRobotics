#pragma once
#include "Cycle/Phases/LoopPhase.h"
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "Objects/StateObject.h"
#include <vector>
#include <memory>
#include <queue>

struct CompareTelemetryUpdate {
	bool operator()(const TelemetryBase* a, const TelemetryBase* b) const {
		return a->getNextUpdate() > b->getNextUpdate();
	}
};
class TelemetryPhase : public LoopPhase {
public:
	TelemetryPhase();

	void registerTelemetryUpdate(StateObject*)
	void registerTelemetryUpdate(TelemetryBase** objects, unsigned int count);
	void registerTelemetryUpdate(TelemetryBase* object);

	void execute(const unsigned long tick);

private:
	std::priority_queue<TelemetryBase*, std::vector<TelemetryBase*>, CompareTelemetryUpdate> minHeap;
};