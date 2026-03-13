#pragma once
#include "DataTypes/Vectors.h"
#include "DataTypes/Rotations.h"
#include "ObjectGroups/Motors/Precision/PreciseSegment.h"
#include <array>
#include <cstddef>
#include <cmath>

template <size_t Joints>
Vector<double, Joints> InverseKinematics(std::array<PreciseSegment*, Joints>& segments, Rotation& baseOrientation, Vector3D<double> targetVelocity) {
	static_assert(Joints > 0, "InverseKinematics requires at least one joint");

	Vector<double, Joints> zeroVelocities;
	for (size_t i = 0; i < Joints; i++) {
		zeroVelocities[i] = 0.0;
	}

	auto finiteVector3 = [](const Vector3D<double>& vec) -> bool {
		return std::isfinite(vec[0]) && std::isfinite(vec[1]) && std::isfinite(vec[2]);
	};

	auto normalizeVector3 = [&](const Vector3D<double>& vec, const Vector3D<double>& fallback) -> Vector3D<double> {
		if (!finiteVector3(vec)) {
			return fallback;
		}
		double mag = vec.magnitude();
		if (!std::isfinite(mag) || mag < 1e-9) {
			return fallback;
		}
		double invMag = 1.0 / mag;
		return Vector3D<double>(vec[0] * invMag, vec[1] * invMag, vec[2] * invMag);
	};

	auto buildLinkDirection = [&](const Vector3D<double>& normalizedAxis) -> Vector3D<double> {
		Vector3D<double> reference = (std::abs(normalizedAxis[2]) < 0.9)
			? Vector3D<double>(0.0, 0.0, 1.0)
			: Vector3D<double>(0.0, 1.0, 0.0);

		Vector3D<double> orthogonal = normalizedAxis.crossProduct(reference);
		return normalizeVector3(orthogonal, Vector3D<double>(1.0, 0.0, 0.0));
	};

	if (!finiteVector3(targetVelocity)) {
		return zeroVelocities;
	}

	const double targetVelocityMagnitudeSquared =
		targetVelocity[0] * targetVelocity[0] +
		targetVelocity[1] * targetVelocity[1] +
		targetVelocity[2] * targetVelocity[2];
	if (targetVelocityMagnitudeSquared < 1e-12) {
		return zeroVelocities;
	}

	for (size_t i = 0; i < Joints; i++) {
		if (segments[i] == nullptr) {
			return zeroVelocities;
		}
	}

	std::array<Matrix<double, 3, 3>, Joints> rotationMatrices;
	std::array<Vector3D<double>, Joints + 1> jointPositions;

	rotationMatrices[0] = static_cast<const Matrix<double, 3, 3>&>(baseOrientation);
	jointPositions[0] = Vector3D<double>(0, 0, 0);

	for (size_t i = 1; i < Joints; i++) {
		rotationMatrices[i] = rotationMatrices[i - 1] * segments[i - 1]->getRotationMatrix();

		Vector3D<double> segmentAxis = normalizeVector3(segments[i - 1]->getRotationAxis(), Vector3D<double>(0.0, 0.0, 1.0));
		Vector3D<double> segmentDirection = buildLinkDirection(segmentAxis);
		Vector3D<double> segmentOffset = rotationMatrices[i - 1] * (segmentDirection * segments[i - 1]->getEndPosition());
		if (!finiteVector3(segmentOffset)) {
			return zeroVelocities;
		}

		Vector3D<double> nextPosition;
		for (size_t axis = 0; axis < 3; axis++) {
			nextPosition[axis] = jointPositions[i - 1][axis] + segmentOffset[axis];
		}
		jointPositions[i] = nextPosition;
	}

	Vector3D<double> endAxis = normalizeVector3(segments[Joints - 1]->getRotationAxis(), Vector3D<double>(0.0, 0.0, 1.0));
	Vector3D<double> endDirection = buildLinkDirection(endAxis);
	Vector3D<double> endOffset = rotationMatrices[Joints - 1] * (endDirection * segments[Joints - 1]->getEndPosition());
	if (!finiteVector3(endOffset)) {
		return zeroVelocities;
	}

	Vector3D<double> endEffectorPosition;
	for (size_t axis = 0; axis < 3; axis++) {
		endEffectorPosition[axis] = jointPositions[Joints - 1][axis] + endOffset[axis];
	}
	jointPositions[Joints] = endEffectorPosition;

	Matrix<double, 3, Joints> Jacobian;
	for (size_t i = 0; i < Joints; i++) {
		Vector3D<double> worldAxis = normalizeVector3(rotationMatrices[i] * segments[i]->getRotationAxis(), Vector3D<double>(0.0, 0.0, 1.0));
		if (!finiteVector3(worldAxis)) {
			return zeroVelocities;
		}

		Vector3D<double> leverArm;
		for (size_t axis = 0; axis < 3; axis++) {
			leverArm[axis] = jointPositions[Joints][axis] - jointPositions[i][axis];
		}
		if (!finiteVector3(leverArm)) {
			return zeroVelocities;
		}

		Jacobian.setColumn(i, worldAxis.crossProduct(leverArm));
	}

	for (size_t row = 0; row < 3; row++) {
		for (size_t col = 0; col < Joints; col++) {
			if (!std::isfinite(Jacobian(row, col))) {
				return zeroVelocities;
			}
		}
	}

	// Replace pseudo-inverse solve with damped least-squares:
	// qdot = J^T * (J*J^T + lambda^2 I)^-1 * v
	const double lambda = 0.08;
	const double lambda2 = lambda * lambda;

	double A[3][3] = {};
	for (size_t r = 0; r < 3; r++) {
		for (size_t c = 0; c < 3; c++) {
			double sum = 0.0;
			for (size_t k = 0; k < Joints; k++) {
				sum += Jacobian(r, k) * Jacobian(c, k);
			}
			A[r][c] = sum + ((r == c) ? lambda2 : 0.0);
		}
	}

	// Inverse of 3x3 A
	const double a00 = A[0][0], a01 = A[0][1], a02 = A[0][2];
	const double a10 = A[1][0], a11 = A[1][1], a12 = A[1][2];
	const double a20 = A[2][0], a21 = A[2][1], a22 = A[2][2];

	const double c00 = (a11 * a22 - a12 * a21);
	const double c01 = (a02 * a21 - a01 * a22);
	const double c02 = (a01 * a12 - a02 * a11);

	const double c10 = (a12 * a20 - a10 * a22);
	const double c11 = (a00 * a22 - a02 * a20);
	const double c12 = (a02 * a10 - a00 * a12);

	const double c20 = (a10 * a21 - a11 * a20);
	const double c21 = (a01 * a20 - a00 * a21);
	const double c22 = (a00 * a11 - a01 * a10);

	const double det = a00 * c00 + a01 * c10 + a02 * c20;
	if (!std::isfinite(det) || std::abs(det) < 1e-12) {
		return zeroVelocities;
	}

	const double invDet = 1.0 / det;
	double invA[3][3] = {
		{ c00 * invDet, c01 * invDet, c02 * invDet },
		{ c10 * invDet, c11 * invDet, c12 * invDet },
		{ c20 * invDet, c21 * invDet, c22 * invDet }
	};

	double y[3] = { 0.0, 0.0, 0.0 }; // y = invA * targetVelocity
	for (size_t r = 0; r < 3; r++) {
		for (size_t c = 0; c < 3; c++) {
			y[r] += invA[r][c] * targetVelocity[c];
		}
		if (!std::isfinite(y[r])) {
			return zeroVelocities;
		}
	}

	Vector<double, Joints> jointVelocities;
	for (size_t i = 0; i < Joints; i++) {
		double sum = 0.0;
		for (size_t c = 0; c < 3; c++) {
			sum += Jacobian(c, i) * y[c]; // J^T * y
		}
		jointVelocities[i] = std::isfinite(sum) ? sum : 0.0;
	}

	return jointVelocities;
}