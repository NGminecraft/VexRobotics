#include "Cycle/Phases/DisplayPhase.h"
#include "Telemetry/Displaying/Widgets/Containers/BasicContainer.h"

DisplayPhase::DisplayPhase(int interval, vex::brain& brain) : LoopPhase(), interval(interval), brain(brain) {
	screen = new BasicContainer(0, 0);
	brain.Screen.render();
}

void DisplayPhase::execute(const unsigned long tick) {
	if (tick % interval == 0) {
		screen->print(brain, 0, 0);
		brain.Screen.render();
	}
}