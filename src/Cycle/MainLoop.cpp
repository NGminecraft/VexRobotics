#include "Cycle/MainLoop.h"
#include "Telemetry/Logging/Logger.h"
#include "vex.h"

MainLoop::MainLoop() : tick(0), running(true) {}

void MainLoop::loop() {
	auto& logger = Logger::getInstance("Main");
	logger.log("Starting main loop", Logger::LogLevel::INFO);
	while (running) {
		std::stringstream msg;
		msg << "Main loop tick: " << tick;
		logger.log(msg.str(), Logger::LogLevel::DEBUG);
		
		// Execute each registered phase
		for (size_t i = 0; i < phases.size(); ++i) {
			auto& phase = phases[i];
			phase->execute(tick);
		}

		msg.str("");
		msg << "Completed " << phases.size() << " phases";
		logger.log(msg.str(), Logger::LogLevel::DEBUG); 

		// Increment tick counter
		tick++;
		// Give async tasks time to run
		vex::this_thread::sleep_for(10);
	}
}

MainLoop::~MainLoop() {
	phases.clear();
}