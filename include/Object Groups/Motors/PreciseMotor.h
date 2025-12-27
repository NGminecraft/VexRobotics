// A motor with a rotation sensor for precise control
#include "vex.h"

struct PreciseMotor {
public:
	PreciseMotor(vex::motor& m, vex::rotation& r);
	vex::motor& getMotor();
	vex::rotation& getRotationSensor();
protected:
	vex::motor& motor;
	vex::rotation& rotationSensor;
};