#include "Telemetry/Telemetry Objects/Telemetry.h"
#include "vex.h"

class MotorAmperage : public Telemetry<double> {
public:
	MotorAmperage(vex::motor& motor);

	void updateData() override;
private:
	vex::motor& motorRef;
};