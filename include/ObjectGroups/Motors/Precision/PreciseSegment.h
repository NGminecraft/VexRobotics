#pragma once
#include "DataTypes/Rotations.h"
#include "Objects/MotorState.h"
#include "DataTypes/Vectors.h"
#include "DataTypes/Matrix.h"
#include <cmath>

class PreciseSegment {
public:
	PreciseSegment(MotorState& motor, double length, Rotation axis) : motor(motor), rotationAxis(axis), length(length) {};

	virtual double getAngle() = 0;

	virtual void calibrate() {};

	Matrix<double, 3, 3> getRotationMatrix() {
		Matrix<double, 3, 3> mountRotation = static_cast<const Matrix<double, 3, 3>&>(rotationAxis);
		Vector3D<double> axis = rotationAxis.axis();
		double axisMagnitude = axis.magnitude();
		if (!std::isfinite(axisMagnitude) || axisMagnitude < 1e-9) {
			return mountRotation;
		}

		Vector3D<double> unitAxis = axis * (1.0 / axisMagnitude);
		Rotation dynamicRotation = Rotation::aboutAxis(unitAxis, getAngle());
		return mountRotation * static_cast<const Matrix<double, 3, 3>&>(dynamicRotation);
	}

	const Vector3D<double>& getRotationAxis() const {
		return rotationAxis.axis();
	}

	void setLength(double length) {
		this->length = length;
	}

	const double getLength() const {
		return length;
	}

	const double getEndPosition() const {
		return length;
	}

	MotorState& getMotorState() {
		return motor;
	}

protected:
	MotorState& motor;

private:
	Rotation rotationAxis;

	double length;
};