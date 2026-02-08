#pragma once
#include "Telemetry/Displaying/ScreenItem.h"
#include <vector>

class BasicContainer : public ScreenItem {
public:
	BasicContainer(int x, int y) : offsetX(x), offsetY(y) {}

	virtual void print(vex::brain& brain, int x, int y) override {
		for (ScreenItem* child : children) {
			child->print(brain, x + offsetX, y + offsetY);
		}
	}

protected:
	std::vector<ScreenItem*> children;
	int offsetX;
	int offsetY;
};