#include "ObjectGroups/Motors/Arm.h"
#include "DataTypes/Matrix.h"
#include "Algorithms/InverseKinematics.h"

Arm::Arm(std::vector<ArmSegment> arm) : segments(arm) {
}

void Arm::AddSegment(ArmSegment segment) {
	segments.push_back(segment);
}

void Arm::VelocityTowardsPosition(const Vector3D<double>& position) {
	// Precompute some of the values and place them in an array
	
}