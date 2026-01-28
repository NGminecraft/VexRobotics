#include "Objects/DrivetrainState.h"

DrivetrainState::DrivetrainState(vex::drivetrain& dt) : StateObject<vex::drivetrain>(dt), velocity(dt) {}

void DrivetrainState::update(unsigned long tick) {
	velocity.update(tick);
}