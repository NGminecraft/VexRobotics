#include "Object Groups/Motors/Arm.h"
#include "Data Types/Matrix.h"

Arm::Arm(std::vector<ArmSegment> arm) : segments(arm) {
}

void Arm::AddSegment(ArmSegment segment) {
	segments.push_back(segment);
}

void Arm::VelocityTowardsPosition(const Vector3D<double>& position) {
	// Precompute some of the values and place them in an array
	std::optional<KinematicsState> states[segments.size()];
	for (size_t i = 0; i < segments.size(); i++) {
		states[i] = KinematicsState(segments[i], epsilon);
	}

	// Create the Jacobian matrix
	Matrix<double, 3, 3> R = Matrix<double, 3, 3>::identity(); // Rotation matrix
	Matrix<double, 3, segments.size()> J; // Jacobian matrix
	Vector3D<double> jointPos;
	for (size_t col = 0; col < segments.size(); col++) {

	}
}