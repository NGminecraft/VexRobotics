#pragma once
#include "vex.h"
#include "Telemetry/Displaying/ScreenItem.h"
#include "Cycle/Phases/LoopPhase.h"

class DisplayPhase : public LoopPhase {
public:
	DisplayPhase(int interval, vex::brain& brain);

	void execute(const unsigned long tick) override;

	~DisplayPhase() {
		delete screen;
	}
private:
	ScreenItem* screen;
	int interval;
	vex::brain& brain;
};