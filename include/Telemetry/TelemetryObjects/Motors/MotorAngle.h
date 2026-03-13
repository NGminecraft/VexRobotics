#pragma once
#include "Telemetry/TelemetryObjects/Telemetry.h"
#include "vex.h"

class MotorAngle : public Telemetry<double> {
public:
    MotorAngle(vex::motor& motor);

    double newData() override;
private:
    vex::motor& motorRef;
};