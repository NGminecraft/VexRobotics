#include "Telemetry/Telemetry Objects/Telemetry.h"
#include "vex.h"

class MotorTemperature : public Telemetry<double> {
public:
	MotorTemperature(vex::motor& motor);

	double newData() override;
private:
	vex::motor& motorRef;
};