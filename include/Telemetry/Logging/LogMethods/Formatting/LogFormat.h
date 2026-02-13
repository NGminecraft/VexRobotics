#pragma once
#include "Telemetry/Logging/Logger.h"
#include <sstream>

// Base class for log elements, things that add content to a log message
class LogElement {
public:
	// Add content to the log message by writing to the stringstream
	virtual void addElement(std::stringstream& ss) = 0;

	// By default ignore log level, but some elements may want to change that
	virtual void addElement(std::stringstream& ss, Logger::LogLevel level) {
		addElement(ss);
	}
};