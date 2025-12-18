#include "Telemetry/Telemetry Objects/Telemetry.h"
#include "vex.h"

class MotorTemperature : public Telemetry {
public:
	MotorTemperature(vex::motor& motor);

	double getData() override;
private:
	vex::motor& motorRef;
};