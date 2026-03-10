#pragma once
#include "DataTypes/Vectors.h"
#include "DataTypes/Rotations.h"
#include "ObjectGroups/Motors/Precision/PreciseSegment.h"
#include <array>
#include <cstddef>

template <size_t Joints>
Vector<double, Joints> InverseKinematics(std::array<PreciseSegment*, Joints>& segments, Rotation& baseOrientation, Vector3D<double> targetVelocity) {
	std::array<Matrix<double, 3, 3>, Joints> rotationMatrices;
	std::array<Vector3D<double>, Joints + 1> jointPositions;

	rotationMatrices[0] = static_cast<const Matrix<double, 3, 3>&>(baseOrientation);
	jointPositions[0] = Vector3D<double>(0, 0, 0);

	for (size_t i = 1; i < Joints; i++) {
		rotationMatrices[i] = rotationMatrices[i - 1] * segments[i - 1]->getRotationMatrix();

		Vector3D<double> segmentAxis = segments[i - 1]->getRotationAxis();
		Vector3D<double> segmentOffset = rotationMatrices[i - 1] * (segmentAxis * segments[i - 1]->getEndPosition());

		Vector3D<double> nextPosition;
		for (size_t axis = 0; axis < 3; axis++) {
			nextPosition[axis] = jointPositions[i - 1][axis] + segmentOffset[axis];
		}
		jointPositions[i] = nextPosition;
	}

	Vector3D<double> endAxis = segments[Joints - 1]->getRotationAxis();
	Vector3D<double> endOffset = rotationMatrices[Joints - 1] * (endAxis * segments[Joints - 1]->getEndPosition());

	Vector3D<double> endEffectorPosition;
	for (size_t axis = 0; axis < 3; axis++) {
		endEffectorPosition[axis] = jointPositions[Joints - 1][axis] + endOffset[axis];
	}
	jointPositions[Joints] = endEffectorPosition;

	Matrix<double, 3, Joints> Jacobian;
	for (size_t i = 0; i < Joints; i++) {
		Vector3D<double> worldAxis = rotationMatrices[i] * segments[i]->getRotationAxis();

		Vector3D<double> leverArm;
		for (size_t axis = 0; axis < 3; axis++) {
			leverArm[axis] = jointPositions[Joints][axis] - jointPositions[i][axis];
		}

		Jacobian.setColumn(i, worldAxis.crossProduct(leverArm));
	}

	Matrix<double, Joints, 3> JacobianPseudoInverse = Jacobian.pseudoInverse();

	Vector<double, Joints> jointVelocities;
	for (size_t row = 0; row < Joints; row++) {
		double sum = 0.0;
		for (size_t col = 0; col < 3; col++) {
			sum += JacobianPseudoInverse(row, col) * targetVelocity[col];
		}
		jointVelocities[row] = sum;
	}

	return jointVelocities;
}