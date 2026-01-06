#pragma once
#include "Object Groups/Motors/PreciseMotor.h"
#include "Objects/MotorState.h"
#include "Objects/RotationState.h"
#include "Data Types/Vectors.h"
#include <cmath>

class ArmSegment {
public:
	ArmSegment(MotorState& m, RotationState& r, double len);
	ArmSegment(const PreciseMotor& motor, double len);

	PreciseMotor getPreciseMotor() { return motor; }
	const PreciseMotor getPreciseMotor() const { return motor; }


	const Vector2D<double> getEndPosition();

	double dx() { return getEndPosition()[0]; };
	double dy() { return getEndPosition()[1]; };

protected:
	PreciseMotor motor;
	double length; // Length of the arm segment in inches

	double cachedAngleRad = -5;
	Vector2D<double> cachedEndPos = Vector2D<double>( 0.0, 0.0 );
};

struct KinematicsState {
	ArmSegment& segment;
	double angle;
	double endX; // X 
	double endY; // Y of segment end
	double sin; // Sin(theta)
	double cos; // Cos(theta)
	double e; // epsilon
	double eSin; // Sin(theta + epsilon)
	double eCos;// Cos(theta + epsilon)

	KinematicsState(ArmSegment& seg, double epsilon)
		: segment(seg) {
		angle = seg.getPreciseMotor().getRotationState().getAngleRadians();

		Vector2D<double> endPos = segment.getEndPosition();
		endX = endPos[0];
		endY = endPos[1];
		e = epsilon;
		sin = std::sin(angle);
		cos = std::cos(angle);
		eSin = std::sin(angle + e);
		eCos = std::cos(angle + e);
	}
};