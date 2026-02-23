#pragma once
#include <sstream>

// Forward declaration to avoid circular includes
class Logger;

// Base class for log elements, things that add content to a log message
class LogElement {
public:
	// Add content to the log message by writing to the stringstream
	virtual void addElement(std::stringstream& ss) = 0;

	// By default ignore log level, but some elements may want to change that
	// Note: Logger::LogLevel is defined in Logger.h
	virtual void addElement(std::stringstream& ss, int level) {
		addElement(ss);
	}
};

enum class LogElementSeperators {
	NONE,
	SPACE,
	BRACKET,
	BRACE
};

std::string seperateElement(LogElementSeperators sep, const std::string text);