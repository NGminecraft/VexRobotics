#pragma once
#include <vector>
#include "Cycle/Phases/LoopPhase.h"
#include "Telemetry/Logging/Logger.h"

class MainLoop {
public:
	MainLoop();

	~MainLoop();

	inline void registerPhase(LoopPhase* phase) {
		Logger::getInstance("Main").log("Registering new phase", Logger::LogLevel::DEBUG);
		phases.push_back(phase);
	}

	void loop();

private:
	unsigned long tick = 0;
	std::vector<LoopPhase*> phases;

	bool running = true;
};