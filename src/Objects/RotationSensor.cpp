#include "Objects/RotationSensor.h"

RotationSensorState::RotationSensorState(vex::rotation& r) : StateObject<vex::rotation>(r), angle(r) {}