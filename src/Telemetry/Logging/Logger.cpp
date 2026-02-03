#include "Telemetry/Logging/Logger.h"
#include <iostream>

Logger* Logger::instance = nullptr;

Logger::Logger(vex::brain& brain, const char* Name) : brainRef(brain), name(Name) {

}

Logger& Logger::getInstance(vex::brain& brain, const char* Name) {
	// FIX 3: Use static instance instead of local variable
	if (instance == nullptr) {
		static Logger logInstance(brain, Name);
		instance = &logInstance;
	}
	return *instance;
}

Logger& Logger::getInstance() {
	// FIX 4: Add null check to prevent dereferencing null pointer
	if (instance == nullptr) {
		// This is a critical error - getInstance(brain, name) must be called first
		// For embedded systems, we can't throw exceptions, so we need to handle this gracefully
		// You should call the two-parameter version first during initialization
		vex::brain dummyBrain;
		static Logger defaultInstance(dummyBrain, "DefaultLogger");
		instance = &defaultInstance;
	}
	return *instance;
}

void Logger::log(const char* msg) {
	// FIX 5: Add null check before logging
	if (msg != nullptr) {
		brainRef.Screen.print(msg);
		brainRef.Screen.newLine();
	}
}

void Logger::clear() {
	brainRef.Screen.clearScreen();
}