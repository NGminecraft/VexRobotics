#include "Algorithms/InverseKinematics.h"
#include "Data Types/Matrix.h"
#include "Data Types/Rotations.h"
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
	
	std::array<Rotation*, Joints> rotationMatrices;
	std::array<Vector3D<double>*, Joints + 1> jointPositions;

	// Caching loop
	for (size_t i = 0; i < Joints; i++) {
		auto matrix = orientation * segments[i]
	}
}
