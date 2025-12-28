#include "Object Groups/Motors/PreciseMotor.h"

class ArmSegment {
public:
	ArmSegment(vex::motor& m, vex::rotation& r, double len);
	ArmSegment(const PreciseMotor& motor, double len);

	
protected:
	PreciseMotor motor;
	double length; // Length of the arm segment in inches
};