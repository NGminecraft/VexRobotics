#include "Objects/MotorState.h"

MotorState::MotorState(vex::motor& m) : StateObject<vex::motor, 3>(m), motor(m)
{}