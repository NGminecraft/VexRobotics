#include "Telemetry/Telemetry Objects/Telemetry.h"
#include "vex.h"

class MotorTemperature : public Telemetry<double> {
public:
	MotorTemperature(vex::motor& motor);

	void updateData() override;
private:
	vex::motor& motorRef;
};