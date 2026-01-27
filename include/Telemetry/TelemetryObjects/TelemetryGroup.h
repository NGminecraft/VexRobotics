#pragma once
#include <vector>
#include "Telemetry/TelemetryObjects/Telemetry.h"

class TelemetryGroup {
public:
	TelemetryGroup();

	void addTelemetryObject(Telemetry* telemetry);

	double totalValue();

	double averageValue();

	double minValue();

	double maxValue();

private:
	std::vector<Telemetry*> telemetryObjects;
};