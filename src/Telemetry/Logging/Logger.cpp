#include "Telemetry/Logging/Logger.h"
#include <iostream>

Logger* Logger::instance = nullptr;

Logger::Logger(const char* Name) : name(Name), defaultLevel(Logger::LogLevel::DEBUG) {}

Logger::Logger(const char* Name, LogLevel defaultLevel) : name(Name), defaultLevel(defaultLevel) {}

Logger& Logger::getInstance(const char* Name) {
	// FIX 3: Use static instance instead of local variable
	if (instance == nullptr) {
		static Logger logInstance(Name);
		instance = &logInstance;
	}
	return *instance;
}

Logger& Logger::getInstance() {
	if (instance == nullptr) {
		// This is a critical error - getInstance(brain, name) must be called first
		// For embedded systems, we can't throw exceptions, so we need to handle this gracefully
		// You should call the two-parameter version first during initialization
		static Logger defaultInstance("DefaultLogger");
		instance = &defaultInstance;
	}
	return *instance;
}

void Logger::log(const char* msg) {
	if (msg != nullptr) {
	}
}