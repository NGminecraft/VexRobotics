#pragma once
#include "Object Groups/Motors/ArmSegment.h"
#include <vector>

class Arm {
public:
	Arm(ArmSegment& Arms, size_t length);

	void AddSegment(ArmSegment& segment);

private:
	std::vector<ArmSegment&> segments;
};