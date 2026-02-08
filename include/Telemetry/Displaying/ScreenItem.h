#pragma once
#include "vex.h"

// Base class for items that can be printed on the screen
class ScreenItem {
public:
	virtual void print(vex::brain& brain, int x, int y) = 0;
};