#pragma once
#include "Telemetry/Displaying/Widgets/Containers/BasicContainer.h"
#include <Telemetry/Displaying/ScreenItem.h>

class RectangleContainer : public BasicContainer {
public:
	RectangleContainer(int x, int y, int width, int height) : BasicContainer(x, y), width(width), height(height) {}
	void print(vex::brain& brain, int x, int y) override {
		// Draw the rectangle border
		brain.Screen.drawRectangle(x + offsetX, y + offsetY, x + offsetX + width, y + offsetY + height);
		// Print children inside the rectangle
		for (ScreenItem* child : children) {
			child->print(brain, x + offsetX, y + offsetY);
		}
	}
protected:
	int width;
	int height;
}