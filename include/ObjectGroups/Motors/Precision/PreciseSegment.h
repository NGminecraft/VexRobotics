#pragma once
#include "DataTypes/Rotations.h"
#include "Objects/MotorState.h"


class PreciseSegment {
public:
	PreciseSegment(MotorState& motor, double length) : motor(motor), length(length) {};

	virtual double getAngle() = 0;

	const Matrix<double, 3, 3>& getRotationMatrix() const {
		return rotationAxis;
	}

	const Vector3D<double>& getRotationAxis() const {
		return rotationAxis.axis();
	}

	void setLength(double length) {
		length = length;
	}

	const double getLength(double length) {
		return length;
	}

	const double getEndPosition() {
		return length * getAngle();
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