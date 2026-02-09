#pragma once
#include "Telemetry/Displaying/ScreenItem.h"

class ConstantString : public ScreenItem {
public:
	ConstantString(const char* str) : str(str) {}

	void print(vex::brain& brain, int x, int y) {
		brain.Screen.printAt(x, y, str);
	}

private:
	const char* str;
};