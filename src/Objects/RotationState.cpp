#include "Objects/RotationState.h"

RotationState::RotationState(vex::rotation& r) : StateObject<vex::rotation>(r), angle(r) {}

void RotationState::update(unsigned long tick) {
	angle.update(tick);
}