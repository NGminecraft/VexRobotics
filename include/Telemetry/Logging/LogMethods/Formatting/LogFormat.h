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

enum class LogElementSeperators {
	NONE,
	SPACE,
	BRACKET,
	BRACE
};

std::string seperateElement(LogElementSeperators sep, std::string text) {
	switch (sep) {
	case LogElementSeperators::SPACE:
		return " " + std::string(text) + " ";
	case LogElementSeperators::BRACKET:
		return "[" + std::string(text) + "] ";
	case LogElementSeperators::BRACE:
		return "{" + std::string(text) + "} ";
	default:
		return std::string(text);
	}
}