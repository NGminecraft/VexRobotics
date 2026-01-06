#pragma once
#include "Object Groups/Motors/ArmSegment.h"
#include <vector>

class Arm {
public:
	Arm() = default;

	Arm(std::vector<ArmSegment> arm);

	void AddSegment(ArmSegment segment);

	void VelocityTowardsPosition(const Vector3D<double>& position);

private:
	std::vector<ArmSegment> segments;

	constexpr static double epsilon = 0.1;
};