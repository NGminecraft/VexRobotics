#include "Objects/MotorState.h"

MotorState::MotorState(vex::motor& m) : StateObject<vex::motor, 2>(m)
{}