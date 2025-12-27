#include "vex.h"
#include "Telemetry/Telemetry Objects/Telemetry.h"

class RotationAngle : public Telemetry<double> {
public:
	RotationAngle(vex::rotation& sensor);

	void updateData() override;
private:
	vex::rotation& sensorRef;
};