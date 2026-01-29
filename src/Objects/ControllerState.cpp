#include "Objects/ControllerState.h"


ControllerState::ControllerState(controller& c) : StateObject<controller>(c) {}

void ControllerState::update(const unsigned long tick) {}