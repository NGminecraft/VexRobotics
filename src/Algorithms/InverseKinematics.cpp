#include "Algorithms/InverseKinematics.h"
#include "Data Types/Rotations.h"
#include <array>
#include <cstddef>
#include <Data Types/Vectors.h>
#include <Object Groups/Motors/ArmSegment.h>

// Performs inverse kinematics on an array of joint segments
template<size_t Joints>
Vector<double, Joints> InverseKinematics(std::array<ArmSegment, Joints>& segments, Matrix<double, 3, 3>& orientation)
{
	// THINGS I NEED TO CACHE:
	// [ ] Rotation matrices for each joint
	// [ ] Joint locations
	
	std::array<Matrix<double, 3, 3> *, Joints> rotationMatrices;
	std::array<Vector3D<double>*, Joints + 1> jointPositions;

	rotationMatrices[0] = &orientation;
	jointPositions[0] = new Vector3D<double>(0, 0, 0);
	// Caching loop
	for (size_t i = 1; i < Joints; i++) {
		rotationMatrices[i] = rotationMatrices[i-1] * segments[i].getRotationAxis();
		jointPositions[i] = rotationMatrices[i] * (segments[i].getRotationAxis().axis() * segments[i].getLength());
	}

	// MATH

	// Cleanup
	for (size_t i = 1; i < Joints; i++) {
		delete rotationMatrices[i];
		delete jointPositions[i];
	}
}
