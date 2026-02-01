#include "Cycle/Phases/TelemetryPhase.h"

TelemetryPhase::TelemetryPhase() : LoopPhase() {}

template <typename T>
void TelemetryPhase::registerTelemetryUpdate(TelemetryUpdate<T>& obj) {
	minHeap.push(&obj);
}

void TelemetryPhase::execute(const unsigned long tick) {

}