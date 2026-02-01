#pragma once
#include "Cycle/Phases/LoopPhase.h"
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include <queue>
#include <vector>
#include <memory>

// Base class for type erasure
struct TelemetryUpdateBase {
	uint updateInterval;
	uint nextUpdate;

	TelemetryUpdateBase(uint interval) : updateInterval(interval), nextUpdate(0) {}
	virtual ~TelemetryUpdateBase() = default;

	virtual void update() = 0;

	bool operator>(const TelemetryUpdateBase& other) const {
		return nextUpdate > other.nextUpdate;
	}
};

// Comparator for priority queue with pointers
struct CompareTelemetryUpdate {
	bool operator()(const TelemetryUpdateBase* a, const TelemetryUpdateBase* b) const {
		return *a > *b;
	}
};

// Forward declaration
template <typename T>
struct TelemetryUpdate;

class TelemetryPhase : public LoopPhase {
public:
	TelemetryPhase();

	template <typename T>
	void registerTelemetryUpdate(TelemetryUpdate<T>& obj);

	void execute(const unsigned long tick);

private:
	std::priority_queue<TelemetryUpdateBase*, std::vector<TelemetryUpdateBase*>, CompareTelemetryUpdate> minHeap;
};

template <typename T>
struct TelemetryUpdate : public TelemetryUpdateBase {
	Telemetry<T>* telemetryObject;

	TelemetryUpdate(Telemetry<T>* obj, uint interval) 
		: TelemetryUpdateBase(interval), telemetryObject(obj) {}

	void update() override {
		if (telemetryObject) {
			telemetryObject->update();
		}
	}
};