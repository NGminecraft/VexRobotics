#pragma once
#include "vex.h"
#include "Telemetry/Displaying/ScreenItem.h"
#include "Telemetry/Displaying/Widgets/Containers/BasicContainer.h"
#include "Cycle/Phases/LoopPhase.h"

class DisplayPhase : public LoopPhase {
public:
	DisplayPhase(int interval, vex::brain& brain);

	void execute(const unsigned long tick) override;

	BasicContainer* getScreen() {
		return screen;
	}

	void addToScreen(ScreenItem* item) {
		screen->addChild(item);
	}

	~DisplayPhase() {
		delete screen;
	}

private:
	BasicContainer* screen;
	int interval;
	vex::brain& brain;
};