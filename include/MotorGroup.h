#include "vex.h"

template<int N>
class MotorGroup {

    private:
        vex::motor motors[N];
        vex::motor_group motorGroup;

    public:
        MotorGroup(const vex::motor (&motorArray)[N]): motorGroup() {
            for (int i = 0; i < N; i++) {
                motors[i] = motorArray[i];
                motorGroup.addMotor(motors[i]);
            }
        };

        void setVelocity(double velocity) {
            motorGroup.setVelocity(veloctiy, vex::velocityUnits::pct);
        }

        void spin(vex::directionType direction) {
            motorGroup.spin(direction);
        }
};