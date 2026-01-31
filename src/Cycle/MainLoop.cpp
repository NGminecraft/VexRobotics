#include "Cycle/MainLoop.h"
#include "vex.h"

MainLoop::MainLoop() : tick(0), running(true) {}

void MainLoop::loop() {
	while (running) {
		// Execute each registered phase
		for (auto& phase : phases) {
			phase->execute(tick);
		}

		// Increment tick counter
		tick++;
		// Give async tasks time to run
		vex::this_thread::sleep_for(10);
	}
}

MainLoop::~MainLoop() {
	// Cleanup
	for (auto phase : phases) {
		delete phase;
	}
}