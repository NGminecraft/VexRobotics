#include <vector>
#include "Telemetry/Telemetry Objects/Telemetry.h"

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