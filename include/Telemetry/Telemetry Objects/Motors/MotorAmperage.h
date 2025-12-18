#include "Telemetry/Telemetry Objects/Telemetry.h"
#include "vex.h"

class MotorAmperage : public Telemetry {
public:
	MotorAmperage(vex::motor& motor);

	double getData();
private:
	vex::motor& motorRef;
};