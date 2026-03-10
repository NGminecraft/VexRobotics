#include "ObjectGroups/Motors/Precision/PreciseSegment.h"
#include "Objects/RotationState.h"

class SensorPreciseSegment : public PreciseSegment {
public:
	SensorPreciseSegment(MotorState& motor, double length, Rotation axis, RotationState& rotation) : PreciseSegment(motor, length, axis), rotation(rotation) {}

	double getAngle() override {
		return rotation.getAngleRadians();
	}

private:
	RotationState& rotation;
};