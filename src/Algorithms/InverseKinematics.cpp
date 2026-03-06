#include "Algorithms/InverseKinematics.h"
#include "DataTypes/Rotations.h"
#include <array>
#include <cstddef>
#include <DataTypes/Vectors.h>
#include <ObjectGroups/Motors/ArmSegment.h>

// Performs inverse kinematics on an array of joint segments
template<size_t Joints>
Vector<double, Joints> InverseKinematics(std::array<ArmSegment, Joints>& segments, Matrix<double, 3, 3>& orientation, Vector3D<double>& targetVelocity)
{
	
	std::array<Matrix<double, 3, 3>, Joints> rotationMatrices;
	std::array<Vector3D<double>, Joints + 1> jointPositions;

	rotationMatrices[0] = orientation;
	jointPositions[0] = Vector3D<double>(0, 0, 0);
	// Caching loop
	for (size_t i = 1; i < Joints; i++) {
		// Add this joints rotation to the net rotation matrix
		rotationMatrices[i] = rotationMatrices[i - 1] * segments[i].getRotationAxis();
		// Use the state of the previous joint to estimate where this joint lies
		jointPositions[i] = jointPositions[i - 1] + (rotationMatrices[i - 1] * (segments[i - 1].getRotationAxis().axis() * segments[i - 1].getLength()));
	}

	// Add the last joint position (the end effector)
	jointPositions[Joints] = jointPositions[Joints - 1] + (rotationMatrices[Joints - 1] * (segments[Joints - 1].getRotationAxis().axis() * segments[Joints - 1].getLength()));

	// MATH
	Matrix<double, 3, Joints> Jacobian;
	for (size_t i = 0; i < Joints; i++) {
		// Sets the column in the Jacobian matrix
		Jacobian.setColumn(i,
			segments[i].getRotationAxis() // Get the rotation axis for the joint
			.crossProduct(
				jointPositions[Joints] - jointPositions[i] // Get the vector from the joint to the end effector
			)
		);
	}

	// Pseudo-inverse of the Jacobian
	Matrix<double, Joints, 3> JacobianPseudoInverse = Jacobian.pseudoInverse();

	// Multiply the pseudo-inverse by the target velocity to get the joint velocities
	return JacobianPseudoInverse * targetVelocity;
}
