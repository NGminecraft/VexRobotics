#include "motor_manager.h"

void MotorManager::registerMotor(vex::motor& motor) {
    motors.push_back(motor);
}

vex::motor MotorManager::createMotor(const int32_t port, const bool reverse) {
    vex::motor newMotor(port);

    if (reverse) {
        newMotor.setReversed(true);
    }
    registerMotor(newMotor);

    return newMotor;
}