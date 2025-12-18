#include "Telemetry/Telemetry Objects/TelemetryGroup.h"

TelemetryGroup::TelemetryGroup() {
}

TelemetryGroup::addTelemetryObject(Telemetry* telemetry) {
	telemetryObjects.push_back(telemetry);
}

TelemetryGroup::totalValue() {
	double total = 0.0;
	for (auto telemetry : telemetryObjects) {
		total += telemetry->getData();
	}
	return total;
}

TelemetryGroup::averageValue() {
	if (telemetryObjects.empty()) {
		return 0.0;
	}
	else {
		return totalValue() / telemetryObjects.size();
	}
}

TelemetryGroup::maxValue() {
	double max = -INFINITY;
	for (auto telemetry : telemetryObjects) {
		double val = telemetry->getData();
		if (val > max) {
			max = val;
		}
	}
	return max;
}