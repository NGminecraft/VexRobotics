#include "Telemetry/Logging/Logger.h"
#include <iostream>

Logger* Logger::instance = nullptr;

Logger::Logger(vex::brain& brain, const char* Name) : brainRef(brain), name(Name) {

}

Logger& Logger::getInstance(vex::brain& brain, const char* Name) {
	Logger logInstance(brain, Name);
	instance = &logInstance;
	return *instance;
}

Logger& Logger::getInstance() {
	return *instance;
}

void Logger::log(const char* msg) {
	brainRef.Screen.print(msg);
}