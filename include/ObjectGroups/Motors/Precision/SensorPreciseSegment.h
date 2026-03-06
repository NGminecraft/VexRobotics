#include "ObjectGroups/Motors/Precision/PreciseSegment.h"
#include "Objects/RotationState.h"

class SensorPreciseSegment : public PreciseSegment {
public:
	SensorPreciseSegment(MotorState& motor, double length, RotationState& rotation) : PreciseSegment(motor, length), rotation(rotation) {}

	double getAngle() override {
		return rotation.getAngleRadians();
	}

private:
	RotationState& rotation;
};