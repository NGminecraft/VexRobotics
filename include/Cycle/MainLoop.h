#pragma once
#include <vector>
#include "Cycle/Phases/LoopPhase.h"

class MainLoop {
public:
	MainLoop() = default;

	inline void registerPhase(LoopPhase phase) {
		phases.push_back(phase);
	}

	void loop();

private:
	unsigned long tick = 0;
	std::vector<LoopPhase> phases;

	bool running = true;
};