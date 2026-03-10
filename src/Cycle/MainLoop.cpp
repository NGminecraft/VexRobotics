#include "Cycle/MainLoop.h"
#include "Telemetry/Logging/Logger.h"
#include "vex.h"

MainLoop::MainLoop() : tick(0), running(true) {}

void MainLoop::loop() {
	auto& logger = Logger::getInstance("Main");
	logger.log("Starting main loop", Logger::LogLevel::INFO);
	while (running) {
		char buffer[64];
		sprintf(buffer, "Tick: %lu", tick);
		logger.log(buffer, Logger::LogLevel::DEBUG);
		
		// Execute each registered phase
		for (size_t i = 0; i < phases.size(); ++i) {
			char phaseBuffer[64];
			sprintf(phaseBuffer, "Phase %u begin", static_cast<unsigned int>(i));
			logger.log(phaseBuffer, Logger::LogLevel::DEBUG);
			auto& phase = phases[i];
			phase->execute(tick);
			sprintf(phaseBuffer, "Phase %u end", static_cast<unsigned int>(i));
			logger.log(phaseBuffer, Logger::LogLevel::DEBUG);
		}

		// Increment tick counter
		tick++;
		// Give async tasks time to run
		vex::this_thread::sleep_for(10);
	}
}

MainLoop::~MainLoop() {
	phases.clear();
}